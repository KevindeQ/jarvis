#ifndef DAEMON_H
#define DAEMON_H

#include "bridge/singleton.h"

#include <signal.h>

#include <functional>
#include <type_traits>

namespace jarvis::bridge
{
  class daemon : public singleton<daemon>
  {
  public:
    daemon();
    ~daemon();

    void update();
    void shutdown();

    inline void stop();

    inline void on_sigint(std::function<void()> handler);
    inline void on_sigterm(std::function<void()> handler);
    inline void on_sighup(std::function<void()> handler);

    inline bool running() const;

  private:
    void install_signal_handlers();
    void uninstall_signal_handlers();

    void call_signal_handlers();

    template <typename func_signature_t, typename... arguments_t>
    void call_sig_handler(
      const std::function<func_signature_t>& handler, arguments_t&&... arguments);

    inline void signal_handled();

    static void handle_sigint(int signal);
    static void handle_sigterm(int signal);
    static void handle_sighup(int signal);

  private:
    volatile sig_atomic_t continue_execution;

    volatile sig_atomic_t sig_handled;
    std::function<void()> sigint_handler;
    std::function<void()> sigterm_handler;
    std::function<void()> sighup_handler;
  };

  inline void daemon::stop() { continue_execution = false; }

  inline bool daemon::running() const { return continue_execution; }

  inline void daemon::on_sigint(std::function<void()> handler)
  {
    sigint_handler = handler;
  }

  inline void daemon::on_sigterm(std::function<void()> handler)
  {
    sigterm_handler = handler;
  }

  inline void daemon::on_sighup(std::function<void()> handler)
  {
    sighup_handler = handler;
  }

  template <typename func_signature_t, typename... arguments_t>
  void daemon::call_sig_handler(
    const std::function<func_signature_t>& handler, arguments_t&&... arguments)
  {
    if (handler)
    {
      handler(std::forward<arguments_t>(arguments)...);
    }
  }

  inline void daemon::signal_handled() { sig_handled = true; }
} // namespace jarvis::bridge

#endif