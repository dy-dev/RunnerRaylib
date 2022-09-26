#pragma once
#include <windows.h>
#include <xstring>
#define BUF_SIZE 256

class IPCManager
{
private:

	std::wstring szName;
	HANDLE hMapFile;
	LPCTSTR pBuf;

	HANDLE GetProcessByName(const std::wstring& p_wsName);
	void ManageIPC(HANDLE processHandle);
	HANDLE OpenIPC();
	void CommunicationLoop(HANDLE processHandle);

public:
	IPCManager();
	void runIPC(std::wstring processName);
};

