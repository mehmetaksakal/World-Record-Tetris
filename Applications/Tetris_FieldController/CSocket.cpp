//---------------------------------------------------------------------------

#pragma hdrstop

#include "CSocket.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)

CSocket::CSocket(CDebugConsole *DebugConsole) : TThread(true)
{
    // create WSADATA object
	WSADATA wsaData;
	this->DC = DebugConsole;
	this->Connected = false;
	this->Terminated = true;
	//this->Terminate();

    // socket
    ConnectSocket = INVALID_SOCKET;

    // holds address info for socket to connect to
    struct addrinfo *result = NULL,
                    *ptr = NULL,
                    hints;

    // Initialize Winsock
    iResult = WSAStartup(MAKEWORD(2,2), &wsaData);

	if (iResult != 0) {
		DC->WriteError("WSAStartup failed with error: " + AnsiString(iResult));
        return;
    }



    // set address info
    ZeroMemory( &hints, sizeof(hints) );
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;
	hints.ai_protocol = IPPROTO_TCP;  //TCP connection!!!
    //resolve server address and port
    iResult = getaddrinfo("127.0.0.1", DEFAULT_PORT, &hints, &result);

    if( iResult != 0 )
	{
		DC->WriteError("getaddrinfo failed with error: " + AnsiString(iResult));
        WSACleanup();
        return;
    }

    // Attempt to connect to an address until one succeeds
    for(ptr=result; ptr != NULL ;ptr=ptr->ai_next) {

        // Create a SOCKET for connecting to server
        ConnectSocket = socket(ptr->ai_family, ptr->ai_socktype,
            ptr->ai_protocol);

		if (ConnectSocket == INVALID_SOCKET) {
			DC->WriteError("Socket failed with error: " + AnsiString(WSAGetLastError()));
			WSACleanup();
            return;
        }

        // Connect to server.
        iResult = connect( ConnectSocket, ptr->ai_addr, (int)ptr->ai_addrlen);

        if (iResult == SOCKET_ERROR)
        {
            closesocket(ConnectSocket);
			ConnectSocket = INVALID_SOCKET;
			DC->WriteError("The server is down... did not connect");
		}
    }



    // no longer need address info for server
    freeaddrinfo(result);



    // if connection failed
    if (ConnectSocket == INVALID_SOCKET)
	{
		DC->WriteError("Unable to connect to server!");
        WSACleanup();
        return;
	}

    // Set the mode of the socket to be nonblocking
    u_long iMode = 1;

    iResult = ioctlsocket(ConnectSocket, FIONBIO, &iMode);
    if (iResult == SOCKET_ERROR)
	{
		DC->WriteError("ioctlsocket failed with error: " + AnsiString(WSAGetLastError()));
        closesocket(ConnectSocket);
        WSACleanup();
        return;
	}

	this->Connected = true;
}

int CSocket::receivePackets()
{
	iResult = CNetworkServices::receiveMessage(ConnectSocket, recvbuf, MAX_PACKET_SIZE);

	if ( iResult == 0 )
	{
		DC->WriteError("Connection closed");
		closesocket(ConnectSocket);
		WSACleanup();
		return 0;
	}

	return iResult;
}

void CSocket::Run()
{
	if(this->Connected)
	{
		this->Terminated = false;
		this->Start();
	}
}

void CSocket::Kill()
{
    this->Terminated = true;
}

void __fastcall CSocket::Execute()
{
	while (!Terminated) {
		if(receivePackets() == 0)
		{
			this->Terminated = true;
			this->Terminate();
			return;
		}

		this->DC->WriteMessage(AnsiString(recvbuf));

	}
}

