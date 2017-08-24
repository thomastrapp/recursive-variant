#pragma once

#include <Value/Value.h>

#include <boost/mpl/at.hpp>
#include <boost/mpl/int.hpp>
#include <boost/mpl/size.hpp>


namespace Value {


template<typename Type> constexpr int TypeIndex = -1;
template<> constexpr int TypeIndex<Int>    = 0;
template<> constexpr int TypeIndex<String> = 1;
template<> constexpr int TypeIndex<Vector> = 2;
template<> constexpr int TypeIndex<Map>    = 3;


constexpr int ValueTypeSize = boost::mpl::size<Value::types>::value;


namespace {


template<typename Type, int Index>
using ValueHasTypeAtIndex = std::is_same<
  typename boost::mpl::at<Value::types, boost::mpl::int_<Index>>::type,
  Type
>;
static_assert(ValueHasTypeAtIndex<Int,    TypeIndex<Int>>   ::value);
static_assert(ValueHasTypeAtIndex<String, TypeIndex<String>>::value);
static_assert(ValueHasTypeAtIndex<Vector, TypeIndex<Vector>>::value);
static_assert(ValueHasTypeAtIndex<Map,    TypeIndex<Map>>   ::value);


} // namespace


} // namespace Value

