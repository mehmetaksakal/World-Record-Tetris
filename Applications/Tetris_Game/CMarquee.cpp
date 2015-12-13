//---------------------------------------------------------------------------

#pragma hdrstop

#include "CMarquee.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)

CMarquee::CMarquee(TWinControl *_Owner, CGame *_Game) : TTimer(_Owner)
{
	this->Game = _Game;
	this->Board = new CBoard();

	this->Interval		= 100;
	this->Enabled		= false;
	this->OnTimer		= this->OnTimerEvent;

	strcpy (sponsors[0], " Thales\0");
	strcpy (sponsors[1], " Prodrive\0");
	strcpy (sponsors[2], " Arrow Europe\0");
	strcpy (sponsors[3], " Everlight\0");
	strcpy (sponsors[4], " Pipelife\0");
	strcpy (sponsors[5], " Nexans\0");
	strcpy (sponsors[6], " EuroCircuits\0");
	strcpy (sponsors[7], " www.RS-Online.nl\0");
	strcpy (sponsors[8], " V-PS\0");
	strcpy (sponsors[9], " NXP\0");
	strcpy (sponsors[10], " AME\0");
	strcpy (sponsors[11], " Ziut\0");



	this->BuildFontData();
	srand(time(NULL));
}

__fastcall CMarquee::~CMarquee()
{

}

bool CMarquee::Running()
{
	return this->_Running;
}

void CMarquee::Start()
{
	this->Game->ClearField();
	this->buffer_line1.clear();
	this->buffer_line2.clear();
	this->buffer_line3.clear();
	this->buffer_line4.clear();
	this->buffer_line5.clear();
	this->buffer_line6.clear();
	this->buffer_line7.clear();
	this->buffer_line8.clear();
	this->buffer_line9.clear();
	this->buffer_line10.clear();
	this->buffer_line11.clear();
	this->buffer_line12.clear();
	this->buffer_line13.clear();
	this->buffer_line14.clear();
	this->buffer_line15.clear();
	this->buffer_line16.clear();
	this->buffer_line17.clear();
	this->buffer_line18.clear();
	this->buffer_line19.clear();
	this->buffer_line20.clear();
	this->InsertRandomSponsor();
	this->Enabled = true;
	this->_Running = true;
}

void CMarquee::Stop()
{
	this->Enabled = false;
	this->_Running = false;
}

void __fastcall CMarquee::OnTimerEvent(TObject *Sender)
{
	unsigned int x, y;
	BLOCK_TYPE MyBlock;

	for(y = 0; y < 20; y++)
	{
		for(x = 1; x < 10; x++)
		{
			this->Game->Block[x][y] = this->Game->Block[x+1][y];
		}
	}

	this->Game->Block[10][0] = this->buffer_line1[0];
	this->buffer_line1.pop_front();

	this->Game->Block[10][1] = this->buffer_line2[0];
	this->buffer_line2.pop_front();

	this->Game->Block[10][2] = this->buffer_line3[0];
	this->buffer_line3.pop_front();

	this->Game->Block[10][3] = this->buffer_line4[0];
	this->buffer_line4.pop_front();

	this->Game->Block[10][4] = this->buffer_line5[0];
	this->buffer_line5.pop_front();

	this->Game->Block[10][5] = this->buffer_line6[0];
	this->buffer_line6.pop_front();

	this->Game->Block[10][6] = this->buffer_line7[0];
	this->buffer_line7.pop_front();

	this->Game->Block[10][7] = this->buffer_line8[0];
	this->buffer_line8.pop_front();

	this->Game->Block[10][8] = this->buffer_line9[0];
	this->buffer_line9.pop_front();

	this->Game->Block[10][9] = this->buffer_line10[0];
	this->buffer_line10.pop_front();

	this->Game->Block[10][10] = this->buffer_line11[0];
	this->buffer_line11.pop_front();

	this->Game->Block[10][11] = this->buffer_line12[0];
	this->buffer_line12.pop_front();

	this->Game->Block[10][12] = this->buffer_line13[0];
	this->buffer_line13.pop_front();

	this->Game->Block[10][13] = this->buffer_line14[0];
	this->buffer_line14.pop_front();

	this->Game->Block[10][14] = this->buffer_line15[0];
	this->buffer_line15.pop_front();

	this->Game->Block[10][15] = this->buffer_line16[0];
	this->buffer_line16.pop_front();

	this->Game->Block[10][16] = this->buffer_line17[0];
	this->buffer_line17.pop_front();

	this->Game->Block[10][17] = this->buffer_line18[0];
	this->buffer_line18.pop_front();

	this->Game->Block[10][18] = this->buffer_line19[0];
	this->buffer_line19.pop_front();

	this->Game->Block[10][19] = this->buffer_line20[0];
	this->buffer_line20.pop_front();

	if(this->buffer_line1.empty())
		this->InsertRandomSponsor();
}

void CMarquee::InsertRandomSponsor()
{
	unsigned char random, color;
	unsigned int x, y, i;
	unsigned char letter;
	unsigned char data;

	random = (rand() % 12);
	color = (rand() % 7) + 1;

	for(i = 0; i < strlen(sponsors[random]); i++)
	{
		for(x = 0; x < FONT_WIDTH; x++)
		{
		 letter = sponsors[random][i];

		data = FontData[letter][0*FONT_WIDTH + x] * color;
		if(FONT_HEIGHT < 1) data = 0x00;
		buffer_line1.push_back(data);

		data = FontData[letter][1*FONT_WIDTH + x] * color;
		if(FONT_HEIGHT < 2) data = 0x00;
		buffer_line2.push_back(data);

		data = FontData[letter][2*FONT_WIDTH + x] * color;
		if(FONT_HEIGHT < 3) data = 0x00;
		buffer_line3.push_back(data);

		data = FontData[letter][3*FONT_WIDTH + x] * color;
		if(FONT_HEIGHT < 4) data = 0x00;
		buffer_line4.push_back(data);

		data = FontData[letter][4*FONT_WIDTH + x] * color;
		if(FONT_HEIGHT < 5) data = 0x00;
		buffer_line5.push_back(data);

		data = FontData[letter][5*FONT_WIDTH + x] * color;
		if(FONT_HEIGHT < 6) data = 0x00;
		buffer_line6.push_back(data);

		data = FontData[letter][6*FONT_WIDTH + x] * color;
		if(FONT_HEIGHT < 7) data = 0x00;
		buffer_line7.push_back(data);

		data = FontData[letter][7*FONT_WIDTH + x] * color;
		if(FONT_HEIGHT < 8) data = 0x00;
		buffer_line8.push_back(data);

		data = FontData[letter][8*FONT_WIDTH + x] * color;
		if(FONT_HEIGHT < 9) data = 0x00;
		buffer_line9.push_back(data);

		data = FontData[letter][9*FONT_WIDTH + x] * color;
		if(FONT_HEIGHT < 10) data = 0x00;
		buffer_line10.push_back(data);

		data = FontData[letter][10*FONT_WIDTH + x] * color;
		if(FONT_HEIGHT < 11) data = 0x00;
		buffer_line11.push_back(data);

		data = FontData[letter][11*FONT_WIDTH + x] * color;
		if(FONT_HEIGHT < 12) data = 0x00;
		buffer_line12.push_back(data);

		data = FontData[letter][12*FONT_WIDTH + x] * color;
		if(FONT_HEIGHT < 13) data = 0x00;
		buffer_line13.push_back(data);

		data = FontData[letter][13*FONT_WIDTH + x] * color;
		if(FONT_HEIGHT < 14) data = 0x00;
		buffer_line14.push_back(data);

		data = FontData[letter][14*FONT_WIDTH + x] * color;
		if(FONT_HEIGHT < 15) data = 0x00;
		buffer_line15.push_back(data);

		data = FontData[letter][15*FONT_WIDTH + x] * color;
		if(FONT_HEIGHT < 16) data = 0x00;
		buffer_line16.push_back(data);

		data = FontData[letter][16*FONT_WIDTH + x] * color;
		if(FONT_HEIGHT < 17) data = 0x00;
		buffer_line17.push_back(data);

		data = FontData[letter][17*FONT_WIDTH + x] * color;
		if(FONT_HEIGHT < 18) data = 0x00;
		buffer_line18.push_back(data);

		data = FontData[letter][18*FONT_WIDTH + x] * color;
		if(FONT_HEIGHT < 19) data = 0x00;
		buffer_line19.push_back(data);

		data = FontData[letter][19*FONT_WIDTH + x] * color;
		if(FONT_HEIGHT < 20) data = 0x00;
		buffer_line20.push_back(data);

		}
	}


}

void CMarquee::BuildFontData()
{
	this->FontData[0x20] = FontData_0x20;
	this->FontData[0x21] = FontData_0x21;
	this->FontData[0x22] = FontData_0x22;
	this->FontData[0x23] = FontData_0x23;
	this->FontData[0x24] = FontData_0x24;
	this->FontData[0x25] = FontData_0x25;
	this->FontData[0x26] = FontData_0x26;
	this->FontData[0x27] = FontData_0x27;
	this->FontData[0x28] = FontData_0x28;
	this->FontData[0x29] = FontData_0x29;
	this->FontData[0x2a] = FontData_0x2a;
	this->FontData[0x2b] = FontData_0x2b;
	this->FontData[0x2c] = FontData_0x2c;
	this->FontData[0x2d] = FontData_0x2d;
	this->FontData[0x2e] = FontData_0x2e;
	this->FontData[0x2f] = FontData_0x2f;
	this->FontData[0x30] = FontData_0x30;
	this->FontData[0x31] = FontData_0x31;
	this->FontData[0x32] = FontData_0x32;
	this->FontData[0x33] = FontData_0x33;
	this->FontData[0x34] = FontData_0x34;
	this->FontData[0x35] = FontData_0x35;
	this->FontData[0x36] = FontData_0x36;
	this->FontData[0x37] = FontData_0x37;
	this->FontData[0x38] = FontData_0x38;
	this->FontData[0x39] = FontData_0x39;
	this->FontData[0x3a] = FontData_0x3a;
	this->FontData[0x3b] = FontData_0x3b;
	this->FontData[0x3c] = FontData_0x3c;
	this->FontData[0x3d] = FontData_0x3d;
	this->FontData[0x3e] = FontData_0x3e;
	this->FontData[0x3f] = FontData_0x3f;
	this->FontData[0x40] = FontData_0x40;
	this->FontData[0x41] = FontData_0x41;
	this->FontData[0x42] = FontData_0x42;
	this->FontData[0x43] = FontData_0x43;
	this->FontData[0x44] = FontData_0x44;
	this->FontData[0x45] = FontData_0x45;
	this->FontData[0x46] = FontData_0x46;
	this->FontData[0x47] = FontData_0x47;
	this->FontData[0x48] = FontData_0x48;
	this->FontData[0x49] = FontData_0x49;
	this->FontData[0x4a] = FontData_0x4a;
	this->FontData[0x4b] = FontData_0x4b;
	this->FontData[0x4c] = FontData_0x4c;
	this->FontData[0x4d] = FontData_0x4d;
	this->FontData[0x4e] = FontData_0x4e;
	this->FontData[0x4f] = FontData_0x4f;
	this->FontData[0x50] = FontData_0x50;
	this->FontData[0x51] = FontData_0x51;
	this->FontData[0x52] = FontData_0x52;
	this->FontData[0x53] = FontData_0x53;
	this->FontData[0x54] = FontData_0x54;
	this->FontData[0x55] = FontData_0x55;
	this->FontData[0x56] = FontData_0x56;
	this->FontData[0x57] = FontData_0x57;
	this->FontData[0x58] = FontData_0x58;
	this->FontData[0x59] = FontData_0x59;
	this->FontData[0x5a] = FontData_0x5a;
	this->FontData[0x5b] = FontData_0x5b;
	this->FontData[0x5c] = FontData_0x5c;
	this->FontData[0x5d] = FontData_0x5d;
	this->FontData[0x5e] = FontData_0x5e;
	this->FontData[0x5f] = FontData_0x5f;
	this->FontData[0x60] = FontData_0x60;
	this->FontData[0x61] = FontData_0x61;
	this->FontData[0x62] = FontData_0x62;
	this->FontData[0x63] = FontData_0x63;
	this->FontData[0x64] = FontData_0x64;
	this->FontData[0x65] = FontData_0x65;
	this->FontData[0x66] = FontData_0x66;
	this->FontData[0x67] = FontData_0x67;
	this->FontData[0x68] = FontData_0x68;
	this->FontData[0x69] = FontData_0x69;
	this->FontData[0x6a] = FontData_0x6a;
	this->FontData[0x6b] = FontData_0x6b;
	this->FontData[0x6c] = FontData_0x6c;
	this->FontData[0x6d] = FontData_0x6d;
	this->FontData[0x6e] = FontData_0x6e;
	this->FontData[0x6f] = FontData_0x6f;
	this->FontData[0x70] = FontData_0x70;
	this->FontData[0x71] = FontData_0x71;
	this->FontData[0x72] = FontData_0x72;
	this->FontData[0x73] = FontData_0x73;
	this->FontData[0x74] = FontData_0x74;
	this->FontData[0x75] = FontData_0x75;
	this->FontData[0x76] = FontData_0x76;
	this->FontData[0x77] = FontData_0x77;
	this->FontData[0x78] = FontData_0x78;
	this->FontData[0x79] = FontData_0x79;
	this->FontData[0x7a] = FontData_0x7a;
	this->FontData[0x7b] = FontData_0x7b;
	this->FontData[0x7c] = FontData_0x7c;
	this->FontData[0x7d] = FontData_0x7d;
	this->FontData[0x7e] = FontData_0x7e;
}
