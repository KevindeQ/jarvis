#include "bridge/modules.h"

namespace jarvis::bridge
{
  std::string basic_module::model_name() const
  {
    return std::string{ model_name.cbegin(), model_name.cend() };
  }

  std::uint32_t basic_module::product_id() const
  {
    return (product_id[3] << 24) | (product_id[2] << 16) | (product_id[1] << 8) |
      product_id[0];
  }

  std::string basic_module::serial_number() const
  {
    return std::string{ serial_number.cbegin(), serial_number.cend() };
  }

  std::uint32_t basic_module::firmware_version() const
  {
    return (firmware_version[3] << 24) | (firmware_version[2] << 16) |
      (firmware_version[1] << 8) | firmware_version[0];
  }
} // namespace jarvis::bridge