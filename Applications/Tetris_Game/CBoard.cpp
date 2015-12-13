// ---------------------------------------------------------------------------

#pragma hdrstop

#include "CBoard.h"
// ---------------------------------------------------------------------------
#pragma package(smart_init)

CBoard::CBoard() {
	unsigned int Rows, Cols;
	unsigned int i;

	Board = new CMatrix<BLOCK_TYPE>(BOARD_MAX_Y, BOARD_MAX_X, 0);

	Rows = Board->get_rows();
	Cols = Board->get_cols();

	/* Add side blocks */
	for (i = 0; i < Rows; i++) {
		Board->operator()((i), (0)) = BLOCK_BORDER;
		Board->operator()((i), (11)) = BLOCK_BORDER;
	}

	/* Add bottom blocks */
	for (i = 0; i < Cols; i++) {
		Board->operator()((20), (i)) = BLOCK_BORDER;
	}

	return;
}

CBoard::~CBoard() {
	return;
}

unsigned int CBoard::GetCols() {
	return this->Board->get_cols();
}

unsigned int CBoard::GetRows() {
	return this->Board->get_rows();
}

BLOCK_TYPE CBoard::GetBlock(unsigned int x, unsigned int y) {
	return this->Board->operator()((y), (x));
}

void CBoard::SetBlock(unsigned int x, unsigned int y, BLOCK_TYPE Block) {
	this->Board->operator()((y), (x)) = Block;
}

void CBoard::Transpose()
{
	CMatrix<BLOCK_TYPE> TempBoard(1, 1, 0);

	TempBoard = (this->Board->transpose(false));

	this->Board = &TempBoard;
}

/*CMatrix<BLOCK_TYPE> &CBoard::GetPositions()
{
	CMatrix<BLOCK_TYPE> *result = new CMatrix<BLOCK_TYPE>(this->NumRows, this->NumCols, 0);

	for (unsigned int i = 0; i < GetRows(); i++)
	{
		for (unsigned int j = 0; j < GetCols(); j++)
		{
			if(this->Board->operator()((i), (j)) == 0)
			{
				result->insert(i, j, 1);
            }
		}
	}

	return *result;
}*/
