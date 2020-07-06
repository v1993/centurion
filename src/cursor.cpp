#ifndef CENTURION_CURSOR_SOURCE
#define CENTURION_CURSOR_SOURCE

#include "cursor.hpp"

#include "centurion_utils.hpp"
#include "error.hpp"

namespace centurion {

CENTURION_DEF
Cursor::Cursor(SystemCursor id)
{
  m_cursor = SDL_CreateSystemCursor(static_cast<SDL_SystemCursor>(id));
  if (!m_cursor) {
    throw detail::Error::from_core("Failed to create system cursor!");
  }
}

CENTURION_DEF
Cursor::Cursor(Owner<SDL_Cursor*> cursor)
{
  if (cursor) {
    m_cursor = cursor;
  } else {
    throw CenturionException{"Can't create Cursor from null SDL_Cursor!"};
  }
}

CENTURION_DEF
Cursor::Cursor(const Surface& surface, IPoint hotspot)
{
  m_surface = SDL_DuplicateSurface(surface.get());
  if (!m_surface) {
    throw detail::Error::from_core("Failed to create color cursor!");
  }

  m_cursor = SDL_CreateColorCursor(m_surface, hotspot.x(), hotspot.y());
  if (!m_cursor) {
    throw detail::Error::from_core("Failed to create color cursor!");
  }
}

CENTURION_DEF
Cursor::Cursor(Cursor&& other) noexcept
{
  move(std::move(other));
}

CENTURION_DEF
Cursor& Cursor::operator=(Cursor&& other) noexcept
{
  if (this != &other) {
    move(std::move(other));
  }
  return *this;
}

CENTURION_DEF
Cursor::~Cursor() noexcept
{
  destroy();
}

CENTURION_DEF
void Cursor::destroy() noexcept
{
  if (m_cursor) {
    SDL_FreeCursor(m_cursor);
  }

  if (m_surface) {
    SDL_FreeSurface(m_surface);
  }
}

CENTURION_DEF
void Cursor::move(Cursor&& other) noexcept
{
  destroy();

  m_cursor = other.m_cursor;
  m_surface = other.m_surface;

  other.m_cursor = nullptr;
  other.m_surface = nullptr;
}

CENTURION_DEF
UniquePtr<Cursor> Cursor::unique(SystemCursor id)
{
  return std::make_unique<Cursor>(id);
}

CENTURION_DEF
UniquePtr<Cursor> Cursor::unique(Owner<SDL_Cursor*> cursor)
{
  return std::make_unique<Cursor>(cursor);
}

CENTURION_DEF
UniquePtr<Cursor> Cursor::unique(const Surface& surface, IPoint hotspot)
{
  return std::make_unique<Cursor>(surface, hotspot);
}

CENTURION_DEF
SharedPtr<Cursor> Cursor::shared(SystemCursor id)
{
  return std::make_shared<Cursor>(id);
}

CENTURION_DEF
SharedPtr<Cursor> Cursor::shared(Owner<SDL_Cursor*> cursor)
{
  return std::make_shared<Cursor>(cursor);
}

CENTURION_DEF
SharedPtr<Cursor> Cursor::shared(const Surface& surface, IPoint hotspot)
{
  return std::make_shared<Cursor>(surface, hotspot);
}

CENTURION_DEF
void Cursor::enable() noexcept
{
  SDL_SetCursor(m_cursor);
}

CENTURION_DEF
bool Cursor::is_enabled() const noexcept
{
  return SDL_GetCursor() == m_cursor;
}

CENTURION_DEF
void Cursor::force_redraw() noexcept
{
  SDL_SetCursor(nullptr);
}

CENTURION_DEF
void Cursor::reset() noexcept
{
  SDL_SetCursor(SDL_GetDefaultCursor());
}

CENTURION_DEF
void Cursor::set_visible(bool visible) noexcept
{
  SDL_ShowCursor(visible ? SDL_ENABLE : SDL_DISABLE);
}

CENTURION_DEF
bool Cursor::visible() noexcept
{
  return SDL_ShowCursor(SDL_QUERY) == SDL_ENABLE;
}

CENTURION_DEF
bool operator==(SystemCursor lhs, SDL_SystemCursor rhs) noexcept
{
  return static_cast<SDL_SystemCursor>(lhs) == rhs;
}

CENTURION_DEF
bool operator==(SDL_SystemCursor lhs, SystemCursor rhs) noexcept
{
  return lhs == static_cast<SDL_SystemCursor>(rhs);
}

CENTURION_DEF
bool operator!=(SystemCursor lhs, SDL_SystemCursor rhs) noexcept
{
  return !(lhs == rhs);
}

CENTURION_DEF
bool operator!=(SDL_SystemCursor lhs, SystemCursor rhs) noexcept
{
  return !(lhs == rhs);
}

}  // namespace centurion

#endif  // CENTURION_CURSOR_SOURCE