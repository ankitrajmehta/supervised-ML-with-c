#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "ml.h"

#define TRAIN_ROWS 456    // Maximum number of rows in the CSV file
#define MAX_COLS 14    // Maximum number of columns in the CSV file
#define TEST_ROWS 50


void csvopener(float train[TRAIN_ROWS][MAX_COLS],float test[TEST_ROWS][MAX_COLS])
{
    char filename[] = "data.csv";
    char testname[] = "test.csv";
    FILE *csvFile;
    char line[1000];
    char *token;
    int rows = 0;
    int cols = 0;

    csvFile = fopen(filename, "r");
    if (csvFile == NULL) {
        perror("Error opening file");
        return;
    }

    // Read lines from the train CSV file and parse them into the 2D array
    while (fgets(line, sizeof(line), csvFile)) {
        token = strtok(line, ",");
        cols = 0;
        while (token != NULL) {
            train[rows][cols] = atof(token);
            cols++;
            token = strtok(NULL, ",");
        }
        rows++;
    }
    fclose(csvFile);

    csvFile = fopen(testname, "r");
    if (csvFile == NULL) {
        perror("Error opening file");
        return;
    }

    // Read lines from the test CSV file and parse them into the 2D array
    rows=0;
    cols=0;
    while (fgets(line, sizeof(line), csvFile)) {
        token = strtok(line, ",");
        cols = 0;
        while (token != NULL) {
            test[rows][cols] = atof(token);
            cols++;
            token = strtok(NULL, ",");
        }
        rows++;
    }
    fclose(csvFile);
}


int main()
{
    float train[TRAIN_ROWS][MAX_COLS];
    float test[TEST_ROWS][MAX_COLS];
    double w[MAX_COLS];
    double b;
    csvopener(train,test);
    int c = TRAIN_ROWS;
    int max_cols = MAX_COLS;


    int epoch=20000;
    double rate=1e-3;
    double range_max=100000000000;
    double range_min=0 ;
    

    float *wb = (float*)malloc(max_cols*sizeof(int));
    wb = linear_regression_model(c,max_cols, train,epoch,rate ,range_max,
    range_min);


    for (int l = 0; l< max_cols-1; l++)
    {
        w[l] = wb[l];
    }
    b = wb[max_cols-1];

    printf("%lf\n", acc(TEST_ROWS,max_cols,w,b,test));

    
for(int k=0; k<=TEST_ROWS; k++)
   { float resultant=0.0;
    for (int l = 0; l<MAX_COLS; l++)
    {
    resultant += w[l]*test[k][l];
    }
    resultant+=b;

    printf("result for %d = %lf with %f\n",k, resultant, test[k][1]);}


    double costt =  rmse(c,max_cols, w, b, test);
    printf("RMSE = %lf",costt);



}