
#include <string>
#include <raylib.h>

#define MAX_FRAME_SPEED     15
#define MIN_FRAME_SPEED      1

int main(void)
{
    // Initialization
    //--------------------------------------------------------------------------------------
    const int screenWidth = 800;
    const int screenHeight = 400;

    InitWindow(screenWidth, screenHeight, "Empty");
    // NOTE: Textures/Fonts MUST be loaded after Window initialization (OpenGL context is required)


    SetTargetFPS(60);               // Set our game to run at 60 frames-per-second
                                    //--------------------------------------------------------------------------------------
                                    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        // Update
        //----------------------------------------------------------------------------------


		//----------------------------------------------------------------------------------
        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();

        ClearBackground(RAYWHITE);
	

        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
   
    
    CloseWindow();              // Close window and OpenGL context

    return 0;
}