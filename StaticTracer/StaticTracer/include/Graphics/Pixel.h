#ifndef PIXEL
#define PIXEL

namespace pt
{
  class Pixel
  {
  public:
    Pixel(uint8_t r, uint8_t g, uint8_t b) : r{ r }, g{ g }, b{ b } {}
    Pixel(float r, float g, float b) 
      : r{ static_cast<unsigned char>(r * 255.999f) }, 
        g{ static_cast<unsigned char>(g * 255.999f) }, 
        b{ static_cast<unsigned char>(b * 255.999f) } 
    {}


    uint8_t r, g, b;
  };
}

#endif // !PIXEL
