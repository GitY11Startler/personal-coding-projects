#include "textParser.hpp"
#include "vector.hpp"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <memory>
#include "ObjTriangle.hpp"

Vector3 TextParser::readVector3(tinyxml2::XMLElement* element) {
        float x = element->FloatAttribute("x");
        float y = element->FloatAttribute("y");
        float z = element->FloatAttribute("z");
        return Vector3(x, y, z);
    }

bool TextParser::parseShapes(std::vector<std::unique_ptr<Shape>>& shapes) {
    tinyxml2::XMLDocument doc;
    
    if (doc.LoadFile(m_filename.c_str()) != tinyxml2::XML_SUCCESS) {
        std::cerr << "Failed to load XML file: " << m_filename << std::endl;
        return false;
    }

    tinyxml2::XMLElement* root = doc.FirstChildElement("Shapes");
    if (!root) {
        std::cerr << "No <Shapes> element found in the XML file." << std::endl;
        return false;
    }

    // Iterate through the shapes
    for (tinyxml2::XMLElement* element = root->FirstChildElement(); element != nullptr; element = element->NextSiblingElement()) {
        std::string type = element->Name();

        if (type == "Sphere") {
            // Parse sphere data
            float x = element->FloatAttribute("x");
            float y = element->FloatAttribute("y");
            float z = element->FloatAttribute("z");
            float r = element->FloatAttribute("radius");
            float colorR = element->FloatAttribute("colorR");
            float colorG = element->FloatAttribute("colorG");
            float colorB = element->FloatAttribute("colorB");

            Vector3 position(x, y, z);
            Vector3 color(colorR, colorG, colorB);

            // Create and add the sphere
            shapes.push_back(std::make_unique<Sphere>(position,r, color));

        } else if (type == "Triangle") {
            // Parse triangle data
            float x0 = element->FloatAttribute("x0");
            float y0 = element->FloatAttribute("y0");
            float z0 = element->FloatAttribute("z0");

            float x1 = element->FloatAttribute("x1");
            float y1 = element->FloatAttribute("y1");
            float z1 = element->FloatAttribute("z1");

            float x2 = element->FloatAttribute("x2");
            float y2 = element->FloatAttribute("y2");
            float z2 = element->FloatAttribute("z2");

            float colorR = element->FloatAttribute("colorR");
            float colorG = element->FloatAttribute("colorG");
            float colorB = element->FloatAttribute("colorB");

            Vector3 v0(x0, y0, z0);
            Vector3 v1(x1, y1, z1);
            Vector3 v2(x2, y2, z2);
            Vector3 color(colorR, colorG, colorB);

            // Compute the normal of the triangle
            Vector3 edge1 = v1 - v0;
            Vector3 edge2 = v2 - v0;
            Vector3 normal = edge1.cross(edge2).normalize();

            // Create and add the triangle
            shapes.push_back(std::make_unique<Triangle>(v0, v1, v2, normal, color));
        } else {
            std::cerr << "Unknown shape type: " << type << std::endl;
            return false;
        }
    }
    return true;
}


