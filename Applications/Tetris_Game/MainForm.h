//---------------------------------------------------------------------------

#ifndef MainFormH
#define MainFormH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.ExtCtrls.hpp>


#include "CBoard.h"
#include "CGame.h"
#include "CMarquee.h"
#include <IdUDPBase.hpp>
#include <IdUDPServer.hpp>
#include <IdUDPClient.hpp>
#include <Vcl.Imaging.jpeg.hpp>
#include <IdBaseComponent.hpp>
#include <IdComponent.hpp>
#include <Vcl.Imaging.pngimage.hpp>
#include <Vcl.MPlayer.hpp>

//---------------------------------------------------------------------------
class TFormMain : public TForm
{
__published:	// IDE-managed Components
	TPanel *PanelTetris;
	TTimer *DrawTimer;
	TPanel *PanelNext;
	TLabel *Label1;
	TLabel *Label2;
	TLabel *Label3;
	TLabel *Label4;
	TLabel *Label5;
	TIdUDPServer *UDPServer;
	TImage *ImageBackground;
	TLabel *Label6;
	TLabel *Label7;
	TLabel *Label8;
	TLabel *Label9;
	TImage *Image1;
	TImage *Image2;
	TImage *Image3;
	TImage *Image4;
	TImage *Image5;
	TImage *Image6;
	TImage *Image7;
	TShape *Shape1;
	TTimer *SponsorTimer;
	TMediaPlayer *MPLoop;
	void __fastcall FormCreate(TObject *Sender);
	void __fastcall FormKeyDown(TObject *Sender, WORD &Key, TShiftState Shift);
	void __fastcall DrawTimerTimer(TObject *Sender);
	void __fastcall FormKeyUp(TObject *Sender, WORD &Key, TShiftState Shift);
	void __fastcall SponsorTimerTimer(TObject *Sender);
	void __fastcall FormShow(TObject *Sender);
	void __fastcall MPLoopNotify(TObject *Sender);


private:	// User declarations
	CGame *Game;
	CMarquee *Marquee;
	unsigned int timerticker;
	unsigned int timerticker2;
	unsigned long long HighScore;
	unsigned char music;

	bool SponsorPage;
	bool MusicStop;

	unsigned long long ReadHighScore();
	void WriteHighScore(unsigned long long Score);

	void ReadHostIP(AnsiString &Host);

public:		// User declarations
	__fastcall TFormMain(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TFormMain *FormMain;
//---------------------------------------------------------------------------
#endif
