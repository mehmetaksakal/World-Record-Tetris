//---------------------------------------------------------------------------

#ifndef CSocketH
#define CSocketH
//---------------------------------------------------------------------------

#include <winsock2.h>
#include <Windows.h>
#include <ws2tcpip.h>
#include <stdio.h>
#include "CDebugConsole.h"
#include "CNetworkServices.h"

// size of our buffer
#define DEFAULT_BUFLEN 512
#define MAX_PACKET_SIZE 1000000

// port to connect sockets through
#define DEFAULT_PORT "5454"

// Need to link with Ws2_32.lib, Mswsock.lib, and Advapi32.lib
#pragma comment (lib, "Ws2_32.lib")
#pragma comment (lib, "Mswsock.lib")
#pragma comment (lib, "AdvApi32.lib")

class CSocket : public TThread {
	public:
		// ctor/dtor
		CSocket(CDebugConsole *DebugConsole);
		int receivePackets();

		void Run();
		void Kill();

	private:
	// for error checking function calls in Winsock library
	int iResult;
	CDebugConsole *DC;
	char recvbuf[DEFAULT_BUFLEN];

	// socket for client to connect to server
	SOCKET ConnectSocket;

	void __fastcall Execute();

	bool Connected;
	bool Terminated;
};

#endif
