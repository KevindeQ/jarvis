#include "bridge_app.h"

int main(void)
{
  int exit_code = EXIT_SUCCESS;

  // Creation of this logger must not fail!
  auto syslog_sink = std::make_shared<spdlog::sinks::syslog_sink_mt>(
    "jarvis_bridge", LOG_NDELAY | LOG_PID, LOG_LOCAL0, false);
  syslog_sink->set_level(spdlog::level::critical);

  spdlog::logger logger{ "critical_logger", { syslog_sink } };

  try
  {
    jarvis::bridge::daemon daemon{};
    jarvis::bridge::app app{};

    while (daemon.running())
    {
      daemon.update();
      app.update();

      std::this_thread::yield();
    }
  }
  catch (const std::exception& ex)
  {
    logger.critical("Caught critical exception. Error message: {}", ex.what());
    exit_code = EXIT_FAILURE;
  }
  catch (...)
  {
    logger.critical("Caught unexpected critical exception.");
    exit_code = EXIT_FAILURE;
  }

  // jarvis::bridge::i2c device{};

  // int file;
  // int adapter_nr = 1;
  // char filename[20];
  // snprintf(filename, 19, "/dev/i2c-%d", adapter_nr);
  // file = open(filename, O_RDWR);
  // if (file < 0) {
  //    exit(1);
  //}
  // int addr = 0x30;
  // if (ioctl(file, I2C_SLAVE, addr) < 0) {
  //    exit(1);
  //}
  //__u8 reg = 0x10;
  //__s32 res;
  // char buf[10];
  // res = i2c_smbus_read_word_data(file, reg);
  // if (res < 0) {
  //    /* ERROR HANDLING: i2c transaction failed */
  //    std::cout << "error" << std::endl;
  //}
  // else {
  //    /* res contains the read word */
  //    std::cout << "success" << std::endl;
  //}
  // buf[0] = reg;
  // buf[1] = 0x43;
  // buf[2] = 0x65;
  // if (write(file, buf, 3) != 3) {
  //    /* ERROR HANDLING: i2c transaction failed */
  //    std::cout << "error" << std::endl;
  //}

  return exit_code;
}