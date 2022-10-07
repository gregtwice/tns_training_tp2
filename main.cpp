#include <iostream>
#include <ostream>
#include <fstream>
#include <string>
#include <cstdio>

#include "UserInterface.hpp"

#include "Astre.hpp"
#include "MyStaticVector.hpp"
#include "Planet.hpp"
#include "Point.hpp"
#include "Position.hpp"
#include "Sphere.hpp"
#include "Vec3.hpp"

void createSolarSystem();

void println(std::string str) {
  std::cout << str << std::endl;
}

void testPlanets() {
  using namespace planets;

  // Point sun_p = Point("Sun", Position(0, 0, 0));
  // Sphere sun_s(sun_p, 6.96e8 * 2);
  // Astre sun_a = Astre(sun_s, 1.989e30 / sun_s.getVolume());
  // Planet sun(sun_a, Vec3(0, 0, 0));

  // Point earth_p = Point("Earth", Position(149.57e9, 0, 0));
  Point earth_p = Point("Earth", Position(0, 0, 0));
  Sphere earth_s(earth_p, 6371e3 * 2);
  Astre earth_a = Astre(earth_s, 5.972e24 / earth_s.getVolume());
  Planet earth(earth_a, Vec3(0, 0, 0));
  // earth.setVelocityRelativeToOrbitDistance(sun, 0);

  println("-------------------------------------------------------------");
  println("MOON");
  Point moon_p = Point("Moon", Position(earth.getPosition()._x + 384400e3, 0, 0));
  Sphere moon_s(moon_p, 1737e3 * 2);
  Astre moon_a = Astre(moon_s, 7.342e22 / moon_s.getVolume());
  Planet moon(moon_a, Vec3(0, 0, 0));
  moon.setVelocityRelativeToOrbitDistance(earth);
  Vec3 v = moon.getVelocity();
  std::cout << v._x << ", " << v._y << ", " << v._z << "\nmagnitude: " << v.mag() << "\n";

  println("-------------------------------------------------------------");
  println("Sat");
  double sat_dist = 6e3;

  Point sat_p("Satelite", Position(moon.getPosition()._x + moon.getDiameter() / 2 + sat_dist, 0, 0));
  Sphere sat_s(sat_p, 10);
  Astre sat_a(sat_s, 10);
  Planet sat(sat_a, Vec3(0, 0, 0));

  sat.setVelocityRelativeToOrbitDistance(moon);
  v = sat.getVelocity();
  std::cout << v._x << ", " << v._y << ", " << v._z << "\nmagnitude: " << v.mag() << "\n";
  println("-------------------------------------------------------------");

  FILE* pFile = fopen("/mnt/c/Users/g.defoy/Desktop/dump.txt", "w");
  double simu_step = 0.05;

  auto bodies = mycollections::StaticVector<Planet*, 20>();
  bodies.push(&earth);
  // bodies.push(&sun);
  bodies.push(&sat);
  bodies.push(&moon);

  for (int64_t i = 0; i < 10; i++) {
    for (size_t i = 0; i < 24; i++) {
      for (size_t i = 0; i < 3600; i++) {
        if (i % 60 == 0) {
          fprintf(pFile, "%e %e %e %e\n", moon.getPosition()._x, moon.getPosition()._y, sat.getPosition()._x, sat.getPosition()._y);
        }

        for (size_t i = 0; i < 50; i++) {
          for (size_t j = 0; j < bodies.getSize(); j++) {
            bodies[j]->updateVelocity(bodies.iter(), simu_step);
          }
          for (size_t j = 0; j < bodies.getSize(); j++) {
            bodies[j]->updatePosition(simu_step);
          }
        }
      }
    }
    std::cout << "\r\r\r" << i;
    std::flush(std::cout);
  }
  fclose(pFile);
}

int main(int, char**) {
  // createSolarSystem();
  auto cli = cli::UserInterface::getInstance();
  cli.loop();
}

void createSolarSystem() {
  using namespace planets;
  println("-------------------------------------------------------------");
  println("SUN");
  Point sun_p = Point("Sun", Position(0, 0, 0));
  Sphere sun_s(sun_p, 1500 * 2);
  Astre sun_a = Astre(sun_s, (50 * sun_s.getDiameter() / 2 * sun_s.getDiameter() / 2 / Astre::gravitationnalConstantModel) / sun_s.getVolume());
  Planet sun(sun_a, Vec3(0, 0, 0));
  println("-------------------------------------------------------------");
  println("EARTHs");
  Point earth_p = Point("Earth", Position(-11033.0, 0.0, 0.0));
  Sphere earth_s(earth_p, 300 * 2);
  Astre earth_a = Astre(earth_s, earth_s.getVolume());
  earth_a.setMass((10 * earth_s.getDiameter() / 2 * earth_s.getDiameter() / 2 / Astre::gravitationnalConstantModel));
  Planet earth1(earth_a, Vec3(0, 102.57, 0));
  Planet earth2(earth_a, Vec3(0, 102.57, 0));

  earth2.setPosition(Position(-13038, 0, 0));
  earth2.setVelocity(Vec3(0, 80.6, 0));
  earth1.setVelocity(Vec3(0, 115.3, 0));

  println("-------------------------------------------------------------");
  println("Far away");
  Point far_away_p = Point("far_away", Position(-24295, 0, 0));
  Sphere far_away_s(far_away_p, 400);
  Astre far_away_a = Astre(far_away_s, 7.342e22 / far_away_s.getVolume());
  far_away_a.setMass((8 * far_away_a.getDiameter() / 2 * far_away_a.getDiameter() / 2 / Astre::gravitationnalConstantModel));
  Planet far_away(far_away_a, Vec3(0, 70.23, 0));

  println("-------------------------------------------------------------");
  println("Far away sat");

  Point sat_p("Green Satelite", Position(-23549, 0, 0));
  Sphere sat_s(sat_p, 50 * 2);
  Astre sat_a(sat_s, 0);
  sat_a.setMass((3 * sat_a.getDiameter() / 2 * sat_a.getDiameter() / 2 / Astre::gravitationnalConstantModel));
  Planet sat(sat_a, Vec3(0, 51, 0));

  println("-------------------------------------------------------------");
  println("Puple gas giant");

  Point pgg_p("Purple gas giant", Position(-58811, 0, 0));  //49811

  Sphere pgg_s(pgg_p, 500 * 2);
  Astre pgg_a(pgg_s, 0);
  pgg_a.setMass((14 * pgg_a.getDiameter() / 2 * pgg_a.getDiameter() / 2 / Astre::gravitationnalConstantModel));
  Planet pgg(pgg_a, Vec3(0, 50.3, 0));

  Point pggs1_p("Purple gas giant sat1", Position(-55700, 0, 0));
  Sphere pggs1_s(pggs1_p, 40 * 2);
  Astre pggs1_a(pggs1_s, 0);
  pggs1_a.setMass((2 * pggs1_a.getDiameter() / 2 * pggs1_a.getDiameter() / 2 / Astre::gravitationnalConstantModel));
  Planet pggs1(pggs1_a, Vec3(0, 18.3, 0));

  FILE* pFile = fopen("/mnt/c/Users/g.defoy/Desktop/dump.txt", "w");
  double simu_step = 1;

  auto bodies = mycollections::StaticVector<Planet*, 20>();
  bodies.push(&earth1);
  bodies.push(&earth2);
  bodies.push(&sun);
  bodies.push(&sat);
  bodies.push(&pgg);
  bodies.push(&pggs1);
  bodies.push(&far_away);

  for (int i = 0; i < 50000; i++) {
    fprintf(pFile, "%e %e %e %e %e %e %e %e %e %e %e %e %e %e\n",
      earth1.getPosition()._x, earth1.getPosition()._y,
      earth2.getPosition()._x, earth2.getPosition()._y,
      sun.getPosition()._x, sun.getPosition()._y,
      far_away.getPosition()._x, far_away.getPosition()._y,
      sat.getPosition()._x, sat.getPosition()._y,
      pgg.getPosition()._x, pgg.getPosition()._y,
      pggs1.getPosition()._x, pggs1.getPosition()._y);
    for (size_t j = 0; j < bodies.getSize(); j++) {
      bodies[j]->updateVelocity(bodies.iter(), 1);
    }
    for (size_t j = 0; j < bodies.getSize(); j++) {
      bodies[j]->updatePosition(1);
    }
  }
}
