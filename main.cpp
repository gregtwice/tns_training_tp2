#include <iostream>
#include <ostream>
#include <string>
#include <vector>

#include "Astre.hpp"
#include "Point.hpp"
#include "Position.hpp"
#include "Sphere.hpp"

void testDistances();
void testSpheres();
void testAstres();

void println(std::string str) { std::cout << str << std::endl; }

int main(int, char**) {
  // testDistances();
  // testSpheres();
  testAstres();
}

void testDistances() {
  planets::Point p1("Centre", planets::Position(0, 0, 0));
  planets::Point x1("unit distance x1", planets::Position(1, 0, 0));
  planets::Point y1("unit distance y1", planets::Position(0, 1, 0));
  planets::Point z1("unit distance z1", planets::Position(0, 0, 1));
  std::cout << p1 << std::endl;

  std::cout << p1.getDistance(x1) << std::endl;
  std::cout << p1.getDistance(y1) << std::endl;
  std::cout << p1.getDistance(z1) << std::endl;
}

void testSpheres() {
  planets::Sphere p(planets::Point("Earth", planets::Position(0, 0, 0)), 12742);

  planets::Sphere s1(planets::Point("Centre", planets::Position(0, 0, 0)), 2);
  planets::Sphere s2(planets::Point("Centre", planets::Position(2, 0, 0)), 2);
  // planets::Sphere s2("Close to centre", 2, 0, 0, 2);

  std::cout << "Test equality " << (s1 == s2) << std::endl;
  std::cout << "distance : " << s1.getDistance(s2) << std::endl;

  // planets::Point ps2 = static_cast<planets::Point>(s2);

  std::cout << "Distance : " << s1.getDistance(s2) << std::endl;
  std::cout << "Distance : " << s1.getDistance_center(s2) << std::endl;
}

void printlneq(std::string str, std::string res) {
  std::cout << str << res << std::endl;
}

void test_compare(planets::Astre a, planets::Sphere s) {
  printlneq("a == b : ", (a == s ? "true" : "false"));
  printlneq("a <= b : ", (a <= s ? "true" : "false"));
  printlneq("a >= b : ", (a >= s ? "true" : "false"));
  printlneq("a < b : ", (a < s ? "true" : "false"));
  printlneq("a > b : ", (a > s ? "true" : "false"));
}

void testAstres() {
  using namespace planets;
  Sphere s(Point("Sun", Position(0, 1, 0)), 20);
  Sphere s1(Point("Sun", Position(0, 0, 2)), 30);
  Astre a(s, 30);

  Astre a1(s1, 10);

  test_compare(a, s);
  test_compare(a, s1);
  test_compare(a1, s);

  // 5,98.1024

  /*
      mean density | 5.515 g/cm^3 (grams per cubic centimeter)
      mass | 5.97×10^24 kg (kilograms)
      volume | 1.083207×10^21 m^3 (cubic meters)
      average diameter | 12742.018 km (kilometers)
  */
  Sphere s2(Point("Earth", Position(0, 0, 0)), 12742000);

  Astre earth(s2, 5515);

  Astre moon(Point("Moon", Position(0, 3.8e8, 0)), 3480000, 3344);
  std::cout << "E MASS : " << earth.getMass() << std::endl;
  std::cout << "M MASS : " << moon.getMass() << std::endl;

  std::cout << earth.getDistance_center(moon) << std::endl;
  std::cout << earth.getAttraction(moon) << std::endl;
  std::cout << moon.getAttraction(earth) << std::endl;

  auto v = std::vector<Astre*>();
  v.push_back(&moon);
  v.push_back(&a1);
  v.push_back(&a);

  std::cout << earth.sumAttraction(v) << std::endl;
}