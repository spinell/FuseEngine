#pragma once
#include <string_view>

namespace fuse {


/// @brief
/// @tparam T
/// @return
template <auto T>
constexpr auto getEnumName() noexcept;

} // namespace fuse

#include "EnumUtils.inc.h"
