#pragma once

#include <optional>

#include "Vector3D.h"

class Segment3D {
public:
    Vector3D start;
    Vector3D end;

public:
    static std::optional<Vector3D> Intersect(const Segment3D& first, const Segment3D& second, double epsilon = 1e-06);
};
