#include "GraphicElement.h"

#include <windows.h>
#include <stdio.h>
#include <conio.h>
#include <tchar.h>
#include <iostream>
#include <cstdio>
#include <tlhelp32.h>

#pragma comment(lib, "user32.lib")


#define BUF_SIZE 256
TCHAR szName[] = TEXT("Global\\MyFileMappingObject");

HANDLE GetProcessByName(const wchar_t* name);

int main(int argc, char** argv)
{
	const wchar_t* TARGET_PROCESS_NAME = L"Game.exe";
	
	HANDLE processHandle = GetProcessByName(TARGET_PROCESS_NAME);

	GraphicElement* e = nullptr;
	
	HANDLE hMapFile;
	LPCTSTR pBuf;

	hMapFile = OpenFileMapping(
		FILE_MAP_ALL_ACCESS,   // read/write access
		FALSE,                 // do not inherit the name
		szName);               // name of mapping object

	if (hMapFile == NULL)
	{
		_tprintf(TEXT("Could not open file mapping object (%d).\n"),
			GetLastError());
		return 1;
	}

	pBuf = (LPTSTR)MapViewOfFile(hMapFile, // handle to map object
		FILE_MAP_ALL_ACCESS,  // read/write permission
		0,
		0,
		BUF_SIZE);

	if (pBuf == NULL)
	{
		_tprintf(TEXT("Could not map view of file (%d).\n"),
			GetLastError());

		CloseHandle(hMapFile);

		return 1;
	}
	
	while (true)
	{
		unsigned long long adress = std::stoull(std::wstring(pBuf));
		if (adress != 0)
		{
			GraphicElement buffer;
			SIZE_T NumberOfBytesToRead = sizeof(buffer); //this is equal to 4
			SIZE_T NumberOfBytesActuallyRead;
			bool err = ReadProcessMemory(processHandle, (LPCVOID)std::stoull(std::wstring(pBuf)), &buffer, NumberOfBytesToRead, &NumberOfBytesActuallyRead);
			if( !err || NumberOfBytesActuallyRead == NumberOfBytesToRead)
				std::wcout << L"Position : " << buffer.getPosition().x << buffer.getPosition().y << std::endl;
		}
	}

	UnmapViewOfFile(pBuf);

	CloseHandle(hMapFile);

	return 0;
}



HANDLE GetProcessByName(const wchar_t* name)
{
	DWORD pid = 0;

	// Create toolhelp snapshot.
	HANDLE snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
	PROCESSENTRY32 process;
	ZeroMemory(&process, sizeof(process));
	process.dwSize = sizeof(process);

	// Walkthrough all processes.
	if (Process32First(snapshot, &process))
	{
		do
		{
			// Compare process.szExeFile based on format of name, i.e., trim file path
			// trim .exe if necessary, etc.
			if (std::wstring(process.szExeFile) == std::wstring(name))
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