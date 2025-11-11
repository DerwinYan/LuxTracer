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
    void setPixel(size_t x, size_t y, unsigned char r, unsigned char g, unsigned char b);
    std::vector<unsigned char> const& getBuffer() const noexcept;

  private:
    int width;
    int height;
    std::vector<unsigned char> buffer;
  };
}

#endif // !FRAMEBUFFER
