#ifndef BRIDGE_APP_H
#define BRIDGE_APP_H

#include "bridge/daemon.h"
#include "bridge/i2c.h"
#include "bridge/std_lib.h"

namespace jarvis::bridge
{
  class app
  {
  public:
    app();
    ~app();

    void update();

  private:
    spdlog::logger build_logger();

    void systemd_check_watchdog_enabled();

    void systemd_notify_ready() const;
    void systemd_notify_watchdog_keepalive() const;
    void systemd_notify_watchdog_trigger() const;
    void systemd_notify_stopping() const;

    spdlog::logger logger;

    std::uint64_t watchdog_interval_us;
    std::chrono::system_clock::time_point watchdog_last_keepalive;
  };
} // namespace jarvis::bridge

#endif