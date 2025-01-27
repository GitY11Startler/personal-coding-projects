#include "Ray.hpp"

Vector3 Ray::at(float t) const {
    return m_origin + m_direction*t;
}