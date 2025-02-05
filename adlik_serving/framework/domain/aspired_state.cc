#include "adlik_serving/framework/domain/aspired_state.h"

namespace adlik {
namespace serving {

AspiredState::AspiredState() : aspired(true) {
}

void AspiredState::unaspired() {
  aspired = false;
}

bool AspiredState::wasAspired() const {
  return aspired;
}

}  // namespace serving
}  // namespace adlik
