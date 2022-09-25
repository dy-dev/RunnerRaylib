#pragma once
#include <raylib.h>

class Player;
class GameManager
{

private:
	static int s_iFPS;
	static int s_iGameSpeed;   // Number of sprites heet frames shown by second
	static int s_iScreenWidth;
	static int s_iScreenHeight;
	static Vector2 m_PlayerStartingPosition;

	static GameManager* s_pGameManager;
	static Player* s_pPlayer;

	GameManager();

	static void manageGameSpeed();

public:
	static GameManager* getInstance();
	

	static void setup(int p_iGameSpeed, int p_iScreenWidth, int p_iScreenHeight);
	static void setTargetFrameRate(int p_iFPS);
	static void setPlayer(Player* p_pPlayer);
	static void manageInputs();

	int getGameSpeed();
	

	const Vector2& getPlayerStartingPosition();
};

