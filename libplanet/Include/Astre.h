#pragma once

#include "Point.h"
#include "Sphere.h"

namespace libPlanet {
class Astre : public Sphere {
private:
  double density;

public:
  Astre(Sphere sphere, double density);
  Astre(Point point, double diameter, double density);
  ~Astre() = default;

  double getMass();
  double getDensity();

  bool operator==(Sphere &);
  bool operator<=(Sphere &);
  bool operator>=(Sphere &);
  bool operator>(Sphere &);
  bool operator<(Sphere &);

  bool operator==(Astre &);
  bool operator<=(Astre &);
  bool operator>=(Astre &);
  bool operator>(Astre &);
  bool operator<(Astre &);
};

} // namespace libPlanet