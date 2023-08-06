#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <raylib.h>


#define MAX_DATA_POINTS 100


int p = 0;
double min[13]={0.006320,0.000000,0.460000,0.000000,0.385000,3.561000,2.900000,1.129600,1.000000,187.000000,12.600000,0.320000,1.730000};
double max[13]={88.976200,100.000000, 27.740000,1.000000,0.871000,8.780000,100.000000,12.126500,24.000000,711.000000,22.000000,396.900000,37.970000};


int count;
 
double cost(int c,int max_cols, double w[max_cols-1], float b, float test[c][max_cols])
{
    int x_vals = max_cols-1;
    double result = 0, y_p=0;
    for (int i = 0; i < c; i++)
    {
        y_p=0;
        for (int j=0; j<x_vals;j++)
        {
        y_p += w[j] * test[i][j];
        }
        y_p+=b;
        float t =y_p - test[i][13];
        result+=t;
    }
    double tmp = result/c;
    return tmp;
}

double rmse(int c,int max_cols,double w[max_cols - 1], float b, float test[c][max_cols])
{
    int x_vals = max_cols-1;
    double result = 0, y_p=0;
    for (int i = 0; i < c; i++)
    {
        y_p=0;
        for (int j=0; j<x_vals;j++)
        {
        y_p += w[j] * test[i][j];
        }
        y_p+=b;
        float t =y_p - test[i][13];
        result+=t*t;
    }
    double tmp = result/c;
    return pow(tmp,.5);
}

double acc(int c,int max_cols,double w[max_cols - 1], float b, float test[c][max_cols])
{
    int x_vals = max_cols-1;
    double result = 0, y_p=0,t;
    for (int i = 0; i < c ; i++)
    {
        y_p=0;
        for (int j=0; j<x_vals;j++)
        {
        y_p += w[j] * test[i][j];
        }
        y_p+=b;
        t =fabs(y_p - test[i][x_vals])/test[i][x_vals];
        result+=t;
    }
    double tmp = result/c;
    return (100-tmp*100);
}

void gradiant(int max_cols,double w[max_cols-1], double b,double rate,double range_max, double range_min, float train[count][max_cols])
{
    int c = count;
    int x_vals = max_cols-1;
    double x[x_vals],y;
    double dw[x_vals];
    for (int i=0;i<x_vals;i++)
    {
        dw[i]=0;
    }
    double db = 0;
    double y_p = 0;

    
    for (int i =0; i < c; i++)
    {
        y_p = 0;
        for (int j=0; j<x_vals;j++)
        {
            x[j] = (train[i][j]);
        }
        
        y = (train[i][x_vals]);
        for ( int k =0; k<x_vals; k++)
        {        
            y_p += w[k] * x[k];
        }
        y_p += b;


       // printf("%lf\n", y-y_p);
        //y_p = fmin(y_p, range_max);
        //y_p = fmax(y_p, range_min);
        for ( int k =0; k<x_vals; k++)
        {
            dw[k]+= (y_p - y) * (x[k])/255; //(max[k]);

        }
        db+= y_p - y;
    }

    for (int i = 0; i<max_cols -1 ; i++){
        w[i] -= (dw[i]/count)*rate; //dw
    }

    p++;
    if (p%100 == 0 || p == 1 )
    {
        printf("Epoch: %d\n", p);
        printf("%lf \n",rmse(count,max_cols,w,b,train));
    }


}

void drawGraph(float dataPoints[], int dataCount) {

        //     // Draw graph
        // BeginDrawing();
        // ClearBackground(RAYWHITE);

        // // Draw graph using dataPoints array
        // int startX = 50;
        // int spacingX = (GetScreenWidth() - 2 * startX) / (MAX_DATA_POINTS - 1);

        // for (int i = 0; i < dataCount - 1; i++) {
        //     DrawLine(startX + i * spacingX, GetScreenHeight() - dataPoints[i]*20,
        //              startX + (i + 1) * spacingX, GetScreenHeight() - dataPoints[i + 1]*20, RED);
        // }

        // EndDrawing();


    int startX = 50;
    int spacingX = (GetScreenWidth() - 2 * startX) / (MAX_DATA_POINTS - 1);
    int centerY = GetScreenHeight() /1.2;

    BeginDrawing();
    ClearBackground(RAYWHITE);

    // Draw x-axis line
    DrawLine(startX, centerY, GetScreenWidth() - startX, centerY, BLACK);

    // Draw y-axis line
    DrawLine(startX, 0, startX, GetScreenHeight(), BLACK);

    // Draw graph using dataPoints array
    for (int i = 0; i < dataCount - 1; i++) {        
            DrawLine(startX + i * spacingX, GetScreenHeight() - dataPoints[i]*30,
                     startX + (i + 1) * spacingX, GetScreenHeight() - dataPoints[i + 1]*30, RED);
    }

    // Draw x-axis title
    DrawText("Epoch", GetScreenWidth() / 2 - MeasureText("Epoch", 20) / 2, centerY + 30, 20, BLACK);

    // Draw y-axis title
    DrawText("Cost", 10, GetScreenHeight() / 4, 20, BLACK);

    EndDrawing();

}


float* linear_regression_model(int c,int max_cols, float train[c][max_cols])
{

    // Initialization
    InitWindow(800, 600, "Cost vs Epoch Graph");
    SetTargetFPS(60);
    float dataPoints[MAX_DATA_POINTS]; // Array to store data points
    int dataCount = 0; // Number of data points


    count = c;
    srand(10);    
    double w[max_cols];
    for (int i=0; i < max_cols;i++)
    {
        w[i] = 0*(rand()/RAND_MAX)/2;
    }
    double b = 0;
    int epoch = 100000;
    //double h = 1e-5;
    double rate = 1e-6;
    double range_max=255;
    double range_min =0;
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

p=0;

    while(p<epoch)
    {

    if (p%1000 == 0 || p == 1 )
    {        float newValue = rmse(count,max_cols,w,b,train);

        if (dataCount < MAX_DATA_POINTS) {
            dataPoints[dataCount] = newValue;
            dataCount++;
        } else {
            // Shift data to accommodate new value
            for (int i = 0; i < MAX_DATA_POINTS - 1; i++) {
                dataPoints[i] = dataPoints[i + 1];
            }
            dataPoints[MAX_DATA_POINTS - 1] = newValue;
        }

        drawGraph(dataPoints, dataCount);
    }



        if(WindowShouldClose())
        {
            break;
        }
        gradiant( max_cols,w,b,rate,range_max,range_min, train);

    }

    while(!WindowShouldClose())
    {
        drawGraph(dataPoints, dataCount);

    }

    // Close Raylib
    CloseWindow();
    float *wb = (float*)malloc(max_cols*sizeof(int));
    for (int i =0; i<max_cols-1;i++)
    {
        wb[i] = w[i];
    }
    wb[max_cols-1]= b;
    printf("--\n");
    return wb;

}


