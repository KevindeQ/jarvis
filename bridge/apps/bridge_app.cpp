#include "bridge_app.h"

namespace jarvis::bridge
{
  app::app() :
    logger{ build_logger() }, watchdog_interval_us{ 0 }, watchdog_last_keepalive{}
  {
    systemd_check_watchdog_enabled();
    systemd_notify_ready();

    // Initial kick of the watchdog
    systemd_notify_watchdog_keepalive();
  }

  app::~app() { systemd_notify_stopping(); }

  void app::update()
  {
    try
    {
      systemd_notify_watchdog_keepalive();
    }
    catch (const std::exception& e)
    {
      // Send a signal to the watchdog that an unexpected error has occured so it can take
      // appropriate actions
      systemd_notify_watchdog_trigger();
    }
  }

  spdlog::logger app::build_logger()
  {
    auto file_sink =
      std::make_shared<spdlog::sinks::daily_file_sink_mt>("logs/runtime.log", 3, 0, true);
#if defined(_DEBUG)
    file_sink->set_level(spdlog::level::debug);
#else
    file_sink->set_level(spdlog::level::info);
#endif

    return spdlog::logger{ "runtime_logger", { file_sink } };
  }

  void app::systemd_check_watchdog_enabled()
  {
    std::uint64_t interval = 0;
    int status = sd_watchdog_enabled(0, &interval);
    if (status < 0)
    {
      throw std::runtime_error{ "Could not acquire watchdog status" };
    }
    else if (status > 0)
    {
      // Activate the watchdog every half expected watchdog period
      watchdog_interval_us = interval / 2;
    }
    else
    {
      watchdog_interval_us = 0;
    }
  }

  void app::systemd_notify_ready() const { sd_notify(0, "READY=1\n"); }

  void app::systemd_notify_watchdog_keepalive() const
  {
    std::chrono::system_clock::time_point now = std::chrono::system_clock::now();
    if (now > watchdog_last_keepalive + std::chrono::microseconds(watchdog_interval_us))
    {
      sd_notify(0, "WATCHDOG=1\n");
    }
  }

  void app::systemd_notify_watchdog_trigger() const
  {
    sd_notify(0, "WATCHDOG=trigger\n");
  }

  void app::systemd_notify_stopping() const { sd_notify(0, "STOPPING=1\n"); }
} // namespace jarvis::bridge