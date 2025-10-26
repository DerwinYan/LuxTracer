#ifndef FRAMEBUFFER
#define FRAMEBUFFER

#include <vector>

namespace graphics
{
  struct Pixel
  {
    int r, g, b;
  };

  class FrameBuffer
  {
  public:
    FrameBuffer(int _width, int _height);

    void setPixel(int _index, int r, int g, int b);
    std::vector<Pixel> const& getBuffer() const;
    
  private:
    int width{ 256 };
    int height{ 256 };
    std::vector<Pixel> buffer;
  };
}

#endif // !FRAMEBUFFER
