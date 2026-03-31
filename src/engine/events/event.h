#ifndef EVENT_H_
#define EVENT_H_

#include "core/uuid.h"

namespace musashi {

class Event {
 public:
  virtual ~Event() = default;

  [[nodiscard]] virtual UUID GetEventID() const = 0;
};

}  // namespace musashi

#endif