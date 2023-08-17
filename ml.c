#include <stdio.h>
#include <stdlib.h>
#include <math.h>

//graph header files
#include <SDL2/SDL.h>
#include <SDL_ttf.h>

//graph
// Screen dimensions
const int SCREEN_WIDTH = 1000;
const int SCREEN_HEIGHT = 800;

// Graph dimensions and parameters
const int GRAPH_WIDTH = 1000;
const int GRAPH_HEIGHT = 500;
const int GRAPH_X = 60;//(SCREEN_WIDTH - GRAPH_WIDTH) / 2;
const int GRAPH_Y = 700; //(SCREEN_HEIGHT - GRAPH_HEIGHT) / 0.2;
const int NUM_VALUES = GRAPH_WIDTH; // Number of values to display
const double SCALE_X = 0.9; // X-axis scaling factor
const double SCALE_Y = 20; // Y-axis scaling factor

//current position of x coordinate
int currentX = 0;


//ML code
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

void drawgraph(double values[NUM_VALUES], int p, SDL_Window* window, SDL_Renderer* renderer ){
    // Clear the screen
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        SDL_RenderClear(renderer);

        // Draw axes
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderDrawLine(renderer, GRAPH_X - 10, GRAPH_Y, GRAPH_X - 10, GRAPH_Y - GRAPH_HEIGHT);
        SDL_RenderDrawLine(renderer, GRAPH_X - 10, GRAPH_Y, GRAPH_X + GRAPH_WIDTH, GRAPH_Y);

        // Draw graph
        SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
        for (int i = 1; i < currentX; i++) {
            int x1 = GRAPH_X + (i - 1)* SCALE_X;
            int y1 = GRAPH_Y - (int)(values[i - 1] * SCALE_Y);
            int x2 = GRAPH_X + i * SCALE_X;
            int y2 = GRAPH_Y - (int)(values[i] * SCALE_Y);
            SDL_RenderDrawLine(renderer, x1, y1, x2, y2);
        }

        // Draw epoch and cost values on top
        

        char epochText[20];
        char costText[20];
        snprintf(epochText, sizeof(epochText), "Epoch: %d", p);
        snprintf(costText, sizeof(costText), "Cost: %lf", values[currentX - 1]);

        SDL_Color textColor = {0, 0, 0, 255};

         //open font
        TTF_Font* Sans = TTF_OpenFont("OpenSans-Regular.ttf", 24);
        if (!Sans) {
            SDL_Log("Failed to open font: %s", TTF_GetError());
            SDL_DestroyRenderer(renderer);
            SDL_DestroyWindow(window);
            SDL_Quit();
           
        }
        
        SDL_Surface* epochSurface = TTF_RenderText_Solid(Sans, epochText, textColor);
        SDL_Surface* costSurface = TTF_RenderText_Solid(Sans, costText, textColor);

        SDL_Texture* epochTexture = SDL_CreateTextureFromSurface(renderer, epochSurface);
        SDL_Texture* costTexture = SDL_CreateTextureFromSurface(renderer, costSurface);

        int epochWidth, epochHeight;
        SDL_QueryTexture(epochTexture, NULL, NULL, &epochWidth, &epochHeight);
        int costWidth, costHeight;
        SDL_QueryTexture(costTexture, NULL, NULL, &costWidth, &costHeight);

        SDL_Rect epochRect = {SCREEN_WIDTH / 2 - epochWidth / 2, 700, epochWidth, epochHeight};
        SDL_Rect costRect = {140 / 2, 30 + epochHeight, costWidth, costHeight};

        SDL_RenderCopy(renderer, epochTexture, NULL, &epochRect);
        SDL_RenderCopy(renderer, costTexture, NULL, &costRect);

        SDL_DestroyTexture(epochTexture);
        SDL_DestroyTexture(costTexture);
        SDL_FreeSurface(epochSurface);
        SDL_FreeSurface(costSurface);

        // Close the font at the end of each loop iteration
        TTF_CloseFont(Sans);
        
        // Introduce a delay of 100 milliseconds (adjust as needed)
        //SDL_Delay(10); // Delay for 10 milliseconds

       

        // Render to screen
        SDL_RenderPresent(renderer);

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
    
    // Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        SDL_Log("Unable to initialize SDL: %s", SDL_GetError());
        
    }

    // Create a window
    SDL_Window* window = SDL_CreateWindow("SUPERVISED ML", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, 0);
    if (!window) {
        SDL_Log("Failed to create window: %s", SDL_GetError());
        SDL_Quit();
        
    }

    // Create a renderer
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer) {
        SDL_Log("Failed to create renderer: %s", SDL_GetError());
        SDL_DestroyWindow(window);
        SDL_Quit();
        
    }
    // Initialize SDL_TTF
    if (TTF_Init() != 0) {
        SDL_Log("Unable to initialize SDL_TTF: %s", TTF_GetError());
        SDL_Quit();
        
    }
    double values[NUM_VALUES] = {0.0};

    //ML code
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

while (p<epoch) {
        
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                p = epoch;
            }
        }

        
       
        


//p=0;
    
        gradiant( max_cols,w,b,rate,range_max,range_min, train,max);
    


    if (p%(epoch / 100000) == 0 || p == 1 )
        {
            // Get live cost values
            if (currentX < NUM_VALUES) {
            
            values[currentX] = rmse(count,max_cols,w,b,train);
            currentX++;
            }
            else {
            // Shift data to accommodate new value
            for (int i = 0; i < NUM_VALUES - 1; i++) {
                values[i] = values[i + 1];
            }
            values[NUM_VALUES - 1] = rmse(count,max_cols,w,b,train);
        }

            //Draw graph function call
            drawgraph(values, p ,window, renderer);

        }
        



}





    // Cleanup and exit
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    TTF_Quit();
    SDL_Quit();



    float *wb = (float*)malloc(max_cols*sizeof(int));
    for (int i =0; i<max_cols-1;i++)
    {
        wb[i] = w[i];
    }
    wb[max_cols-1]= b;
    printf("--\n");
    return wb;


}
