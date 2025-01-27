#include "Ray.hpp"

Vector3 Ray::at(float t) const {
    return m_origin + m_direction*t;
}

bool Ray::IsInShadow(const Vector3& point, const Vector3& lightPos, std::vector<Shape> Objects){
    Vector3 direction = (lightPos - point).normalize();
    Ray shadowRay(point + direction * 1e-4, direction);

    for(Shape& object: Objects){
        float t;
        if (object.intersect(shadowRay, t)) return false;
    }

    return true;
}