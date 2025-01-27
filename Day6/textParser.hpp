#include "tinyxml2.h"
#include "Objsphere.hpp"
#include "camera.hpp"
#include "vector.hpp"
#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <memory>

class TextParser {
public:
    Camera camera;
    Vector3 lightPos;
    Vector3 lightColor;
    float shininess;
    std::vector<Sphere> spheres;

    // Constructeur : charge et analyse le fichier XML
    // TextParser(const std::string& filename) {
    //     tinyxml2::XMLDocument doc;
    //     if (doc.LoadFile(filename.c_str()) != tinyxml2::XML_SUCCESS) {
    //         throw std::runtime_error("Erreur : Impossible de charger le fichier XML.");
    //     }

    //     // Lire les données de la caméra
    //     tinyxml2::XMLElement* cameraElement = doc.FirstChildElement("scene")->FirstChildElement("camera");
    //     float aspectRatio = cameraElement->FirstChildElement("aspectRatio")->FloatText();
    //     camera = Camera(aspectRatio);

    //     // Lire les données d'éclairage
    //     tinyxml2::XMLElement* lightElement = doc.FirstChildElement("scene")->FirstChildElement("light");
    //     lightPos = readVector3(lightElement->FirstChildElement("position"));
    //     lightColor = readVector3(lightElement->FirstChildElement("color"));
    //     shininess = lightElement->FirstChildElement("shininess")->FloatText();

    //     // Lire les objets
    //     tinyxml2::XMLElement* objectsElement = doc.FirstChildElement("scene")->FirstChildElement("objects");
    //     for (tinyxml2::XMLElement* sphereElement = objectsElement->FirstChildElement("sphere");
    //         sphereElement != nullptr; sphereElement = sphereElement->NextSiblingElement("sphere")) {
    //         Vector3 position = readVector3(sphereElement->FirstChildElement("position"));
    //         float radius = sphereElement->FirstChildElement("radius")->FloatText();
    //         Vector3 color = readVector3(sphereElement->FirstChildElement("color"));
    //         spheres.emplace_back(position, radius, color);
    //     }
    // }

    TextParser(const std::string& filename) {
        tinyxml2::XMLDocument doc;
        if (doc.LoadFile(filename.c_str()) != tinyxml2::XML_SUCCESS) {
            throw std::runtime_error("Erreur : Impossible de charger le fichier XML.");
        }

        tinyxml2::XMLElement* sceneElement = doc.FirstChildElement("Scene");
        if (!sceneElement) {
            throw std::runtime_error("Erreur : L'élément <scene> est introuvable dans le fichier XML.");
        }

        // Lire les données de la caméra
        tinyxml2::XMLElement* cameraElement = sceneElement->FirstChildElement("Camera");
        if (!cameraElement) {
            throw std::runtime_error("Erreur : L'élément <camera> est introuvable dans le fichier XML.");
        }
        float aspectRatio = 1.0f; // Valeur par défaut
        if (cameraElement->FirstChildElement("AspectRatio")) {
            aspectRatio = cameraElement->FirstChildElement("AspectRatio")->FloatText();
        }
        camera = Camera(aspectRatio);

        // Lire les données d'éclairage
        tinyxml2::XMLElement* lightElement = sceneElement->FirstChildElement("Light");
        if (!lightElement) {
            throw std::runtime_error("Erreur : L'élément <light> est introuvable dans le fichier XML.");
        }
        lightPos = readVector3(lightElement->FirstChildElement("position"));
        lightColor = readVector3(lightElement->FirstChildElement("color"));
        shininess = lightElement->FirstChildElement("shininess") 
                    ? lightElement->FirstChildElement("shininess")->FloatText() 
                    : 0.0f; // Valeur par défaut

        // Lire les objets
        tinyxml2::XMLElement* objectsElement = sceneElement->FirstChildElement("Shapes");
        if (!objectsElement) {
            throw std::runtime_error("Erreur : L'élément <shapes> est introuvable dans le fichier XML.");
        }
        for (tinyxml2::XMLElement* sphereElement = objectsElement->FirstChildElement("Sphere");
            sphereElement != nullptr; sphereElement = sphereElement->NextSiblingElement("Sphere")) {
            Vector3 position = readVector3(sphereElement->FirstChildElement("position"));
            float radius = sphereElement->FirstChildElement("radius") 
                        ? sphereElement->FirstChildElement("radius")->FloatText() 
                        : 0.0f; // Valeur par défaut
            Vector3 color = readVector3(sphereElement->FirstChildElement("color"));
            spheres.emplace_back(position, radius, color);
        }
    }

    bool parseShapes(std::vector<std::unique_ptr<Shape>>& shapes) ;

private:
    std::string m_filename;

private:
    // Fonction utilitaire pour lire un Vector3 à partir d'un élément XML
    Vector3 readVector3(tinyxml2::XMLElement* element) ;
};
