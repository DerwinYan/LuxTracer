#include <FrameBuffer/FrameBuffer.h>

graphics::FrameBuffer::FrameBuffer(int _width, int _height)
  : width{ _width }, height{ _height }, buffer(width*height)
{}

void graphics::FrameBuffer::setPixel(int _index, int r, int g, int b)
{
  Pixel p{ r,g,b };
  buffer[_index] = p;
}

std::vector<graphics::Pixel> const& graphics::FrameBuffer::getBuffer() const
{
  return buffer;
}
