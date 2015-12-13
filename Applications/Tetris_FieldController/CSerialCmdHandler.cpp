//---------------------------------------------------------------------------

#pragma hdrstop

#include "CSerialCmdHandler.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)


__fastcall CSerialCmdHandler::CSerialCmdHandler(CDebugConsole *DebugConsole, CSerial *Serial, CTetrisNode *Nodes[50], TLightweightSemaphore *_Semaphore) : TThread(true)
{
	this->DC = DebugConsole;
	this->S = Serial;
	this->SerialSem = _Semaphore;

	for(int i =0; i < 50; i++)
	{
		this->TNodes[i] = Nodes[i];
	}

	FreeOnTerminate = true;
	Terminated = false;

	CmdBuf[0] = 0x00;
	CmdBuf[1] = 0x00;
	CmdBuf[2] = 0x00;
	CmdBuf[3] = 0x00;
}

__fastcall CSerialCmdHandler::~CSerialCmdHandler()
{
	this->Terminated = true;
}

void CSerialCmdHandler::Kill()
{
	Terminated = true;
}

void CSerialCmdHandler::Run()
{
	Terminated = false;
	this->Start();
}

void CSerialCmdHandler::NodeConfigure(DWORD devNum, char NodeID)
{
	CmdBuf[0] = USB_SEND_CONFIGURE;
	CmdBuf[1] = NodeID;
	CmdBuf[2] = USB_UNUSED;
	CmdBuf[3] = USB_UNUSED;

	S->Write(devNum, CmdBuf, 4);
}

void CSerialCmdHandler::ProcessError(char Error, char NodeID)
{
	switch (Error) {
	case APP_ERROR_GENERAL_FAILURE:
		DC->WriteError("General failure on node: " + AnsiString((unsigned int)NodeID));
		break;
	case APP_ERROR_UNKOWN_COMMAND:
		DC->WriteError("Unknown command on node: " + AnsiString((unsigned int)NodeID));
		break;
	case APP_ERROR_HEARTBEAT_FAILURE:
		DC->WriteError("Heartbeat failure on node: " + AnsiString((unsigned int)NodeID));
		break;
	case APP_ERROR_COMM_RESET:
		DC->WriteNotification("Communications reset on node " + AnsiString((unsigned int)NodeID));
		break;
	case APP_ERROR_NODE_RESET:
		DC->WriteNotification("Node reset on node " + AnsiString((unsigned int)NodeID));
		break;
	default:
		DC->WriteError("Unknown failure on node: " + AnsiString((unsigned int)NodeID));
		break;
	}
}

void CSerialCmdHandler::ReadHighVoltage(DWORD devNum, char NodeID)
{
	CmdBuf[0] = USB_SEND_HIGHVOLTAGE;
	CmdBuf[1] = NodeID;
	CmdBuf[2] = USB_UNUSED;
	CmdBuf[3] = USB_UNUSED;

	if(TNodes[NodeID - 1]->Present == true)
		S->Write(devNum, CmdBuf, 4);
}

void CSerialCmdHandler::ReadLowVoltage(DWORD devNum, char NodeID)
{
	CmdBuf[0] = USB_SEND_LOWVOLTAGE;
	CmdBuf[1] = NodeID;
	CmdBuf[2] = USB_UNUSED;
	CmdBuf[3] = USB_UNUSED;

	if(TNodes[NodeID - 1]->Present == true)
		S->Write(devNum, CmdBuf, 4);
}

void CSerialCmdHandler::WriteLed(DWORD devNum, char NodeID, char LED, unsigned char Value)
{
	TColor CubeColor;

	CubeColor = clLtGray;
	DWORD Dev;

	Dev = TNodes[NodeID - 1]->devNum;

	switch (LED)
	{
	case 1:
		if(TNodes[NodeID - 1]->Cube1Value == Value)
			return;

		if(TNodes[NodeID - 1] != NULL) TNodes[NodeID-1]->Cube1Value = Value;
		break;

	case 2:
		if(TNodes[NodeID - 1]->Cube2Value == Value)
			return;

		if(TNodes[NodeID - 1] != NULL) TNodes[NodeID-1]->Cube2Value = Value;
		break;

	case 3:
		if(TNodes[NodeID-1]->Cube3Value == Value)
			return;

		if(TNodes[NodeID - 1] != NULL) TNodes[NodeID-1]->Cube3Value = Value;
		break;

	case 4:
		if(TNodes[NodeID - 1]->Cube4Value == Value)
			return;

		if(TNodes[NodeID - 1] != NULL) TNodes[NodeID-1]->Cube4Value = Value;
		break;

	default:
		;
	}

	CmdBuf[0] = USB_SEND_WRITELED;
	CmdBuf[1] = NodeID;
	CmdBuf[2] = LED;
	CmdBuf[3] = Value;

	//if(TNodes[NodeID-1]->Present)
	if(TNodes[NodeID - 1]->Present == true)
		S->Write(Dev, CmdBuf, 4);
}

void CSerialCmdHandler::ConfigureNode(DWORD devNum, char NodeID)
{
	CmdBuf[0] = USB_SEND_CONFIGURE;
	CmdBuf[1] = NodeID;
	CmdBuf[2] = USB_UNUSED;
	CmdBuf[3] = USB_UNUSED;

	S->Write(devNum, CmdBuf, 4);

	//Sleep(500);

	if(TNodes[NodeID - 1] != NULL) TNodes[NodeID - 1]->Connected = true;

}

void CSerialCmdHandler::ResetNode(DWORD devNum, char NodeID)
{
	CmdBuf[0] = USB_SEND_RESETNODE;
	CmdBuf[1] = NodeID;
	CmdBuf[2] = USB_UNUSED;
	CmdBuf[3] = USB_UNUSED;

	S->Write(devNum, CmdBuf, 4);
}

void CSerialCmdHandler::ResetController(DWORD devNum)
{
	CmdBuf[0] = USB_SEND_RESETDEVICE;
	CmdBuf[1] = USB_UNUSED;
	CmdBuf[2] = USB_UNUSED;
	CmdBuf[3] = USB_UNUSED;

	S->Write(devNum, CmdBuf, 4);
}

void CSerialCmdHandler::HardOff(DWORD devNum)
{
	CmdBuf[0] = USB_SEND_HARDOFF;
	CmdBuf[1] = USB_UNUSED;
	CmdBuf[2] = USB_UNUSED;
	CmdBuf[3] = USB_UNUSED;

	S->Write(devNum, CmdBuf, 4);
}

void CSerialCmdHandler::HardOn(DWORD devNum)
{
	CmdBuf[0] = USB_SEND_HARDON;
	CmdBuf[1] = USB_UNUSED;
	CmdBuf[2] = USB_UNUSED;
	CmdBuf[3] = USB_UNUSED;

	S->Write(devNum, CmdBuf, 4);
}

void __fastcall CSerialCmdHandler::Execute()
{
	int16_t ADCValue;
	DWORD i, RxSize;
	unsigned char Cmd0, Cmd1, Cmd2, Cmd3;

	while (!Terminated) {

	this->SerialSem->WaitFor();

		for (i = 0; i < S->NumDevices; i++) {

			RxSize = S->RxRingSize(i);

			//if (S->RxRingSize(i) > 0) {
			while(RxSize > 3) {

				if(S->Read(i, CmdBuf, 4) == true)
				{

					Cmd0 = CmdBuf[0];
					Cmd1 = CmdBuf[1];
					Cmd2 = CmdBuf[2];
					Cmd3 = CmdBuf[3];

					switch (Cmd0) {
					case USB_RESP_BOOTUP:
						DC->WriteNotification("BOOTUP RECEIVED FROM NODE " + AnsiString((unsigned char)Cmd1) + " ON DEVICE: " + S->DevSN(i) + ".");

						if(TNodes[Cmd1 - 1] != NULL) TNodes[Cmd1 - 1]->Present = true;
						if(TNodes[Cmd1 - 1] != NULL) TNodes[Cmd1 - 1]->devNum = i;

						this->ReadHighVoltage(i, Cmd1);
						this->ReadLowVoltage(i, Cmd1);
						break;

					case USB_RESP_HIGHVOLTAGE:
						if(Cmd2 == (char)0x01)
							if(TNodes[Cmd1 - 1] != NULL) TNodes[Cmd1 - 1]->HighVoltage = true;
						else
							if(TNodes[Cmd1 - 1] != NULL) TNodes[Cmd1 - 1]->HighVoltage = false;
						break;

					case USB_RESP_CMD_OK:
						if(TNodes[Cmd1 - 1] != NULL) TNodes[Cmd1 - 1]->ResetErrorCount();
						break;

					case USB_RESP_ERROR:
						//if(TNodes[Cmd1 - 1] != NULL) TNodes[Cmd1 - 1]->IncreaseErrorCount();
						//ProcessError(Cmd2, CmdBuf[1]);
						break;

					case USB_RESP_COMM_TEST:
						break;

					case USB_RESP_LOWVOLTAGE:
						ADCValue = (int16_t) Cmd2 << 8;
						ADCValue = ADCValue | (0x00FF & (int16_t) Cmd3);
						if(TNodes[Cmd1 - 1] != NULL) TNodes[Cmd1 - 1]->LowVoltage = (float)((ADCValue * 0.0032) / 0.1971);
						break;

					default:
						break;
					}
				}

				RxSize = RxSize - 4;
			}
		}

		this->SerialSem->Release();

		Sleep(1);
	}
}
