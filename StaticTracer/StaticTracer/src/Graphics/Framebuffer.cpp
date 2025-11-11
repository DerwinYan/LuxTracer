#include <Graphics/Framebuffer.h>

pt::Framebuffer::Framebuffer(int width, int height)
  : width{ width }, height{ height }, buffer(width * height * 3)
{}

void pt::Framebuffer::setPixel(size_t x, size_t y, unsigned char r, unsigned char g, unsigned char b)
{
  if (x < width && y < height)
  {
    size_t index{ 3 * (x + y * height) };
    buffer[index]   = r;
    buffer[index+1] = g;
    buffer[index+2] = b;
  }
}

std::vector<unsigned char> const& pt::Framebuffer::getBuffer() const noexcept
{
  return buffer;
}
