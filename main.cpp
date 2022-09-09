#include <iostream>

#include "Point.h"

void testDistances();

int main(int, char**) {
  testDistances();
}

void testDistances() {
  Point p1("Centre", 0, 0, 0);
  Point x1("unit distance x1", 1, 0, 0);
  Point y1("unit distance y1", 0, 1, 0);
  Point z1("unit distance z1", 0, 0, 1);
  std::cout << p1 << std::endl;

  std::cout << p1.distance(x1) << std::endl;
  std::cout << p1.distance(y1) << std::endl;
  std::cout << p1.distance(z1) << std::endl;
}