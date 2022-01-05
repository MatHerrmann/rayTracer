#pragma once
#include <cmath>

class Vec3 {
public:
  Vec3() : x(0), y(0), z(0) {}
  Vec3(double x, double y, double z) : x(x), y(y), z(z) {}

  auto getX() const {
    return x;
  }
  auto getY() const {
    return y;
  }
  auto getZ() const {
    return z;
  }
  double getLength() const {
    return sqrt(x * x + y * y + z * z);
  }

  Vec3 operator*(const double t) const {
    return Vec3(x * t, y * t, z * t);
  }

  Vec3 operator/(const double t) const {
    return *this * (1 / t);
  }

  Vec3 operator-() const {
    return Vec3(-x, -y, -z);
  }

  Vec3 operator+(const Vec3& rhs) const {
    return Vec3(x + rhs.x, y + rhs.y, z + rhs.z);
  }

  Vec3 operator-(const Vec3& rhs) const {
    return Vec3(x - rhs.x, y - rhs.y, z - rhs.z);
  }

  Vec3& operator-=(const Vec3& rhs) {
    *this = *this - rhs;
    return *this;
  }

  Vec3& operator+=(const Vec3& rhs) {
    *this = *this + rhs;
    return *this;
  }

  double dot(const Vec3& rhs) const {
    return x * rhs.x + y * rhs.y + z * rhs.z;
  }

private:

  double x;
  double y;
  double z;
};

