// ---------------------------------------------------------------------------

#ifndef CTetrominoH
#define CTetrominoH
// ---------------------------------------------------------------------------
#include "TTetris.h"
#include "CMatrix.h"

class CTetromino {
private:
	CMatrix<BLOCK_TYPE> *Block;

	TETROMINO_TYPE MyType;
	signed int X_pos;
	unsigned int Y_pos;
	unsigned MySize;

	void __fastcall SetX(signed int value);
	signed int __fastcall GetX();

	void __fastcall SetY(unsigned int value);
	unsigned int __fastcall GetY();

	void __fastcall SetType(TETROMINO_TYPE type);
	TETROMINO_TYPE __fastcall GetType();

public:
	CTetromino(TETROMINO_TYPE Type);
	CTetromino(CTetromino *Tet);
	~CTetromino();

	__property signed int X = {read = GetX, write = SetX};
	__property unsigned int Y = {read = GetY, write = SetY};
	__property TETROMINO_TYPE Type = {read = GetType, write = SetType};

	void RotateCW();
	void RotateCCW();

	BLOCK_TYPE GetBlock(unsigned int x, unsigned int y);

	unsigned Size();
};

#endif
