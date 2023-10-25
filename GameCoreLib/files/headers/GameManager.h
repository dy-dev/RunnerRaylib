#pragma once
#include <raylib.h>
#include <vector>
#include <functional>

class Player;
class GraphicElement;
class GameManager
{

private:
	static int s_iFPS;
	static int s_iGameSpeed;   // Number of sprite sheet frames shown by second
	static Vector2 s_ScreenSize;
	static Vector2 m_PlayerStartingPosition;

	static GameManager* s_pGameManager;
	static Player* s_pPlayer;
	static GraphicElement* s_tmp;
	
	/**
	 * Every graphics element that will need to be updated and drawn on screen
	 */
	static std::vector<GraphicElement*> s_GameElements;
	static std::vector<int> s_IndexesGameElementsToDelete;

	GameManager();

	static void prepareGame();
	static void manageGameSpeed();
	static void manageReplication();
	static void endReplication();
	

public:
	static GameManager* getInstance();
	

	static void setup(int p_iGameSpeed, int p_iScreenWidth, int p_iScreenHeight);
	static void manageGame();
	static void drawElements();
	static void uninitialise();
	static void playGame(std::function<void ()> update = nullptr, std::function<void ()> draw = nullptr);
	static void freeResources();

	static const Vector2& getWindowSize();
	static const Player* getPlayer();
	static const Vector2& getPlayerStartingPosition();
	int getGameSpeed();
};

