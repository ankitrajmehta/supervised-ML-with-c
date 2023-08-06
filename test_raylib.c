#include <raylib.h>

int main() {
    // Initialize raylib
    InitWindow(800, 600, "Raylib Test");
    
    SetTargetFPS(60);
    
    while (!WindowShouldClose()) {
        BeginDrawing();
        
        ClearBackground(RAYWHITE); // Clear the background to white
        
        EndDrawing();
    }
    
    // Clean up and close raylib
    CloseWindow();
    
    return 0;
}
