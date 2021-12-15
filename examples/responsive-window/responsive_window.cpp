#include <centurion.hpp>

int main(int, char**)
{
  /* Initialize the SDL libraries */
  const cen::SDLLibrary sdl;
  const cen::IMGLibrary img;
  const cen::MixLibrary mix;
  const cen::TTFLibrary ttf;

  /* Create a window and an associated renderer */
  auto [window, renderer] = cen::make_window_and_renderer();

  /* Make sure our window is visible */
  window.show();

  cen::event event;
  bool running = true;

  while (running) {
    while (event.poll()) {
      /* Check if the user wants to quit the application */
      if (event.is<cen::quit_event>()) {
        running = false;
        break;
      }
    }

    renderer.ClearWith(cen::colors::coral);

    /* Miscellaneous rendering code goes here... */

    renderer.Present();
  }

  /* Make the window invisible again, this might not be necessary, but it doesn't hurt */
  window.hide();

  return 0;
}