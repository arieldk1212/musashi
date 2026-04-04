#ifndef EVENT_HANDLER_H_
#define EVENT_HANDLER_H_

#include "event.h"

#include <functional>

namespace musashi {

template <typename EventT>
using EventHandler = std::function<void(const EventT& event)>;

class EventHandlerWrapperInterface {
 public:
  virtual ~EventHandlerWrapperInterface() = default;

  void Execute(const Event& event) { Call(event); }

  [[nodiscard]] virtual std::string GetHandlerType() const = 0;

 private:
  virtual void Call(const Event& event) = 0;
};

template <typename EventT>
class EventHandlerWrapper : public EventHandlerWrapperInterface {
 public:
  explicit EventHandlerWrapper(EventHandler<EventT> handler)
      : handler_(std::move(handler)) {
    handler_type_ = handler_.target_type().name();
  }

 private:
  void Call(const Event& event) final {
    if (event.GetEventType() == EventT::GetEventType()) {
      handler_(static_cast<const EventT&>(event));
    }
  }

  [[nodiscard]] std::string GetHandlerType() const override {
    return handler_type_;
  }

  std::string handler_type_;
  EventHandler<EventT> handler_;
};

}  // namespace musashi

#endif
