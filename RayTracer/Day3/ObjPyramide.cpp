#include "ObjPyramide.hpp"

// float smallest(int x, int y, int z) {

//   int smallest = 99999;

//   if (x < smallest)
//     smallest=x;
//   if (y < smallest)
//     smallest=y;
//   if(z < smallest)
//     smallest=z;

//   return smallest;
// }

// bool Pyramide::intersect(const Ray& ray, float & t) const{
    
//     float t0, t1, t2;
//     m_Faces[0].intersect(ray, t0);
//     m_Faces[1].intersect(ray, t1);
//     m_Faces[2].intersect(ray, t2);

//     // t = smallest(t0,t1,t2);
//     t = std::min(std::min(t0, t1), t2);

//     return true;
// }

bool Pyramide::intersect(const Ray& ray, float& t) const {
    bool hit = false;
    float closestT = std::numeric_limits<float>::max();

    // verifier l'intersection pour chaque face du pyramide
    for (const auto& face: m_Faces) {
        float tTemp;
        if (face.intersect(ray, tTemp) && face.contains(ray.at(tTemp))) {
            // mettre a jour pour l'intersection la plus proche
            if (tTemp < closestT) {
                closestT = tTemp;
                hit = true;
            }
        }
    }

    if (hit) {
        t = closestT; // mettre a jour t avec l'intersection la plus proche
    }

    return hit;
}