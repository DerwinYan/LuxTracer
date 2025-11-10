#include <Graphics/Renderer.h>
#include <stb/stb_image_write.h>

pt::Renderer::Renderer(Window _window) 
  : window{ _window }, framebuffer{ window.getWidth(), window.getHeight() }
{}

void pt::Renderer::render()
{
  for (int y{}; y < window.getHeight(); ++y)
  {
    for (int x{}; x < window.getWidth(); ++x)
    {
      auto r{ static_cast<double>(x) / (window.getWidth() - 1) };
      auto g{ static_cast<double>(y) / (window.getHeight() - 1) };
      
       
      auto ir = static_cast<unsigned char>(r * 255.999);
      auto ig = static_cast<unsigned char>(g * 255.999);
      auto ib = static_cast<unsigned char>(0);
      
      framebuffer.setPixel(x, y, ir, ig, ib);
    }
  }
}

void pt::Renderer::display()
{
  stbi_write_jpg("./output.jpg", window.getWidth(), window.getHeight(), 3, framebuffer.getBuffer().data(), 100);
}
