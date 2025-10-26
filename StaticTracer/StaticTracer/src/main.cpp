
#include <cassert>
#include <memory>

#include <FrameBuffer/FrameBuffer.h>
#include <fstream>

int main()
{
  #if defined(DEBUG) || defined(_DEBUG)
    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
  #endif
  
  int width{ 256 }, height{ 256 };
  graphics::FrameBuffer fb{width, height};
  for (int y{}; y < height; ++y)
  {
    for (int x{}; x < width; ++x)
    {
      auto r{ static_cast<double>(x) / (width - 1) };
      auto g{ static_cast<double>(y) / (height - 1) };

      auto ir{ static_cast<int>(r * 255.999) };
      auto ig{ static_cast<int>(g * 255.999) };
      auto b{ 0 };

      fb.setPixel(y + x * height, ir, ig, b);
    }
  }

  std::ofstream output{ "./output.ppm" };
  output << "P3\n";
  output << width << ' ' << height << '\n';
  output << "255 \n";
  for (auto const& pixel : fb.getBuffer())
  {
    output << pixel.r << ' ' << pixel.g << ' ' << pixel.b << '\n';
  }
}
