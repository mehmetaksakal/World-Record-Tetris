//---------------------------------------------------------------------------

#pragma hdrstop

#include "CTetromino.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)


CTetromino::CTetromino(TETROMINO_TYPE Type)
{
	unsigned int x, y;

	this->MyType = Type;
	this->Y_pos = 0;
	this->X_pos = 0;
	this->MySize = 0;

	if(MyType == TETROMINO_I)
	{
		this->Block = new CMatrix<BLOCK_TYPE>(4, 4, 0);
		this->Block->operator()((1), (0)) = BLOCK_CYAN;
		this->Block->operator()((1), (1)) = BLOCK_CYAN;
		this->Block->operator()((1), (2)) = BLOCK_CYAN;
		this->Block->operator()((1), (3)) = BLOCK_CYAN;
	}
	else if(MyType == TETROMINO_O)
	{
		this->Block = new CMatrix<BLOCK_TYPE>(2, 2, BLOCK_YELLOW);
	}
	else
	{
		this->Block = new CMatrix<BLOCK_TYPE>(3, 3, 0);

		switch (MyType) {
		case TETROMINO_S:
			this->Block->operator()((0), (2)) = BLOCK_GREEN;
			this->Block->operator()((0), (1)) = BLOCK_GREEN;
			this->Block->operator()((1), (1)) = BLOCK_GREEN;
			this->Block->operator()((1), (0)) = BLOCK_GREEN;
			break;
		case TETROMINO_Z:
			this->Block->operator()((0), (0)) = BLOCK_RED;
			this->Block->operator()((0), (1)) = BLOCK_RED;
			this->Block->operator()((1), (1)) = BLOCK_RED;
			this->Block->operator()((1), (2)) = BLOCK_RED;
			break;
		case TETROMINO_J:
			this->Block->operator()((0), (0)) = BLOCK_BLUE;
			this->Block->operator()((1), (0)) = BLOCK_BLUE;
			this->Block->operator()((1), (1)) = BLOCK_BLUE;
			this->Block->operator()((1), (2)) = BLOCK_BLUE;
			break;
		case TETROMINO_L:
			this->Block->operator()((1), (0)) = BLOCK_ORANGE;
			this->Block->operator()((1), (1)) = BLOCK_ORANGE;
			this->Block->operator()((1), (2)) = BLOCK_ORANGE;
			this->Block->operator()((0), (2)) = BLOCK_ORANGE;
			break;
		case TETROMINO_T:
			this->Block->operator()((1), (0)) = BLOCK_PURPLE;
			this->Block->operator()((1), (1)) = BLOCK_PURPLE;
			this->Block->operator()((1), (2)) = BLOCK_PURPLE;
			this->Block->operator()((0), (1)) = BLOCK_PURPLE;
			break;
            
        default:
            break;
		}
	}

	this->MySize = this->Block->get_cols();

	return;
}

CTetromino::CTetromino(CTetromino *Tet)
{
	unsigned int x, y;

	this->MyType = Tet->Type;
	this->Y_pos = Tet->Y;
	this->X_pos = Tet->X;

	if(MyType == TETROMINO_I)
	{
		this->Block = new CMatrix<BLOCK_TYPE>(4, 4, 0);
	}
	else if(MyType == TETROMINO_O)
	{
		this->Block = new CMatrix<BLOCK_TYPE>(2, 2, BLOCK_YELLOW);
	}
	else
	{
		this->Block = new CMatrix<BLOCK_TYPE>(3, 3, 0);
    }

	for(y = 0; y < Tet->Size(); y++)
	{
		for(x = 0; x < Tet->Size(); x++)
		{
			this->Block->operator ()((x), (y)) = Tet->GetBlock(x, y);
        }
    }
}

CTetromino::~CTetromino()
{
	return;
}

void __fastcall CTetromino::SetX(signed int value)
{
	this->X_pos = value;
}

signed int __fastcall CTetromino::GetX()
{
	return this->X_pos;
}

void __fastcall CTetromino::SetY(unsigned int value)
{
	this->Y_pos = value;
}

unsigned int __fastcall CTetromino::GetY()
{
	return this->Y_pos;
}

void __fastcall CTetromino::SetType(TETROMINO_TYPE type)
{
	this->MyType = type;
}

TETROMINO_TYPE __fastcall CTetromino::GetType()
{
	return this->MyType;
}

void CTetromino::RotateCW()
{
	this->Block->transpose(false);
}

void CTetromino::RotateCCW()
{
	this->Block->transpose(true);
}

unsigned CTetromino::Size()
{
	return this->Block->get_cols();
}

BLOCK_TYPE CTetromino::GetBlock(unsigned int x, unsigned int y)
{
	return this->Block->operator()((y), (x));
}
