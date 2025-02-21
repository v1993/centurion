/*
 * MIT License
 *
 * Copyright (c) 2019-2022 Albin Johansson
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#include <fff.h>
#include <gtest/gtest.h>

#include <array>  // array

#include "centurion/vulkan.hpp"
#include "core_mocks.hpp"

extern "C"
{
  FAKE_VALUE_FUNC(int, SDL_Vulkan_LoadLibrary, const char*)
  FAKE_VOID_FUNC(SDL_Vulkan_UnloadLibrary)
}

class VulkanLibraryTest : public testing::Test {
 protected:
  void SetUp() override
  {
    mocks::reset_core();

    RESET_FAKE(SDL_Vulkan_LoadLibrary)
    RESET_FAKE(SDL_Vulkan_UnloadLibrary)
  }
};

TEST_F(VulkanLibraryTest, Initialization)
{
  std::array values{-1, 0};
  SET_RETURN_SEQ(SDL_Vulkan_LoadLibrary, values.data(), cen::isize(values));

  ASSERT_THROW(cen::vk_library{}, cen::sdl_error);
  ASSERT_NO_THROW(cen::vk_library{});
  ASSERT_EQ(2u, SDL_Vulkan_LoadLibrary_fake.call_count);
}
