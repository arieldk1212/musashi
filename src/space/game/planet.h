#ifndef PLANET_H_
#define PLANET_H_

#include <vector>

namespace musashi {

static const std::vector<std::string> kPlantes = {"Neptune", "Mercury"};

class Planet {
 public:
  virtual ~Planet() = default;

  virtual void InitPlanet() = 0;
};

class Mercury : public Planet {
  Mercury();
};

}  // namespace musashi

#endif
