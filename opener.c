#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"

#include "opener.h"

Pixel* readBMP(const char* filename, int* width, int* height) {
    int channels; //channels in the image (3 for RGB)
    uint8_t* pixels = stbi_load(filename, width, height, &channels, 3);

    if (!pixels) {
        printf("Error: Unable to open or decode the file '%s'\n", filename);
        return NULL;
    }

    int numPixels = (*width) * (*height);
    Pixel* pixelData = (Pixel*)malloc(numPixels * sizeof(Pixel));

    // Copy pixel data from stb_image's RGB format (3 bytes per pixel) to our Pixel struct
    for (int i = 0; i < numPixels; i++) {
        pixelData[i].red = pixels[i * 3 + 0];
        pixelData[i].green = pixels[i * 3 + 1];
        pixelData[i].blue = pixels[i * 3 + 2];
    }

    stbi_image_free(pixels);

    return pixelData;
}


void writeBMP(const char* filename, int width, int height, Pixel* pixels) {
    // Convert the Pixel array back to the format required by stb_image_write
    uint8_t* pixelData = (uint8_t*)malloc(width * height * 3 * sizeof(uint8_t));
    
    for (int i = 0; i < width * height; i++) {
        pixelData[i * 3 + 0] = pixels[i].red;
        pixelData[i * 3 + 1] = pixels[i].green;
        pixelData[i * 3 + 2] = pixels[i].blue;
    }

    // Write the pixel data to a new BMP file
    int result = stbi_write_bmp(filename, width, height, 3, pixelData);
    free(pixelData);

    if (!result) {
        printf("Error: Unable to write the BMP file '%s'\n", filename);
    }
}