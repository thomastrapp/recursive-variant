# Serializable Boost Recursive Variant

This project is released under the terms of the MIT license.

Dependencies:
* Boost
* [cereal](http://uscilab.github.io/cereal/)

| Alias           | Type                                     |
|-----------------|------------------------------------------|
| `Value::Value`  | `Int|String|Vector|Map`                  |
| `Value::Int`    | `uint32_t`                               |
| `Value::String` | `std::string`                            |
| `Value::Vector` | `std::vector<Value>`                     |
| `Value::Map`    | `std::unordered_map<std::string, Value>` |

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

## Serialization

```cpp
Value::Map val({{"beep","boop"}, {"whoop","whoop"}})
std::string payload = Value::Pack(val);

Value::Value unpacked = Value::Unpack(payload);
assert(Value::Is<Value::Map>(unpacked));
```

