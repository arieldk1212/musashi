#ifndef APP_LAYER_H_
#define APP_LAYER_H_

#include "engine/events/event.h"
#include "engine/events/mouse_event.h"
#include "engine/layers/layer.h"

namespace dead_verse {

class AppLayer : public musashi::Layer {
 public:
  AppLayer() = default;
  ~AppLayer() override = default;

  void OnEvent(musashi::Event& event) override;
  void OnUpdate(float timestamp) override;
  void OnRender() override;

 private:
  bool OnMousePressedEvent(musashi::MouseEvent& event);
  bool OnWindowClosed();
};

}  // namespace dead_verse

#endif