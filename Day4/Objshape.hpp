#ifndef OBJSHAPE_H
#define OBJSHAPE_H

#include "vector.hpp"
#include "Ray.hpp"

class Ray;

class Shape{
    private:
    Vector3 m_position;
    Vector3 m_color;

    public: //constructeurs
    Shape(): m_position(Vector3(0.0, 0.0, 0.0)), m_color(Vector3(0.0, 0.0, 0.0)){}
    Shape(const Vector3& position, const Vector3& color): m_position(position), m_color(color){}
    public:
    Vector3 getPosition() const {return m_position;}
    Vector3 getColor() const {return m_color;}

    
    public: //fonctions membres
    Vector3 getNormal(const Vector3& point) const {return (point - m_position).normalize();}
    virtual bool intersect(Ray& ray, float& t);
};

#endif