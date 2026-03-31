#ifndef MOUSE_EVENT_H_
#define MOUSE_EVENT_H_

#include "event.h"

namespace musashi {

class MouseEvent : public Event {
 public:
  MouseEvent(float x_pos, float y_pos);

 private:
};

}  // namespace musashi

#endif