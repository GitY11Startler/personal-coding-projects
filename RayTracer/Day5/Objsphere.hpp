#ifndef OBJSPHERE_H
#define OBJSPHERE_H

#include "Objshape.hpp"

class Sphere: public Shape{
    private:
    float m_radius;

    public:
    Sphere(): Shape(), m_radius(0){}
    Sphere(const Vector3& position, float radius, const Vector3& color): Shape(position, color), m_radius(radius){}

    public: 
    bool intersect(const Ray& ray, float& t0);

    Vector3 getNormal(const Vector3& point) const {return (point - getPosition()).normalize();}

};

#endif