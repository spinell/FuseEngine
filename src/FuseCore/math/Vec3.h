#pragma once
#include "Angle.h"

#include <cassert>

namespace fuse {

/// @brief Vector in 3 dimentions space.
struct Vec3 {
public:
    static const Vec3 kZero;     ///< The zero vector (0, 0, 0)
    static const Vec3 kAxisX;    ///< The X unit vector (1, 0, 0), usually facing right
    static const Vec3 kAxisXNeg; ///< The X unit vector (1, 0, 0), usually facing left
    static const Vec3 kAxisY;    ///< The Y unit vector (0, 1, 0), usually facing up
    static const Vec3 kAxisYNeg; ///< The Y unit vector (0, 1, 0), usually facing down
    static const Vec3 kAxisZ;    ///< The Z unit vector (0, 0, 1), usually facing away the screen
    static const Vec3 kAxisZNeg; ///< The Z unit vector (0, 0, 1), usually facing into the screen

    float x; ///< The x component of the vector.
    float y; ///< The y component of the vector.
    float z; ///< The z component of the vector.

    /// @brief Default constructor initializes to (0, 0, 0).
    [[nodiscard]] constexpr Vec3() noexcept = default;

    /// @brief Constructor that initializes the vector components with the same value.
    /// @param value The value used to initialize all components of the vector.
    [[nodiscard]] constexpr explicit Vec3(float value) noexcept
        : x(value)
        , y(value)
        , z(value) {}

    /// @brief Constructor that initializes the vector with given x, y, and z values.
    /// @param x The x component of the vector.
    /// @param y The y component of the vector.
    /// @param z The z component of the vector.
    [[nodiscard]] constexpr Vec3(float x, float y, float z) noexcept
        : x(x)
        , y(y)
        , z(z) {}

    [[nodiscard]] constexpr bool operator==(const Vec3 & rhs) const noexcept = default;

    /// @brief Negates the vector, flipping the sign of each component.
    /// @return A new Vec3 with each component negated.
    [[nodiscard]] constexpr Vec3 operator-() const noexcept { return {-x, -y, -z}; }

    /// @brief Gets the angle between this vector and another vector.
    ///
    /// This function return the smallest angle between this vector and vector \p other
    /// in range [0, 180] degree ([0, PI]).
    ///
    /// The angle is calculated using the dot product and the lengths of the vectors.
    /// \f[
    /// \text{angle}(a, b) = \arccos\left(\frac{a \cdot b}{|a| |b|}\right)
    /// \f]
    ///
    /// \warning Both vector must have a lenght > 0.
    /// @param other The other vector to calculate the angle with.
    /// @return The angle between the two vectors.
    [[nodiscard]] Angle angleBetween(const Vec3& other) const noexcept {
        return fuse::radians(std::acos(normalized().dot(other.normalized())));
    }

    /// @brief Compute the cross product of this vector with another vector by fallowing right-hand rule.
    ///
    ///  In 3D space, the cross product of 2 vector result to another
    ///  3D vector orthogonal (perpendicular) to both vector.
    ///
    ///  The cross product is defined as:
    ///  \f[
    ///  \text{cross}(a, b) = (a.y \cdot b.z - a.z \cdot b.y, a.z \cdot b.x - a.x \cdot b.z, a.x \cdot b.y - a.y \cdot b.x)
    ///  \f]
    ///
    /// @warning Cross product between 2 vectors are not cumutative.
    ///
    ///     Which means, a x b != b x a.
    ///     In fact, a x b = -(b x a)
    ///
    /// By definition, |a x b| = |a| |b| sin(t)
    ///      - |a x b| : The length of resulting vector
    ///      - |a|     : The length of vector a
    ///      - |b|     : The length of vector b
    ///      - sin(t)  : The sinus of the angle between vector a and b.
    ///
    /// @note
    ///        - The cross product of two parallel vectors is zero.
    ///          - If the vectors are parallel, the cross product is zero.
    ///          - If the vectors are anti-parallel (pointing in opposite directions), the cross product is also zero.
    ///        - If both vectors are normalized, the cross product result will be a normalized perpenticular vector.
    /// @remarks This function use the right-hand rule.
    ///       The direction of the resulting vector is determined by the right-hand rule.
    ///       Assuming, positive X is right and possitive Y is up,
    ///       positive Z go away from the screen and negative Z go into the screen.
    ///       - (1,0,0) x (0,1,0) = (0,0,1)
    ///       - (0,1,0) x (1,0,0) = (0,0,-1)
    /// @pre  The lenght of either, this vector and @p other must not be 0.
    /// @param other The other vector to calculate the cross product with.
    /// @return The cross product of the two vectors.
    [[nodiscard]] Vec3 crossRH(const Vec3& other) const noexcept {
        return {y * other.z - z * other.y, z * other.x - x * other.z, x * other.y - y * other.x};
    }

    /// @brief Compute the cross product of this vector with another vector by fallowing left-hand rule.
    /// @param other The other vector to calculate the cross product with.
    /// @return The cross product of the two vectors.
    /// @see  crossRH(const Vec3& other) const
    [[nodiscard]] Vec3 crossLH(const Vec3& other) const noexcept { return other.crossRH(*this); }

    /// @brief Returns the distance to another vector.
    ///
    ///	@warning
    ///		This operation requires a square root and is expensive in
    ///		terms of CPU operations. If you don't need to know the exact
    ///		distance (e.g. for just comparing distances) use distanceSquared()
    ///		instead.
    /// @return The distance to another vector.
    [[nodiscard]] float distance(const Vec3& rhs) const;

    /// @brief Returns the square of the distance to another vector.
    ///	@remarks
    ///		This method is for efficiency - calculating the actual
    ///		distance to another vector requires a square root, which is
    ///		expensive in terms of the operations required. This method
    ///		returns the square of the distance to another vector, i.e.
    ///		the same as the distance but before the square root is taken.
    ///		Use this if you want to find the longest / shortest distance
    ///		without incurring the square root.
    /// @return The square distance to another vector.
    [[nodiscard]] float distanceSquared(const Vec3& rhs) const noexcept;

    /// @brief Calculates the dot (scalar) product of this vector with another vector.
    /// @details The dot product is a measure of how parallel two vectors are.
    // It is calculated as the sum of the products of their corresponding components.
    // \f[
    // \text{dot}(a, b) = a.x \cdot b.x + a.y \cdot b.y + a.z \cdot b.z
    // \f]
    /// @details If either vector is a zero vector, the dot product will be zero.
    /// @remarks  - If the vectors are normalized (unit vectors), the dot product is equal to the cosine of the angle between them.
    ///           - If the vectors are orthogonal (perpendicular), the dot product is zero.
    ///           - If both vectors are non-zero, the dot product is equal to the cosine of the angle between them multiplied by the product of their lengths.
    ///           - If the vectors are not normalized, the dot product is equal to the cosine of the angle between them multiplied by the product of their lengths.
    ///           - If the vectors are parallel, the dot product is equal to the product of their lengths.
    ///           - If the vectors are anti-parallel (pointing in opposite directions), the dot product is negative and equal to the negative product of their lengths.
    /// @pre         The vectors should not be zero vectors for meaningful results.
    /// @param other The other vector to calculate the dot product with.
    /// @note        The dot product is commutative, meaning \p a.dot(b) is equal to \p b.dot(a).
    /// \remarks     By definition, a dot b = |a| |b| cos(a)
    ///                 -  a dot b  : The dot product of a and b.
    ///                 - |a|     : The length of vector a
    ///                 - |b|     : The length of vector b
    ///                 - cos(a)  : The cosinus of the angle between vector a and b.
    /// @return      The dot product of the two vectors.
    [[nodiscard]] float dot(const Vec3& other) const noexcept {
        return x * other.x + y * other.y + z * other.z;
    }

    /// \brief Compute the lenght (magnitude) of this vector.
    ///
    ///	\warning This operation requires a square root and is expensive in
    ///			 terms of CPU operations. If you don't need to know the exact
    ///			 length (e.g. for just comparing lengths) use lengthSq()
    ///			 instead.
    ///
    /// \return Returns the lenght of this vector.
    [[nodiscard]] float length() const noexcept { return std::sqrt(dot(*this)); }

    /// \brief Compute the square lenght (magnitude) of this vector.
    ///
    ///	\remarks
    ///		This method is for efficiency - calculating the actual
    ///		lenght of a vector requires a square root, which is
    ///		expensive in terms of the operations required. This method
    ///		returns the square of the lenght, i.e.
    ///		the same as the lenght but before the square root is taken.
    ///		Use this if you want to find the longest / shortest lenght
    ///		without incurring the square root.
    ///
    /// \return Returns the square lenght of this vector.
    [[nodiscard]] float lengthSq() const noexcept { return dot(*this); }

    /// @brief Normalize this vector.
    /// @copydetails normalized()
    /// \return This vector with same direction but a length of 1.
    Vec3& normalize() noexcept {
        *this = normalized();
        return *this;
    }

    /// Compute the normalized vector of this vector.
    ///
    /// @remarks This method normalises the vector such that it's
    ///          length / magnitude is 1. The result is called a unit vector.
    ///
    /// @pre @c *this is no zero vector.
    ///
    /// @return A vector with same direction but a length of 1.
    [[nodiscard]] Vec3 normalized() const noexcept {
        const float len = length();
        assert(len != 0.F && "Cannot normalize a zero vector");
        return {x / len, y / len, z / len};
    }

    /// @brief Compute the projection of this vector onto another vector.
    ///
    /// Projection is a method of finding components of a vector along the direction of a second vector.
    /// By projecting a vector on another vector we obtain a vector which represents the component of the
    /// first vector along the direction of the second vector. It represents the length of the shadow of a
    /// vector over another vector.
    ///
    /// For example, if you have two vectors:
    ///
    ///     a = [1, 1, 0]
    ///     b = [2, 0, 0]
    ///     the projection of a onto b is the vector [1,0,0], that lies along b and represents
    ///     how much of a is in the direction of b.
    ///
    /// It is calculated as the dot product of the first vector with the second vector, divided by the square of the
    /// length of the second vector, multiplied by the second vector.
    /// @f[
    /// \text{proj}_{\text{other}}(\text{this}) = \frac{\text{this} \cdot \text{other}}{\text{other} \cdot \text{other}} \cdot \text{other}
    /// @f]
    /// @warning If the @p other vector is a zero vector, the projection is undefined.
    /// @pre    @p other must not have length zero.
    /// @note    The @p other vector does not need to be normalized (The lenght of @p other vector does not affect the projection).
    /// @note    The direction of @p other vector does not matter. [1,0,0] and [-1,0,0] will yield the same projection.
    /// @remarks If the projection is zero, the two vectors are orthogonal (perpendicular)
    /// @param  other Vector being projected onto. Need not be normalized.
    /// @return  The projection of this vector into vector @p other.
    [[nodiscard]] Vec3 projecteTo(const Vec3& other) const noexcept;

    /// @brief Compute the perpenticular projection of this vector onto another vector.
    ///
    ///  The perpenticular vector is a vector that is orthogonal (perpendicular) to the other
    ///  vector and lies in the plane defined by this vector and the other vector.
    ///
    ///  It is calculated as the difference between this vector and its projection onto the other vector.
    ///  \f[
    ///  \text{perp}_{\text{other}}(\text{this}) = \text{this} - \text{proj}_{\text{other}}(\text{this})
    ///  \f]
    ///
    /// @note
    ///  The perpenticular vector is orthogonal (perpendicular) to the other vector.
    ///  It lies in the plane defined by this vector and the other vector.
    ///  The perpenticular vector is the component of this vector that is orthogonal to
    ///  the other vector.
    ///  It is the vector that is left after removing the projection of this vector onto the
    ///  other vector.
    /// @pre  The @p other vector must not be a zero vector.
    /// @param  other Vector being projected onto. Need not be normalized.
    /// @return
    [[nodiscard]] Vec3 perpenticularTo(const Vec3& other) const noexcept;

    /// @brief Returns a pointer to the underlying data of the vector.
    /// @return A pointer to the first element of the vector's data.
    [[nodiscard]] float* ptr() noexcept { return &x; }

    /// @copydoc ptr()
    [[nodiscard]] const float* ptr() const noexcept { return &x; }
};

// define all static constant.
// This is done here to avoid the need for a separate .cpp file.
//
inline constexpr Vec3 Vec3::kZero(0.F, 0.F, 0.F);
inline constexpr Vec3 Vec3::kAxisX(1.F, 0.F, 0.F);
inline constexpr Vec3 Vec3::kAxisXNeg = -kAxisX;
inline constexpr Vec3 Vec3::kAxisY(0.F, 1.F, 0.F);
inline constexpr Vec3 Vec3::kAxisYNeg = -kAxisY;
inline constexpr Vec3 Vec3::kAxisZ(0.F, 0.F, 1.F);
inline constexpr Vec3 Vec3::kAxisZNeg = -kAxisZ;

static_assert(sizeof(Vec3) == 12, "Vec3 size must be 12 bytes.");

/// @relates Vec3
/// @brief Adds two vectors component-wise.
/// @param lhs The left-hand side Vec3.
/// @param rhs The right-hand side Vec3.
/// @return A new Vec3 that is the sum of the two vectors.
[[nodiscard]] constexpr Vec3 operator+(const Vec3& lhs, const Vec3& rhs) noexcept {
    return {lhs.x + rhs.x, lhs.y + rhs.y, lhs.z + rhs.z};
}

/// @relates Vec3
/// @brief Subtracts two vectors component-wise.
/// @param lhs The left-hand side Vec3.
/// @param rhs The right-hand side Vec3.
/// @return A new Vec3 that is the difference of the two vectors.
[[nodiscard]] constexpr Vec3 operator-(const Vec3& lhs, const Vec3& rhs) noexcept {
    return {lhs.x - rhs.x, lhs.y - rhs.y, lhs.z - rhs.z};
}

/// @relates Vec3
/// @brief Multiply a vector by a scalar.
/// @param lhs The Vec3 to be multiplied.
/// @param rhs The scalar value to multiply the vector by.
/// @return A new Vec3 that is the product of the vector and the scalar.
[[nodiscard]] constexpr Vec3 operator*(const Vec3& rhs, float lhs) noexcept {
    return {rhs.x * lhs, rhs.y * lhs, rhs.z * lhs};
}

/// @relates Vec3
/// @copybrief operator*(const Vec3& rhs, float lhs)
/// @param lhs The scalar value to multiply the vector by.
/// @param rhs  The Vec3 to be multiplied.
/// @return A new Vec3 that is the product of the vector and the scalar.
[[nodiscard]] constexpr Vec3 operator*(float lhs, const Vec3& rhs) noexcept { return rhs * lhs; }

/// @relates Vec3
/// @brief Divide a vector by a scalar.
/// @param lhs The Vec3 to be divided.
/// @param rhs The scalar value to divide the vector by.
/// @return A new Vec3 that is the result of dividing the vector by the scalar.
[[nodiscard]] constexpr Vec3 operator/(const Vec3& lhs, float rhs) noexcept {
    assert(rhs != 0.F && "Division by zero in Vec3 operator/");
    const float inv = 1.F / rhs;
    return {lhs.x * inv, lhs.y * inv, lhs.z * inv};
}

/// @relates Vec3
/// @brief Multiply a vector by a scalar and assign the result to the vector.
/// @param lhs The Vec3 to be multiplied.
/// @param rhs The scalar value to multiply the vector by.
/// @return A new Vec3 that is the result of multiplying the vector by the scalar.
constexpr Vec3& operator*=(Vec3& lhs, float rhs) noexcept {
    lhs.x *= rhs;
    lhs.y *= rhs;
    lhs.z *= rhs;
    return lhs;
}

/// @relates Vec3
/// @brief Divide a vector by a scalar and assign the result to the vector.
/// @param lhs The Vec3 to be divided.
/// @param rhs The scalar value to divide the vector by.
/// @pre \p rhs must not be zero. Division by zero is undefined behavior.
/// @return A new Vec3 that is the result of dividing the vector by the scalar.
constexpr Vec3& operator/=(Vec3& lhs, float rhs) noexcept {
    assert(rhs != 0.F && "Division by zero in Vec3 operator/=");
    const float inv = 1.F / rhs;
    lhs.x *= inv;
    lhs.y *= inv;
    lhs.z *= inv;
    return lhs;
}

/// @relates Vec3
/// @brief Adds two vectors component-wise and assigns the result to the first vector.
/// @param lhs The Vec3 to be added to.
/// @param rhs The Vec3 to add.
/// @return A new Vec3 that is the result of adding the two vectors.
constexpr Vec3& operator+=(Vec3& lhs, const Vec3& rhs) noexcept { return lhs = lhs + rhs; }

/// @relates Vec3
/// @brief Subtracts two vectors component-wise and assigns the result to the first vector.
/// @param lhs The Vec3 to be subtracted from.
/// @param rhs The Vec3 to subtract.
/// @return A new Vec3 that is the result of subtracting the two vectors.
constexpr Vec3& operator-=(Vec3& lhs, const Vec3& rhs) noexcept { return lhs = lhs - rhs; }

inline float Vec3::distance(const Vec3& rhs) const { return (*this - rhs).length(); }

inline float Vec3::distanceSquared(const Vec3& rhs) const noexcept {
    return (*this - rhs).lengthSq();
}

inline Vec3 Vec3::projecteTo(const Vec3& other) const noexcept {
    assert(other != Vec3::kZero);
    // proj = (a dot b / b dot b) * b
    return dot(other) / other.dot(other) * other;
}

inline Vec3 Vec3::perpenticularTo(const Vec3& other) const noexcept {
    assert(other != Vec3::kZero);
    // perp = a - proj
    return *this - projecteTo(other);
}

} // namespace fuse
