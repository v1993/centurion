#ifndef CENTURION_BLEND_MODE_SOURCE
#define CENTURION_BLEND_MODE_SOURCE

#include "blend_mode.h"

namespace centurion {
namespace video {

CENTURION_DEF bool operator==(BlendMode a, SDL_BlendMode b) noexcept
{
  return static_cast<SDL_BlendMode>(a) == b;
}

CENTURION_DEF bool operator==(SDL_BlendMode a, BlendMode b) noexcept
{
  return a == static_cast<SDL_BlendMode>(b);
}

CENTURION_DEF bool operator!=(BlendMode a, SDL_BlendMode b) noexcept
{
  return static_cast<SDL_BlendMode>(a) != b;
}

CENTURION_DEF bool operator!=(SDL_BlendMode a, BlendMode b) noexcept
{
  return a != static_cast<SDL_BlendMode>(b);
}

}  // namespace video
}  // namespace centurion

#endif  // CENTURION_BLEND_MODE_SOURCE
