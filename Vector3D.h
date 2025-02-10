#pragma once

class Vector3D {
public:
    double X;
    double Y;
    double Z;

public:
    static const Vector3D zero;

public:
    Vector3D() = default;
    Vector3D(double x, double y, double z);
    ~Vector3D() = default;

    Vector3D operator+(const Vector3D& b) const;
    Vector3D operator-(const Vector3D& b) const;
    Vector3D operator*(double scalar) const;
    Vector3D operator/(double scalar) const;

    double length() const;
    Vector3D get_normalized() const;

    static Vector3D cross(const Vector3D& a, const Vector3D& b);
    static double dot(const Vector3D& a, const Vector3D& b);
};
