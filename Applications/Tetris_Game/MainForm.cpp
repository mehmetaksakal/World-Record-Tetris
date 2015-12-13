//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "MainForm.h"
#include <mmsystem.h>
#include <iostream>
#include <fstream>
#include <string>
//---------------------------------------------------------------------------
//#pragma package(smart_init)
#pragma resource "*.dfm"
TFormMain *FormMain;
//---------------------------------------------------------------------------
__fastcall TFormMain::TFormMain(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------

void __fastcall TFormMain::FormCreate(TObject *Sender)
{
	AnsiString IP;

	this->Game = new CGame(this->PanelTetris, this->PanelNext, this->Label1, this->UDPServer);
	this->Marquee = new CMarquee(this->PanelTetris, this->Game);

	this->ReadHostIP(IP);
	this->Game->Host = IP;
	this->SponsorPage = false;
	this->MusicStop = false;

	this->MPLoop->FileName = PATH_AUDIO_LOOP;
	this->MPLoop->AutoRewind = true;
	this->MPLoop->AutoOpen = true;
	this->MPLoop->Play();
	this->MPLoop->Notify = true;
	this->music = 1;
	//PlaySound(PATH_AUDIO_LOOP, NULL, SND_FILENAME|SND_LOOP|SND_ASYNC);

	this->HighScore = this->ReadHighScore();
	this->Label9->Caption = AnsiString(this->HighScore);

	this->PanelTetris->Left = (this->Width/2) - 240;
	this->PanelNext->Left = (this->Width/2) + 272;
	this->Label2->Left = (this->Width/2) + 272;
	this->Label3->Left = (this->Width/2) + 272;
	this->Label4->Left = (this->Width/2) + 272;
	this->Label5->Left = (this->Width/2) + 272;
	this->Label6->Left = (this->Width/2) + 272;
	this->Label7->Left = (this->Width/2) + 272;
	this->Label8->Left = (this->Width/2) + 272;
	this->Label9->Left = (this->Width/2) + 272;

}
//---------------------------------------------------------------------------


void __fastcall TFormMain::FormKeyDown(TObject *Sender, WORD &Key, TShiftState Shift)

{
	//
	switch (Key) {
	case 37U: // Left
	case 65U: // A
		if(this->Game->GameRunning())
			this->Game->MoveLeft();
		break;
	case 38U: // Up
	case 87U: // W
	case 82U: // R
		if(this->Game->GameRunning())
			this->Game->RotateCCW();
		break;
	case 39U: //Right
	case 68U: // D
		if(this->Game->GameRunning())
			this->Game->MoveRight();
		break;
	case 40U: // Down
	case 83U: // S
		if(this->Game->GameRunning())
			this->Game->FastDownStart();
		break;
	case 69U: // E
		if(this->Game->GameRunning())
			this->Game->RotateCW();
		break;
	case 101U:
	case 53U:
		this->MusicStop = true;
		this->MPLoop->Notify = false;
		this->MPLoop->Stop();
		this->MPLoop->Rewind();
		break;
	case 102U:
	case 54U:
		if(this->music == 1)
		{
			this->MusicStop = true;
			this->MPLoop->Notify = false;
			this->MPLoop->Stop();
			this->MPLoop->Close();
			this->MPLoop->FileName = PATH_AUDIO_LOOP_MUSIC1;
			this->MPLoop->Open();
			this->MPLoop->Play();
			this->music = 2;
			this->MPLoop->Notify = true;
			this->MusicStop = false;
		} else if(this->music == 2) {
			this->MusicStop = true;
			this->MPLoop->Notify = false;
			this->MPLoop->Stop();
			this->MPLoop->Close();
			this->MPLoop->FileName = PATH_AUDIO_LOOP_MUSIC2;
			this->MPLoop->Open();
			this->MPLoop->Play();
			this->music = 3;
			this->MPLoop->Notify = true;
			this->MusicStop = false;
		} else if(this->music == 3) {
			this->MusicStop = true;
			this->MPLoop->Notify = false;
			this->MPLoop->Stop();
			this->MPLoop->Close();
			this->MPLoop->FileName = PATH_AUDIO_LOOP_MUSIC3;
			this->MPLoop->Open();
			this->MPLoop->Play();
			this->music = 4;
			this->MPLoop->Notify = true;
			this->MusicStop = false;
		} else {
			this->MusicStop = true;
			this->MPLoop->Notify = false;
			this->MPLoop->Stop();
			this->MPLoop->Close();
			this->MPLoop->FileName = PATH_AUDIO_LOOP;
			this->MPLoop->Open();
			this->MPLoop->Play();
			this->music = 1;
			this->MPLoop->Notify = true;
			this->MusicStop = false;
		}
		break;

	case 32U: // Space
	case 84U: // T
		if(!this->Game->GameRunning())
		{
			this->Game->GameStart();
			this->Marquee->Stop();
		}
		break;

	default:
		;
	}
}
//---------------------------------------------------------------------------

void __fastcall TFormMain::FormKeyUp(TObject *Sender, WORD &Key, TShiftState Shift)
{
	//
	switch (Key) {
	case 40U: // Down
	case 83U: // S
		if(this->Game->GameRunning())
			this->Game->FastDownStop();
		break;
	default:
		;
	}
}
//---------------------------------------------------------------------------

void __fastcall TFormMain::DrawTimerTimer(TObject *Sender)
{
	unsigned int x, y, value;
	AnsiString Msg;

	//this->DrawTimer->Enabled = false;

	this->Game->DrawBoard();
	this->Label3->Caption = AnsiString(this->Game->GetScore());
	this->Label5->Caption = AnsiString(this->Game->GetLevel());
	this->Label7->Caption = AnsiString(this->Game->GetLines());




	if(!this->Game->GameRunning())
	{
		this->Label1->BringToFront();
		this->Label1->Caption = "game over" + AnsiString((char)13) + "press start";

		this->timerticker++;
		this->timerticker2++;

		if(this->timerticker == 13)
		{
			this->timerticker = 0;
			this->Label1->Visible = !this->Label1->Visible;
		}

		if((this->timerticker2 == 100))
		{
			this->timerticker2 = 0;
			if(this->Marquee->Running() == false)
				this->Marquee->Start();
        }

		if(Game->GetScore() > this->HighScore)
		{
			this->WriteHighScore(Game->GetScore());
			this->HighScore = Game->GetScore();
			this->Label9->Caption = AnsiString(this->HighScore);
        }
	}

	//this->DrawTimer->Enabled = true;
}

unsigned long long TFormMain::ReadHighScore()
{
	FILE *FOpen;

	unsigned long long result;

	FOpen = fopen("./hs.bin", "rb");

	if( FOpen == NULL )
	{
		return 0;
	}

	//fscanf(FOpen, "%u", &result);
	fread(&result, sizeof(unsigned long long), 1, FOpen);
	fclose(FOpen);

	return result;
}

void TFormMain::WriteHighScore(unsigned long long Score)
{
	FILE *FSave;

	unsigned long long result;

	FSave = fopen("./hs.bin", "wb");

	if( FSave == NULL )
	{
		return;
	}

	//fprintf(FSave, "%u", Score);
	fwrite(&Score, sizeof(unsigned long long), 1, FSave);
	fclose(FSave);

	return;
}

void TFormMain::ReadHostIP(AnsiString &Host)
{
	FILE *FOpen;

	char IP[32];

	FOpen = fopen("ip.bin", "r");

	if( FOpen == NULL )
	{
		Host = "127.0.0.1";
		return;
	}

	fgets(IP, 16, FOpen);
	Host = AnsiString(IP);
	Host = Host.Trim();

	fclose(FOpen);

	return;
}

void __fastcall TFormMain::SponsorTimerTimer(TObject *Sender)
{
	if(!this->SponsorPage)
	{
		this->SponsorPage = true;
		this->Image1->Picture->LoadFromFile("./Images/NXP_Logo.jpg");
		this->Image2->Picture->LoadFromFile("./Images/RS_Logo.jpg");
		this->Image3->Picture->LoadFromFile("./Images/AME_Logo.jpg");
		this->Image4->Picture->LoadFromFile("./Images/Prodrive_Logo.jpg");
		this->Image5->Picture->LoadFromFile("./Images/Thales_Logo.png");
		this->Image6->Picture->LoadFromFile("./Images/Arrow_Logo.jpg");
		this->Image7->Picture->LoadFromFile("./Images/VPS_Logo.png");
	}
	else
	{
		this->SponsorPage = false;
		this->Image1->Picture->LoadFromFile("./Images/TUe_Logo.png");
		this->Image2->Picture->LoadFromFile("./Images/Ziut_Logo.png");
		this->Image3->Picture->LoadFromFile("./Images/Everlight_Logo.png");
		this->Image4->Picture->LoadFromFile("./Images/Thor_Logo.png");
		this->Image5->Picture->LoadFromFile("./Images/Pipelife_Logo.jpg");
		this->Image6->Picture->LoadFromFile("./Images/EC_Logo.jpg");
		this->Image7->Picture->LoadFromFile("./Images/Nexans_Logo.jpg");

    }
}
//---------------------------------------------------------------------------

void __fastcall TFormMain::FormShow(TObject *Sender)
{
	this->Marquee->Start();
}
//---------------------------------------------------------------------------

void __fastcall TFormMain::MPLoopNotify(TObject *Sender)
{
	if(this->MusicStop == false)
	{
		if(this->MPLoop->NotifyValue == nvSuccessful)
		{
			this->MPLoop->Play();
			this->MPLoop->Notify = true;
		}
	}
}
//---------------------------------------------------------------------------

