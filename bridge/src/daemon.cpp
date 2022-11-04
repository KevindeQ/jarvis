#include "bridge/daemon.h"

namespace jarvis::bridge
{
  daemon::daemon() : sig_handled{ false }, continue_execution{ true }
  {
    install_signal_handlers();
  }

  daemon::~daemon() { uninstall_signal_handlers(); }

  void daemon::update()
  {
    if (sig_handled)
    {
      call_signal_handlers();
      sig_handled = false;
    }
  }

  void daemon::install_signal_handlers()
  {
    struct sigaction sa = {};

    sigemptyset(&sa.sa_mask);
    sa.sa_flags = 0;
    sa.sa_handler = handle_sigint;
    if (sigaction(SIGINT, &sa, nullptr) == -1)
    {
      // TODO: Raise exception
    }

    sigemptyset(&sa.sa_mask);
    sa.sa_flags = 0;
    sa.sa_handler = handle_sigterm;
    if (sigaction(SIGTERM, &sa, nullptr) == -1)
    {
      // TODO: Raise exception
    }

    sigemptyset(&sa.sa_mask);
    sa.sa_flags = 0;
    sa.sa_handler = handle_sighup;
    if (sigaction(SIGHUP, &sa, nullptr) == -1)
    {
      // TODO: Raise exception
    }
  }

  void daemon::uninstall_signal_handlers()
  {
    struct sigaction sa = {};

    sigemptyset(&sa.sa_mask);
    sa.sa_flags = 0;
    sa.sa_handler = SIG_DFL;
    sigaction(SIGINT, &sa, nullptr);

    sigemptyset(&sa.sa_mask);
    sa.sa_flags = 0;
    sa.sa_handler = SIG_DFL;
    sigaction(SIGTERM, &sa, nullptr);

    sigemptyset(&sa.sa_mask);
    sa.sa_flags = 0;
    sa.sa_handler = SIG_DFL;
    sigaction(SIGHUP, &sa, nullptr);
  }

  void daemon::call_signal_handlers()
  {
    call_sig_handler(sigint_handler);
    call_sig_handler(sigterm_handler);
    call_sig_handler(sighup_handler);
  }

  void daemon::handle_sigint(int signal)
  {
    daemon& inst = daemon::instance();
    inst.stop();
    inst.signal_handled();
  }

  void daemon::handle_sigterm(int signal)
  {
    daemon& inst = daemon::instance();
    inst.stop();
    inst.signal_handled();
  }

  void daemon::handle_sighup(int signal)
  {
    daemon& inst = daemon::instance();
    inst.signal_handled();
  }
} // namespace jarvis::bridge