#include "Matrix3D.h"

Matrix3D::Matrix3D(const Vector3D& row0, const Vector3D& row1, const Vector3D& row2) {
    data[0] = row0.X;
    data[1] = row1.X;
    data[2] = row2.X;

    data[3] = row0.Y;
    data[4] = row1.Y;
    data[5] = row2.Y;

    data[6] = row0.Z;
    data[7] = row1.Z;
    data[8] = row2.Z;
}

Vector3D Matrix3D::operator*(const Vector3D& vector) const {
    return Vector3D{
        data[0] * vector.X + data[3] * vector.Y + data[6] * vector.Z,
        data[1] * vector.X + data[4] * vector.Y + data[7] * vector.Z,
        data[2] * vector.X + data[5] * vector.Y + data[8] * vector.Z
    };
}

Matrix3D Matrix3D::get_transposed() const {
    Matrix3D transposed;

    transposed.data[0] = data[0];
    transposed.data[3] = data[1];
    transposed.data[6] = data[2];

    transposed.data[1] = data[3];
    transposed.data[4] = data[4];
    transposed.data[7] = data[5];

    transposed.data[2] = data[6];
    transposed.data[5] = data[7];
    transposed.data[8] = data[8];

    return transposed;
}
