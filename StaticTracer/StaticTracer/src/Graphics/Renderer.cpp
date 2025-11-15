#include <Graphics/Renderer.h>
#include <stb/stb_image_write.h>
#include <iostream>
#include <Graphics/Pixel.h>
#include <Math/vec3.h>
#include <Graphics/Ray.h>


math::vec3 skyboxColor(pt::Ray const& ray)
{
  static const math::vec3 skyColor{ 0.5f, 0.7f, 1.0f };
  static const math::vec3 horizonColor{ 1.0f };

  math::vec3 direction{ math::normalize(ray.getDirection()) };
  float t{ 0.5f * (direction.y + 1.0f) };
  return math::lerp(skyColor, horizonColor, t);
}

bool hitSphere(math::vec3 const& center, float radius, pt::Ray const& ray)
{
  // Point from vector: Q + t * vector
  // Sphere formula: 
  // [C-P]*[C-P} = r^2
  // [C- (Q+tv) ]*[C- (Q+tv) ] = r^2
  // {t^2 * v*v} + {2tv(C-Q)} + {(C-Q)^2 - r^2} = 0
  //     a            b               c

  math::vec3 CQvec{ center - ray.getOrigin() };

  // Quadratic equation formula
  float a{ math::dot(ray.getDirection(), ray.getDirection()) };
  float b{ 2.0f * math::dot(ray.getDirection(), CQvec) };
  float c{ math::dot(CQvec, CQvec) - radius * radius };

  float discriminant{ b*b - 4*a*c };
  return discriminant >= 0.0f;
}

math::vec3 traceRay(pt::Ray const& ray)
{
  static const math::vec3 sphereCenter{ 0,0,-1 };
  static const float radius{ 0.5 };

  if (hitSphere(sphereCenter, radius, ray))
  {
    return { 1,0,0 };
  }
  else
  {
    return skyboxColor(ray);
  }
}

pt::Renderer::Renderer(Window _window) 
  : window{ _window }, framebuffer{ window.getWidth(), window.getHeight() }
{}

void pt::Renderer::render()
{
  float aspectRatio{ static_cast<float>(window.getWidth()) / window.getHeight() };
  float viewportHeight{ 2.0f };
  float viewportWidth{ viewportHeight * aspectRatio };
  float viewportZ{ 1.0f };
  math::vec3 cameraPosition{};

  math::vec3 viewportX{ viewportWidth, 0.0f, 0.0f };
  math::vec3 viewportY{ 0.0f, -viewportHeight, 0.0f };
  math::vec3 pixelDeltaX{ viewportX / static_cast<float>(window.getWidth()) };
  math::vec3 pixelDeltaY{ viewportY / static_cast<float>(window.getHeight()) };
  math::vec3 topLeftViewport{ cameraPosition - math::vec3{0.0f, 0.0f, viewportZ} - viewportX / 2 - viewportY / 2 };
  math::vec3 pixel00{ topLeftViewport + 0.5f * (pixelDeltaX + pixelDeltaY) };

  for (int y{}; y < window.getHeight(); ++y)
  {
    std::cout << "\33[2K\rScanlines remaining: " << (window.getHeight() - y) << std::flush;

    for (int x{}; x < window.getWidth(); ++x)
    {
      math::vec3 pixelCenter{ pixel00 + (static_cast<float>(x) * pixelDeltaX) + (static_cast<float>(y) * pixelDeltaY) };
      math::vec3 rayDirection{ pixelCenter - cameraPosition };
      pt::Ray ray{ cameraPosition, rayDirection };

      Pixel pixel{ traceRay(ray) };

      framebuffer.setPixel(x, y, pixel);
    }
  }

  std::cout << "\33[2K\rPathtracing complete\n";
}

void pt::Renderer::display()
{
  //stbi_write_jpg("./output.jpg", window.getWidth(), window.getHeight(), 3, framebuffer.getBuffer().data(), 100);
  stbi_write_png("./output.png", window.getWidth(), window.getHeight(), 3, framebuffer.getBuffer().data(), 3 * window.getWidth());
}
