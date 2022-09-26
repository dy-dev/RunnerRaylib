#include "GraphicElement.h"

#include "IPCManager.h"

#include <stdio.h>
#include <conio.h>
#include <tchar.h>
#include <iostream>
#include <cstdio>
#include <tlhelp32.h>


#pragma comment(lib, "user32.lib")

IPCManager::IPCManager()
{
	szName = L"Global\\MyFileMappingObject";
}

void IPCManager::runIPC(std::wstring processName)
{
	HANDLE processHandle = GetProcessByName(processName);
	ManageIPC(processHandle);
}

HANDLE IPCManager::GetProcessByName(const std::wstring& p_wsName)
{
	DWORD pid = 0;

	// Create tool help snapshot.
	HANDLE snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
	PROCESSENTRY32 process;
	ZeroMemory(&process, sizeof(process));
	process.dwSize = sizeof(process);

	// Walk through all processes.
	if (Process32First(snapshot, &process))
	{
		do
		{
			// Compare process.szExeFile based on format of name, i.e., trim file path
			// trim .exe if necessary, etc.
			if (std::wstring(process.szExeFile) == p_wsName)
			{
				pid = process.th32ProcessID;
				break;
			}
		} while (Process32Next(snapshot, &process));
	}

	CloseHandle(snapshot);

	if (pid != 0)
	{
		return OpenProcess(PROCESS_ALL_ACCESS, FALSE, pid);
	}

	// Not found
	return NULL;
}

void IPCManager::ManageIPC(HANDLE processHandle)
{
	hMapFile = OpenIPC();
	if (hMapFile)
	{
		CommunicationLoop(processHandle);
		UnmapViewOfFile(pBuf);
		CloseHandle(hMapFile);
	}
}

HANDLE IPCManager::OpenIPC()
{
	HANDLE mapFile = OpenFileMapping(
		FILE_MAP_ALL_ACCESS,   // read/write access
		FALSE,                 // do not inherit the name
		szName.c_str());               // name of mapping object

	if (mapFile == NULL)
	{
		_tprintf(TEXT("Could not open file mapping object (%d).\n"),
			GetLastError());
		return 0;
	}

	pBuf = (LPCTSTR)MapViewOfFile(mapFile, // handle to map object
		FILE_MAP_ALL_ACCESS,  // read/write permission
		0,
		0,
		BUF_SIZE);

	if (pBuf == NULL)
	{
		_tprintf(TEXT("Could not map view of file (%d).\n"),
			GetLastError());

		CloseHandle(mapFile);
		return 0;
	}
	return mapFile;
}

void IPCManager::CommunicationLoop(HANDLE processHandle)
{
	GraphicElement buffer;
	unsigned long long adress = std::stoull(pBuf);
	if (adress != 0)
	{
		SIZE_T NumberOfBytesToRead = sizeof(buffer); //this is equal to 4
		SIZE_T NumberOfBytesActuallyRead;
		bool err = ReadProcessMemory(processHandle, (LPCVOID)std::stoull(pBuf), &buffer, NumberOfBytesToRead, &NumberOfBytesActuallyRead);
		if (!err || NumberOfBytesActuallyRead == NumberOfBytesToRead)
		{
			while (true)
			{
				std::wcout << L"Position -> x : " << buffer.getPosition().x << ", and y : " << buffer.getPosition().y << std::endl;
			}
		}
	}
}