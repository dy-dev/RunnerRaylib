
#include <string>
#include <raylib.h>
#include <raymath.h>
#include "GameManager.h"
#include "Player.h"
#include "Background.h"
#include "Obstacle.h"
#include "Rock.h"
#include "UI.h"

int main(void)
{
	// Initialization
	//--------------------------------------------------------------------------------------
	/**
	 * GameManager creation (parameter are speed and window size)
	 */
	// NOTE: Textures/Fonts MUST be loaded after Window initialization (OpenGL context is required)
	GameManager::getInstance()->setup(8, 800, 400);
	
	UI* ui = new UI(GameManager::getInstance()->getWindowSize());

									//--------------------------------------------------------------------------------------
									// Main game loop
	while (!WindowShouldClose())    // Detect window close button or ESC key
	{
		//----------------------------------------------------------------------------------
		// Update
		//----------------------------------------------------------------------------------

		// Send the input management to the game manager
		GameManager::getInstance()->manageGame();
		ui->update();
		
		//----------------------------------------------------------------------------------
		// Draw
		//----------------------------------------------------------------------------------
		BeginDrawing();
		ClearBackground(RAYWHITE);
		
		/**
		 * draw each element
		 */
		GameManager::getInstance()->drawElements();
		ui->draw();

		EndDrawing();
		//----------------------------------------------------------------------------------
	}

	//--------------------------------------------------------------------------------------
	// De-Initialization
	//--------------------------------------------------------------------------------------
	GameManager::getInstance()->uninitialise();

	Ray_CloseWindow();              // Close window and OpenGL context
	return 0;
}