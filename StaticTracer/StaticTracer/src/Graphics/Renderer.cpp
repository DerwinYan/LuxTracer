#include <Graphics/Renderer.h>
#include <stb/stb_image_write.h>
#include <iostream>
#include <Graphics/Pixel.h>

pt::Renderer::Renderer(Window _window) 
  : window{ _window }, framebuffer{ window.getWidth(), window.getHeight() }
{}

void pt::Renderer::render()
{
  for (int y{}; y < window.getHeight(); ++y)
  {
    std::cout << "\33[2K\rScanlines remaining: " << (window.getHeight() - y) << std::flush;

    for (int x{}; x < window.getWidth(); ++x)
    {
      auto r{ static_cast<float>(x) / (window.getWidth() - 1) };
      auto g{ static_cast<float>(y) / (window.getHeight() - 1) };

      Pixel pixel{ r ,g, 0.0f };

      framebuffer.setPixel(x, y, pixel);
    }
  }

  std::cout << "\33[2K\rPathtracing complete\n";
}

void pt::Renderer::display()
{
  stbi_write_jpg("./output.jpg", window.getWidth(), window.getHeight(), 3, framebuffer.getBuffer().data(), 100);
}
