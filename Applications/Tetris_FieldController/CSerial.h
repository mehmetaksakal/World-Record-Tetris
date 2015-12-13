//---------------------------------------------------------------------------

#ifndef CSerialH
#define CSerialH
//---------------------------------------------------------------------------
#include <vcl.h>
#include <deque>
#include <vector>
#include "CDebugConsole.h"
#include "FTDI\ftd2xx.h"

typedef struct
{
	DWORD devNum;
	AnsiString devSerial;
	FT_HANDLE devHandle;
	FT_STATUS ftStatus;
	char CmdBuf[4];

	std::deque<char> txring;
	std::deque<char> rxring;
} FTDIDevice;


class CSerial : public TThread
{
	private:
		FT_STATUS myFtStatus;
		DWORD numDevs;
		bool Terminated;
		CDebugConsole *DC;

		std::vector<FTDIDevice *> ftDevices;

		TLightweightSemaphore *SerialSem;

		FT_STATUS WriteByte(DWORD devNum, char byte);
		FT_STATUS ReadByte(DWORD devNum, char &byte);

		FT_STATUS WriteF(DWORD devNum, char *Cmd);
		FT_STATUS ReadF(DWORD devNum, char *Cmd);

		DWORD GetNumDev() const {
				return ftDevices.size();
		}

		void __fastcall Execute();
	public:
		__fastcall CSerial(CDebugConsole *DebugConsole, TLightweightSemaphore *_Semaphore);
		__fastcall ~CSerial();

		void Kill();
		void Run();

		bool Read(DWORD devNum, char buf[4], DWORD len);
		void Write(DWORD devNum, char *buf, DWORD len);
		AnsiString DevSN(DWORD devNum);
		DWORD RxRingSize(DWORD devNum);

		//__declspec ( property ( get = GetNumDev ) ) const DWORD NumDevices ;
		__property const DWORD NumDevices = {read=GetNumDev };
};
#endif
