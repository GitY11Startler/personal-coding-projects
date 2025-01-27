#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "Ray.hpp"
#include "Objsphere.hpp"
#include "Objshape.hpp"
#include "vector.hpp"
#include "camera.hpp"
#include "ObjTriangle.hpp"
#include "stb_image_write.h"
#include "textParser.hpp"
#include <iostream>
#include <vector>
#include <string>

Vector3 computeDiffuse(Vector3& point, Vector3& normal, Vector3& lightPos, Vector3& lightColor, Vector3& objectColor) {
    Vector3 lightDir = (lightPos - point).normalize();
    float intensity = std::max(0.0f, lightDir.dot(normal));
    return objectColor * lightColor * intensity;
}

Vector3 computeSpecular(Vector3& point, Vector3& normal, Vector3& lightPos, Vector3& viewDir, Vector3& lightColor, float shininess) {
    Vector3 lightDir = (lightPos - point).normalize();
    Vector3 reflectDir = (normal * 2 * normal.dot(lightDir) - lightDir).normalize();
    float intensity = std::pow(std::max(0.0f, reflectDir.dot(viewDir)), shininess);
    return lightColor * intensity;
}

Vector3 computeShading(Vector3& point, Vector3& normal, Vector3& lightPos, Vector3& viewDir, Vector3& lightColor, Vector3& objectColor, float shininess, 
bool isShadowed) {
    Vector3 ambient = objectColor * 0.3f; // faible luminosité ambiante
    if (isShadowed) return ambient; // Uniquement la lumière ambiante dans les ombres

    Vector3 diffuse = computeDiffuse(point, normal, lightPos, objectColor, objectColor);
    Vector3 specular = computeSpecular(point, normal, lightPos, viewDir, lightColor, shininess);

    return ambient + diffuse + specular; // combiner les trois composantes
}

int main() {
    // // Load shapes from XML file using TextParser
    TextParser parser("shapes.xml");
    std::vector<std::unique_ptr<Shape>> objects; // Vector of unique pointers to store different shapes

    if (!parser.parseShapes(objects)) {
        std::cerr << "Failed to load shapes from the XML file." << std::endl;
        return 1;
    }

    float imageWidth = 1280;
    float imageHeight = 720;
    float aspectRatio = imageWidth / imageHeight;

    Camera camera(aspectRatio);

    // Définir des paramètres d'éclairage
    Vector3 lightPos(2, -1, 4);    // position de la source lumineuse
    Vector3 lightColor(1, 1, 1);   // lumière blanche
    float shininess = 2.0;         // brillance modérée

    std::vector<unsigned char> image(imageWidth * imageHeight * 3); // pour générer le fichier .png

    for (int x = 0; x < imageWidth; x++) {
        for (int y = 0; y < imageHeight; y++) {
            float u = float(x) / (imageWidth - 1);
            float v = float(y) / (imageHeight - 1);

            Ray ray = camera.getRay(u, v);
            Vector3 color(1, 1, 1);

            for (auto& object : objects) {
                float t;
                if (object->intersect(ray, t)) {
                    Vector3 point = ray.at(t);
                    Vector3 normal = object->getNormal(point);
                    bool shadowed = ray.IsInShadow(point, lightPos, objects);
                    Vector3 viewDir = ray.getDirection() * (-1);
                    Vector3 objColor = object->getColor();
                    color = computeShading(point, normal, lightPos, viewDir, lightColor, objColor, shininess, shadowed);
                    break; // Exit the loop once an intersection is found
                }
            }

            int index = (y * imageWidth + x) * 3;
            image[index + 0] = static_cast<unsigned char>(255.0 * color.x);
            image[index + 1] = static_cast<unsigned char>(255.0 * color.y);
            image[index + 2] = static_cast<unsigned char>(255.0 * color.z);
        }
    }

    std::cout << "Saving file to rayTracer.png: \n";
    stbi_write_png("rayTracer.png", imageWidth, imageHeight, 3, image.data(), imageWidth * 3);

    // No need to manually delete objects as they are managed by unique_ptr

    return 0;
}
