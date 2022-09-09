#pragma once

#include <iostream>
#include <string>

class Point {
 private:
  std::string nom;
  double x;
  double y;
  double z;

 public:
  Point(std::string, double, double, double);
  ~Point(){};
  friend std::ostream& operator<<(std::ostream& os, const Point p);
  double getX();
  double getY();
  double getZ();

  double distance(Point&);
};
