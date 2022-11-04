#ifndef I2C_H
#define I2C_H

#include <i2c/smbus.h>

#include <filesystem>

#include <linux/i2c-dev.h>

namespace jarvis::bridge
{
  class i2c_device
  {
  public:
    i2c_device(const std::filesystem::path& device, const std::int32_t address);
    ~i2c_device();

    std::uint8_t read_data(const std::uint8_t address);
    void write_data(const std::uint8_t address, const std::uint8_t data);

  private:
    int device_handle;
    std::int32_t device_address;
  };
} // namespace jarvis::bridge

#endif