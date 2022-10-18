#include <gtest/gtest.h>
#include <cmath>

#include "Vec3.hpp"

TEST(Vec3, normalise) {
  using namespace planets;
  //   Unit vectors
  auto x = Vec3(1, 0, 0);
  ASSERT_EQ(x.normalize(), x);

  auto y = Vec3(0, 1, 0);
  ASSERT_EQ(y.normalize(), y);

  auto z = Vec3(0, 0, 1);
  ASSERT_EQ(z.normalize(), z);

  auto all = Vec3(1, 1, 1);
  ASSERT_EQ(all.normalize(), Vec3(1 / std::sqrt(3), 1 / std::sqrt(3), 1 / std::sqrt(3)));

  auto null = Vec3(0, 0, 0);
  ASSERT_EQ(null.normalize(), Vec3(0, 0, 0));
}

TEST(Vec3, mag) {
  using namespace planets;
  auto x = Vec3(1, 0, 0);
  ASSERT_EQ(x.mag(), 1);

  auto y = Vec3(0, 1, 0);
  ASSERT_EQ(y.mag(), 1);

  auto z = Vec3(0, 0, 1);
  ASSERT_EQ(z.mag(), 1);

  auto all = Vec3(1, 1, 1);
  ASSERT_EQ(all.mag(), std::sqrt(3));

  auto null = Vec3(0, 0, 0);
  ASSERT_EQ(null.mag(), 0);
}

TEST(Vec3, mul) {
  using namespace planets;
  auto all = Vec3(1, 1, 1);
  ASSERT_EQ(all * 3, Vec3(3, 3, 3));
}

TEST(Vec3, div) {
  using namespace planets;
  auto all = Vec3(1, 1, 1);
  ASSERT_EQ(all / 2, Vec3(0.5, 0.5, 0.5));
}

TEST(Vec3, add) {
  using namespace planets;
  auto all = Vec3(1, 1, 1);
  ASSERT_EQ(all + 3, Vec3(4, 4, 4));
}

TEST(Vec3, sub) {
  using namespace planets;
  auto all = Vec3(1, 1, 1);
  ASSERT_EQ(all - 1, Vec3(0, 0, 0));
}