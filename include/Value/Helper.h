#pragma once

#include <Value/TypeIndex.h>
#include <Value/Value.h>

#include <boost/variant/get.hpp>


namespace Value {


template<typename Type>
inline bool Is(const Value& value) { return value.which() == TypeIndex<Type>; }

template<typename Type>
inline Type& Get(Value& value) { return boost::get<Type>(value); }

template<typename Type>
inline const Type& Get(const Value& value) { return boost::get<Type>(value); }


} // namespace Value

