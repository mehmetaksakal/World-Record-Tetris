//---------------------------------------------------------------------------

#ifndef CMarqueeH
#define CMarqueeH

#include <stdio.h>
#include <string.h>
#include <vector>
#include <deque>
#include <random>

#include "CGame.h"
#include "CBoard.h"
#include "TTetris.h"
#include "FontType_basis33_16.h"
//#include "FontType_basis33_20.h"
//#include "FontType_Kongtext.h"
//#include "FontType_Graph35_20.h"


//using namespace std;
//---------------------------------------------------------------------------

class CMarquee : public TTimer
{
private:
	char	sponsors[12][32];

	std::deque<BLOCK_TYPE> buffer_line1;
	std::deque<BLOCK_TYPE> buffer_line2;
	std::deque<BLOCK_TYPE> buffer_line3;
	std::deque<BLOCK_TYPE> buffer_line4;
	std::deque<BLOCK_TYPE> buffer_line5;
	std::deque<BLOCK_TYPE> buffer_line6;
	std::deque<BLOCK_TYPE> buffer_line7;
	std::deque<BLOCK_TYPE> buffer_line8;
	std::deque<BLOCK_TYPE> buffer_line9;
	std::deque<BLOCK_TYPE> buffer_line10;
	std::deque<BLOCK_TYPE> buffer_line11;
	std::deque<BLOCK_TYPE> buffer_line12;
	std::deque<BLOCK_TYPE> buffer_line13;
	std::deque<BLOCK_TYPE> buffer_line14;
	std::deque<BLOCK_TYPE> buffer_line15;
	std::deque<BLOCK_TYPE> buffer_line16;
	std::deque<BLOCK_TYPE> buffer_line17;
	std::deque<BLOCK_TYPE> buffer_line18;
	std::deque<BLOCK_TYPE> buffer_line19;
	std::deque<BLOCK_TYPE> buffer_line20;

	CGame	*Game;
	CBoard	*Board;
	bool _Running;
	uint8_t *FontData[0xff];

	void __fastcall OnTimerEvent(TObject *Sender);
	void InsertRandomSponsor();

	void BuildFontData();

public:
	CMarquee(TWinControl *_Owner, CGame *_Game);
	__fastcall virtual ~CMarquee();

	bool Running();
	void Start();
	void Stop();
};
#endif
