#ifndef FRAMEBUFFER
#define FRAMEBUFFER

#include <vector>
#include <Common.h>

namespace pt
{
  class Framebuffer
  {
  public:
    Framebuffer(int width, int height);
    void setPixel(int x, int y, Pixel const pixel);
    std::vector<Pixel> const& getBuffer();

  private:
    int width;
    int height;
    std::vector<Pixel> buffer;
  };
}

#endif // !FRAMEBUFFER
