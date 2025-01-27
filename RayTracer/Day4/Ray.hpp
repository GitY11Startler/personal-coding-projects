#ifndef RAY_H
#define RAY_H

#include "vector.hpp"
#include "Objshape.hpp"
#include <vector>

class Shape;

class Ray{
    private:
    // origine et direction du rayon
    Vector3 m_origin, m_direction;

    public: //getters
    Vector3 getOrigin() const {return m_origin;}
    Vector3 getDirection() const {return m_direction;}

    public:
    // constructeurs
    Ray(): m_origin(Vector3(0.0, 0.0, 0.0)), m_direction(Vector3(0.0, 0.0, 0.0)){}
    Ray(const Vector3& origin, const Vector3& direction) : m_origin(origin), m_direction(direction.normalize()){}

    // point P(t) = origine + t*direction
    Vector3 at(float t) const;

    bool IsInShadow(const Vector3& point, const Vector3& lightPos, std::vector<Shape> Objects);

};

#endif