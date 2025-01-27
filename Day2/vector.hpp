// classe pour des vecteurs en 3D
#ifndef VECTOR_3
#define VECTOR_3
#include <math.h>
#include <iostream>

class Vector3{
    public:
    float x, y, z;

    // constructeurs
    Vector3() : x(0), y(0), z(0){}
    Vector3(float x1, float y1, float z1) : x(x1), y(y1), z(z1){}

    // qqs operateurs
    Vector3 operator+(const Vector3& other) const{return Vector3(x+other.x, y+other.y, z+other.z);}
    Vector3 operator-(const Vector3& other) const{return Vector3(x-other.x, y-other.y, z-other.z);}
    Vector3 operator*(float scalar) const {return Vector3(x*scalar, y*scalar, z*scalar);}
    Vector3 operator/(float scalar) const {return Vector3(x/scalar, y/scalar, z/scalar);}

    // produit scalaire
    float dot(const Vector3& other){return x*other.x + y*other.y + z*other.z;}

    // produit vectoriel
    Vector3 cross(const Vector3& other){return Vector3(y*other.z - z*other.y, -x*other.z + z*other.x, x*other.y - y*other.x);}

    // norme
    float magnitude() const {return sqrt(x*x + y*y + z*z);}

    // normalisation
    Vector3 normalize() const {return *this / magnitude();}

    // affichage:
    void print() const{std::cout << "Vector3(" << x << ", " << y << ", " << z << ")\n";}
};

#endif