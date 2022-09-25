
#include <string>
#include <raylib.h>
#include "GameManager.h"
#include "Player.h"
#include "Background.h"

int main(void)
{
	// Initialization
	//--------------------------------------------------------------------------------------
	/**
	 * GameManager creation (parameter are speed and window size)
	 */
	GameManager::getInstance()->setup(8, 800, 400);
	// NOTE: Textures/Fonts MUST be loaded after Window initialization (OpenGL context is required)

	/**
	 * Every graphics element that will need to be updated and drawn on screen
	 */
	std::vector<GraphicElement*> gameElements;

	/**
	 * The background and the player are instanced and added to the list
	 */
	Background* bg = new Background("assets/desert_BG.png", (float)GameManager::getInstance()->getGameSpeed());
	gameElements.push_back(bg);
	Player* player = new Player("assets/sprites.png", (float)GameManager::getInstance()->getGameSpeed(), 7, 4);
	gameElements.push_back(player);

	/**
	 * Game manager setup
	 */
	GameManager::getInstance()->setPlayer(player);
	GameManager::getInstance()->setTargetFrameRate(60);
									//--------------------------------------------------------------------------------------
									// Main game loop
	while (!WindowShouldClose())    // Detect window close button or ESC key
	{
		//----------------------------------------------------------------------------------
		// Update
		//----------------------------------------------------------------------------------

		// Send the input management to the game manager
		GameManager::getInstance()->manageInputs();
		
		/**
		 * update each element
		 */
		for (auto element : gameElements)
		{
			element->update();
		}

		
		//----------------------------------------------------------------------------------
		// Draw
		//----------------------------------------------------------------------------------
		BeginDrawing();
		ClearBackground(RAYWHITE);
		
		/**
		 * draw each element
		 */
		for (auto element : gameElements)
		{
			element->draw();
		}
		
		EndDrawing();
		//----------------------------------------------------------------------------------
	}

	//--------------------------------------------------------------------------------------
	// De-Initialization
	//--------------------------------------------------------------------------------------
	for (auto element : gameElements)
	{
		element->unloadTexture();
	}

	CloseWindow();              // Close window and OpenGL context
	return 0;
}