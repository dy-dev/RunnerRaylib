#include "GameManager.h"
#include "Player.h"
#include "Background.h"
#include "Rock.h"

#include <raymath.h>

#include <windows.h>
#include <stdio.h>
#include <conio.h>
#include <tchar.h>

#define MAX_FRAME_SPEED     15
#define MIN_FRAME_SPEED      1

int GameManager::s_iFPS = 0;
int GameManager::s_iGameSpeed = 0;   // Number of sprite
Vector2 GameManager::s_ScreenSize = {};
Vector2 GameManager::m_PlayerStartingPosition = { 0,0 };

GameManager* GameManager::s_pGameManager = nullptr;
Player* GameManager::s_pPlayer = nullptr;
GraphicElement* GameManager::s_tmp = nullptr;
std::vector<GraphicElement*> GameManager::s_GameElements;
std::vector<int> GameManager::s_IndexesGameElementsToDelete;
/************************************************************************/
/* REPLICATION MANAGEMENT                                               */
/************************************************************************/
#define BUF_SIZE 256
wchar_t szName[] = L"Global\\MyFileMappingObject";


HANDLE hMapFile;
LPCTSTR pBuf;

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
	hMapFile = CreateFileMapping(
		INVALID_HANDLE_VALUE,    // use paging file
		NULL,                    // default security
		PAGE_READWRITE,          // read/write access
		0,                       // maximum object size (high-order DWORD)
		BUF_SIZE,                // maximum object size (low-order DWORD)
		szName);                 // name of mapping object

	if (hMapFile == NULL)
	{
		_tprintf(TEXT("Could not create file mapping object (%d).\n"), GetLastError());
	}
	pBuf = (LPTSTR)MapViewOfFile(hMapFile,   // handle to map object
		FILE_MAP_ALL_ACCESS, // read/write permission
		0,
		0,
		BUF_SIZE);

	if (pBuf == NULL)
	{
		_tprintf(TEXT("Could not map view of file (%d).\n"), GetLastError());

		CloseHandle(hMapFile);
	}
}

void GameManager::setup(int p_iGameSpeed, int p_iScreenWidth, int p_iScreenHeight)
{
	s_iGameSpeed = p_iGameSpeed;
	s_ScreenSize = { (float)p_iScreenWidth, (float)p_iScreenHeight };
	m_PlayerStartingPosition = Vector2{ 50.0f, 240.0f };

	InitWindow((int)s_ScreenSize.x, (int)s_ScreenSize.y, "Empty");
	s_tmp = new GraphicElement("assets/rock.png", 1);
	prepareGame();
}

void GameManager::prepareGame()
{
	/**
	 * The background and the player are instanced and added to the list
	 */
	Background* bg = new Background("assets/desert_BG.png", (float)GameManager::getInstance()->getGameSpeed());
	s_GameElements.push_back(bg);
	s_pPlayer = new Player("assets/sprites.png", (float)GameManager::getInstance()->getGameSpeed(), 7, 4);
	s_GameElements.push_back(s_pPlayer);


	s_iFPS = 60;
	SetTargetFPS(s_iFPS);               // Set our game to run at 60 frames-per-second
}

void GameManager::manageGame()
{
	manageGameSpeed();
	manageReplication();
	s_pPlayer->manageInput();
	s_tmp->addToPosition(Vector2{ 1,1 });

	/**
	 * update each element
	 */
	if (rand() % 100 > 95)
	{
		Rock* obstacle = new Rock("assets/rock.png", (float)GameManager::getInstance()->getGameSpeed());
		auto pos = s_GameElements[s_GameElements.size() - 1]->getPosition();
		auto tmppos = Vector2Add({ pos.x,getPlayerStartingPosition().y }, { 850.f + rand() % 100, (float)s_pPlayer->getHeight() });
		obstacle->setPosition(tmppos);

		s_GameElements.push_back(obstacle);
	}
	int i = 0;
	for (auto element : s_GameElements)
	{
		Obstacle* obs = dynamic_cast<Obstacle*>(element);
		if (obs) {
			if (obs->isOffScreen())
			{
				s_IndexesGameElementsToDelete.push_back(i);
			}
			else
			{
				if (obs->getState() == EObstacleState::ON && s_pPlayer->isColliding(obs))
				{
					s_pPlayer->addPoints(-1);
					obs->setState(EObstacleState::COLLIDED);
				}
			}
		}
		element->update();
		i++;
	}
	for (int i = s_IndexesGameElementsToDelete.size() - 1; i >= 0; i--)
	{
		auto elmtIndex = s_IndexesGameElementsToDelete[i];
		GraphicElement* element = s_GameElements[elmtIndex];
		Obstacle* obs = dynamic_cast<Obstacle*>(element);
		if (obs && obs->getState() == EObstacleState::ON)
			s_pPlayer->addPoints(1);

		s_GameElements.erase(s_GameElements.begin() + elmtIndex);
		delete element;
	}
	s_IndexesGameElementsToDelete.clear();
}

void GameManager::drawElements()
{
	for (auto element : s_GameElements)
	{
		element->draw();
	}
}

const Vector2& GameManager::getWindowSize()
{
	return s_ScreenSize;
}

const Player* GameManager::getPlayer()
{
	return s_pPlayer;
}

void GameManager::uninitialise()
{
	for (auto element : s_GameElements)
	{
		element->unloadTexture();
	}
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

void GameManager::manageReplication()
{
	std::wstring szMsg = std::to_wstring((unsigned long long)s_tmp);
	if (pBuf)
		CopyMemory((PVOID)pBuf, szMsg.c_str(), (_tcslen(szMsg.c_str()) * sizeof(TCHAR)));
}

void GameManager::endReplication()
{
	UnmapViewOfFile(pBuf);
	CloseHandle(hMapFile);
}

const Vector2& GameManager::getPlayerStartingPosition()
{
	return m_PlayerStartingPosition;
}
