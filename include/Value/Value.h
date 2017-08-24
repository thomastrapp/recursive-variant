#pragma once

#include <cstdint>
#include <string>
#include <unordered_map>
#include <vector>

#include <boost/mpl/at.hpp>
#include <boost/mpl/int.hpp>
#include <boost/variant.hpp>


namespace Value {


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


} // namespace Value

