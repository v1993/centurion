#include <gtest/gtest.h>

#include "events/event.hpp"

using type = cen::event_type;

TEST(EventType, EqualityOperator)
{
  EXPECT_EQ(type::quit, SDL_QUIT);
  EXPECT_EQ(type::app_terminating, SDL_APP_TERMINATING);
  EXPECT_EQ(type::app_low_memory, SDL_APP_LOWMEMORY);
  EXPECT_EQ(type::app_will_enter_background, SDL_APP_WILLENTERBACKGROUND);
  EXPECT_EQ(type::app_did_enter_background, SDL_APP_DIDENTERBACKGROUND);
  EXPECT_EQ(type::app_did_enter_foreground, SDL_APP_DIDENTERFOREGROUND);
  EXPECT_EQ(type::display, SDL_DISPLAYEVENT);
  EXPECT_EQ(type::window, SDL_WINDOWEVENT);
  EXPECT_EQ(type::system, SDL_SYSWMEVENT);
  EXPECT_EQ(type::key_down, SDL_KEYDOWN);
  EXPECT_EQ(type::key_up, SDL_KEYUP);
  EXPECT_EQ(type::text_editing, SDL_TEXTEDITING);
  EXPECT_EQ(type::text_input, SDL_TEXTINPUT);
  EXPECT_EQ(type::keymap_changed, SDL_KEYMAPCHANGED);
  EXPECT_EQ(type::mouse_motion, SDL_MOUSEMOTION);
  EXPECT_EQ(type::mouse_button_down, SDL_MOUSEBUTTONDOWN);
  EXPECT_EQ(type::mouse_button_up, SDL_MOUSEBUTTONUP);
  EXPECT_EQ(type::mouse_wheel, SDL_MOUSEWHEEL);
  EXPECT_EQ(type::joystick_axis_motion, SDL_JOYAXISMOTION);
  EXPECT_EQ(type::joystick_ball_motion, SDL_JOYBALLMOTION);
  EXPECT_EQ(type::joystick_hat_motion, SDL_JOYHATMOTION);
  EXPECT_EQ(type::joystick_button_down, SDL_JOYBUTTONDOWN);
  EXPECT_EQ(type::joystick_button_up, SDL_JOYBUTTONUP);
  EXPECT_EQ(type::joystick_device_added, SDL_JOYDEVICEADDED);
  EXPECT_EQ(type::joystick_device_removed, SDL_JOYDEVICEREMOVED);
  EXPECT_EQ(type::controller_axis_motion, SDL_CONTROLLERAXISMOTION);
  EXPECT_EQ(type::controller_button_down, SDL_CONTROLLERBUTTONDOWN);
  EXPECT_EQ(type::controller_button_up, SDL_CONTROLLERBUTTONUP);
  EXPECT_EQ(type::controller_device_added, SDL_CONTROLLERDEVICEADDED);
  EXPECT_EQ(type::controller_device_removed, SDL_CONTROLLERDEVICEREMOVED);
  EXPECT_EQ(type::controller_device_remapped, SDL_CONTROLLERDEVICEREMAPPED);
  EXPECT_EQ(type::touch_down, SDL_FINGERDOWN);
  EXPECT_EQ(type::touch_up, SDL_FINGERUP);
  EXPECT_EQ(type::touch_motion, SDL_FINGERMOTION);
  EXPECT_EQ(type::dollar_gesture, SDL_DOLLARGESTURE);
  EXPECT_EQ(type::dollar_record, SDL_DOLLARRECORD);
  EXPECT_EQ(type::multi_gesture, SDL_MULTIGESTURE);
  EXPECT_EQ(type::clipboard_update, SDL_CLIPBOARDUPDATE);
  EXPECT_EQ(type::drop_file, SDL_DROPFILE);
  EXPECT_EQ(type::drop_text, SDL_DROPTEXT);
  EXPECT_EQ(type::drop_begin, SDL_DROPBEGIN);
  EXPECT_EQ(type::drop_complete, SDL_DROPCOMPLETE);
  EXPECT_EQ(type::audio_device_added, SDL_AUDIODEVICEADDED);
  EXPECT_EQ(type::audio_device_removed, SDL_AUDIODEVICEREMOVED);
  EXPECT_EQ(type::sensor_update, SDL_SENSORUPDATE);
  EXPECT_EQ(type::render_targets_reset, SDL_RENDER_TARGETS_RESET);
  EXPECT_EQ(type::render_device_reset, SDL_RENDER_DEVICE_RESET);
  EXPECT_EQ(type::user, SDL_USEREVENT);

  EXPECT_EQ(SDL_QUIT, type::quit);
  EXPECT_EQ(SDL_APP_TERMINATING, type::app_terminating);
  EXPECT_EQ(SDL_APP_LOWMEMORY, type::app_low_memory);
  EXPECT_EQ(SDL_APP_WILLENTERBACKGROUND, type::app_will_enter_background);
  EXPECT_EQ(SDL_APP_DIDENTERBACKGROUND, type::app_did_enter_background);
  EXPECT_EQ(SDL_APP_DIDENTERFOREGROUND, type::app_did_enter_foreground);
  EXPECT_EQ(SDL_DISPLAYEVENT, type::display);
  EXPECT_EQ(SDL_WINDOWEVENT, type::window);
  EXPECT_EQ(SDL_SYSWMEVENT, type::system);
  EXPECT_EQ(SDL_KEYDOWN, type::key_down);
  EXPECT_EQ(SDL_KEYUP, type::key_up);
  EXPECT_EQ(SDL_TEXTEDITING, type::text_editing);
  EXPECT_EQ(SDL_TEXTINPUT, type::text_input);
  EXPECT_EQ(SDL_KEYMAPCHANGED, type::keymap_changed);
  EXPECT_EQ(SDL_MOUSEMOTION, type::mouse_motion);
  EXPECT_EQ(SDL_MOUSEBUTTONDOWN, type::mouse_button_down);
  EXPECT_EQ(SDL_MOUSEBUTTONUP, type::mouse_button_up);
  EXPECT_EQ(SDL_MOUSEWHEEL, type::mouse_wheel);
  EXPECT_EQ(SDL_JOYAXISMOTION, type::joystick_axis_motion);
  EXPECT_EQ(SDL_JOYBALLMOTION, type::joystick_ball_motion);
  EXPECT_EQ(SDL_JOYHATMOTION, type::joystick_hat_motion);
  EXPECT_EQ(SDL_JOYBUTTONDOWN, type::joystick_button_down);
  EXPECT_EQ(SDL_JOYBUTTONUP, type::joystick_button_up);
  EXPECT_EQ(SDL_JOYDEVICEADDED, type::joystick_device_added);
  EXPECT_EQ(SDL_JOYDEVICEREMOVED, type::joystick_device_removed);
  EXPECT_EQ(SDL_CONTROLLERAXISMOTION, type::controller_axis_motion);
  EXPECT_EQ(SDL_CONTROLLERBUTTONDOWN, type::controller_button_down);
  EXPECT_EQ(SDL_CONTROLLERBUTTONUP, type::controller_button_up);
  EXPECT_EQ(SDL_CONTROLLERDEVICEADDED, type::controller_device_added);
  EXPECT_EQ(SDL_CONTROLLERDEVICEREMOVED, type::controller_device_removed);
  EXPECT_EQ(SDL_CONTROLLERDEVICEREMAPPED, type::controller_device_remapped);
  EXPECT_EQ(SDL_FINGERDOWN, type::touch_down);
  EXPECT_EQ(SDL_FINGERUP, type::touch_up);
  EXPECT_EQ(SDL_FINGERMOTION, type::touch_motion);
  EXPECT_EQ(SDL_DOLLARGESTURE, type::dollar_gesture);
  EXPECT_EQ(SDL_DOLLARRECORD, type::dollar_record);
  EXPECT_EQ(SDL_MULTIGESTURE, type::multi_gesture);
  EXPECT_EQ(SDL_CLIPBOARDUPDATE, type::clipboard_update);
  EXPECT_EQ(SDL_DROPFILE, type::drop_file);
  EXPECT_EQ(SDL_DROPTEXT, type::drop_text);
  EXPECT_EQ(SDL_DROPBEGIN, type::drop_begin);
  EXPECT_EQ(SDL_DROPCOMPLETE, type::drop_complete);
  EXPECT_EQ(SDL_AUDIODEVICEADDED, type::audio_device_added);
  EXPECT_EQ(SDL_AUDIODEVICEREMOVED, type::audio_device_removed);
  EXPECT_EQ(SDL_SENSORUPDATE, type::sensor_update);
  EXPECT_EQ(SDL_RENDER_TARGETS_RESET, type::render_targets_reset);
  EXPECT_EQ(SDL_RENDER_DEVICE_RESET, type::render_device_reset);
  EXPECT_EQ(SDL_USEREVENT, type::user);
}

TEST(EventType, InequalityOperator)
{
  EXPECT_NE(type::dollar_gesture, SDL_RENDER_DEVICE_RESET);
  EXPECT_NE(SDL_MOUSEMOTION, type::controller_device_removed);
}
