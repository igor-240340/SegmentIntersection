#include <cmath>

#include "Vector3D.h"

const Vector3D Vector3D::zero{ 0.0, 0.0, 0.0 };

Vector3D::Vector3D(double x, double y, double z) {
    this->X = x;
    this->Y = y;
    this->Z = z;
}

Vector3D Vector3D::operator+(const Vector3D& b) const {
    return Vector3D(X + b.X, Y + b.Y, Z + b.Z);
}

Vector3D Vector3D::operator-(const Vector3D& b) const {
    return Vector3D(X - b.X, Y - b.Y, Z - b.Z);
}

Vector3D Vector3D::operator*(double scalar) const {
    return Vector3D(X * scalar, Y * scalar, Z * scalar);
}

Vector3D Vector3D::operator/(double scalar) const {
    const double scalar_inv = 1.0 / scalar;
    return Vector3D(X * scalar_inv, Y * scalar_inv, Z * scalar_inv);
}

double Vector3D::length() const {
    return std::sqrt(X * X + Y * Y + Z * Z);
}

Vector3D Vector3D::get_normalized() const {
    return *this / length();
}

Vector3D Vector3D::cross(const Vector3D& a, const Vector3D& b) {
    return Vector3D(a.Y * b.Z - a.Z * b.Y, a.Z * b.X - a.X * b.Z, a.X * b.Y - a.Y * b.X);
}

double Vector3D::dot(const Vector3D& a, const Vector3D& b) {
    return a.X * b.X + a.Y * b.Y + a.Z * b.Z;
}
