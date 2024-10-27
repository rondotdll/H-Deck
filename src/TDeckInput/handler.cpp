#include "handler.h"

namespace TDeckInput {
  void handler_t::handle() {
    // If the queue is empty, reset the position and return
    if (_queue.empty()) return;

    _queue[0]();
    _queue.erase(_queue.begin());

    _qpos++;
  }
}