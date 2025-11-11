#include "Framebuffer.h"

pt::Framebuffer::Framebuffer(int width, int height)
  : width{ width }, height{ height }, buffer(width* height)
{}

void pt::Framebuffer::setPixel(int x, int y, Pixel const pixel)
{
  if (x >= 0 && x < width && y >= 0 && y < height)
  {
    int index{ y + x * height };
    buffer[index] = pixel;
  }
}

std::vector<pt::Pixel> const& pt::Framebuffer::getBuffer()
{
  return buffer;
}
