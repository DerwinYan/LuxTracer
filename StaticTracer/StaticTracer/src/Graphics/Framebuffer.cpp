#include <Graphics/Framebuffer.h>
#include <Graphics/Pixel.h>

pt::Framebuffer::Framebuffer(int width, int height)
  : width{ width }, height{ height }, buffer(static_cast<size_t>(width) * height * 3)
{}

void pt::Framebuffer::setPixel(int x, int y, Pixel const& pixel)
{
  if (x < width && y < height)
  {
    size_t index = 3ull * (static_cast<size_t>(x) + static_cast<size_t>(y) * height);
    buffer[index]   = pixel.r;
    buffer[index+1] = pixel.g;
    buffer[index+2] = pixel.b;
  }
}

std::vector<unsigned char> const& pt::Framebuffer::getBuffer() const noexcept
{
  return buffer;
}
