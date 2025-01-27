#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "Ray.hpp"
#include "Objsphere.hpp"
#include "vector.hpp"
#include "camera.hpp"
#include "stb_image_write.h"
#include <iostream>
#include <vector>

int main(){
    float imageWidth = 1280;
    float imageHeight = 720;
    float aspectRatio = imageWidth / imageHeight;

    Sphere sphere(Vector3(0.5, 0.5, 4), 1.5, Vector3(1, 0, 0));
    Camera camera(aspectRatio);

    std::vector<unsigned char> image(imageWidth * imageHeight * 3); //pour generer le fichier .png

    for(int x=0; x<imageWidth; x++){
        for(int y=0; y<imageHeight; y++){
            float u = float(x) / (imageWidth - 1);
            float v = float(y) / (imageHeight - 1);

            Ray ray = camera.getRay(u, v);
            float t0, t1;
            Vector3 color(0.5, 0.7, 1.0);

            if (sphere.intersect(ray, t0, t1)) color = sphere.getColor();

            int index = (y*imageWidth + x) * 3;
            image[index] = static_cast<unsigned char>(255.0*color.x);
            image[index+1] = static_cast<unsigned char>(255.0*color.y);
            image[index+2] = static_cast<unsigned char>(255.0*color.z);
        }
    }

    stbi_write_png("firstRT.png", imageWidth, imageHeight, 3, image.data(), imageWidth*3);
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