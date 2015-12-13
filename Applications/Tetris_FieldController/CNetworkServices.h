//---------------------------------------------------------------------------

#ifndef CNetworkServicesH
#define CNetworkServicesH
//---------------------------------------------------------------------------

#include <vcl.h>
#include "CSerialCmdHandler.h"
#include "CTetrisNode.h"
#include <deque>

#include <IdUDPBase.hpp>
#include <IdUDPClient.hpp>

class CNetworkServices : public TThread
{
private:
	CSerialCmdHandler *SerialHandler;
	TIdUDPClient *UDPClient;
	std::deque<unsigned char> RecvQ;

	void __fastcall Execute();

	bool Terminated;

	unsigned char NodeMap[11][21];
	unsigned char LedMap[11][21];

	CTetrisNode *TNodes[50];


	unsigned char CorrectValue(unsigned char Value);

public:
	__fastcall CNetworkServices(CSerialCmdHandler *_SerialHandler, CTetrisNode *Nodes[50], TIdUDPClient *_UDPClient);
	__fastcall ~CNetworkServices();

	void XY2NodeLed(unsigned char x, unsigned char y, unsigned char &NodeID, unsigned char &LED);

	void Run();
	void Kill();

};

#endif
