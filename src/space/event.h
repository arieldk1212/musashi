#ifndef EVENT_H_
#define EVENT_H_

#include <cstdint>
#include <queue>
#include <unordered_map>

namespace musashi {

// TODO: Think this thru, implement when needed.

class Event {
 public:
  virtual ~Event() = default;

  virtual void RegisterEvent() = 0;
};

enum class EventCategories : uint8_t {};

class EventHandler {
 public:
  using EventQueue = std::queue<Event>;

  EventHandler();

  void Notify(EventCategories category, Event event) {
    events_[category] = std::move(event);
  }

 private:
  std::unordered_map<EventCategories, EventQueue> events_;
};

}  // namespace musashi

#endif
