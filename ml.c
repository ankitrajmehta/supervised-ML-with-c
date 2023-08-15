#include <stdio.h>
#include <stdlib.h>
#include <math.h>



int p = 0;




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
    for (int i = 0; i < c; i++)
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

void gradiant(int max_cols,double w[max_cols-1], double b,double rate,double range_max, double range_min, float train[count][max_cols],double max[max_cols-1])
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
        y_p = fmin(y_p, range_max);
        y_p = fmax(y_p, range_min);
        for ( int k =0; k<x_vals; k++)
        {
            dw[k]+= (y_p - y) * (x[k])/max[k]; //(max[k]);

        }
        db+= y_p - y;
    }

    for (int i = 0; i<max_cols -1 ; i++){
        w[i] -= (dw[i]/count)*rate; //dw
    }

    p++;
    if (p%10000 == 0 || p == 1 )
    {
        printf("Epoch: %d\n", p);
        printf("%lf \n",rmse(count,max_cols,w,b,train));
    }


}


  
void max_find(int TRAIN_ROWS ,int n,float train[TRAIN_ROWS][n],double max[n])
{
    
    for (int i =0; i < n;i++)
    {
        max[i]=train[0][i];
        
    }
    
    for (int i =0; i < n;i++)
    {
        

            for (int j =0; j < TRAIN_ROWS; j++)
            {
                if (max[i] < train[j][i])
                {
                    max[i] = train[j][i];
                    
                }

            } 
            
            
        }
    }
void min_find(int TRAIN_ROWS ,int n,float train[TRAIN_ROWS][n],double min[n])
{
    
    for (int i =0; i < n;i++)
    {
        min[i]=train[0][i];
        
    }
    
    for (int i =0; i < n;i++)
    {
        

            for (int j =0; j < TRAIN_ROWS; j++)
            {
                if (min[i] > train[j][i])
                {
                    min[i] = train[j][i];
                    
                }
            } 
            
        }
    }

float* linear_regression_model(int c,int max_cols, float train[c][max_cols],int epoch,double rate ,double range_max,
    double range_min )
{
    count = c;
    srand(10);    
    double w[max_cols];
    for (int i=0; i < max_cols;i++)
    {
        w[i] = 0*(rand()/RAND_MAX)/2;
    }
    double b = 0;
    
    double max[max_cols];
    


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
min_find( c, max_cols,train,max);
max_find( c, max_cols,train,max);

p=0;
    for (int i = 0; i < epoch; i++)
    {
        gradiant( max_cols,w,b,rate,range_max,range_min, train,max);
    }

    float *wb = (float*)malloc(max_cols*sizeof(int));
    for (int i =0; i<max_cols-1;i++)
    {
        wb[i] = w[i];
    }
    wb[max_cols-1]= b;
    printf("--\n");
    return wb;

}
