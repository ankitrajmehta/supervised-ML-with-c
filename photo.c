#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "ml.h"
#include "opener.h"

void apply(int height, int width, Pixel* pixels,float w_blue, float b_blue,float w_red, float b_red,float w_green, float b_green, char* outfile)
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int blue = ceil(pixels[i * width + j].blue* w_blue + b_blue);
            int red = ceil(pixels[i * width + j].red * w_red + b_red);
            int green =  ceil(pixels[i * width + j].green * w_green + b_green);
            blue = fmin(blue ,255);
            pixels[i * width + j].blue = fmax(blue, 0);
            red = fmin(red,255);
            pixels[i * width + j].red = fmax(red,0);
            green =fmin(green,255);
            pixels[i * width + j].green =fmax(green,0);

        }
    }



    writeBMP(outfile, width, height, pixels);



}

int main()
{
    
    // Remember filenames
    char *infile = "aaa.bmp";
    char *outfile = "om.bmp";
    char *label_file="blue.bmp";
    char *to_edit="aaa.bmp";

    int width, height;
    Pixel* x_pixels = readBMP(infile, &width, &height); // Updated function call
    Pixel* label_pixels = readBMP(label_file, &width, &height); // Updated function call
    Pixel* test_pixels = readBMP(to_edit, &width, &height); // Updated function call


  


    // Filter image
    //for blue
    float train[height*width][2];
    int c = 0;
    for (int i = 0; i <height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            train[c][0]=fmin(fmax(x_pixels[i * width + j].blue,0),255);
            train[c][1]=fmin(fmax(label_pixels[i * width + j].blue,0),255);
            c++;

        }
    }


    float* wb = linear_regression_model(c,2,train,400,1e-2,255,0);
    float w_blue = wb[0];
    float b_blue=wb[1];
    free(wb);

    //for red
    c = 0;
    for (int i = 0; i <height; i++)
    {
        for (int j = 0; j < width; j++)
        {            
            train[c][0]=fmin(fmax(x_pixels[i * width + j].red,0),255);
            train[c][1]=fmin(fmax(label_pixels[i * width + j].red,0),255);
            c++;

        }
    }

    float* wr = linear_regression_model(c,2,train,400,1e-2,255,0);
    float w_red = wr[0];
    float b_red=wr[1];
    free(wr);

    //for green
    c = 0;
    for (int i = 0; i <height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            train[c][0]=fmin(fmax(x_pixels[i * width + j].green,0),255);
            train[c][1]=fmin(fmax(label_pixels[i * width + j].green,0),255);
            c++;

        }
    }


    float* wg = linear_regression_model(c,2,train,400,1e-2,255,0);
    float w_green = wg[0];
    float b_green=wg[1];
    free(wg);
    printf("w_blue: %f b_blue: %f, w_r: %f b_r: %f, w_g: %f b_g: %f", w_blue, b_blue, w_red, b_red, w_green, b_green);
   
    
    apply(height, width, test_pixels, w_blue, b_blue, w_red, b_red, w_green, b_green,outfile);



    // Free memory for image
    free(x_pixels);
    free(label_pixels);

    return 0;
}
