#include "adlik_serving/framework/manager/boarding_loop.h"

#include "adlik_serving/framework/manager/boarding_functor.h"
#include "cub/env/concurrent/auto_lock.h"

namespace adlik {
namespace serving {

BoardingLoop::BoardingLoop() {
  // auto action = [this] { this->poll(); };
  // loop.reset(new cub::LoopThread(action, 10 * 1000 /* ms */));
}

void BoardingLoop::poll() {
  auto action = [this] {
    cub::AutoLock lock(this->mu);
    BoardingFunctor f(this->ROLE(ManagedStore));
    f(streams);
  };
  loop.reset(new cub::LoopThread(action, 10 * 1000 /* ms */));

  // cub::AutoLock lock(mu);
  // BoardingFunctor f(ROLE(ManagedStore));
  // f(streams);
}

void BoardingLoop::update(ModelStream& stream) {
  cub::AutoLock lock(mu);
  streams.push_back(stream);
}

}  // namespace serving
}  // namespace adlik
