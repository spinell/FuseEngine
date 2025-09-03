#pragma once

#include <string_view>

namespace fuse {


/// @brief Retrive the name of type.
///
/// This function return the name of a template paramater type with qualifier.
///
/// Usage example:
/// @code{.cpp}
/// class Foo {};
///
/// getTypeName<Foo>();        // return Foo
/// getTypeName<const Foo>();  // return const Foo
/// getTypeName<Foo*>();       // return Foo*
/// @endcode
///
/// @tparam T The type to retrive the name.
/// @return The name of the type.
/// @note With MSVC this function keep the class/struct/union/enum keyword.
template <class T>
constexpr auto getTypeFullName() noexcept;

/// @brief Retrive the name of type.
///
/// This function return the name of a template paramater type without qualifier.
///
/// Usage example:
/// @code{.cpp}
/// class Foo {};
///
/// getTypeName<Foo>();        // return Foo
/// getTypeName<const Foo>();  // return Foo
/// getTypeName<Foo*>();       // return Foo
/// @endcode
///
/// @tparam T The type to retrive the name.
/// @return The name of the type.
/// @note With MSVC this function keep the class/struct/union/enum keyword.
template <class T>
constexpr auto getTypeName() noexcept;

} // namespace fuse

#include "GetTypeName.inc.h"
