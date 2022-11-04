#ifndef MODULES_H
#define MODULES_H

#include <cstddef>

namespace jarvis::bridge
{
  struct module_info
  {
    std::array<char, 32> model_name;
    std::array<std::byte, 4> product_id;
    std::array<char, 24> serial_number;
    std::array<std::byte, 4> firmware_version;
  };

  class basic_module
  {
  public:
    using byte_type = std::byte;

    std::string model_name() const;
    std::uint32_t product_id() const;
    std::string serial_number() const;
    std::uint32_t firmware_version() const;

  private:
    module_info info;
  };

  template <typename config_t>
  class stateful_module : public basic_module, private config_t
  {
  public:
    byte_type read_state(const std::size_t byte_offset) const;
    void write_state(const std::size_t byte_offset, const byte_type new_state);

  private:
    using configuration = config_t;

    std::array<std::byte, configuration::state_memory_size> state;
  };

  class io_module : public basic_module
  {
  public:
  private:
  };

  class modules
  {
  public:
  private:
  };

  template <typename config_t>
  stateful_module<config_t>::read_state(const std::size_t byte_offset) const
  {}

  template <typename config_t>
  stateful_module<config_t>::write_state(
    const std::size_t byte_offset, const byte_type new_state) const
  {}
} // namespace jarvis::bridge

#endif