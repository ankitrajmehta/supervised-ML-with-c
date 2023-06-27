#include <stdio.h>

int train[9][2] = {
    {0,0},
    {1,4},
    {2,8},
    {3,12},
    {4,16},
    {5,20},
    {6,24},
    {7,28},
    {8,32}
    
};

#define COUNT 9

float cost(float w, float b)
{
    float res = 0, y_p;
    for (int i = 0; i < COUNT; i++)
    {
        y_p = w * train[i][0] + b;
        float t =y_p - train[i][1];
        res+=t*t;
    }
    float tmp = res/COUNT;
    return tmp;
}

int main()
{
    float w = 1;
    float b = 0;
    int epoch = 90000;
    float h = 1e-5;
    for (int i = 0; i < epoch; i++)
    {
        float acc = cost(w,b);
        float dw = (cost(w + h, b) - acc);
        float db = (cost(w , b+h) - acc);
        
        w -= dw;
        b -= db;
    }
        printf("w = %f, b = %f \n", w, b);
}
