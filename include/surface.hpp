/*
 * MIT License
 *
 * Copyright (c) 2019-2020 Albin Johansson
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

/**
 * @file surface.hpp
 *
 * @brief Provides the `Surface` class.
 *
 * @author Albin Johansson
 *
 * @date 2019-2020
 *
 * @copyright MIT License
 */

#ifndef CENTURION_SURFACE_HEADER
#define CENTURION_SURFACE_HEADER

#include <SDL.h>

#include <type_traits>

#include "blend_mode.hpp"
#include "centurion_api.hpp"
#include "centurion_fwd.hpp"
#include "centurion_utils.hpp"
#include "color.hpp"
#include "pixel_format.hpp"
#include "rect.hpp"

namespace centurion {

/**
 * @class Surface
 *
 * @brief Represents a non-accelerated image.
 *
 * @note In most cases, it's preferable to use the `texture` class instead.
 *
 * @since 4.0.0
 *
 * @headerfile surface.hpp
 */
class Surface final {
 public:
  /**
   * @brief Creates a surface based on the image at the specified path.
   *
   * @param file the file path of the image file that will be loaded.
   *
   * @throws centurion_exception if the surface cannot be created.
   *
   * @since 4.0.0
   */
  CENTURION_API
  explicit Surface(czstring file);

  /**
   * @brief Creates a surface by claiming the supplied SDL surface.
   *
   * @param surface a pointer to the surface that will be claimed, mustn't be
   * null.
   *
   * @throws centurion_exception if the supplied pointer is null.
   *
   * @since 4.0.0
   */
  CENTURION_API
  explicit Surface(owner<SDL_Surface*> surface);

  /**
   * @brief Creates a copy of the supplied surface.
   *
   * @param other the surface that will be copied.
   *
   * @throws centurion_exception if the supplied surface couldn't be copied.
   *
   * @since 4.0.0
   */
  CENTURION_API
  Surface(const Surface& other);

  /**
   * @brief Creates a surface by moving the supplied surface.
   *
   * @param other the surface that will be moved.
   * @since 4.0.0
   */
  CENTURION_API
  Surface(Surface&& other) noexcept;

  /**
   * @brief Copies the supplied surface.
   *
   * @param other the surface that will be copied.
   *
   * @throws centurion_exception if the supplied surface couldn't be copied.
   *
   * @since 4.0.0
   */
  CENTURION_API
  auto operator=(const Surface& other) -> Surface&;

  /**
   * @brief Moves the supplied surface into this surface.
   *
   * @param other the surface that will be moved.
   *
   * @return the surface that claimed the supplied surface.
   *
   * @since 4.0.0
   */
  CENTURION_API
  auto operator=(Surface&& other) noexcept -> Surface&;

  CENTURION_API
  ~Surface() noexcept;

  /**
   * @brief Sets the color of the pixel at the specified coordinate.
   *
   * @details This method has no effect if the coordinate is out-of-bounds or if
   * something goes wrong when attempting to modify the pixel data.
   *
   * @param pixel the pixel that will be changed.
   * @param color the new color of the pixel.
   *
   * @since 4.0.0
   */
  CENTURION_API
  void set_pixel(const point_i& pixel, const color& color) noexcept;

  /**
   * @brief Sets the alpha component modulation value.
   *
   * @param alpha the new alpha component value, in the range [0, 255].
   *
   * @since 4.0.0
   */
  CENTURION_API
  void set_alpha(u8 alpha) noexcept;

  /**
   * @brief Sets the color modulation that will be used by the surface.
   *
   * @param color the color that represents the color modulation that will be
   * used.
   *
   * @since 4.0.0
   */
  CENTURION_API
  void set_color_mod(const color& color) noexcept;

  /**
   * @brief Sets the blend mode that will be used by the surface.
   *
   * @param mode the blend mode that will be used.
   *
   * @since 4.0.0
   */
  CENTURION_API
  void set_blend_mode(blend_mode mode) noexcept;

  /**
   * @brief Returns the alpha component modulation of the surface.
   *
   * @return the alpha modulation value, in the range [0, 255].
   *
   * @since 4.0.0
   */
  CENTURION_QUERY
  auto alpha() const noexcept -> u8;

  /**
   * @brief Returns the color modulation of the surface.
   *
   * @return a color that represents the color modulation of the surface.
   *
   * @since 4.0.0
   */
  CENTURION_QUERY
  auto color_mod() const noexcept -> color;

  /**
   * @brief Returns the blend mode that is being used by the surface.
   *
   * @return the blend mode that the surface uses.
   *
   * @since 4.0.0
   */
  CENTURION_QUERY
  auto blend_mode() const noexcept -> enum blend_mode;

  // TODO add
  //  /**
  //   * Converts the surface into its texture equivalent.
  //   *
  //   * @param renderer the renderer that will be used to create the
  //   * texture.
  //   * @return a texture that is equivalent to the surface.
  //   * @since 4.0.0
  //   */
  //  template <typename Renderer>
  //  [[nodiscard]] auto to_texture(Renderer&& renderer) const noexcept ->
  //  Texture
  //  {
  //    return {SDL_CreateTextureFromSurface(renderer.get(), m_surface)};
  //  }

  /**
   * @brief Creates and returns a surface based on this surface with the
   * specified pixel format.
   *
   * @param format the pixel format that will be used by the new surface.
   *
   * @return a surface based on this surface with the specified
   * pixel format.
   *
   * @throws centurion_exception if the surface cannot be created.
   *
   * @since 4.0.0
   */
  CENTURION_QUERY
  auto convert(pixel_format format) const -> Surface;

  /**
   * @brief Returns the width of the surface.
   *
   * @return the width of the surface.
   *
   * @since 4.0.0
   */
  [[nodiscard]] auto width() const noexcept -> int { return m_surface->w; }

  /**
   * @brief Returns the height of the surface.
   *
   * @return the height of the surface.
   *
   * @since 4.0.0
   */
  [[nodiscard]] auto height() const noexcept -> int { return m_surface->h; }

  /**
   * @brief Returns the pitch (the length of a row of pixels in bytes) of the
   * surface.
   *
   * @return the pitch of the surface.
   *
   * @since 4.0.0
   */
  [[nodiscard]] auto pitch() const noexcept -> int { return m_surface->pitch; }

  /**
   * @brief Returns a pointer to the pixel data of the surface.
   *
   * @details It's possible to modify the surface through the returned pointer.
   *
   * @return a pointer to the pixel data of the surface.
   *
   * @since 4.0.0
   */
  [[nodiscard]] auto pixels() noexcept -> void* { return m_surface->pixels; }

  /**
   * @brief Returns a const pointer to the pixel data of the surface.
   *
   * @return a const pointer to the pixel data of the surface.
   *
   * @since 4.0.0
   */
  [[nodiscard]] auto pixels() const noexcept -> const void*
  {
    return m_surface->pixels;
  }

  /**
   * @brief Returns the clipping information associated with the surface.
   *
   * @return the clipping information associated with the surface.
   *
   * @since 4.0.0
   */
  [[nodiscard]] auto clip() const noexcept -> rect_i
  {
    const auto rect = m_surface->clip_rect;
    return {{rect.x, rect.y}, {rect.w, rect.h}};
  }

  /**
   * @brief Returns a pointer to the associated `SDL_Surface`.
   *
   * @warning Use of this method is not recommended, since it purposefully
   * breaks const-correctness. However it is useful since many SDL calls use
   * non-const pointers even when no change will be applied. Don't take
   * ownership of the returned pointer, or bad things will happen.
   *
   * @return a pointer to the associated `SDL_Surface`.
   *
   * @since 4.0.0
   */
  [[nodiscard]] auto get() const noexcept -> SDL_Surface* { return m_surface; }

  /**
   * @brief Converts to `SDL_Surface*`.
   *
   * @return a pointer to the associated `SDL_Surface`.
   *
   * @since 4.0.0
   */
  [[nodiscard]] explicit operator SDL_Surface*() noexcept { return m_surface; }

  /**
   * @brief Converts to `const SDL_Surface*`.
   *
   * @return a pointer to the associated `SDL_Surface`.
   *
   * @since 4.0.0
   */
  [[nodiscard]] explicit operator const SDL_Surface*() const noexcept
  {
    return m_surface;
  }

 private:
  SDL_Surface* m_surface = nullptr;

  /**
   * @brief Destroys the associated SDL_Surface.
   *
   * @details This method has no effect if the associated surface is null.
   *
   * @since 4.0.0
   */
  void destroy() noexcept;

  /**
   * @brief Moves the contents of the supplied Surface instance into this
   * instance.
   *
   * @param other the instance that will be moved.
   *
   * @since 4.0.0
   */
  void move(Surface&& other) noexcept;

  /**
   * @brief Copies the contents of the supplied Surface instance into this
   * instance.
   *
   * @param other the instance that will be copied.
   *
   * @since 4.0.0
   */
  void copy(const Surface& other) noexcept;

  /**
   * @brief Indicates whether or not the supplied point is within the bounds of
   * the surface.
   *
   * @param point the point that will be checked.
   *
   * @return true if the point is within the bounds of the surface; false
   * otherwise.
   *
   * @since 4.0.0
   */
  [[nodiscard]] auto in_bounds(const point_i& point) const noexcept -> bool;

  /**
   * @brief Indicates whether or not the surface must be locked before modifying
   * the pixel data associated with the surface.
   *
   * @return `true` if the surface must be locked before modification; `false`
   * otherwise.
   *
   * @since 4.0.0
   */
  [[nodiscard]] auto must_lock() const noexcept -> bool;

  /**
   * @brief Attempts to lock the surface, so that the associated pixel data can
   * be modified.
   *
   * @details This method has no effect if `must_lock()` returns `false`.
   *
   * @return `true` if the locking of the surface was successful or if locking
   * isn't required for modifying the surface; `false` if something went wrong.
   *
   * @since 4.0.0
   */
  auto lock() noexcept -> bool;

  /**
   * @brief Unlocks the surface.
   *
   * @details This method has no effect if `must_lock()` returns `false`.
   *
   * @since 4.0.0
   */
  void unlock() noexcept;

  /**
   * @brief Creates and returns copy of the associated `SDL_Surface`.
   *
   * @return a copy of the associated `SDL_Surface`, the returned pointer won't
   * be null.
   *
   * @throws centurion_exception if the copy couldn't be created.
   *
   * @since 4.0.0
   */
  [[nodiscard]] auto copy_surface() const -> SDL_Surface*;
};

static_assert(!std::is_nothrow_copy_constructible_v<Surface>);
static_assert(!std::is_nothrow_copy_assignable_v<Surface>);
static_assert(std::is_nothrow_move_constructible_v<Surface>);
static_assert(std::is_nothrow_move_assignable_v<Surface>);

}  // namespace centurion

#ifdef CENTURION_HEADER_ONLY
#include "surface.cpp"
#endif

#endif  // CENTURION_SURFACE_HEADER