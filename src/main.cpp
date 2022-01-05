#include <iostream>
#include "Vec3.hpp"
#include "Ray.hpp"

using Color = Vec3;

double hitSphere(const Vec3& centerSphere, double radius, const Ray& ray) {
  const auto direction = ray.getDirection();
  const auto origin = ray.getOrigin();
  const auto a = direction.dot(direction);
  const auto temp = origin - centerSphere;
  const auto b = 2 * direction.dot(temp);
  const auto c = temp.dot(temp) - radius * radius;
  const auto discriminant = b * b - 4 * a * c;
  if (discriminant < 0) {
    return -1.0;
  } else {
    return (-b - sqrt(discriminant)) / (2.0 * a);
  }
}

Color rayColor(const Ray& ray) {
  const auto centerSphere = Vec3(0, 0, -1);
  constexpr auto radius = 0.25;
  auto t = hitSphere(centerSphere, radius, ray);
  if (t > 0.0) {
    const auto N = ray.at(t);
    const auto N_normalized = Vec3::normalize(N);
    return Color(N_normalized.getX() + 1, N_normalized.getY() + 1, N_normalized.getZ() + 1);
    // const auto distance = (N.getZ() - ray.getOrigin().getZ()) / (centerSphere.getZ() - radius);
    // return Color(1.0, 1.0, 1.0) * (1.0 - distance) + Color(0.1, 0.2, 1.0) * distance;
    // return Color(N_normalized.getX() + 1, N_normalized.getY() + 1, N_normalized.getZ() + 1);
  }

  const auto dir = ray.getDirection();
  const auto dir_normalized = Vec3::normalize(dir);
  t = 0.5 * (dir_normalized.getY() + 1.0);
  // Erzeugt linearen Übergang zwischen
  //              Startwert                          Endwert
  return Color(1.0, 1.0, 1.0) * (1.0 - t) + Color(0.5, 0.7, 1.0) * t;

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