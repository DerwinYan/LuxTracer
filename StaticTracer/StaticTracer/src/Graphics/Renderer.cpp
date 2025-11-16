#include <Graphics/Renderer.h>
#include <stb/stb_image_write.h>
#include <iostream>
#include <Graphics/Pixel.h>
#include <Math/vec3.h>
#include <Graphics/Ray.h>

math::vec3 s_vpx;
math::vec3 s_vpy;

math::vec3 skyboxColor(pt::Ray const& ray)
{
  static const math::vec3 skyColor{ 0.5f, 0.7f, 1.0f };
  static const math::vec3 horizonColor{ 1.0f };

  math::vec3 direction{ math::normalize(ray.getDirection()) };
  float t{ 0.5f * (direction.y + 1.0f) };
  return math::lerp(skyColor, horizonColor, 1.0f - t);
}

/// @brief  Test ray vs sphere
/// @return Return hit time 't' for ray
float hitSphere(math::vec3 const& center, float radius, pt::Ray const& ray)
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
  if (discriminant < 0.0f)
    return FLT_MIN;
  else
    return (-b - std::sqrtf(discriminant)) / 2*a;
}

math::vec3 traceRay(pt::Ray const& ray)
{
  static const math::vec3 sphereCenter{ 0,0,-1 };
  static const float radius{ 0.5 };

  float t{ hitSphere(sphereCenter, radius, ray) };
  if (t >= 0.0f)
    return skyboxColor(ray);

  math::vec3 pointOnSphere{ ray.at(t) };
  math::vec3 normal{ pointOnSphere - sphereCenter };
  return 0.5f * (normal + 1.0f);
}

pt::Renderer::Renderer(Window _window) 
  : window{ _window }, framebuffer{ window.getWidth(), window.getHeight() }
{}

void pt::Renderer::render()
{
  float aspectRatio{ static_cast<float>(window.getWidth()) / window.getHeight() };
  float viewportHeight{ 2.0f };
  float viewportWidth{ aspectRatio * viewportHeight };
  float viewportZ{ 1.0f };
  math::vec3 cameraPosition{};

  math::vec3 vpX{ viewportWidth, 0,0 }; 
  math::vec3 vpY{ 0, viewportHeight, 0 };
  s_vpx = vpX; s_vpy = vpY;
  math::vec3 topLeftVP
  {
    cameraPosition -
    math::vec3{0,0,viewportZ} -
    vpX * 0.5f +
    vpY * 0.5f
  };

  math::vec3 pixelDeltaX{ vpX / static_cast<float>(window.getWidth()) };
  math::vec3 pixelDeltaY{ vpY / static_cast<float>(window.getHeight()) };
  math::vec3 pixel00World{ topLeftVP + 0.5f * (pixelDeltaX + pixelDeltaY) };

  for (int y{}; y < window.getHeight(); ++y)
  {
    std::cout << "\33[2K\rScanlines remaining: " << (window.getHeight() - y) << std::flush;

    for (int x{}; x < window.getWidth(); ++x)
    {
      // Debug framebuffer coords
      //Pixel pixel{ (float)x / window.getWidth(), (float)y / window.getHeight(), 0.0f};
      //framebuffer.setPixel(x, y, pixel);

      // Debug world space viewport coords
      math::vec3 pixelCenter{ pixel00World + (static_cast<float>(x) * pixelDeltaX) - (static_cast<float>(y) * pixelDeltaY) };
      math::vec3 rayDirection{ pixelCenter - cameraPosition };
      pt::Ray ray{ cameraPosition, rayDirection };
      Pixel pixel{ 0.5f * (1.0f + math::normalize(ray.getDirection())) };
      framebuffer.setPixel(x, y, pixel);

      //math::vec3 pixelCenter{ pixel00World + (static_cast<float>(x) * pixelDeltaX) - (static_cast<float>(y) * pixelDeltaY) };
      //math::vec3 rayDirection{ pixelCenter - cameraPosition };
      //pt::Ray ray{ cameraPosition, rayDirection };

      //Pixel pixel{ traceRay(ray) };

      //framebuffer.setPixel(x, y, pixel);
    }
  }

  std::cout << "\33[2K\rPathtracing complete\n";
}

void pt::Renderer::display()
{
  //stbi_write_jpg("./output.jpg", window.getWidth(), window.getHeight(), 3, framebuffer.getBuffer().data(), 100);
  stbi_write_png("./output.png", window.getWidth(), window.getHeight(), 3, framebuffer.getBuffer().data(), 3 * window.getWidth());
}
