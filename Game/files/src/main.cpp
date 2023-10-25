
#include <string>
#include <raylib.h>
#include <raymath.h>
#include "GameManager.h"
#include "Player.h"
#include "Background.h"
#include "Obstacle.h"
#include "Rock.h"
#include "UI.h"


#define DEBUG_LOG(text) DrawText(text, 300,200,48,RED);
 

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
	//();
	//ui->update();
	GameManager::getInstance()->playGame(std::bind(&UI::update, ui), std::bind(&UI::draw, ui));
	GameManager::getInstance()->freeResources();
	GameManager::getInstance()->uninitialise();

	             
	return 0;
}