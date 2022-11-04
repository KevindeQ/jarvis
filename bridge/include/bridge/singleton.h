#ifndef SINGLETON_H
#define SINGLETON_H

#include "bridge/std_lib.h"

namespace jarvis::bridge
{
  template <typename derived_t>
  class singleton
  {
  public:
    singleton() = default;

    static derived_t& instance();

  private:
    singleton(const singleton&) = delete;
    singleton(singleton&&) = delete;

    singleton& operator=(const singleton&) = delete;
    singleton& operator=(singleton&&) = delete;
  };

  template <typename derived_t>
  derived_t& singleton<derived_t>::instance()
  {
    static_assert(std::is_base_of_v<singleton<derived_t>, derived_t>);

    static derived_t inst{};
    return inst;
  }
} // namespace jarvis::bridge

#endif