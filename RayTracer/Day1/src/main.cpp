#define STB_IMAGE_WRITE_IMPLEMENTATION

#include "../includes/stb_image_write.h"
#include <vector>
#include <iostream>

// utiliser stb_image_write.h pour ecrire une image test

int main(){
    int width = 256;
    int height = 256;
    
    std::vector<unsigned char> image(width * height * 3);

    // remplir l'image par des gradients de couleur
    for(int y = 0; y < height; y++){
        for(int x = 0; x < width; x++){
            // indice
            int index = (y * width + x) * 3;
            // rouge
            image[index] = static_cast<unsigned char>(255.0 * (x/float(width)));
            // vert
            image[index+1] = static_cast<unsigned char>(255.0 * (y/float(height)));
            // bleu
            image[index+2] = 0;
        }
    }

    // sauvegarder l'image dans un fichier
    stbi_write_png("../output/gradient1.png", width, height, 3, image.data(), width*3);
    return 0;
}