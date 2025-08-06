#pragma once
#include "Vec4.h"

#include <algorithm>
#include <cassert>

namespace fuse {

/// @brief 4 dimensional matrix.
/// This class represents a 4x4 matrix, which is commonly used in 3D graphics for transformations.
///
/// It can be used for operations such as translation, rotation, and scaling in 3D space.
///
/// The matrix is stored in column-major order, which is the standard for OpenGL and many
/// other graphics APIs.
class Mat4 {
public:
    static constexpr unsigned kNbRow = 4;
    static constexpr unsigned kNbCol = 4;
    static constexpr unsigned kSize  = kNbRow * kNbCol;
    static const Mat4         kZero;     ///< The zero matrix.
    static const Mat4         kIdentity; ///< The identity matrix.

    Mat4() noexcept = default;

    /// @brief Construct a 4x4 matrix by spefified which values.
    // clang-format off
    constexpr Mat4(float m00, float m01, float m02, float m03,
                   float m10, float m11, float m12, float m13,
                   float m20, float m21, float m22, float m23,
                   float m30, float m31, float m32, float m33) noexcept
        : Mat4(Vec4(m00, m01, m02, m03),
               Vec4(m10, m11, m12, m13),
               Vec4(m20, m21, m22, m23),
               Vec4(m30, m31, m32, m33)) {}

    // clang-format on

    /// @brief Construct a 4x4 matrix from an array of 16 values.
    ///
    /// The value's layout in the array is assuming to be row layout.
    ///
    /// For example, the array
    /// <b>[0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15]</b>
    /// will result in matrix
    /// @f$
    /// \begin{bmatrix}
    ///  0 &  1 &  2 &  3 \\
    ///  4 &  5 &  6 &  7 \\
    ///  8 &  9 & 10 & 11 \\
    /// 12 & 13 & 14 & 15
    /// \end{bmatrix}
    /// @f$
    ///
    /// @param data The value used to construct the matrix.
    constexpr Mat4(const float data[kSize]) noexcept
        : Mat4(Vec4(data[0], data[1], data[2], data[3]),
               Vec4(data[4], data[5], data[6], data[7]),
               Vec4(data[8], data[9], data[10], data[11]),
               Vec4(data[12], data[13], data[14], data[15])) {}

    /// @brief Construct a 4x4 matrix from 4 vectors.
    /// @param row1 The first column of the matrix.
    /// @param row2 The second column of the matrix.
    /// @param row3 The third column of the matrix.
    /// @param row4 The fourth column of the matrix.
    constexpr Mat4(const Vec4& row1,
                   const Vec4& row2,
                   const Vec4& row3,
                   const Vec4& row4) noexcept {
        // clang-format off
        mData[0][0] = row1.x; mData[0][1] = row1.y; mData[0][2] = row1.z; mData[0][3] = row1.w;
        mData[1][0] = row2.x; mData[1][1] = row2.y; mData[1][2] = row2.z; mData[1][3] = row2.w;
        mData[2][0] = row3.x; mData[2][1] = row3.y; mData[2][2] = row3.z; mData[2][3] = row3.w;
        mData[3][0] = row4.x; mData[3][1] = row4.y; mData[3][2] = row4.z; mData[3][3] = row4.w;
        // clang-format on
    }

    /// @brief Strict comparion between this matrix and another matrix.
    [[nodiscard]] constexpr bool operator==(const Mat4&) const noexcept = default;

    /// @brief Direct access matrix element by row and column
    /// @pre @b row and @b col must be between <b>[0,3]</b>
    /// @param row The row index.
    /// @param col The col index.
    /// @return Return the matrix element at <b>(row,col)</b>
#if 0
    constexpr float& operator[](unsigned row, unsigned col) noexcept {
        assert(row < kNbRow);
        assert(col < kNbCol);
        return mData[row, col];
    }

    /// @copydoc operator[]
    constexpr const float& operator[](unsigned row, unsigned col) const noexcept {
        assert(row < kNbRow);
        assert(col < kNbCol);
        return mData[row][col];
    }
#endif

    /// @copydoc operator[]
    constexpr float& operator()(unsigned row, unsigned col) noexcept {
        assert(row < kNbRow);
        assert(col < kNbCol);
        return mData[row][col];
    }

    /// @copydoc operator[]
    [[nodiscard]] constexpr const float& operator()(unsigned row, unsigned col) const noexcept {
        assert(row < kNbRow);
        assert(col < kNbCol);
        return mData[row][col];
    }

    [[nodiscard]] constexpr Mat4 operator*(float scalar) const noexcept;
    [[nodiscard]] constexpr Vec4 operator*(const Vec4& vec) const noexcept;
    [[nodiscard]] constexpr Mat4 operator*(const Mat4& other) const noexcept;

    /// @brief Calculates the determinant of the matrix
    /// This function computes the determinant of the 4x4 matrix using a cofactor expansion.
    /// The determinant is a scalar value that can be used to determine if the matrix is invertible.
    /// If the determinant is zero, the matrix is singular (not invertible).
    /// \f[
    /// \text{det}(M) = m_{00} \cdot \text{det}(M_{00}) - m_{01} \cdot \text{det}(M_{01}) + m_{02} \cdot \text{det}(M_{02}) - m_{03} \cdot \text{det}(M_{03})
    /// \f]
    /// where \( M_{ij} \) is the 3x3 matrix obtained by removing the i-th row and j-th column from M.
    /// @note The determinant is used in various applications, including solving systems of linear equations, finding the
    /// inverse of a matrix, and determining the volume of a parallelepiped defined by the matrix's columns.
    /// @pre The matrix must be a valid 4x4 matrix.
    /// @return The determinant of the matrix.
    [[nodiscard]] float determinant() const noexcept;

    /// @brief Check if the matrix is an affine transformation matrix.
    /// An affine transformation matrix has the last row as (0, 0, 0, 1).
    /// This means it can represent translations, rotations, and scalings without perspective distortion.
    /// @return True if the matrix is affine, false otherwise.
    [[nodiscard]] constexpr bool isAffine() const noexcept {
        return mData[3][0] == 0 && mData[3][1] == 0 && mData[3][2] == 0 && mData[3][3] == 1;
    }

    /// @brief Trqnspose this matrix in-place.
    constexpr Mat4& transpose() noexcept;

    /// @brief Return the tranpose of this matrix.
    constexpr [[nodiscard]] Mat4 transposed() const noexcept;

    [[nodiscard]] float* ptr() noexcept { return reinterpret_cast<float*>(mData); }

    [[nodiscard]] const float* ptr() const noexcept {
        return reinterpret_cast<const float*>(mData);
    }

private:
    float mData[4][4];
};

inline constexpr Mat4 Mat4::kZero(Vec4(0.F, 0.F, 0.F, 0.F),
                                  Vec4(0.F, 0.F, 0.F, 0.F),
                                  Vec4(0.F, 0.F, 0.F, 0.F),
                                  Vec4(0.F, 0.F, 0.F, 0.F));
inline constexpr Mat4 Mat4::kIdentity(Vec4(1.F, 0.F, 0.F, 0.F),
                                      Vec4(0.F, 1.F, 0.F, 0.F),
                                      Vec4(0.F, 0.F, 1.F, 0.F),
                                      Vec4(0.F, 0.F, 0.F, 1.F));

constexpr Mat4 Mat4::operator*(float scalar) const noexcept {
    Mat4 result;
    for (unsigned row = 0; row < Mat4::kNbRow; ++row) {
        for (unsigned col = 0; col < Mat4::kNbCol; ++col) {
            result.mData[row][col] = mData[row][col] * scalar;
        };
    }
    return result;
}

constexpr Vec4 Mat4::operator*(const Vec4& vec) const noexcept {
    return {
      mData[0][0] * vec.x + mData[0][1] * vec.y + mData[0][2] * vec.z + mData[0][3] * vec.w,
      mData[1][0] * vec.x + mData[1][1] * vec.y + mData[1][2] * vec.z + mData[1][3] * vec.w,
      mData[2][0] * vec.x + mData[2][1] * vec.y + mData[2][2] * vec.z + mData[2][3] * vec.w,
      mData[3][0] * vec.x + mData[3][1] * vec.y + mData[3][2] * vec.z + mData[3][3] * vec.w,
    };
}

constexpr Mat4 Mat4::operator*(const Mat4& other) const noexcept {
    Mat4 result;
    for (int row = 0; row < kNbRow; row++) {
        for (int col = 0; col < kNbCol; col++) {
            float temp = 0;
            for (int inner = 0; inner < 4; inner++) {
                temp += mData[row][inner] * other.mData[inner][col];
            }
            result.mData[row][col] = temp;
        }
    }
    return result;
}

/// @relates Mat4
inline Mat4 operator*(float scalar, const Mat4& mat) { return mat * scalar; }

constexpr Mat4& Mat4::transpose() noexcept {
    std::swap(mData[0][1], mData[1][0]);
    std::swap(mData[0][2], mData[2][0]);
    std::swap(mData[0][3], mData[3][0]);
    std::swap(mData[1][2], mData[2][1]);
    std::swap(mData[1][3], mData[3][1]);
    std::swap(mData[2][3], mData[3][2]);
    return *this;
}

constexpr Mat4 Mat4::transposed() const noexcept {
    Mat4 mat = *this;
    mat.transpose();
    return mat;
}

} // namespace fuse
