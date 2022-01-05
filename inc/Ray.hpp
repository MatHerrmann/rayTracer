#pragma once
#include "Vec3.hpp"

class Ray {
public:
  Ray() : origin(0, 0, 0), direction(0, 0, 0) {}
  Ray(const Vec3& origin, const Vec3& direction) : origin(origin), direction(direction) {}
  auto getOrigin() const {
    return origin;
  }
  auto getDirection() const {
    return direction;
  }
  auto at(const double t) {
    return origin + direction * t;
  }
private:
  Vec3 origin;
  Vec3 direction;
};