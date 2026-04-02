#ifndef LAYER_H_
#define LAYER_H_

#include "events/event.h"

namespace musashi {

class Layer {
 public:
  virtual ~Layer() = default;

  virtual void OnEvent(Event& event) = 0;
  virtual void OnUpdate(float ts) = 0;
  virtual void OnRender() = 0;

  virtual void Pause() {}
  virtual void QueueTransition() {}
};

}  // namespace musashi

#endif