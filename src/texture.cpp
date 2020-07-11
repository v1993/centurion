#ifndef CENTURION_IMAGE_SOURCE
#define CENTURION_IMAGE_SOURCE

#include <SDL_image.h>

#include "centurion_exception.hpp"
#include "centurion_utils.hpp"
#include "graphics.hpp"
#include "surface.hpp"

namespace centurion {

CENTURION_DEF
texture::texture(gsl::owner<SDL_Texture*> sdlTexture)
{
  if (!sdlTexture) {
    throw centurion_exception{
        "Texture can't be created from null SDL texture!"};
  }
  this->m_texture = sdlTexture;
}

CENTURION_DEF
texture::texture(texture&& other) noexcept
{
  move(std::move(other));
}

CENTURION_DEF
texture::~texture() noexcept
{
  destroy();
}

CENTURION_DEF
auto texture::operator=(texture&& other) noexcept -> texture&
{
  if (this != &other) {
    move(std::move(other));
  }
  return *this;
}

CENTURION_DEF
void texture::destroy() noexcept
{
  if (m_texture) {
    SDL_DestroyTexture(m_texture);
  }
}

CENTURION_DEF
void texture::move(texture&& other) noexcept
{
  destroy();
  m_texture = other.m_texture;
  other.m_texture = nullptr;
}

CENTURION_DEF
auto texture::lock(u32** pixels, int* pitch) noexcept -> bool
{
  if (pitch) {
    const auto result = SDL_LockTexture(
        m_texture, nullptr, reinterpret_cast<void**>(pixels), pitch);
    return result == 0;
  } else {
    int dummyPitch;
    const auto result = SDL_LockTexture(
        m_texture, nullptr, reinterpret_cast<void**>(pixels), &dummyPitch);
    return result == 0;
  }
}

CENTURION_DEF
void texture::unlock() noexcept
{
  SDL_UnlockTexture(m_texture);
}

CENTURION_DEF
auto texture::unique(gsl::owner<SDL_Texture*> sdlTexture)
    -> std::unique_ptr<texture>
{
  return std::make_unique<texture>(sdlTexture);
}

CENTURION_DEF
auto texture::shared(gsl::owner<SDL_Texture*> sdlTexture)
    -> std::shared_ptr<texture>
{
  return std::make_shared<texture>(sdlTexture);
}

CENTURION_DEF
void texture::set_pixel(point_i pixel, const color& color) noexcept
{
  if (get_access() != access::streaming || pixel.x() < 0 || pixel.y() < 0 ||
      pixel.x() >= width() || pixel.y() >= height()) {
    return;
  }

  u32* pixels = nullptr;
  int pitch;
  const auto success = lock(&pixels, &pitch);
  if (!success) {
    return;
  }

  const int nPixels = (pitch / 4) * height();
  const int index = (pixel.y() * width()) + pixel.x();

  if ((index >= 0) && (index < nPixels)) {
    auto* pixelFormat = SDL_AllocFormat(static_cast<u32>(format()));
    const auto value = SDL_MapRGBA(
        pixelFormat, color.red(), color.green(), color.blue(), color.alpha());

    SDL_FreeFormat(pixelFormat);

    pixels[index] = value;
  }

  unlock();
}

CENTURION_DEF
void texture::set_alpha(u8 alpha) noexcept
{
  SDL_SetTextureAlphaMod(m_texture, alpha);
}

CENTURION_DEF
void texture::set_blend_mode(enum blend_mode mode) noexcept
{
  SDL_SetTextureBlendMode(m_texture, static_cast<SDL_BlendMode>(mode));
}

CENTURION_DEF
void texture::set_color_mod(color color) noexcept
{
  SDL_SetTextureColorMod(m_texture, color.red(), color.green(), color.blue());
}

CENTURION_DEF
void texture::set_scale_mode(enum scale_mode mode) noexcept
{
  SDL_SetTextureScaleMode(m_texture, static_cast<SDL_ScaleMode>(mode));
}

CENTURION_DEF
auto texture::format() const noexcept -> pixel_format
{
  u32 format = 0;
  SDL_QueryTexture(m_texture, &format, nullptr, nullptr, nullptr);
  return static_cast<pixel_format>(format);
}

CENTURION_DEF
auto texture::get_access() const noexcept -> texture::access
{
  int access = 0;
  SDL_QueryTexture(m_texture, nullptr, &access, nullptr, nullptr);
  return static_cast<enum access>(access);
}

CENTURION_DEF
auto texture::width() const noexcept -> int
{
  int width = 0;
  SDL_QueryTexture(m_texture, nullptr, nullptr, &width, nullptr);
  return width;
}

CENTURION_DEF
auto texture::height() const noexcept -> int
{
  int height = 0;
  SDL_QueryTexture(m_texture, nullptr, nullptr, nullptr, &height);
  return height;
}

CENTURION_DEF
auto texture::size() const noexcept -> area_i
{
  int width = 0;
  int height = 0;
  SDL_QueryTexture(m_texture, nullptr, nullptr, &width, &height);
  return {width, height};
}

CENTURION_DEF
auto texture::is_target() const noexcept -> bool
{
  return get_access() == access::target;
}

CENTURION_DEF
auto texture::is_static() const noexcept -> bool
{
  return get_access() == access::no_lock;
}

CENTURION_DEF
auto texture::is_streaming() const noexcept -> bool
{
  return get_access() == access::streaming;
}

CENTURION_DEF
auto texture::alpha() const noexcept -> u8
{
  u8 alpha;
  SDL_GetTextureAlphaMod(m_texture, &alpha);
  return alpha;
}

CENTURION_DEF
auto texture::get_blend_mode() const noexcept -> blend_mode
{
  SDL_BlendMode mode;
  SDL_GetTextureBlendMode(m_texture, &mode);
  return static_cast<enum blend_mode>(mode);
}

CENTURION_DEF
auto texture::color_mod() const noexcept -> color
{
  u8 r = 0, g = 0, b = 0;
  SDL_GetTextureColorMod(m_texture, &r, &g, &b);
  return {r, g, b, 0xFF};
}

CENTURION_DEF
auto texture::get_scale_mode() const noexcept -> texture::scale_mode
{
  SDL_ScaleMode mode;
  SDL_GetTextureScaleMode(m_texture, &mode);
  return static_cast<enum scale_mode>(mode);
}

CENTURION_DEF
auto texture::to_string() const -> std::string
{
  const auto address = detail::address_of(this);
  const auto w = std::to_string(width());
  const auto h = std::to_string(height());
  return "[Texture@" + address + " | Width: " + w + ", Height: " + h + "]";
}

}  // namespace centurion

#endif  // CENTURION_IMAGE_SOURCE