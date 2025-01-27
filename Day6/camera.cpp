#include "camera.hpp"

Camera::Camera(){
    float aspectRatio = 1.77;
    float viewportHeight = 2.0;
    float viewportWidth = viewportHeight * aspectRatio; //aspect ratio est 16.0/9.0 par defaut
    float focalLength = 1.0;

    m_origin = Vector3(0.0, 0.0, 0.0);
    m_horizontal = Vector3(viewportWidth, 0.0, 0.0);
    m_vertical = Vector3(0.0, viewportHeight, 0.0);
    m_lowerleftcorner = m_origin - m_horizontal/2 - m_vertical/2 - Vector3(0.0, 0.0, focalLength);  
}

Camera::Camera(float aspectRatio){
    float viewportHeight = 2.0;
    float viewportWidth = viewportHeight * aspectRatio; //aspect ratio est 16.0/9.0 par defaut
    float focalLength = 1.0;

    m_origin = Vector3(0.0, 0.0, 0.0);
    m_horizontal = Vector3(viewportWidth, 0.0, 0.0);
    m_vertical = Vector3(0.0, viewportHeight, 0.0);
    m_lowerleftcorner = m_origin - m_horizontal/2 - m_vertical/2 - Vector3(0.0, 0.0, focalLength);  
}

Ray Camera::getRay(float u, float v) const {
    return Ray(m_origin, m_lowerleftcorner + m_horizontal * u + m_vertical * v - m_origin);
}