#include "ObjTriangle.hpp"

bool Triangle::contains(const Vector3& point) const {
    // Vecteurs du triangle
    Vector3 v0 = m_v2 - m_v0;
    Vector3 v1 = m_v1 - m_v0;
    Vector3 v2 = point - m_v0;

    // Produits scalaires nécessaires pour calculer les coordonnées barycentriques
    float dot00 = v0.dot(v0);
    float dot01 = v0.dot(v1);
    float dot02 = v0.dot(v2);
    float dot11 = v1.dot(v1);
    float dot12 = v1.dot(v2);

    // Calcul des coordonnées barycentriques
    float denom = dot00 * dot11 - dot01 * dot01;
    if (fabs(denom) < 1e-6) {
        // Si denom est proche de 0, le triangle est dégénéré
        return false;
    }

    float u = (dot11 * dot02 - dot01 * dot12) / denom;
    float v = (dot00 * dot12 - dot01 * dot02) / denom;

    // Le point est dans le triangle si 0 <= u <= 1, 0 <= v <= 1, et u + v <= 1
    return (u >= 0.0f) && (v >= 0.0f) && (u + v <= 1.0f);
}

bool Triangle::intersect(const Ray& ray, float& t) const{

    //solution geomètrique

    //On a besoin de la normal au plan (getNormal)

    Vector3 N = getNormal();

    //Calculer D
    float D = -N.dot(m_v0);

    // calculer t
    t = -(N.dot(ray.getOrigin()) + D) / N.dot(ray.getDirection());

    return true;  

}

