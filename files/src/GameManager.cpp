#include "GameManager.h"
#include "Player.h"

#define MAX_FRAME_SPEED     15
#define MIN_FRAME_SPEED      1

int GameManager::s_iFPS = 0;
int GameManager::s_iGameSpeed = 0;   // Number of sprite
int GameManager::s_iScreenWidth = 0;
int GameManager::s_iScreenHeight = 0;
Vector2 GameManager::m_PlayerStartingPosition = { 0,0 };

GameManager* GameManager::s_pGameManager = nullptr;
Player* GameManager::s_pPlayer = nullptr;

GameManager* GameManager::getInstance()
{
	if (s_pGameManager == nullptr)
	{
		s_pGameManager = new GameManager();
	}
	return s_pGameManager;
}

GameManager::GameManager()
{

}

void GameManager::setup(int p_iGameSpeed, int p_iScreenWidth, int p_iScreenHeight)
{
	s_iGameSpeed = p_iGameSpeed;
	s_iScreenWidth = p_iScreenWidth;
	s_iScreenHeight = p_iScreenHeight;
	m_PlayerStartingPosition = Vector2{ 50.0f, 240.0f };

	InitWindow(s_iScreenWidth, s_iScreenHeight, "Empty");
}

void GameManager::setTargetFrameRate(int p_iFPS)
{
	s_iFPS = p_iFPS;
	SetTargetFPS(s_iFPS);               // Set our game to run at 60 frames-per-second
}

void GameManager::setPlayer(Player* p_pPlayer)
{
	s_pPlayer = p_pPlayer;
}

void GameManager::manageInputs()
{
	manageGameSpeed();
	s_pPlayer->manageInput();
}

int GameManager::getGameSpeed()
{
	return s_iGameSpeed;
}

void GameManager::manageGameSpeed()
{
	if (IsKeyPressed(KEY_RIGHT)) s_iGameSpeed++;
	else if (IsKeyPressed(KEY_LEFT)) s_iGameSpeed--;

	if (s_iGameSpeed > MAX_FRAME_SPEED) s_iGameSpeed = MAX_FRAME_SPEED;
	else if (s_iGameSpeed < MIN_FRAME_SPEED) s_iGameSpeed = MIN_FRAME_SPEED;
}

const Vector2& GameManager::getPlayerStartingPosition()
{
	return m_PlayerStartingPosition;
}
