#include <stdio.h>
#include <stdlib.h>

float train[][2] = {
    {2.4, 1.2},
    {4.8, 2.4},
    {6.2, 3.1},
    {8.0, 4.0},
    {9.0, 4.5},
    {10.4, 5.2},
    {12.0, 6.0},
    {13.6, 6.8},
    {14.2, 7.1},
    {16.0, 8.0},
    {17.0, 8.5},
    {18.4, 9.2},
    {20.2, 10.1},
    {21.8, 10.9},
    {23.0, 11.5},
    {24.4, 12.2},
    {25.6, 12.8},
    {27.4, 13.7},
    {28.8, 14.4},
    {30.0, 15.0}
};



#define MAX 30

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

double* gradiant(double w, double b)
{
    double dw = 0;
    double db = 0;
    double* tmp = (double*)malloc(2 * sizeof(double));

    for (int i =0; i < COUNT; i++)
    {
        double x = (train[i][0]/MAX);
        double y = (train[i][1]/MAX);
        double y_p = w * x  + b;
        double dj_dw_i = (y_p - y) * x;
        double dj_db_i = y_p - y;

        dw+= dj_dw_i;
        db+=dj_db_i;
    }
    tmp[0] = dw*MAX/COUNT; //dw
    tmp[1] = db*MAX/COUNT; //dw

    return tmp;
}


int main()
{
    srand(10);
    double w = (rand()/RAND_MAX);
    double b = (rand()/RAND_MAX);
    int epoch = 1000000;
    //double h = 1e-5;
    double rate = 1e-2;

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
        w -= tmp[0] ; //tmp[0] is dw
        b -= tmp[1] ; //tmp[0] is db
        free(tmp);  
    }

    printf("w = %lf, b = %lf \n", w, b);
    printf("y p = %lf", w*20+ b);

}