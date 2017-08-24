#define CATCH_CONFIG_MAIN

#include <Value/Helper.h>
#include <Value/Print.h>
#include <Value/Serialization.h>
#include <Value/Value.h>

#include <catch.hpp>

#include <sstream>


struct ValuePrintStringMaker
{
  static std::string convert(const Value::Value& value)
  {
    std::stringstream ss;
    Value::Print(value, ss);
    return ss.str();
  }
};


namespace Catch {


template<> struct StringMaker<Value::Map>    : ValuePrintStringMaker {};
template<> struct StringMaker<Value::Vector> : ValuePrintStringMaker {};
template<> struct StringMaker<Value::Value>  : ValuePrintStringMaker {};


} // namespace Catch


TEST_CASE("Types")
{
  namespace V = Value;

  SECTION("Value::Int")
  {
    V::Int   input = 23;
    V::Value value = input;

    REQUIRE( V::Is<V::Int>(value) );
    REQUIRE( V::Get<V::Int>(value) == input );
  }
  SECTION("Value::String")
  {
    V::String input = "Test";
    V::Value  value = input;

    REQUIRE( V::Is<V::String>(value) );
    REQUIRE( V::Get<V::String>(value) == input );
  }
  SECTION("Value::Vector")
  {
    V::Vector input = {"One", 2};
    V::Value  value = input;
    V::Vector vec   = V::Get<V::Vector>(value);

    REQUIRE( V::Is<V::Vector>(vec) );

    REQUIRE( vec.size() == 2 );
    REQUIRE( V::Is<V::String>(vec.front()) );
    REQUIRE( V::Is<V::Int>(vec.back()) );

    REQUIRE( vec == input );
    REQUIRE( V::Get<V::String>(vec.front()) ==
             V::Get<V::String>(input.front()) );
    REQUIRE( V::Get<V::Int>(vec.back()) == V::Get<V::Int>(input.back()) );
  }
  SECTION("Value::Map")
  {
    V::Map input = {{"key1", "Test1"},
                    {"key2", V::Vector({1, 2, 3, 4, 5, "Test"})}};
    V::Value value = input;

    REQUIRE( V::Is<V::Map>(value) );
    V::Map map = V::Get<V::Map>(value);

    REQUIRE( map.size() == 2 );
    REQUIRE( map.count("key1") == 1 );
    REQUIRE( map.count("key2") == 1 );
    auto first = map["key1"];
    auto last = map["key2"];
    REQUIRE( V::Is<V::String>(first) );
    REQUIRE( V::Is<V::Vector>(last) );

    REQUIRE( map == input );
  }
}

TEST_CASE("Serialization")
{
  namespace V = Value;

  V::Value input = V::Map({
    {
      "Value::Vector",
      V::Vector({
        1,
        "one",
        2,
        "two",
        3,
        V::Map({{"beep","boop"}, {"whoop","whoop"}})
      }),
    },
    {"Value::Int", 23}
  });

  REQUIRE( input == V::Unpack(V::Pack(input)) );
}

