float* linear_regression_model(int c,int max_cols, float train[c][max_cols],int epoch,double rate ,double range_max,
    double range_min);


double cost(int c,int max_cols, double w[max_cols-1], float b, float test[c][max_cols]);

double rmse(int c,int max_cols,double w[max_cols - 1], float b, float test[c][max_cols]);

double acc(int c,int max_cols,double w[max_cols - 1], float b, float test[c][max_cols]);



