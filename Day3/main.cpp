#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"
#include "vector.hpp"
#include "Ray.hpp"
#include "camera.hpp"
#include "Objsphere.hpp"
#include "ObjPyramide.hpp"
#include "ObjTriangle.hpp"

#include <iostream>
#include <vector>

int main(){
    float imageWidth = 1920;
    float imageHeight = 1080;
    float aspectRatio = imageWidth / imageHeight;

    Camera camera(aspectRatio);

    std::vector<unsigned char> image(imageWidth * imageHeight * 3); //pour generer le fichier .png

    // Code pour tester le pyramide
    std::cout << "Testing Pyramide intersection...\n";
    std::vector<Triangle> faces;
    std::vector<Vector3> base;
    Vector3 sommet(3, 1, 6);

    // sommets de la base
    base.push_back(Vector3(0, 0, 3));
    base.push_back(Vector3(3, 2, 3));
    base.push_back(Vector3(5, 0, 3));

    // definir les faces du pyramide a travers les sommets de la base et le sommet du pyramide
    faces.push_back(Triangle(Vector3(0, 0, 2), Vector3(1, 0, 0), base[0], base[1], sommet));
    faces.push_back(Triangle(Vector3(0, 0, 2), Vector3(1, 0, 0), base[1], base[2], sommet));
    faces.push_back(Triangle(Vector3(0, 0, 2), Vector3(1, 0, 0), base[2], base[3], sommet));
    // faces.push_back(Triangle(Vector3(0, 0, 2), Vector3(1, 0, 0), base[0], base[1], base[2]));

    // test code
    Triangle triangle(Vector3(0, 0, 3), Vector3(1, 0, 0), base[0], base[1], base[2]);

    // definir le pyramide en se basant sur la base et les faces calculees precedemment
    Pyramide pyramide(Vector3(0, 0, 3), Vector3(0, 1, 0), faces, base, sommet);

    for (int x=0; x<imageWidth; x++){
        for (int y=0; y<imageHeight; y++){
            float u = float(x) / (imageWidth - 1);
            float v = float(y) / (imageHeight - 1);

            Ray ray = camera.getRay(u, v);
            float t;
            Vector3 color(0.5, 0.7, 1.0);

            // pour l'affichage du triangle: (read below)
            // if (triangle.intersect(ray, t) && triangle.contains(ray.at(t))) color = triangle.getColor();
            // pyramide.intersect(ray, t)
            if (triangle.intersect(ray, t) && triangle.contains(ray.at(t))) color = triangle.getColor();
            // if (pyramide.intersect(ray, t) && faces[0].contains(ray.at(t)) || faces[1].contains(ray.at(t)) || faces[2].contains(ray.at(t))) color = pyramide.getColor();

            int index = (y*imageWidth + x) * 3;
            image[index+0] = static_cast<unsigned char>(255.0*color.x);
            image[index+1] = static_cast<unsigned char>(255.0*color.y);
            image[index+2] = static_cast<unsigned char>(255.0*color.z);
        }
    }

    stbi_write_png("firstRT.png", imageWidth, imageHeight, 3, image.data(), imageWidth*3);
    return 0;
}
