#include <Graphics/Framebuffer.h>
#include <Graphics/Pixel.h>

pt::Framebuffer::Framebuffer(int width, int height)
  : width{ width }, height{ height }, buffer(width * height * 3)
{}

void pt::Framebuffer::setPixel(size_t x, size_t y, Pixel const& pixel)
{
  if (x < width && y < height)
  {
    size_t index{ 3 * (x + y * height) };
    buffer[index]   = pixel.r;
    buffer[index+1] = pixel.g;
    buffer[index+2] = pixel.b;
  }
}

std::vector<unsigned char> const& pt::Framebuffer::getBuffer() const noexcept
{
  return buffer;
}
