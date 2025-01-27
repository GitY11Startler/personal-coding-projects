#include "Objshape.hpp"

bool Shape::intersect(Ray& ray, float& t){
    return true;
}

// Vector3 Shape::computeDiffuse(Vector3& point, Vector3& normal, Vector3& lightPos, Vector3& lightColor, Vector3& objectColor){
//     Vector3 lightDir = (lightPos - point).normalize();
//     float intensity = std::max(0.0f, lightDir.dot(normal));
//     return objectColor * lightColor * intensity;
// }

// Vector3 Shape::computeSpecular(Vector3& point, Vector3& normal, Vector3& lightPos, Vector3& viewDir, Vector3& lightColor, float shininess){
//     Vector3 lightDir = (lightPos - point).normalize();
//     Vector3 reflectDir = (normal * 2 * normal.dot(lightDir) - lightDir).normalize();
//     float intensity = std::pow(std::max(0.0f, reflectDir.dot(viewDir)), shininess); 
//     return lightColor * intensity; 
// }

// Vector3 Shape::computeShading(Vector3& point, Vector3& normal, Vector3& lightPos, Vector3& viewDir, Vector3& lightColor, Vector3& objectColor, float shininess, bool isShadowed) {
//     Vector3 ambient = objectColor * 0.1f; // Low ambient light
//     if (isShadowed) return ambient; // Only ambient light in shadows

//     Vector3 diffuse = computeDiffuse(point, normal, lightPos, lightColor, objectColor);
//     Vector3 specular = computeSpecular(point, normal, lightPos, viewDir, lightColor, shininess);

//     return ambient + diffuse + specular; // Combine all components
// }