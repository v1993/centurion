#include "joystick.h"

#include <catch.hpp>

#include "centurion_exception.h"

using namespace centurion;

// Note, it's hard to actually test the joystick API, so coverage is the best
// we can do really.

TEST_CASE("Constructors", "[Joystick]")
{
  SECTION("Index ctor") { CHECK_THROWS_AS(Joystick{0}, CenturionException); }

  SECTION("SDL_Joystick* ctor")
  {
    SDL_Joystick* ptr = nullptr;
    CHECK_THROWS_AS(Joystick{ptr}, CenturionException);
  }
}

TEST_CASE("Smart pointer factory methods", "[Joystick]")
{
  SECTION("Unique")
  {
    CHECK_THROWS_AS(Joystick::unique(0), CenturionException);
    CHECK_THROWS_AS(Joystick::unique(nullptr), CenturionException);
  }

  SECTION("Shared")
  {
    CHECK_THROWS_AS(Joystick::shared(0), CenturionException);
    CHECK_THROWS_AS(Joystick::shared(nullptr), CenturionException);
  }
}

TEST_CASE("Joystick::update", "[Joystick]")
{
  CHECK_NOTHROW(Joystick::update());
}

TEST_CASE("Joystick locking/unlocking", "[Joystick]")
{
  CHECK_NOTHROW(Joystick::lock());
  CHECK_NOTHROW(Joystick::unlock());
}

TEST_CASE("Joystick polling", "[Joystick]")
{
  Joystick::set_polling(false);
  CHECK(!Joystick::polling());

  Joystick::set_polling(true);
  CHECK(Joystick::polling());
}

TEST_CASE("Joystick::from_instance_id", "[Joystick]")
{
  const auto* ptr = Joystick::from_instance_id(0);
  CHECK(!ptr);
}

TEST_CASE("Joystick::from_player_index", "[Joystick]")
{
  const auto* ptr = Joystick::from_player_index(0);
  CHECK(!ptr);
}

TEST_CASE("Joystick::amount", "[Joystick]")
{
  const auto amount = Joystick::amount();
  REQUIRE(amount.has_value());
  CHECK(*amount == 0);
}

TEST_CASE("Joystick::guid(int)", "[Joystick]")
{
  CHECK_NOTHROW(Joystick::guid(0));
}

TEST_CASE("Joystick::player_index(int)", "[Joystick]")
{
  CHECK_NOTHROW(Joystick::player_index(0));
}

TEST_CASE("Joystick::vendor(int)", "[Joystick]")
{
  CHECK_NOTHROW(Joystick::vendor(0));
}

TEST_CASE("Joystick::product(int)", "[Joystick]")
{
  CHECK_NOTHROW(Joystick::product(0));
}

TEST_CASE("Joystick::product_version(int)", "[Joystick]")
{
  CHECK_NOTHROW(Joystick::product_version(0));
}

TEST_CASE("Joystick::type(int)", "[Joystick]")
{
  CHECK_NOTHROW(Joystick::type(0));
}

TEST_CASE("Joystick::instance_id(int)", "[Joystick]")
{
  CHECK_NOTHROW(Joystick::instance_id(0));
}

TEST_CASE("Joystick::name(int)", "[Joystick]")
{
  CHECK_NOTHROW(Joystick::name(0));
}

TEST_CASE("Joystick::guid_from_string(int)", "[Joystick]")
{
  const CZString str = "";
  CHECK_NOTHROW(Joystick::guid_from_string(str));
}

TEST_CASE("Joystick::axis_max", "[Joystick]")
{
  CHECK(Joystick::axis_max() == SDL_JOYSTICK_AXIS_MAX);
}

TEST_CASE("Joystick::axis_min", "[Joystick]")
{
  CHECK(Joystick::axis_min() == SDL_JOYSTICK_AXIS_MIN);
}

TEST_CASE("Joystick::Power values", "[Joystick]")
{
  using JPower = Joystick::Power;

  CHECK(JPower::Unknown == static_cast<JPower>(SDL_JOYSTICK_POWER_UNKNOWN));
  CHECK(JPower::Empty == static_cast<JPower>(SDL_JOYSTICK_POWER_EMPTY));
  CHECK(JPower::Low == static_cast<JPower>(SDL_JOYSTICK_POWER_LOW));
  CHECK(JPower::Medium == static_cast<JPower>(SDL_JOYSTICK_POWER_MEDIUM));
  CHECK(JPower::Full == static_cast<JPower>(SDL_JOYSTICK_POWER_FULL));
  CHECK(JPower::Wired == static_cast<JPower>(SDL_JOYSTICK_POWER_WIRED));
  CHECK(JPower::Max == static_cast<JPower>(SDL_JOYSTICK_POWER_MAX));
}

TEST_CASE("Joystick::HatState values", "[Joystick]")
{
  using HS = Joystick::HatState;

  CHECK(HS::Centered == static_cast<HS>(SDL_HAT_CENTERED));
  CHECK(HS::Up == static_cast<HS>(SDL_HAT_UP));
  CHECK(HS::Right == static_cast<HS>(SDL_HAT_RIGHT));
  CHECK(HS::Down == static_cast<HS>(SDL_HAT_DOWN));
  CHECK(HS::Left == static_cast<HS>(SDL_HAT_LEFT));
  CHECK(HS::RightUp == static_cast<HS>(SDL_HAT_RIGHTUP));
  CHECK(HS::RightDown == static_cast<HS>(SDL_HAT_RIGHTDOWN));
  CHECK(HS::LeftUp == static_cast<HS>(SDL_HAT_LEFTUP));
  CHECK(HS::LeftDown == static_cast<HS>(SDL_HAT_LEFTDOWN));
}

TEST_CASE("Joystick::Type values", "[Joystick]")
{
  using Type = Joystick::Type;

  CHECK(Type::Unknown == static_cast<Type>(SDL_JOYSTICK_TYPE_UNKNOWN));
  CHECK(Type::GameController ==
        static_cast<Type>(SDL_JOYSTICK_TYPE_GAMECONTROLLER));
  CHECK(Type::Wheel == static_cast<Type>(SDL_JOYSTICK_TYPE_WHEEL));
  CHECK(Type::ArcadeStick == static_cast<Type>(SDL_JOYSTICK_TYPE_ARCADE_STICK));
  CHECK(Type::FlightStick == static_cast<Type>(SDL_JOYSTICK_TYPE_FLIGHT_STICK));
  CHECK(Type::DancePad == static_cast<Type>(SDL_JOYSTICK_TYPE_DANCE_PAD));
  CHECK(Type::Guitar == static_cast<Type>(SDL_JOYSTICK_TYPE_GUITAR));
  CHECK(Type::DrumKit == static_cast<Type>(SDL_JOYSTICK_TYPE_DRUM_KIT));
  CHECK(Type::ArcadePad == static_cast<Type>(SDL_JOYSTICK_TYPE_ARCADE_PAD));
  CHECK(Type::Throttle == static_cast<Type>(SDL_JOYSTICK_TYPE_THROTTLE));
}