# Serializable Boost Recursive Variant

A Boost.Variant for JSON-like data with serialization support
for [cereal](http://uscilab.github.io/cereal/).

This project is released under the terms of the MIT license.

## Dependencies

* Boost.Variant, Boost.MPL
* [cereal](http://uscilab.github.io/cereal/)
* Testing: cmake, [catch](https://github.com/philsquared/Catch)

## Types

| Alias           | Type                                            |
|-----------------|-------------------------------------------------|
| `Value::Value`  | `Int\|String\|Vector\|Map`                      |
| `Value::Int`    | `int32_t`                                       |
| `Value::String` | `std::string`                                   |
| `Value::Vector` | `std::vector<Value::Value>`                     |
| `Value::Map`    | `std::unordered_map<std::string, Value::Value>` |

## The gist

```cpp
using Int = std::int32_t;
using String = std::string;
using Value = boost::make_recursive_variant<
    Int
  , String
  , std::vector<boost::recursive_variant_>
  , std::unordered_map<String, boost::recursive_variant_>
>::type;
using Vector = boost::mpl::at<Value::types, boost::mpl::int_<2>>::type;
using Map = boost::mpl::at<Value::types, boost::mpl::int_<3>>::type;
```

Defined in [Value.h](include/Value/Value.h).

## Helpers

```cpp
template<typename Type>
inline bool Is(const Value& value) { return value.which() == TypeIndex<Type>; }

template<typename Type>
inline Type& Get(Value& value) { return boost::get<Type>(value); }

template<typename Type>
inline const Type& Get(const Value& value) { return boost::get<Type>(value); }
```

Defined in [Helper.h](include/Value/Helper.h).

## Serialization

Powered by [cereal](http://uscilab.github.io/cereal/).

```cpp
Value::Map val({{"beep","boop"}, {"whoop", Value::Vector({1,2,3,"whoop"})}});
std::string payload = Value::Pack(val);

Value::Value unpacked = Value::Unpack(payload);
assert(Value::Is<Value::Map>(unpacked));
```

Defined in [Serialization.h](include/Value/Serialization.h).

## Switching by type

```cpp
namespace V = Value;
switch( value.which() )
{
case V::TypeIndex<V::Int>:    /* ... */ break;
case V::TypeIndex<V::String>: /* ... */ break;
case V::TypeIndex<V::Vector>: /* ... */ break;
case V::TypeIndex<V::Map>:    /* ... */ break;
default: break;
}
```

Defined in [TypeIndex.h](include/Value/TypeIndex.h).

## Printing

```cpp
Value::Print(Value::Map({{"beep","boop"}, {"whoop", Value::Vector({1,2,3,"whoop"})}}), std::cout);
// {"whoop":[1, 2, 3, "whoop"], "beep":"boop"}
```

Defined in [Print.h](include/Value/Print.h).

