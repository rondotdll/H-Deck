#pragma once

#include <cstdint>
#include <vector>

namespace TDeckInput {
  typedef std::vector<void*> Queue_t;

  class handler_t {
  public:
    Queue_t _queue;
    uint32_t _qpos = 0;

    void handle();

    handler_t() = default;
    explicit handler_t(Queue_t queue) : _queue(queue) {}
  };
}