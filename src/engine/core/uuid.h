#ifndef UUID_H_
#define UUID_H_

#include <cstdint>

namespace musashi {

class UUID {
 public:
  UUID();

 private:
  uint32_t uuid_;
};

}  // namespace musashi
#endif