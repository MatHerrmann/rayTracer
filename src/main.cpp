#include <iostream>
#include "Vec3.hpp"
#include "Ray.hpp"

using Color = Vec3;

bool hitSphere(const Vec3& centerSphere, double radius, const Ray& ray) {
  const auto direction = ray.getDirection();
  const auto origin = ray.getOrigin();
  const auto a = direction.dot(direction);
  const auto temp = origin - centerSphere;
  const auto b = 2 * direction.dot(temp);
  const auto c = temp.dot(temp) - radius * radius;
  const auto discriminant = b * b - 4 * a * c;
  return (discriminant > 0);
}

Color rayColor(const Ray& ray) {
  if (hitSphere(Vec3(1, 0, -1), 0.25, ray)) {
    return Color(1, 0, 0);
  }
  const auto direction = ray.getDirection();
  const auto t = 0.5 * (direction.getY() + 1.0);
  // Erzeugt linearen Übergang zwischen
  //              Startwert                          Endwert
  return Color(1.0, 1.0, 1.0) * (1.0 - t) + Color(0.8, 0.7, 1.0) * t;

}
void writeColor(std::ostream& os, const Color& color) {
  os << static_cast<int>(255.99 * color.getX()) << ' ' << static_cast<int>(255.99 * color.getY()) << ' ' << static_cast<int>(255.99 * color.getZ()) << '\n';
}

int main() {
  constexpr auto ratio = 16.0 / 9.0;
  constexpr auto imageWidth = 400;
  constexpr auto imageHeight = imageWidth / ratio;

  constexpr auto viewportWidth = 2.0;
  constexpr auto viewportHeight = viewportWidth / ratio;
  constexpr auto focalLength = 1.0;

  const Vec3 origin(0, 0, 0);
  const Vec3 horizontal(viewportWidth, 0, 0);
  const Vec3 vertical(0, viewportHeight, 0);
  const auto lowerLeftCorner = origin - horizontal / 2 - vertical / 2 - Vec3(0, 0, focalLength);

  std::cout << "P3\n" << imageWidth << ' ' << imageHeight << "\n255\n";
  for (int j = imageHeight - 1; j >= 0; --j) {
    std::cerr << "\rScanlines remaining: " << j << ' ' << std::flush;
    for (int i = 0; i < imageWidth; ++i) {
      const auto u = double(i) / (imageWidth - 1);
      const auto v = double(j) / (imageHeight - 1);
      Ray r(origin, lowerLeftCorner + horizontal * u + vertical * v - origin);
      const auto pixelColor = rayColor(r);
      writeColor(std::cout, pixelColor);
    }
  }
}