//---------------------------------------------------------------------------

#pragma hdrstop

#include "CSerial.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)

__fastcall CSerial::CSerial(CDebugConsole *DebugConsole, TLightweightSemaphore *_Semaphore) : TThread(true)
{
	wchar_t DeviceSerial[64];
	char Buffer[64];
	DWORD BytesWritten;
	FTDIDevice *myFtDevice;

    this->Terminated = true;
	this->DC = DebugConsole;
	this->SerialSem = _Semaphore;

	myFtStatus = FT_ListDevices(&numDevs,NULL,FT_LIST_NUMBER_ONLY);

	for(DWORD i = 0; i < numDevs; i++)
	{
		myFtStatus = FT_ListDevices((PVOID)i, Buffer, FT_LIST_BY_INDEX|FT_OPEN_BY_SERIAL_NUMBER);
		myFtDevice = new FTDIDevice;

		if (myFtStatus == FT_OK) {
			myFtDevice->devNum = i;
			myFtDevice->devSerial = AnsiString(Buffer);

			myFtDevice->ftStatus = FT_Open(myFtDevice->devNum, &(myFtDevice->devHandle));
			myFtDevice->ftStatus = FT_SetBaudRate(myFtDevice->devHandle, 115200);
			myFtDevice->ftStatus = FT_SetDataCharacteristics(myFtDevice->devHandle, FT_BITS_8, FT_STOP_BITS_1, FT_PARITY_NONE);
			myFtDevice->ftStatus = FT_SetFlowControl(myFtDevice->devHandle, FT_FLOW_NONE, 0, 0);
			myFtDevice->ftStatus = FT_ClrDtr(myFtDevice->devHandle);
			//myFtDevice->ftStatus = FT_SetDtr(myFtDevice->devHandle);
			myFtDevice->ftStatus = FT_SetTimeouts(myFtDevice->devHandle, 100, 100);

			myFtDevice->CmdBuf[0] = 0x08;
			myFtDevice->CmdBuf[1] = 0xFF;
			myFtDevice->CmdBuf[2] = 0xFF;
			myFtDevice->CmdBuf[3] = 0xFF;

			myFtDevice->ftStatus = FT_Write(myFtDevice->devHandle, myFtDevice->CmdBuf, 4, &BytesWritten);
			myFtDevice->ftStatus = FT_Read(myFtDevice->devHandle, myFtDevice->CmdBuf, 4, &BytesWritten);

			if((myFtDevice->devHandle != NULL) && (myFtDevice->CmdBuf[0] == (char)0x83))
			{
				DC->WriteMessage("USB <-> CAN DEVICE SN:" + myFtDevice->devSerial + " ATTACHED.");
				this->ftDevices.push_back(myFtDevice);
            }
			else
			{
				DC->WriteError("USB <-> CAN DEVICE SN:" + myFtDevice->devSerial + " FAILED.");
            }

		}
	}

	//this->Run();
}

__fastcall CSerial::~CSerial()
{
	std::vector<FTDIDevice *>::iterator itr;

	this->Terminated = true;

	for(itr = ftDevices.begin(); itr != ftDevices.end(); itr++)
	{
		if((*itr)->devHandle !=  NULL)
		{
			FT_Close((*itr)->devHandle);
		}
	}
}
AnsiString CSerial::DevSN(DWORD devNum)
{
	return this->ftDevices[devNum]->devSerial;
}

bool CSerial::Read(DWORD devNum, char buf[4], DWORD len)
{
	DWORD i;
	bool result;

	result = false;

	if(ftDevices[devNum]->rxring.size() >= len)
	{
		result = true;

		for(i = 0; i < len; i++)
		{
			buf[i] = ftDevices[devNum]->rxring.back();
			ftDevices[devNum]->rxring.pop_back();
		}
	}

	return result;
}

void CSerial::Write(DWORD devNum, char *buf, DWORD len)
{
	DWORD i;

	for(i = 0; i < len; i++)
	{
		ftDevices[devNum]->txring.push_front(buf[i]);
	}
}

DWORD CSerial::RxRingSize(DWORD devNum)
{
	DWORD result;

	result = 0;

	if(ftDevices.size() > 0)
	{
        result = ftDevices[devNum]->rxring.size();
	}

	return result;
}


FT_STATUS CSerial::WriteF(DWORD devNum, char *Cmd)
{
	DWORD BytesWritten;

	myFtStatus = FT_DEVICE_NOT_FOUND;

	ftDevices[devNum]->CmdBuf[0] = Cmd[0];
	ftDevices[devNum]->CmdBuf[1] = Cmd[1];
	ftDevices[devNum]->CmdBuf[2] = Cmd[2];
	ftDevices[devNum]->CmdBuf[3] = Cmd[3];

	ftDevices[devNum]->ftStatus = FT_Write(ftDevices[devNum]->devHandle, ftDevices[devNum]->CmdBuf, 4, &BytesWritten);
	myFtStatus = ftDevices[devNum]->ftStatus;

	return myFtStatus;
}

FT_STATUS CSerial::ReadF(DWORD devNum, char *Cmd)
{
	DWORD BytesRead;

	myFtStatus = FT_DEVICE_NOT_FOUND;

	ftDevices[devNum]->ftStatus = FT_Read(ftDevices[devNum]->devHandle, ftDevices[devNum]->CmdBuf, 4, &BytesRead);

	Cmd[0] = ftDevices[devNum]->CmdBuf[0];
	Cmd[1] = ftDevices[devNum]->CmdBuf[1];
	Cmd[2] = ftDevices[devNum]->CmdBuf[2];
	Cmd[3] = ftDevices[devNum]->CmdBuf[3];

	myFtStatus = ftDevices[devNum]->ftStatus;

	return myFtStatus;
}

FT_STATUS CSerial::WriteByte(DWORD devNum, char byte)
{
	DWORD BytesWritten;

	myFtStatus = FT_DEVICE_NOT_FOUND;
	ftDevices[devNum]->ftStatus = FT_Write(ftDevices[devNum]->devHandle, &byte, 1, &BytesWritten);
	myFtStatus = ftDevices[devNum]->ftStatus;

	return myFtStatus;
}

FT_STATUS CSerial::ReadByte(DWORD devNum, char &byte)
{
	DWORD BytesRead;

	myFtStatus = FT_DEVICE_NOT_FOUND;
	ftDevices[devNum]->ftStatus = FT_Read(ftDevices[devNum]->devHandle, ftDevices[devNum]->CmdBuf, 1, &BytesRead);

	byte = ftDevices[devNum]->CmdBuf[0];

	myFtStatus = ftDevices[devNum]->ftStatus;

	return myFtStatus;
}

void CSerial::Kill()
{
	Terminated = true;
}

void CSerial::Run()
{
	Terminated = false;
	this->Start();
}

void __fastcall CSerial::Execute()
{
	std::vector<FTDIDevice *>::iterator itr;
	DWORD RxBytes;
	char byte;

	while (!Terminated)
	{

		this->SerialSem->WaitFor();

		for(itr = ftDevices.begin(); itr != ftDevices.end(); itr++)
		{
			// transmit buffer
			if((*itr)->txring.size() > 0)
			{
				while((*itr)->txring.size() > 0)
				{
					this->WriteByte((*itr)->devNum, (*itr)->txring.back());
					(*itr)->txring.pop_back();
				}
			}

			//FT_Purge((*itr)->devHandle,  FT_PURGE_RX);

			FT_GetQueueStatus((*itr)->devHandle, &RxBytes);

			while(RxBytes > 0)
			{
				this->ReadByte((*itr)->devNum, byte);
				(*itr)->rxring.push_front(byte);
				RxBytes--;
			}
		}

		this->SerialSem->Release();

		Sleep(10);
	}
}


