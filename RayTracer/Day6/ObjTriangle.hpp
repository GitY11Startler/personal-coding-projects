#ifndef OBJTRIANGLE_HPP
#define OBJTRIANGLE_HPP

#include "Ray.hpp"
#include "Objshape.hpp"
#include "vector.hpp"

class Ray;

class Triangle : public Shape {
    private:
    Vector3 m_v0, m_v1, m_v2; //Sommets
    Vector3 m_normal; //Généré automatiquement

    public:

    Triangle(): Shape(Vector3(0,0,0), Vector3(0,0,0)), m_v0(Vector3(1,0,0)), m_v1(Vector3(0,1,0)), m_v2(Vector3(0,0,1)){
        m_normal = (m_v1 - m_v0).cross(m_v2 - m_v0).normalize();
    }
    Triangle(const Vector3& position, const Vector3& color, const Vector3& v0, const Vector3& v1, const Vector3& v2): Shape(position, color), 
    m_v0(v0), m_v1(v1), m_v2(v2){
        m_normal = (m_v1 - m_v0).cross(m_v2 - m_v0).normalize();
    }

    Vector3 getNormal() const {return m_normal;}

    bool intersect(const Ray& ray, float& t) const;

    bool contains(const Vector3&) const;

};
#endif