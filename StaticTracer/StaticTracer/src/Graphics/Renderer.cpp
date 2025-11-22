#include <Graphics/Renderer.h>
#include <stb/stb_image_write.h>
#include <iostream>
#include <Graphics/Pixel.h>
#include <Math/vec3.h>
#include <Graphics/Ray.h>
#include <Graphics/Scene.h>
#include <Graphics/Sphere.h>

pt::Renderer::Renderer(Window _window) 
  : window{ _window }, framebuffer{ window.getWidth(), window.getHeight() }
{
  scene.add(std::make_shared<pt::Sphere>(math::vec3{ 0,0,-1 }, 0.5f));
  scene.add(std::make_shared<pt::Sphere>(math::vec3{ 0,-100.5f,-1.0f }, 100.0f));
}

void pt::Renderer::render()
{
  float aspectRatio{ static_cast<float>(window.getWidth()) / window.getHeight() };
  float viewportHeight{ 2.0f };
  float viewportWidth{ aspectRatio * viewportHeight };
  float viewportZ{ 1.0f };
  math::vec3 cameraPosition{};

  math::vec3 vpX{ viewportWidth, 0,0 }; 
  math::vec3 vpY{ 0, viewportHeight, 0 };
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

      //// Debug world space viewport coords
      //math::vec3 pixelCenter{ pixel00World + (static_cast<float>(x) * pixelDeltaX) - (static_cast<float>(y) * pixelDeltaY) };
      //math::vec3 rayDirection{ pixelCenter - cameraPosition };
      //pt::Ray ray{ cameraPosition, rayDirection };
      //Pixel pixel{ 0.5f * (1.0f + math::normalize(ray.getDirection())) };
      //framebuffer.setPixel(x, y, pixel);

      math::vec3 pixelCenter{ pixel00World + (static_cast<float>(x) * pixelDeltaX) - (static_cast<float>(y) * pixelDeltaY) };
      math::vec3 rayDirection{ pixelCenter - cameraPosition };
      pt::Ray ray{ cameraPosition, rayDirection };
      Pixel pixel{ scene.traceRay(ray) };
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
