#pragma once
#include <raylib.h>

class Player;
class GraphicElement;
class GameManager
{

private:
	static int s_iFPS;
	static int s_iGameSpeed;   // Number of sprites heet frames shown by second
	static Vector2 s_ScreenSize;
	static Vector2 m_PlayerStartingPosition;

	static GameManager* s_pGameManager;
	static Player* s_pPlayer;
	static GraphicElement* s_tmp;

	GameManager();

	static void manageGameSpeed();
	static void manageReplication();
	static void endReplication();

public:
	static GameManager* getInstance();
	

	static void setup(int p_iGameSpeed, int p_iScreenWidth, int p_iScreenHeight);
	static void setTargetFrameRate(int p_iFPS);
	static void setPlayer(Player* p_pPlayer);
	static void manageInputs();
	static const Vector2& getWindowSize();
	static const Player* getPlayer();

	int getGameSpeed();
	

	const Vector2& getPlayerStartingPosition();
};

