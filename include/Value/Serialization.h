#pragma once

#include <Value/TypeIndex.h>
#include <Value/Value.h>

#include <cassert>
#include <cstdint>
#include <limits>
#include <sstream>
#include <stdexcept>
#include <string>

#include <boost/variant/static_visitor.hpp>

#include <cereal/archives/binary.hpp>
#include <cereal/types/string.hpp>
#include <cereal/types/unordered_map.hpp>
#include <cereal/types/vector.hpp>


namespace {


template<typename Archive>
class SerializeVisitor : public boost::static_visitor<>
{
public:
  SerializeVisitor(Archive& archive)
  : ar_(archive)
  {}

  template<typename Type>
  void operator()(const Type& value) const
  {
    this->ar_(CEREAL_NVP_("data", value));
  }

private:
  Archive& ar_;
};


template<typename Type, typename Archive>
Type load_type(Archive& ar)
{
  Type value;
  ar(CEREAL_NVP_("data", value));
  return value;
}


} // namespace

namespace cereal {


template<typename Archive>
void save(Archive& ar, const Value::Value& value)
{
  static_assert(Value::ValueTypeSize <= std::numeric_limits<uint8_t>::max());
  uint8_t which = static_cast<uint8_t>(value.which());

  ar(CEREAL_NVP_("which", which));
  SerializeVisitor<Archive> visitor(ar);
  value.apply_visitor(visitor);
}


template<typename Archive>
void load(Archive& ar, Value::Value& value)
{
  namespace V = Value;
  static_assert(V::ValueTypeSize <= std::numeric_limits<uint8_t>::max());

  uint8_t which;
  ar(CEREAL_NVP_("which", which));
  if( which >= V::ValueTypeSize )
    throw std::runtime_error("invalid which");

  switch( which )
  {
    case V::TypeIndex<V::Int>:    { value = load_type<V::Int>   (ar); break; }
    case V::TypeIndex<V::String>: { value = load_type<V::String>(ar); break; }
    case V::TypeIndex<V::Vector>: { value = load_type<V::Vector>(ar); break; }
    case V::TypeIndex<V::Map>:    { value = load_type<V::Map>   (ar); break; }
    default:
    {
      assert(false);
      throw std::runtime_error("unknown type");
      break;
    }
  }
}


} // namespace cereal

namespace Value {


std::string Pack(const Value& value)
{
  std::stringstream ss;
  {
    cereal::BinaryOutputArchive oarchive(ss);
    oarchive(value);
  }

  return ss.str();
}


Value Unpack(const std::string& data)
{
  Value value;
  {
    std::stringstream ss(data);
    {
      cereal::BinaryInputArchive iarchive(ss);
      iarchive(value);
    }
  }

  return value;
}


} // namespace Value

