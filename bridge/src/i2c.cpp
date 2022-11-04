#include "bridge/i2c.h"
#include "bridge/std_lib.h"

namespace jarvis::bridge
{
  i2c_device::i2c_device(const std::filesystem::path& device, const std::int32_t address) :
    device_handle{ -1 }, device_address{ address }
  {
    device_handle = open(device.c_str(), I2C_RDWR);
    if (device_handle < 0)
    {
      throw std::runtime_error{ "Can't open i2c device" };
    }
  }

  i2c_device::~i2c_device()
  {
    if (device_handle >= 0)
    {
      close(device_handle);
    }
  }

  std::uint8_t i2c_device::read_data(const std::uint8_t address) { return 0; }

  void i2c_device::write_data(const std::uint8_t address, const std::uint8_t data) {}
} // namespace jarvis::bridge