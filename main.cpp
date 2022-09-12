#include <iostream>

#include "libplanet/Point.h"
#include "libplanet/Position.h"
#include "libplanet/Sphere.h"

void testDistances();
void testSpheres();

int main(int, char **) {
  // testDistances();
  testSpheres();
}

void testDistances() {
  libPlanet::Point p1("Centre", Position(0, 0, 0));
  libPlanet::Point x1("unit distance x1", Position(1, 0, 0));
  libPlanet::Point y1("unit distance y1", Position(0, 1, 0));
  libPlanet::Point z1("unit distance z1", Position(0, 0, 1));
  std::cout << p1 << std::endl;

  std::cout << p1.distance(x1) << std::endl;
  std::cout << p1.distance(y1) << std::endl;
  std::cout << p1.distance(z1) << std::endl;
}

void testSpheres() {

  libPlanet::Sphere p(libPlanet::Point("Earth", Position(0, 0, 0)), 12742);

  libPlanet::Sphere s1(libPlanet::Point("Centre", Position(0, 0, 0)), 2);
  libPlanet::Sphere s2(libPlanet::Point("Centre", Position(2, 0, 0)), 2);
  // libPlanet::Sphere s2("Close to centre", 2, 0, 0, 2);

  std::cout << "Test equality " << (s1 == s2) << std::endl;
  std::cout << "distance : " << s1.distance(s2) << std::endl;

  // libPlanet::Point ps2 = static_cast<libPlanet::Point>(s2);

  std::cout << "Distance : " << s1.distance(s2) << std::endl;
  std::cout << "Distance : " << s1.distance_centre(s2) << std::endl;
}