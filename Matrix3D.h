#pragma once

#include <array>

#include "Vector3D.h"

class Matrix3D {
public:
    Matrix3D() = default;
    Matrix3D(const Vector3D& row0, const Vector3D& row1, const Vector3D& row2);
    ~Matrix3D() = default;

    Vector3D operator*(const Vector3D& vector) const;

    Matrix3D get_transposed() const;

private:
    std::array<double, 9> data; // Column-major.
};
