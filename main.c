#include <stdio.h>
#include <stdlib.h>

float train[8][2] = {
    {0,0},
    {1,2},
    {2,4},
    {3,6},
    {4,8},
    {6,12},
    {7,14},
    {20,40},
    {400,800}
};

#define COUNT sizeof(train)/sizeof(train[0])

/*double cost(float w, float b)
{
    double result = 0, y_p;
    for (int i = 0; i < COUNT; i++)
    {
        y_p = w * train[i][0] + b;
        float t =y_p - train[i][1];
        result+=t*t;
    }
    double tmp = result/COUNT;
    return tmp;
}*/

double* gradiant(float w, float b)
{
    double dw = 0;
    double db = 0;
    double* tmp = (double*)malloc(2 * sizeof(double));

    for (int i =0; i < COUNT; i++)
    {
        float x = train[i][0];
        float y = train[i][1];
        double y_p = w * x  + b;
        double dj_dw_i = (y_p - y) * x;
        double dj_db_i = y_p - y;

        dw+= dj_dw_i;
        db+=dj_db_i;
    }
    tmp[0] = dw/COUNT;
    tmp[1] = db/COUNT;

    return tmp;
}

int main()
{
    srand(10);
    float w = (rand()/RAND_MAX);
    float b = (rand()/RAND_MAX);
    int epoch = 90000;
    //double h = 1e-5;
    double rate = 1e-3;
    /*
    for (int i = 0; i < epoch; i++)
    {
        float acc = cost(w,b);
        double dw = (cost(w + h, b) - acc);
        double db = (cost(w , b+h) - acc);

        w -= dw;
        b -= db;
    }
    */



    for (int i = 0; i < epoch; i++)
    {
        double* tmp = gradiant(w,b);
        w -= tmp[0]; //tmp[0] is dw
        b -= tmp[1]; //tmp[0] is db
    }

    printf("w = %f, b = %f \n", w, b);
    printf("y p = %f", w*6+ b);
}


