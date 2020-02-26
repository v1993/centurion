#ifndef CENTURION_PLATFORM_SOURCE
#define CENTURION_PLATFORM_SOURCE

#include "platform.h"

#include <string>

namespace centurion {
namespace system {

CENTURION_DEF
Platform get_platform() noexcept
{
  const std::string name{SDL_GetPlatform()};
  if (name == "Windows") {
    return Platform::Windows;
  } else if (name == "Mac OS X") {
    return Platform::MacOSX;
  } else if (name == "Linux") {
    return Platform::Linux;
  } else if (name == "iOS") {
    return Platform::Ios;
  } else if (name == "Android") {
    return Platform::Android;
  } else {
    return Platform::Unknown;
  }
}

#ifdef CENTURION_HAS_OPTIONAL

CENTURION_DEF
std::optional<std::string> get_platform_name() noexcept
{
  const std::string name{SDL_GetPlatform()};
  if (name == "Unknown") {
    return std::nullopt;
  } else {
    return name;
  }
}

#endif

}  // namespace system
}  // namespace centurion

#endif  // CENTURION_PLATFORM_SOURCE