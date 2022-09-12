#include <iostream>
#include <ostream>
#include <string>
#include <vector>

#include "Astre.h"
#include "Point.h"
#include "Position.h"
#include "Sphere.h"

void testDistances();
void testSpheres();
void testAstres();

void println(std::string str) {
    std::cout << str << std::endl;
}

int main(int, char**) {
    // testDistances();
    // testSpheres();
    testAstres();
}

void testDistances() {
    libPlanet::Point p1("Centre", libPlanet::Position(0, 0, 0));
    libPlanet::Point x1("unit distance x1", libPlanet::Position(1, 0, 0));
    libPlanet::Point y1("unit distance y1", libPlanet::Position(0, 1, 0));
    libPlanet::Point z1("unit distance z1", libPlanet::Position(0, 0, 1));
    std::cout << p1 << std::endl;

    std::cout << p1.getDistance(x1) << std::endl;
    std::cout << p1.getDistance(y1) << std::endl;
    std::cout << p1.getDistance(z1) << std::endl;
}

void testSpheres() {
    libPlanet::Sphere p(libPlanet::Point("Earth", libPlanet::Position(0, 0, 0)),
                        12742);

    libPlanet::Sphere s1(
        libPlanet::Point("Centre", libPlanet::Position(0, 0, 0)), 2);
    libPlanet::Sphere s2(
        libPlanet::Point("Centre", libPlanet::Position(2, 0, 0)), 2);
    // libPlanet::Sphere s2("Close to centre", 2, 0, 0, 2);

    std::cout << "Test equality " << (s1 == s2) << std::endl;
    std::cout << "distance : " << s1.getDistance(s2) << std::endl;

    // libPlanet::Point ps2 = static_cast<libPlanet::Point>(s2);

    std::cout << "Distance : " << s1.getDistance(s2) << std::endl;
    std::cout << "Distance : " << s1.getDistance_center(s2) << std::endl;
}

void printlneq(std::string str, std::string res) {
    std::cout << str << res << std::endl;
}

void test_compare(libPlanet::Astre a, libPlanet::Sphere s) {
    printlneq("a == b : ", (a == s ? "true" : "false"));
    printlneq("a <= b : ", (a <= s ? "true" : "false"));
    printlneq("a >= b : ", (a >= s ? "true" : "false"));
    printlneq("a < b : ", (a < s ? "true" : "false"));
    printlneq("a > b : ", (a > s ? "true" : "false"));
}

void testAstres() {
    using namespace libPlanet;
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