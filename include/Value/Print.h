#pragma once

#include <Value/Helper.h>
#include <Value/TypeIndex.h>
#include <Value/Value.h>

#include <cassert>
#include <iostream>
#include <stdexcept>


namespace Value {


void Print(const Value& value, std::ostream& out = std::cout)
{
  switch( value.which() )
  {
    case TypeIndex<Int>:
    {
      out << Get<Int>(value);
      break;
    }
    case TypeIndex<String>:
    {
      out << "\"" << Get<String>(value) << "\"";
      break;
    }
    case TypeIndex<Vector>:
    {
      const char * defaultSeparator = ", ";
      const char * separator = "";
      out << "[";
      const auto& vector = Get<Vector>(value);
      for(const auto& v : vector)
      {
        out << separator;
        Print(v, out);
        separator = defaultSeparator;
      }
      out << "]";
      break;
    }
    case TypeIndex<Map>:
    {
      const char * defaultSeparator = ", ";
      const char * separator = "";
      out << "{";
      const auto& map = Get<Map>(value);
      for(const auto& v : map)
      {
        out << separator;
        out << "\"" << v.first << "\":";
        Print(v.second, out);
        separator = defaultSeparator;
      }
      out << "}";
      break;
    }
    default:
    {
      assert(false);
      throw std::runtime_error("unknown type");
    }
  }
}


} // namespace Value

