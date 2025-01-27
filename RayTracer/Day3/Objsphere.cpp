#include "Objsphere.hpp"
#include "Ray.hpp"

bool Sphere::intersect(const Ray& ray, float& t0, float& t1){
    Vector3 dir = ray.getDirection().normalize();
    Vector3 L = getPosition() - ray.getOrigin();
    float t_ca = L.dot(dir);
    float d2 = L.dot(L) - t_ca*t_ca;
    float radius2 = m_radius * m_radius;
    if (d2 > radius2) return false;
    float t_hc = std::sqrt(radius2 - d2);
    t0 = t_ca - t_hc;
    t1 = t_ca + t_hc;
    return true;
};

