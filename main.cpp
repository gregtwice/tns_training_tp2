#include <iostream>

#include "Point.h"
#include "Sphere.h"

void testDistances();
void testSpheres();

int main(int, char**) {
  // testDistances();
  testSpheres();
}

void testDistances() {
  libPlanet::Point p1("Centre", 0, 0, 0);
  libPlanet::Point x1("unit distance x1", 1, 0, 0);
  libPlanet::Point y1("unit distance y1", 0, 1, 0);
  libPlanet::Point z1("unit distance z1", 0, 0, 1);
  std::cout << p1 << std::endl;

  std::cout << p1.distance(x1) << std::endl;
  std::cout << p1.distance(y1) << std::endl;
  std::cout << p1.distance(z1) << std::endl;
}

void testSpheres() {
  libPlanet::Sphere p("Earth", 0, 0, 0, 12742);

  libPlanet::Sphere s1("Centre", 0, 0, 0, 2);
  libPlanet::Sphere s2("Close to centre", 2, 0, 0, 2);

  std::cout << "Test equality " << (s1 == s2) << std::endl;
  std::cout << "distance : " << s1.distance(s2) << std::endl;
}