#ifndef EVENT_H_
#define EVENT_H_

#include <string>

#include "core/uuid.h"

namespace musashi {

enum class EventType : uint8_t { kKeyPressed, kMouseClicked, kWindowClosed };

class Event {
 public:
  virtual ~Event() = default;

  [[nodiscard]] virtual UUID GetEventID() const = 0;
  [[nodiscard]] virtual EventType GetEventType() const = 0;
  [[nodiscard]] virtual std::string ToString() const = 0;
};

}  // namespace musashi

#endif