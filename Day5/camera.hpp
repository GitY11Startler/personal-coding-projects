#ifndef CAMERA_H
#define CAMERA_H
#include "vector.hpp"
#include "Ray.hpp"

class Camera{
    private:
    Vector3 m_origin;
    Vector3 m_lowerleftcorner;
    Vector3 m_horizontal;
    Vector3 m_vertical;

    public:
    Camera(float aspectRatio);

    public:
    Ray getRay(float u, float v) const;


};

#endif