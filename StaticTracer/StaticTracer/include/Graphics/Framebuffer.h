#ifndef FRAMEBUFFER
#define FRAMEBUFFER

#include <vector>

namespace pt
{
  class Pixel;

  class Framebuffer
  {
  public:
    Framebuffer(int width, int height);
    void setPixel(size_t x, size_t y, Pixel const& pixel);
    std::vector<unsigned char> const& getBuffer() const noexcept;

  private:
    int width;
    int height;
    std::vector<unsigned char> buffer;
  };
}

#endif // !FRAMEBUFFER
