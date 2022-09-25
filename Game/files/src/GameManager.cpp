#include "GameManager.h"
#include "Player.h"


#include <windows.h>
#include <stdio.h>
#include <conio.h>
#include <tchar.h>

#define MAX_FRAME_SPEED     15
#define MIN_FRAME_SPEED      1

int GameManager::s_iFPS = 0;
int GameManager::s_iGameSpeed = 0;   // Number of sprite
int GameManager::s_iScreenWidth = 0;
int GameManager::s_iScreenHeight = 0;
Vector2 GameManager::m_PlayerStartingPosition = { 0,0 };

GameManager* GameManager::s_pGameManager = nullptr;
Player* GameManager::s_pPlayer = nullptr;

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
	manageReplication();
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

void GameManager::manageReplication()
{
	std::wstring szMsg = L"Player position " + std::to_wstring(s_pPlayer->getPosition().x) + L", " + std::to_wstring(s_pPlayer->getPosition().y);
	
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
