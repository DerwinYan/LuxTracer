#ifndef COMMON
#define COMMON

#include <limits>
#include <numbers>

namespace pt::utils
{
  constexpr float infinity = std::numeric_limits<float>::infinity();

  inline float degreesToRadians(float degrees)
  {
    return degrees * static_cast<float>(std::numbers::pi) / 180.0f;
  }
}

#endif // ! COMMON
