//---------------------------------------------------------------------------

#ifndef CSerialCmdHandlerH
#define CSerialCmdHandlerH
//---------------------------------------------------------------------------
#include <vcl.h>
#include "CSerial.h"
#include "CDebugConsole.h"
#include "CTetrisNode.h"

#define APP_ERROR_GENERAL_FAILURE	0x01		/* General read/write failure to CAN node */
#define APP_ERROR_UNKOWN_COMMAND	0x02		/* Unkown command received */
#define APP_ERROR_HEARTBEAT_FAILURE	0x03		/* Heartbeat failure */
#define APP_ERROR_COMM_RESET		0x04		/* Comm reset requested by node */
#define APP_ERROR_NODE_RESET		0x05		/* Node reset requested by node */

#define USB_SEND_CONFIGURE			0x01		/* Send configure node request */
#define USB_SEND_WRITELED			0x02		/* Send writeled request */
#define USB_SEND_HIGHVOLTAGE		0x04		/* Send read Highvoltage request */
#define USB_SEND_COMM_TEST			0x08		/* Send Comm test request */
#define USB_SEND_LOWVOLTAGE			0x10		/* Send read Lowvoltage request */
#define USB_SEND_RESETNODE			0x20		/* Send Reset node request */
#define USB_SEND_RESETDEVICE		0x40		/* Send reset this device request */
#define USB_SEND_HARDOFF			0x60		/* Send hard cycle this device request */
#define USB_SEND_HARDON				0x61		/* Send hard cycle this device request */

#define USB_RESP_BOOTUP				0x7F		/* Response to bootup received */
#define USB_RESP_HIGHVOLTAGE		0x80		/* Response to Highvoltage request */
#define USB_RESP_CMD_OK				0x81		/* Response to no error */
#define USB_RESP_ERROR				0x82		/* Response to error */
#define USB_RESP_COMM_TEST			0x83		/* Response to Comm Test request */
#define USB_RESP_LOWVOLTAGE			0x84		/* Response to Lowvoltage request */

#define USB_UNUSED					0xFF		/* Placeholder for unused bytes in packet */

class CSerialCmdHandler : public TThread
{
	private:
		CDebugConsole *DC;
		CSerial *S;
		CTetrisNode *TNodes[50];
		char CmdBuf[4];
		bool Terminated;

		TLightweightSemaphore *SerialSem;

		void NodeConfigure(DWORD devNum, char NodeID);
		void ProcessError(char Error, char NodeID);

		void __fastcall Execute();
	public:
		__fastcall CSerialCmdHandler(CDebugConsole *DebugConsole, CSerial *Serial, CTetrisNode *Nodes[50], TLightweightSemaphore *_Semaphore);
		__fastcall ~CSerialCmdHandler();

		void ConfigureNode(DWORD devNum, char NodeID);
		void WriteLed(DWORD devNum, char NodeID, char LED, unsigned char Value);
		void ReadHighVoltage(DWORD devNum, char NodeID);
		void ReadLowVoltage(DWORD devNum, char NodeID);
		void ResetNode(DWORD devNum, char NodeID);
		void ResetController(DWORD devNum);
		void HardOff(DWORD devNum);
		void HardOn(DWORD devNum);

		void Kill();
		void Run();
};

#endif
