#ifndef OBJPYRAMIDE_H
#define OBJPYRAMIDE_H

#include "Objshape.hpp"
#include "ObjTriangle.hpp"
#include <vector>

class Pyramide : public Shape {

    //3 sommets de la base 
    // std::vector<Vector3> m_Base;
    std::vector<Vector3> m_Base = std::vector<Vector3>(3, Vector3());
    // std::vector<Triangle> m_Faces;
    std::vector<Triangle> m_Faces = std::vector<Triangle>(3,Triangle());
    Vector3 m_Sommet;
    float m_hauteur; //générée automatiquement par la base et le sommet

    public:

    Pyramide(): Shape(Vector3(0,0,0), Vector3(0,0,0)){

        //Base
        m_Base[0]=Vector3(1,0,0);
        m_Base[1]=Vector3(0,1,0);
        m_Base[2]=Vector3(0,0,1);

        //Faces
        m_Faces[0]= Triangle();
        m_Faces[1]= Triangle();
        m_Faces[2]= Triangle();

        m_Sommet= Vector3(1,1,1);

        Vector3 barycentre = (m_Base[0] + m_Base[1] + m_Base[2]) / 3;
        m_hauteur = (m_Sommet - barycentre).magnitude();
        
    }

    Pyramide(const Vector3& position, const Vector3& color, const std::vector<Triangle>& Faces, const std::vector<Vector3>& Base, const Vector3& Sommet): 
    Shape(position, color){
        
        //Base
        m_Base[0] = Base[0];
        m_Base[1] = Base[1];
        m_Base[2] = Base[2];

        //Faces
        m_Faces[0] = Faces[0];
        m_Faces[1] = Faces[1];
        m_Faces[2] = Faces[2];

        m_Sommet = Sommet;

        Vector3 barycentre = (m_Base[0] + m_Base[1] + m_Base[2]) / 3;
        m_hauteur = (m_Sommet - barycentre).magnitude();

    }

    bool intersect(const Ray&,float&) const;
};

#endif