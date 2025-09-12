#pragma once
#include <cmath>
#include <compare>
#include <numbers>

namespace fuse {

/// @brief Thin wrapper around a float that represent an angle.
///
/// Angle encapsulates an angle value in a flexible way.<br/>
/// It allows for defining an angle value either as a number of degrees or radians.<br/>
/// You can get the angle value in degrees or radian.
///
/// Angle values support the usual mathematical operations.
/// You can add or subtract two angles, multiply or divide
/// an angle by a number, compare two angles, etc.
///
/// This also provide 2 user literal (_deg and _rad).
///
/// To create an angle with a value use:
///     - fuse::degrees()
///     - fuse::radians()
///
/// To get the value of the angle use:
///     - Angle::asDegrees()
///     - Angle::asRadians()
///
/// Usage example:
/// @code
/// fuse::Angle a1  = fuse::degrees(90);
/// float radians = a1.asRadians(); // 1.5708f
///
/// fuse::Angle a2 = fuse::radians(3.141592654f);
/// float degrees = a2.asDegrees(); // 180.0f
///
/// using namespace literals;
/// Angle a3 = 10_deg;   // 10 degrees
/// Angle a4 = 1.5_deg;  // 1.5 degrees
/// Angle a5 = 1_rad;    // 1 radians
/// Angle a6 = 3.14_rad; // 3.14 radians
/// @endcode
///
////////////////////////////////////////////////////////////
class Angle final {
public:
    /// @brief Constant for angle with value 0.
    static const Angle kZero;

    /// @brief Default constructor.
    /// Create a angle of 0 degree.
    constexpr Angle() = default;

    [[nodiscard]] constexpr auto operator<=>(const Angle&) const = default;

    /// @return Return the negation value of the angle.
    [[nodiscard]] constexpr Angle operator-() const noexcept { return -mValue; }

    constexpr Angle& operator+=(Angle rhs) noexcept {
        mValue += rhs.mValue;
        return *this;
    }

    constexpr Angle& operator-=(Angle rhs) noexcept {
        mValue -= rhs.mValue;
        return *this;
    }

    constexpr Angle& operator*=(float rhs) noexcept {
        mValue *= rhs;
        return *this;
    }

    constexpr Angle& operator/=(float rhs) noexcept {
        mValue /= rhs;
        return *this;
    }

    [[nodiscard]] constexpr Angle operator+(Angle rhs) const noexcept {
        return mValue + rhs.mValue;
    }

    [[nodiscard]] constexpr Angle operator-(Angle rhs) const noexcept {
        return mValue - rhs.mValue;
    }

    [[nodiscard]] constexpr Angle operator*(float rhs) const noexcept { return mValue * rhs; }

    [[nodiscard]] constexpr float operator/(Angle rhs) const noexcept {
        return mValue / rhs.mValue;
    }

    [[nodiscard]] constexpr Angle operator/(float rhs) const noexcept { return mValue / rhs; }

    /// @return Return the value of the angle in degree.
    [[nodiscard]] constexpr float asDegrees() const noexcept { return mValue; }

    /// @return Return the value of the angle in radian.
    [[nodiscard]] constexpr float asRadians() const noexcept {
        return mValue / 180.F * std::numbers::pi_v<float>;
    }

    /// @brief Wrap the angle in the range [-359, 359] degrees.
    /// @return Unsigned angle, wrapped to [-359, 359] degrees.
    [[nodiscard]] Angle wrap() const noexcept { return std::fmod(mValue, 360.F); }

    /// @brief Wrap the angle in the range [-180, 180]
    /// @return Unsigned angle, wrapped to [-180, 180]
    [[nodiscard]] Angle wrapSigned() const noexcept {
        float remainder = std::fmod(mValue + 180.f, 360.F);
        if (remainder < 0.0f) {
            remainder += 360.f;
        }
        remainder -= 180.f;
        return remainder;
    }

    /// @brief Wrap the angle in the range [0, 360]
    /// @return Unsigned angle, wrapped to [0, 360]
    [[nodiscard]] Angle wrapUnsigned() const noexcept {
        const float remainder = std::fmod(mValue, 360.F);
        return remainder < 0 ? remainder + 360.F : remainder;
    }

private:
    friend constexpr Angle degrees(float degree) noexcept;
    friend constexpr Angle radians(float radian) noexcept;

    /// @brief Construct a new Angle from a value (degrees).
    ///
    /// @param radian The value in degrees used to create the angle.
    ///
    /// @details This constructor is private to ensure that the angle is always created
    /// using the static methods `Degrees` or `Radians`.
    /// @note This constructor is not intended to be used directly by users of the Angle class.
    constexpr Angle(float value)
        : mValue(value) {}

    /// The angle in degrees.
    float mValue{};
};

inline constexpr Angle Angle::kZero;

/// @brief Create a new Angle from a value in degree.
/// @param degree The value in degree used to create the angle.
/// @return The new Angle.
/// @see radians()
[[nodiscard]] constexpr Angle degrees(float degree) noexcept { return {degree}; }

/// @brief Create a new Angle from a value in radian.
/// @param radian The value in radian used to create the angle.
/// @return The new Angle.
/// @see degrees()
[[nodiscard]] constexpr Angle radians(float radian) noexcept {
    return {radian * 180.F / std::numbers::pi_v<float>};
}

/// @relates Angle
[[nodiscard]] constexpr Angle operator*(float lhs, Angle rhs) noexcept { return rhs * lhs; }

namespace literals {

/// @relates fuse::Angle
/// @brief User-defined literal for degrees.
/// @param angle The angle value in degrees.
/// @return An Angle object representing the angle in degrees.
constexpr Angle operator""_deg(long double angle) { return degrees(static_cast<float>(angle)); }

/// @relates fuse::Angle
/// @brief User-defined literal for degrees.
/// @param angle The angle value in degrees.
/// @return An Angle object representing the angle in degrees.
constexpr Angle operator""_deg(unsigned long long angle) {
    return degrees(static_cast<float>(angle));
}

/// @relates fuse::Angle
/// @brief User-defined literal for radians.
/// @param angle The angle value in radians.
/// @return An Angle object representing the angle in radians.
constexpr Angle operator""_rad(long double angle) { return radians(static_cast<float>(angle)); }

/// @relates fuse::Angle
/// @brief User-defined literal for radians.
/// @param angle The angle value in radians.
/// @return An Angle object representing the angle in radians.
constexpr Angle operator""_rad(unsigned long long angle) {
    return radians(static_cast<float>(angle));
}

} // namespace literals

} // namespace fuse

/// @brief std extention for fuse.
namespace std {

/// @brief Compute the cosine of an angle.
inline float cos(fuse::Angle a) { return std::cos(a.asRadians()); }

/// @brief Compute the sine of an angle.
inline float sin(fuse::Angle a) { return std::sin(a.asRadians()); }

/// @brief Compute the tangent of an angle.
inline float tan(fuse::Angle a) { return std::tan(a.asRadians()); }

} // namespace std
