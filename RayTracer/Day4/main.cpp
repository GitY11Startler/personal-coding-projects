#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "Ray.hpp"
#include "Objsphere.hpp"
#include "Objshape.hpp"
#include "vector.hpp"
#include "camera.hpp"
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
    Vector3 ambient = objectColor * 0.1f; // Low ambient light
    if (isShadowed) return ambient; // Only ambient light in shadows

    Vector3 diffuse = computeDiffuse(point, normal, lightPos, lightColor, objectColor);
    Vector3 specular = computeSpecular(point, normal, lightPos, viewDir, lightColor, shininess);

    return ambient + diffuse + specular; // Combine all components
}

int main(){
    float imageWidth = 1280;
    float imageHeight = 720;
    float aspectRatio = imageWidth / imageHeight;
    Sphere sphere1 = Sphere(Vector3(0, 0, 3), 0.5, Vector3(0, 0, 1));
    Sphere sphere2 = Sphere(Vector3(2, 0.5, 3), 0.5, Vector3(1, 1, 0));
    Sphere sphere3 = Sphere(Vector3(-2, 0.5, 3), 0.5, Vector3(1, 0, 0));
    Sphere sphere4 = Sphere(Vector3(0, 1, 3), 0.5, Vector3(0, 1, 0));
    
    std::vector<Shape> Objects{sphere1, sphere2, sphere3, sphere4};
    std::vector<Sphere> spheres{sphere1, sphere2, sphere3, sphere4};
    
    Camera camera(aspectRatio);

    //definir des parametres d'eclairage
    Vector3 lightPos(0.5, -2, 10);    // Light source position
    Vector3 lightColor(1, 1, 1);     // white light
    float shininess = 2.0;          // Moderate shininess

    std::vector<unsigned char> image(imageWidth * imageHeight * 3); //pour generer le fichier .png

    for(int x=0; x<imageWidth; x++){
        for(int y=0; y<imageHeight; y++){
            float u = float(x) / (imageWidth - 1);
            float v = float(y) / (imageHeight - 1);

            Ray ray = camera.getRay(u, v);
            float t0, t1;
            Vector3 color(0.5, 0.7, 1.0);

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
                

            // float t;
            // if (sphere1.intersect(ray, t)) {
            //     Vector3 point = ray.at(t);
            //     Vector3 normal = sphere1.getNormal(ray.at(t));
            //     bool shadowed = ray.IsInShadow(point, lightPos, Objects);
            //     Vector3 viewDir = ray.getDirection()*(-1);
            //     Vector3 objColor = sphere1.getColor();
            //     color = computeShading(point, normal, lightPos, viewDir, lightColor, objColor, shininess, shadowed);
            // }
                  
            // float t2;
            // if (sphere2.intersect(ray, t2)) {
            //     Vector3 point = ray.at(t2);
            //     Vector3 normal = sphere2.getNormal(ray.at(t2));
            //     bool shadowed = ray.IsInShadow(point, lightPos, Objects);
            //     Vector3 viewDir = ray.getDirection()*(-1);
            //     Vector3 objColor = sphere2.getColor();
            //     color = computeShading(point, normal, lightPos, viewDir, lightColor, objColor, shininess, shadowed);
            //     // std::cout << "The coloring vector: ";
            //     // color.print();
            // }

            // float t3;
            // if (sphere3.intersect(ray, t3)) {
            //     Vector3 point = ray.at(t3);
            //     Vector3 normal = sphere3.getNormal(ray.at(t3));
            //     bool shadowed = ray.IsInShadow(point, lightPos, Objects);
            //     Vector3 viewDir = ray.getDirection()*(-1);
            //     Vector3 objColor = sphere3.getColor();
            //     color = computeShading(point, normal, lightPos, viewDir, lightColor, objColor, shininess, shadowed);
            //     // std::cout << "The coloring vector: ";
            //     // color.print();
            // }

            // float t4;
            // if (sphere4.intersect(ray, t4)) {
            //     Vector3 point = ray.at(t4);
            //     Vector3 normal = sphere4.getNormal(ray.at(t4));
            //     bool shadowed = ray.IsInShadow(point, lightPos, Objects);
            //     Vector3 viewDir = ray.getDirection()*(-1);
            //     Vector3 objColor = sphere4.getColor();
            //     color = computeShading(point, normal, lightPos, viewDir, lightColor, objColor, shininess, shadowed);
            //     // std::cout << "The coloring vector: ";
            //     // color.print();
            // }
            
            int index = (y*imageWidth + x) * 3;
            image[index+0] = static_cast<unsigned char>(255.0*color.x);
            image[index+1] = static_cast<unsigned char>(255.0*color.y);
            image[index+2] = static_cast<unsigned char>(255.0*color.z);
        }
    }

    std::cout << "Saving file to firstRT2.png: \n";
    stbi_write_png("firstRT2.png", imageWidth, imageHeight, 3, image.data(), imageWidth*3);
    return 0;
}


// int main(){
//     float imageWidth = 1280.0;
//     float imageHeight = 720.0;
//     float aspectRatio = imageWidth / imageHeight;

//     Camera camera(aspectRatio);
//     float u = 1.0, v = 1.0;
//     Ray ray = camera.getRay(u, v);
//     std::cout << "Origine du rayon: ";
//     ray.getOrigin().print();
//     std::cout << "Direction du rayon: ";
//     ray.getDirection().print();

//     Sphere sphere(Vector3(0.0, 0.0, -2.0), 3.0f, Vector3(255.0, 0.0, 0.0));
//     float t0, t1;
//     if (sphere.intersect(ray, t0, t1)){
//         std::cout << "Intersection!\n";
//         std::cout << "Point d'intersection 1: ";
//         ray.at(t0).print();
//         std::cout << "Point d'intersection 2: ";
//         ray.at(t1).print();
//     }
//     else{std::cout << "No intersections!\n";}




// }




// int main(){
//     Camera camera(16.0/9.0);

//     Ray ray = camera.getRay(1, 1);
//     std::cout << "Ray origin: ";
//     ray.getOrigin().print();
//     std::cout << "Ray direction: ";
//     ray.getDirection().print();
// }




// int main(){
//     Sphere sphere(Vector3(0.0, 0.0, 0.0), 1.0f, Vector3(1.0, 0.0, 0.0));
//     Ray ray(Vector3(1.0, 0.0, 0.0), Vector3(0.0, 1.0, 0.0));

//     float t0, t1;
//     if (sphere.intersect(ray, t0, t1)){
//         std::cout << "First intersection point: ";
//         ray.at(t0).print();
//         std::cout << "Second intersection point: ";
//         ray.at(t1).print();
//     }
//     else std::cout << "NO INTERSECTIONS!\n";
    
// }






// int main(){
//     Vector3 a{2, 4, 5};
//     Vector3 b{1, 2, 3};

//     std::cout << "a = ";
//     a.print();

//     std::cout << "b = ";
//     b.print();

//     std::cout << "Produit scalaire de a et b: " << a.dot(b) << "\n";
//     std::cout << "Produit vectoriel de a et b: "; 
//     a.cross(b).print();
//     std::cout << "Norme de a: " << a.magnitude() << "\n";
//     std::cout << "a normalisé: ";
//     a.normalize().print();
// }




// #define STB_IMAGE_WRITE_IMPLEMENTATION

// #include "../Day1/includes/stb_image_write.h"
// #include <vector>
// #include <iostream>

// // utiliser stb_image_write.h pour ecrire une image test

// int main(){
//     int width = 256;
//     int height = 256;
    
//     std::vector<unsigned char> image(width * height * 3);

//     // remplir l'image par des gradients de couleur
//     for(int y = 0; y < height; y++){
//         for(int x = 0; x < width; x++){
//             // indice
//             int index = (y * width + x) * 3;
//             // rouge
//             image[index] = static_cast<unsigned char>(255.0 * (x/float(width)));
//             // vert
//             image[index+1] = static_cast<unsigned char>(255.0 * (y/float(height)));
//             // bleu
//             image[index+2] = 0;
//         }
//     }

//     // sauvegarder l'image dans un fichier
//     stbi_write_png("../output/gradient1.png", width, height, 3, image.data(), width*3);
//     return 0;
// }