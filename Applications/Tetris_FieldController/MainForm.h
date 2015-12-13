//---------------------------------------------------------------------------

#ifndef MainFormH
#define MainFormH

#define MODE_AUTO			0xFF
#define MODE_POLICE			0x01
#define MODE_RGB			0x02
#define MODE_RUNNING		0x03
#define MODE_RANDOM			0x04

//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>

#include "CTetrisNode.h"
#include "CDebugConsole.h"
#include "CSerial.h"
#include "CSerialCmdHandler.h"
#include "CSocket.h"
#include "CNetworkServices.h"

#include "FTDI\ftd2xx.h"
#include <Vcl.ExtCtrls.hpp>
#include <Vcl.ComCtrls.hpp>
#include <IdBaseComponent.hpp>
#include <IdComponent.hpp>
#include <IdTCPClient.hpp>
#include <IdTCPConnection.hpp>
#include <Data.DB.hpp>
#include <Datasnap.DBClient.hpp>
#include <Datasnap.Win.MConnect.hpp>
#include <Datasnap.Win.SConnect.hpp>
#include <IdTelnet.hpp>
#include <IdGlobal.hpp>
#include <IdCustomTCPServer.hpp>
#include <IdTelnetServer.hpp>
#include <IdUDPBase.hpp>
#include <IdUDPClient.hpp>
#include <Vcl.Mask.hpp>

//#include <deque>

//---------------------------------------------------------------------------
class TFormMain : public TForm
{
__published:	// IDE-managed Components
	TPanel *Panel1;
	TRichEdit *RichEdit1;
	TButton *Button1;
	TGroupBox *GroupBox1;
	TShape *Shape1;
	TLabel *Label1;
	TTimer *Timer1;
	TGroupBox *GroupBox2;
	TButton *Button2;
	TButton *Button3;
	TButton *Button4;
	TTimer *Timer2;
	TButton *Button5;
	TButton *Button6;
	TGroupBox *GroupBox3;
	TButton *Button7;
	TTrackBar *TrackBar1;
	TEdit *Edit1;
	TLabel *Label2;
	TButton *Button8;
	TButton *Button9;
	TShape *Shape2;
	TLabel *Label3;
	TButton *Button10;
	TMaskEdit *MaskEditIP;
	TLabel *Label4;
	TButton *Button11;
	TEdit *Edit2;
	TIdUDPClient *UDPClient;
	TButton *Button12;
	TButton *Button13;
	TButton *Button14;
	TButton *Button15;
	TButton *Button16;
	TButton *Button17;
	TButton *Button18;
	TButton *Button19;
	TButton *Button20;
	TButton *Button21;
	TButton *Button22;
	TButton *Button23;
	TTimer *Timer3;
	void __fastcall AppException(TObject *Sender, Exception *E);
	void __fastcall FormCreate(TObject *Sender);
	void __fastcall Button1Click(TObject *Sender);
	void __fastcall FormDestroy(TObject *Sender);
	void __fastcall Timer1Timer(TObject *Sender);
	void __fastcall Button4Click(TObject *Sender);
	void __fastcall Button2Click(TObject *Sender);
	void __fastcall Timer2Timer(TObject *Sender);
	void __fastcall Button5Click(TObject *Sender);
	void __fastcall Button3Click(TObject *Sender);
	void __fastcall Button6Click(TObject *Sender);
	void __fastcall TrackBar1Change(TObject *Sender);
	void __fastcall Edit1Change(TObject *Sender);
	void __fastcall Button7Click(TObject *Sender);
	void __fastcall Button9Click(TObject *Sender);
	void __fastcall Button8Click(TObject *Sender);
	void __fastcall Button10Click(TObject *Sender);
	void __fastcall UDPClientConnected(TObject *Sender);
	void __fastcall UDPClientDisconnected(TObject *Sender);
	void __fastcall Button11Click(TObject *Sender);
	void __fastcall Button12Click(TObject *Sender);
	void __fastcall Button13Click(TObject *Sender);
	void __fastcall Button14Click(TObject *Sender);
	void __fastcall Button15Click(TObject *Sender);
	void __fastcall Button16Click(TObject *Sender);
	void __fastcall Button17Click(TObject *Sender);
	void __fastcall Button18Click(TObject *Sender);
	void __fastcall Button19Click(TObject *Sender);
	void __fastcall Button20Click(TObject *Sender);
	void __fastcall Button21Click(TObject *Sender);
	void __fastcall Button23Click(TObject *Sender);
	void __fastcall Button22Click(TObject *Sender);
	void __fastcall Timer3Timer(TObject *Sender);



private:	// User declarations
	CTetrisNode *tnode[50];
	CDebugConsole *DebugConsole;
	CSerial *Serial;
	CSerialCmdHandler *SerialCmdHandler;
	CSocket *Socket;
	CNetworkServices *NetworkServices;
	TLightweightSemaphore *SerialSem;

	bool ServerConnected;

	void DrawField();

	char LED1;
	char LED2;
	char LED3;
	char LED4;

	char ManualMode;
	bool AutomaticMode;

	DWORD Port1;
	DWORD Port2;
	DWORD Port3;
	DWORD Port4;
	DWORD Port5;


public:		// User declarations
	__fastcall TFormMain(TComponent* Owner);
	void OnClickHandler(unsigned int Node_ID);
	void OnMouseDownHandler(unsigned int Node_ID, unsigned int LED_ID);
};
//---------------------------------------------------------------------------
extern PACKAGE TFormMain *FormMain;
//---------------------------------------------------------------------------
#endif
