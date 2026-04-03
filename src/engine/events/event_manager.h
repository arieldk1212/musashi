#ifndef EVENT_MANANGER_H_
#define EVENT_MANANGER_H_

#include "event.h"

#include <queue>

namespace musashi {

class EventManager {
 public:
  EventManager();

  void TriggerEvent(Event& event);
  void QueueEvent(Event& event);
  void DispatchEvents();

 private:
  std::queue<Event> event_queue_;
  // hash map
};

}  // namespace musashi

#endif
