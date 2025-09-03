#pragma once
#include <type_traits>
#include <utility>

namespace fuse {


/// @brief A class to manage Enum as bit flags.
/// @tparam T The enum type. It must be an unsigned enum.
template <class T>
    requires std::is_enum_v<T> && std::is_unsigned_v<std::underlying_type_t<T>>
class EnumFlags {
public:
    /// @brief Default constructor. All EnumFlags are unset.
    constexpr EnumFlags() = default;

    /// @brief Constructor with one or more EnumFlags to set.
    /// @tparam Ts The enum types. They must be the same as T.
    /// @param first
    /// @param others
    template <class... Ts>
        requires(std::is_same_v<T, Ts> && ...)
    constexpr EnumFlags(T first, Ts... others) noexcept
        : mData((std::to_underlying(first) | ... | std::to_underlying(others))) {}

    /// @brief Flip all the bits.
    /// @return Return the EnumFlags with all bits flipped.
    /// @warning This will flip @b unused bits.
    [[nodiscard]] constexpr EnumFlags operator~() const noexcept {
        EnumFlags flags;
        flags.mData = ~mData;
        return flags;
    }

    /// @brief Check if at least one flag is set
    /// @tparam Ts The enum types. They must be the same as T.
    /// @param  flags Flags to test.
    /// @return True if at least one flag is set. Otherwise false.
    template <class... Ts>
        requires(std::is_same_v<T, Ts> && ...)
    [[nodiscard]] constexpr bool isAnySet(Ts... flags) const noexcept {
        if constexpr (sizeof...(Ts) > 0) {
            const auto v = (std::to_underlying(flags) | ...);
            return (mData & v) != 0;
        } else {
            return mData != 0;
        }
    }

    /// @brief Check if one or mor flag is set.
    /// @tparam Ts The enum types. They must be the same as T.
    /// @param flags One of more flags to test.
    /// @return True if all flags are set.
    template <class... Ts>
        requires(sizeof...(Ts) > 0) && (std::is_same_v<T, Ts> && ...)
    [[nodiscard]] constexpr bool isSet(Ts... flags) const noexcept {
        const auto v = (std::to_underlying(flags) | ...);
        return (mData & v) == v;
    }

    /// @brief Set one or more flags.
    /// @tparam Ts The enum types. They must be the same as T.
    /// @param flags One of more flags to set.
    template <class... Ts>
        requires(sizeof...(Ts) > 0) && (std::is_same_v<T, Ts> && ...)
    constexpr void set(Ts... flags) noexcept {
        mData |= (std::to_underlying(flags) | ...);
    }

    /// @brief Unset one or more flags.
    /// @tparam Ts The enum types. They must be the same as T.
    /// @param flags One of more flags to unset.
    template <class... Ts>
        requires(sizeof...(Ts) > 0) && (std::is_same_v<T, Ts> && ...)
    constexpr void unset(Ts... flags) noexcept {
        mData &= ~(std::to_underlying(flags) | ...);
    }

private:
    using UnderlyingType = std::underlying_type_t<T>;
    UnderlyingType mData{};
};

} // namespace fuse
