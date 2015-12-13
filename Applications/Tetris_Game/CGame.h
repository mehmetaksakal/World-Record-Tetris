// ---------------------------------------------------------------------------

#ifndef CGameH
#define CGameH
// ---------------------------------------------------------------------------
#include <vcl.h>
#include "TTetris.h"
#include "CTetromino.h"
#include "CBoard.h"
#include "CMersenneTwister.h"

#include <IdUDPBase.hpp>
#include <IdUDPServer.hpp>
#include <IdUDPClient.hpp>

class CGame : public TTimer {
private:
	TWinControl *Owner;
	TWinControl *PanelNext;
	TLabel		*Label;
	CMersenneTwister *mt_trng;

	CTetromino	*Tetromino;
	CTetromino	*NextTetromino;

    CBoard		*TransmitBoard;
	CBoard 		*BoardColors;
	CBoard 		*Board;

	unsigned int Rows;
	unsigned int Cols;
	unsigned char LockCount;
	unsigned int IntervalGame;
	unsigned long long score;
	unsigned int level;
	unsigned int numlines;

	bool FastDown;
	bool Running;

	AnsiString _Host;

	TIdUDPServer *UDPServer;

	TPicture *BlockImages[9];
	TImage *BoardImages[BOARD_MAX_X][BOARD_MAX_Y];
	TImage *NextImages[NEXT_MAX_XY][NEXT_MAX_XY];

	void __fastcall OnTimerEvent(TObject *Sender);

	bool DetectLeft();
	bool DetectRight();
	bool DetectRotation(bool RCCW);
	bool DetectDown();
	bool DetectGameOver();
	unsigned int DetectLine();
	void MoveDown();
	void LevelUp();

	//BLOCK_TYPE GetBlock(unsigned int x, unsigned int y);
	//void SetBlock(unsigned int x, unsigned int y, BLOCK_TYPE _Block);

	BLOCK_TYPE GetBlock(unsigned int x, unsigned int y) {
		return this->BoardColors->Block[x][y];
	}

	void SetBlock(unsigned int x, unsigned int y, BLOCK_TYPE _Block)
	{
		this->BoardColors->Block[x][y] = _Block;
	}

	AnsiString GetHost()
	{
        return this->_Host;
	}

	void SetHost(AnsiString _H)
	{
        this->_Host = _H;
    }

	//__fastcall void Execute();
public:
	CGame(TWinControl *_Owner, TWinControl *_PanelNext, TLabel *_Label, TIdUDPServer *_UDPServer);
	__fastcall virtual ~CGame(void);

	void RotateCW();
	void RotateCCW();
	void MoveLeft();
	void MoveRight();
	void FastDownStart();
	void FastDownStop();
	void Drop();

	void GameStart();
	bool GameRunning();

	void DrawBoard();
	void DrawNext();

	unsigned long long GetScore();
	unsigned int GetLevel();
	unsigned int GetLines();

	__property BLOCK_TYPE Block[unsigned int x][unsigned int y] = {read = GetBlock, write = SetBlock};

	__property AnsiString Host = {read = GetHost, write = SetHost};

	void ClearField();

	//AnsiString Host;
};

#endif
