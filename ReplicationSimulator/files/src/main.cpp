#include "IPCManager.h"

int main(int argc, char** argv)
{
	IPCManager* ipMgr = new IPCManager();
	ipMgr->runIPC(L"Game.exe");
	return 0;
}
