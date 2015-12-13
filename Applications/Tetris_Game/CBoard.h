// ---------------------------------------------------------------------------

#ifndef CBoardH
#define CBoardH
// ---------------------------------------------------------------------------

#include "TTetris.h"
#include "CMatrix.h"

class CBoard {
private:
	CMatrix<BLOCK_TYPE> *Board;

	unsigned int 	GetCols();
	unsigned int 	GetRows();
	BLOCK_TYPE 		GetBlock(unsigned int x, unsigned int y);
	void	 		SetBlock(unsigned int x, unsigned int y, BLOCK_TYPE Block);


public:

	CBoard();
	~CBoard();

	__property int NumCols = {read = GetCols};
	__property int NumRows = {read = GetRows};
	__property BLOCK_TYPE Block[unsigned int x][unsigned int y] = {read = GetBlock, write = SetBlock};

	//CMatrix<BLOCK_TYPE> &GetPositions();

	void Transpose();
};

#include "CMatrix.cpp"

#endif
