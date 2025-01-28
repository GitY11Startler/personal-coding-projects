#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "Ray.hpp"
#include "Objsphere.hpp"
#include "Objshape.hpp"
#include "vector.hpp"
#include "camera.hpp"
#include "ObjTriangle.hpp"
#include "stb_image_write.h"
#include <iostream>
#include <vector>


Vector3 computeDiffuse(Vector3& point, Vector3& normal, Vector3& lightPos, Vector3& lightColor, Vector3& objectColor){
    Vector3 lightDir = (lightPos - point).normalize();
    float intensity = std::max(0.0f, lightDir.dot(normal));
    return objectColor * lightColor * intensity;
}

Vector3 computeSpecular(Vector3& point, Vector3& normal, Vector3& lightPos, Vector3& viewDir, Vector3& lightColor, float shininess){
    Vector3 lightDir = (lightPos - point).normalize();
    Vector3 reflectDir = (normal * 2 * normal.dot(lightDir) - lightDir).normalize();
    float intensity = std::pow(std::max(0.0f, reflectDir.dot(viewDir)), shininess); 
    return lightColor * intensity; 
}

Vector3 computeShading(Vector3& point, Vector3& normal, Vector3& lightPos, Vector3& viewDir, Vector3& lightColor, Vector3& objectColor, float shininess, bool isShadowed) {
    Vector3 ambient = objectColor * 0.2f; // faible luminosité ambiante
    if (isShadowed) return ambient; // Uniquement la lumière ambiante dans les ombres

    Vector3 diffuse = computeDiffuse(point, normal, lightPos, lightColor, objectColor);
    Vector3 specular = computeSpecular(point, normal, lightPos, viewDir, lightColor, shininess);

    return ambient + diffuse + specular; // combiner les trois composantes
}

int main(){
    float imageWidth = 1280;
    float imageHeight = 720;
    float aspectRatio = imageWidth / imageHeight;
    
    // ajouter des triangles
    std::vector<Vector3> sommets;
    // 1er triangle
    sommets.push_back(Vector3(3, 0, 3));
    sommets.push_back(Vector3(-1, -2, 3));
    sommets.push_back(Vector3(-2, 0, 3));   
    
    // 2eme triangle
    sommets.push_back(Vector3(1, 0, 3));
    sommets.push_back(Vector3(0, 2, 3));
    sommets.push_back(Vector3(0, -2, 3));

    // 3eme triangle
    sommets.push_back(Vector3(-3, 0, 3));
    sommets.push_back(Vector3(-2, 1.5, 3));
    sommets.push_back(Vector3(-2, -1.5, 3));

    Triangle triangle1(Vector3(0, 0, 2), Vector3(0, 0, 1), sommets[0], sommets[1], sommets[2]);
    Triangle triangle2(Vector3(0, 0, 2), Vector3(1, 1, 0), sommets[3], sommets[4], sommets[5]);
    Triangle triangle3(Vector3(0, 0, 2), Vector3(1, 1, 0), sommets[6], sommets[7], sommets[8]);

    // ajouter des sphères
    Sphere sphere1 = Sphere(Vector3(0, 0, 3), 0.5, Vector3(0, 0, 1));
    Sphere sphere2 = Sphere(Vector3(1, 0.5, 3), 0.5, Vector3(1, 1, 0));
    Sphere sphere3 = Sphere(Vector3(-1, 0.5, 3), 0.5, Vector3(1, 0, 0));
    Sphere sphere4 = Sphere(Vector3(0, 1, 3), 0.5, Vector3(0, 1, 0));
    
    // tous les objets dans un seul vecteur 
    std::vector<Triangle> triangles{triangle1, triangle2, triangle3};
    std::vector<Sphere> spheres{sphere1, sphere2, sphere3, sphere4};
    std::vector<Shape> Objects{sphere1, sphere2, sphere3, sphere4, triangle1, triangle2, triangle3};
    
    Camera camera(aspectRatio);

    //definir des parametres d'eclairage
    Vector3 lightPos(0, 0, 6);    // position de la source lumineuse
    Vector3 lightColor(1, 1, 1);     // lumière blanche
    float shininess = 2.0;          // brillance modérée

    std::vector<unsigned char> image(imageWidth * imageHeight * 3); // pour génerer le fichier .png

    for(int x=0; x<imageWidth; x++){
        for(int y=0; y<imageHeight; y++){
            float u = float(x) / (imageWidth - 1);
            float v = float(y) / (imageHeight - 1);

            Ray ray = camera.getRay(u, v);
            float t0, t1;
            Vector3 color(0.5, 0.7, 1.0); // couleur de l'arriere-plan
            if (y < imageHeight / 2) color.x = color.y = color.z = 0;

            // boucle pour les triangles
            for(auto triangle: triangles){
                float t;
                if (triangle.intersect(ray, t) && triangle.contains(ray.at(t))) {
                    Vector3 point = ray.at(t);
                    Vector3 normal = triangle.getNormal();
                    bool shadowed = ray.IsInShadow(point, lightPos, Objects);
                    Vector3 viewDir = ray.getDirection()*(-1);
                    Vector3 objColor = triangle.getColor();
                    color = computeShading(point, normal, lightPos, viewDir, lightColor, objColor, shininess, shadowed);
                }
            }

            // boucle pour les sphères
            for(auto sphere: spheres){
                float t;
                if (sphere.intersect(ray, t)) {
                    Vector3 point = ray.at(t);
                    Vector3 normal = sphere.getNormal(ray.at(t));
                    bool shadowed = ray.IsInShadow(point, lightPos, Objects);
                    Vector3 viewDir = ray.getDirection()*(-1);
                    Vector3 objColor = sphere.getColor();
                    color = computeShading(point, normal, lightPos, viewDir, lightColor, objColor, shininess, shadowed);
                }
            }

            int index = (y*imageWidth + x) * 3;
            image[index+0] = static_cast<unsigned char>(255.0*color.x);
            image[index+1] = static_cast<unsigned char>(255.0*color.y);
            image[index+2] = static_cast<unsigned char>(255.0*color.z);
        }
    }

    stbi_write_png("rayTracer1.png", imageWidth, imageHeight, 3, image.data(), imageWidth*3);
    return 0;

    // destroy objects
    for(auto sphere: spheres) {sphere.~Sphere();}
    for(auto triangle: triangles) {triangle.~Triangle();}

    triangles.clear();
    spheres.clear();
}
