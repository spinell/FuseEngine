#pragma once

namespace fuse {

/// @brief A four dimensional vector.
class Vec4 final {
public:
    static const Vec4 kZero;  ///< The zero vector   (0, 0, 0, 0)
    static const Vec4 kAxisX; ///< The unit X vector (1, 0, 0, 0), usually facing right
    static const Vec4 kAxisY; ///< The unit Y vector (0, 1, 0, 0), usually facing up
    static const Vec4 kAxisZ; ///< The unit Z vector (0, 0, 1, 0), usually facing away the screen

    /// @brief Default constructor (Does not initialize members).
    constexpr Vec4() = default;

    /// @brief Construct the vector from its coordinates
    /// @param x x component of the vector
    /// @param y y component of the vector
    /// @param z z component of the vector
    /// @param w w component of the vector
    constexpr Vec4(float x, float y, float z, float w = 1.0f)
        : x(x)
        , y(y)
        , z(z)
        , w(w) {}

    /// @brief Strict comparaison of this vector with another vector.
    [[nodiscard]] constexpr bool operator==(const Vec4& rhs) const noexcept = default;

    constexpr Vec4& operator+=(const Vec4& rhs) noexcept { return *this = *this + rhs; }

    constexpr Vec4& operator-=(const Vec4& rhs) noexcept { return *this = *this - rhs; }

    constexpr Vec4& operator*=(float rhs) noexcept { return *this = *this * rhs; }

    constexpr Vec4& operator/=(float rhs) noexcept { return *this = *this / rhs; }

    [[nodiscard]] constexpr Vec4 operator+(const Vec4& rhs) const noexcept {
        return {x + rhs.x, y + rhs.y, z + rhs.z, w + rhs.w};
    }

    [[nodiscard]] constexpr Vec4 operator-(const Vec4& rhs) const noexcept {
        return {x - rhs.x, y - rhs.y, z - rhs.z, w - rhs.w};
    }

    [[nodiscard]] constexpr Vec4 operator*(float rhs) const noexcept {
        return {x * rhs, y * rhs, z * rhs, w * rhs};
    }

    [[nodiscard]] constexpr friend Vec4 operator*(float lhs, const Vec4& rhs) noexcept {
        return rhs * lhs;
    }

    [[nodiscard]] constexpr Vec4 operator/(float rhs) const noexcept {
        const float inv = 1.0F / rhs;
        return *this * inv;
    }

    /// @brief Calculate the dot product of this vector with another vector.
    [[nodiscard]] constexpr float dotProduct(const Vec4& rhs) const noexcept {
        return (x * rhs.x) + (y * rhs.y) + (z * rhs.z) + (w * rhs.w);
    }

    float x; ///< The x component of the vector
    float y; ///< The y component of the vector
    float z; ///< The x component of the vector
    float w; ///< The z component of the vector

}; // class Vector4

static_assert(sizeof(Vec4) == 16, "Vec4 size must be 16 bytes.");

inline constexpr Vec4 Vec4::kZero  = {0.F, 0.F, 0.F, 0.F};
inline constexpr Vec4 Vec4::kAxisX = {1.F, 0.F, 0.F, 0.F};
inline constexpr Vec4 Vec4::kAxisY = {0.F, 1.F, 0.F, 0.F};
inline constexpr Vec4 Vec4::kAxisZ = {0.F, 0.F, 1.F, 0.F};

} // namespace fuse
