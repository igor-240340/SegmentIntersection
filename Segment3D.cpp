#include <cmath>

#include "Segment3D.h"

#include "Matrix3D.h"

std::optional<Vector3D> Segment3D::Intersect(const Segment3D& first, const Segment3D& second, double epsilon) {
    const Vector3D& A = first.start;
    const Vector3D& B = first.end;

    Vector3D C = second.start; // Копируем, поскольку может потребоваться своп.
    Vector3D D = second.end;

    const Vector3D AB = B - A;

    Vector3D AC = C - A;
    Vector3D CD = D - C;

    Vector3D cross = Vector3D::cross(AB, AC);
    // Точка C лежит на одной прямой с AB.
    if (cross.length() < epsilon) {
        std::swap(C, D);

        AC = C - A;
        CD = D - C;

        cross = Vector3D::cross(AB, AC);

        // Обе точки лежат на одной прямой с AB.
        if (cross.length() < epsilon)
            return {};
    }

    const Vector3D plane_normal = cross.get_normalized();
    const double proj = Vector3D::dot(CD, plane_normal);
    const bool same_plane = std::fabs(proj) < epsilon;
    if (!same_plane)
        return {};

    // Базис пространства плоскости, где A - это начало координат.
    Vector3D u = AB.get_normalized();
    Vector3D v = plane_normal;
    Vector3D n = Vector3D::cross(u, v).get_normalized();

    // Переводим точки в пространство плоскости.
    Matrix3D plane_mat{ u,v,n };
    Vector3D A_p = plane_mat * (A - A);
    Vector3D B_p = plane_mat * (B - A);
    Vector3D C_p = plane_mat * (C - A);
    Vector3D D_p = plane_mat * (D - A);

    // Trivial reject 1: Отрезки лежат на одной линии, при этом либо совпадают либо перекрываются.
    // Note: Возможна ситуация, когда обе точки отрезка CD находятся от прямой, на которой лежит
    // отрезок AB, на расстоянии меньше epsilon, но при этом длина векторного произведния оказывается не меньше epsilon.
    // Вопрос в том, когда считать, что точки C и D лежат на одной прямой с AB: когда векторное произведение близко к нулю
    // или когда сами точки близки к прямой, или использовать какую-то другую стратегию?
    // Пока оставим только один критерий: близость векторного произведения к нулю.
    /*if (std::fabs(C_p.Z) < epsilon && std::fabs(D_p.Z) < epsilon)
        return {};*/

        // Trivial reject 2: Отрезок CD полностью в верхней либо нижней полуплоскости.
    if ((C_p.Z > epsilon && D_p.Z > epsilon) || (C_p.Z < -epsilon && D_p.Z < -epsilon))
        return {};

    // Trivial reject 3: Отрезок CD полностью слева или справа от AB.
    const double left = (A_p.X - epsilon);
    const double right = (B_p.X + epsilon);
    if ((C_p.X < left && D_p.X < left) || (C_p.X > right && D_p.X > right))
        return {};

    // Ищем пересечение в пространстве плоскости.
    Vector3D CD_p = D_p - C_p;
    const double t_param = -C_p.Z / CD_p.Z; // При этом параметре t z-компонента будет равна нулю.
    Vector3D intersection_p = C_p + (CD_p * t_param);

    const bool inside_AB = intersection_p.X >= (A_p.X - epsilon) && intersection_p.X <= (B_p.X + epsilon);
    if (!inside_AB)
        return {};

    // Переводим точку пересечения в мировые координаты.
    Matrix3D world_mat = plane_mat.get_transposed();
    Vector3D intersection_w = A + world_mat * intersection_p;

    return intersection_w;
}
