#pragma once
#include <type_traits>

namespace fuse {

/// @brief Typetrait to remove all pointers on a type
/// @tparam T The type to remove pointer
template <typename T>
///NOLINTNEXTLINE(readability-identifier-naming)
struct remove_all_pointers : std::conditional_t<std::is_pointer_v<T>,
                                                remove_all_pointers<std::remove_pointer_t<T>>,
                                                std::type_identity<T>> {};

/// @brief Typetrait to remove all pointers on a type
/// @tparam T The type to remove point
template <typename T>
using remove_all_pointers_t = typename remove_all_pointers<T>::type;

} // namespace fuse
