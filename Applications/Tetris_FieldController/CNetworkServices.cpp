//---------------------------------------------------------------------------

#pragma hdrstop

#include "CNetworkServices.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)

__fastcall CNetworkServices::CNetworkServices(CSerialCmdHandler *_SerialHandler, CTetrisNode *Nodes[50], TIdUDPClient *_UDPClient) : TThread(true)
{
	unsigned char x, y, bx, by, node_m, value;

	this->SerialHandler = _SerialHandler;
	this->UDPClient = _UDPClient;
	this->RecvQ.clear();
	this->Terminated = true;

	for(int i =0; i < 50; i++)
	{
		this->TNodes[i] = Nodes[i];
	}


	// Fill LedMap
	for(x = 1; x < 11; x++)
	{
		for(y = 1; y < 21; y++)
		{
			if(x % 2) // X is Odd
			{
				LedMap[x][y] = 1;
				y++;
				LedMap[x][y] = 2;
			}
			else // X is Even
			{
				LedMap[x][y] = 3;
				y++;
				LedMap[x][y] = 4;
			}
		}
	}

	for(x = 1; x < 6; x++)
	{
		for(y = 1; y < 11; y++)
		{
			by = y + y - 1;
			bx = x + x - 1;
			node_m = (x - 1) * 10;

			NodeMap[bx][by] = y + node_m;
			NodeMap[bx+1][by] = y + node_m;
			NodeMap[bx][by+1] = y + node_m;
			NodeMap[bx+1][by+1] = y + node_m;
		}
	}
}

__fastcall CNetworkServices::~CNetworkServices()
{
    this->Terminated = true;
}

void CNetworkServices::Run()
{
	this->Terminated = false;
	this->Start();
}

void CNetworkServices::Kill()
{
	this->Terminated = true;
	this->Terminate();
}

void CNetworkServices::XY2NodeLed(unsigned char x, unsigned char y, unsigned char &NodeID, unsigned char &LED)
{
	NodeID = this->NodeMap[x][y];
	LED = this->LedMap[x][y];
}

unsigned char CNetworkServices::CorrectValue(unsigned char Value)
{

	switch(Value)
	{
		case 0x01:
			return 0x06;
		case 0x02:
			return 0x03;
		case 0x03:
			return 0x02;
		case 0x04:
			return 0x01;
		case 0x05:
			return 0x04;
		case 0x06:
			return 0x07;
		case 0x07:
			return 0x05;
		default:
			break;
	}

	//if(Value != 0x00) return 0x07;

	return 0x00;
}

void __fastcall CNetworkServices::Execute()
{
	unsigned char value, x, y, node, led;
	AnsiString Msg, X, Y, Value;

	while (!Terminated)
	{
		Msg = this->UDPClient->ReceiveString(1);

		if(Msg.Length() > 0)
		{
			x = Msg[1];
			y = Msg[2];
			value = Msg[3] - 1;

			this->XY2NodeLed(x, y, node, led);
			value = this->CorrectValue(value);

			this->SerialHandler->WriteLed(this->TNodes[node-1]->devNum, node, led, value);
        }
	}
}
