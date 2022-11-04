#ifndef PROCESS_LOCK_H
#define PROCESS_LOCK_H

namespace jarvis::bridge
{
  class process_lock
  {
  public:
    process_lock();
    process_lock(const process_lock&) = delete;
    process_lock(process_lock&&) = default;
    ~process_lock();

    process_lock& operator=(const process_lock&) = delete;
    process_lock& operator=(process_lock&&) = default;

    void lock();
    void unlock();
  };
} // namespace jarvis::bridge

#endif