//---------------------------------------------------------------------------

#pragma hdrstop

#include "CGame.h"
#include <mmsystem.h>
#include <time.h>       /* time */
//---------------------------------------------------------------------------
#pragma package(smart_init)


CGame::CGame(TWinControl *_Owner, TWinControl *_PanelNext, TLabel *_Label, TIdUDPServer *_UDPServer) : TTimer(_Owner)
{
	unsigned int x, y;
	srand(time(NULL));

	this->Owner = _Owner;
	this->PanelNext = _PanelNext;
	this->Label = _Label;
	this->UDPServer = _UDPServer;
	this->BoardColors = new CBoard();
	this->Board = new CBoard();

	this->Rows = BoardColors->NumRows;
	this->Cols = BoardColors->NumCols;

	this->Interval		= 500;
	this->IntervalGame	= 500;
	this->Enabled		= false;
	this->OnTimer		= this->OnTimerEvent;
	//this->Enabled 		= true;

	this->Tetromino		= NULL;
	this->NextTetromino	= NULL;
	this->Running = false;

	this->LockCount = 0;
	this->FastDown = false;
	this->score = 0;
	this->level = 0;
	this->numlines = 0;

	BlockImages[0]		= new TPicture();
	BlockImages[0]->LoadFromFile(PATH_BLOCK_EMPTY);

	BlockImages[1]		= new TPicture();
	BlockImages[1]->LoadFromFile(PATH_BLOCK_CYAN);

	BlockImages[2]		= new TPicture();
	BlockImages[2]->LoadFromFile(PATH_BLOCK_YELLOW);

	BlockImages[3]		= new TPicture();
	BlockImages[3]->LoadFromFile(PATH_BLOCK_GREEN);

	BlockImages[4]		= new TPicture();
	BlockImages[4]->LoadFromFile(PATH_BLOCK_RED);

	BlockImages[5]		= new TPicture();
	BlockImages[5]->LoadFromFile(PATH_BLOCK_BLUE);

	BlockImages[6]		= new TPicture();
	BlockImages[6]->LoadFromFile(PATH_BLOCK_ORANGE);

	BlockImages[7]		= new TPicture();
	BlockImages[7]->LoadFromFile(PATH_BLOCK_PURPLE);

	BlockImages[8]		= new TPicture();
	BlockImages[8]->LoadFromFile(PATH_BLOCK_BORDER);

	for(y = 0; y < Rows; y++)
	{
		for(x = 0; x < Cols; x++)
		{
			this->BoardImages[x][y] = new TImage(_Owner);
			this->BoardImages[x][y]->Parent = _Owner;
			this->BoardImages[x][y]->Name = "BoardImage_x" + AnsiString(x) + "y" + AnsiString(y);
			this->BoardImages[x][y]->Height = 40;
			this->BoardImages[x][y]->Width = 40;
			this->BoardImages[x][y]->Top = y * 40;
			this->BoardImages[x][y]->Left = x * 40;
			this->BoardImages[x][y]->Show();

		}
	}

	for(y = 0; y < NEXT_MAX_XY; y++)
	{
		for(x = 0; x < NEXT_MAX_XY; x++)
		{
			this->NextImages[x][y] = new TImage(_PanelNext);
			this->NextImages[x][y]->Parent = _PanelNext;
			this->NextImages[x][y]->Name = "NextImage_x" + AnsiString(x) + "y" + AnsiString(y);
			this->NextImages[x][y]->Height = 40;
			this->NextImages[x][y]->Width = 40;
			this->NextImages[x][y]->Top = y * 40;
			this->NextImages[x][y]->Left = x * 40;
			this->NextImages[x][y]->Picture = BlockImages[BLOCK_EMPTY];
			this->NextImages[x][y]->Show();

		}
	}

	this->DrawBoard();
	this->Label->Caption = "press start to begin";
	this->Label->Visible = true;
}

__fastcall CGame::~CGame(void)
{
	unsigned int x, y;
	TImage *TempImage;

	for(y = 0; y < Rows; y++)
	{
		for(x = 0; x < Cols; x++)
		{
			this->BoardImages[x][y] = NULL;
		}
	}
}

void CGame::DrawNext()
{
	unsigned int x, y;
	BLOCK_TYPE Block;

	for(y = 0; y < NEXT_MAX_XY; y++)
	{
		for(x = 0; x < NEXT_MAX_XY; x++)
		{
			if(x >= this->NextTetromino->Size() || y >= this->NextTetromino->Size())
			{
				Block = BLOCK_EMPTY;
			}
			else
			{
				Block = this->NextTetromino->GetBlock(x, y);
			}

			this->NextImages[x][y]->Picture = BlockImages[Block];
		}
    }
}

void CGame::DrawBoard()
{
	unsigned int y;
	signed int x, size;
	BLOCK_TYPE block;
	AnsiString Msg;
	unsigned char value;

	this->TransmitBoard = new CBoard();

	for(y = 0; y < Rows; y++)
	{
		for(x = 0; x < Cols; x++)
		{
			switch(this->BoardColors->Block[x][y])
			{
				case BLOCK_BORDER:
					this->BoardImages[x][y]->Picture = BlockImages[BLOCK_BORDER];
					break;
				case BLOCK_EMPTY:
					this->BoardImages[x][y]->Picture = BlockImages[BLOCK_EMPTY];
					break;
				case BLOCK_CYAN:
					this->BoardImages[x][y]->Picture = BlockImages[BLOCK_CYAN];
					break;
				case BLOCK_YELLOW:
					this->BoardImages[x][y]->Picture = BlockImages[BLOCK_YELLOW];
					break;
				case BLOCK_GREEN:
					this->BoardImages[x][y]->Picture = BlockImages[BLOCK_GREEN];
					break;
				case BLOCK_RED:
					this->BoardImages[x][y]->Picture = BlockImages[BLOCK_RED];
					break;
				case BLOCK_BLUE:
					this->BoardImages[x][y]->Picture = BlockImages[BLOCK_BLUE];
					break;
				case BLOCK_ORANGE:
					this->BoardImages[x][y]->Picture = BlockImages[BLOCK_ORANGE];
					break;
				case BLOCK_PURPLE:
					this->BoardImages[x][y]->Picture = BlockImages[BLOCK_PURPLE];
					break;
				default:
					break;
			}

			this->TransmitBoard->Block[x][y] = this->BoardColors->Block[x][y];

			/*if((x > 0) && (x < 11) && (y < 21))
			{
				value = this->BoardColors->Block[x][y];
				Msg.sprintf("%c%c%c", x, y + 1, value + 1);
				UDPServer->Send(this->Host, 16000, Msg);
			}*/
		}
	}

	if(this->Tetromino != NULL)
	{
		for(y = this->Tetromino->Y; y < this->Tetromino->Size() + this->Tetromino->Y; y++)
		{
			size = this->Tetromino->Size() + this->Tetromino->X;

			for(x = this->Tetromino->X; x < size; x++)
			{
				if(x == -1) x++;

				block = Tetromino->GetBlock(x - this->Tetromino->X, y - this->Tetromino->Y);

				if(block != BLOCK_EMPTY)
				{
					this->BoardImages[x][y]->Picture = BlockImages[block];
					this->TransmitBoard->Block[x][y] = block;
				}

				/*if((x > 0) && (x < 11) && (y < 21) && (block != BLOCK_EMPTY))
				{
					value = block;
					Msg.sprintf("%c%c%c", x, y + 1, value + 1);
					UDPServer->Send(this->Host, 16000, Msg);
				}*/
			}
		}
	}

	for(x = 1; x < 11; x++)
	{
		for(y = 0; y < 20; y++)
		{
			value = this->TransmitBoard->Block[x][y];
			Msg.sprintf("%c%c%c", x, y + 1, value + 1);
			UDPServer->Send(this->Host, 15000, Msg);
        }
    }
}

bool CGame::DetectLeft()
{
	bool result;
	BLOCK_TYPE TetBlock, BoardBlock;
	unsigned int x, y, bx, by;

	result = true;

	for(y = 0; y < this->Tetromino->Size(); y++)
	{
		for(x = 0; x < this->Tetromino->Size(); x++)
		{
			TetBlock = this->Tetromino->GetBlock(x, y);

			if(TetBlock != BLOCK_EMPTY)
			{
				bx = this->Tetromino->X + x - 1;
				by = this->Tetromino->Y + y;

				BoardBlock = this->BoardColors->Block[bx][by];

				if((BoardBlock != BLOCK_EMPTY) || (BoardBlock == BLOCK_BORDER))
				{
					result = false;
					break;
				}
			}
		}

		if(result == false) break;
	}

	return result;
}

bool CGame::DetectRight()
{
	bool result;
	BLOCK_TYPE TetBlock, BoardBlock;
	unsigned int x, y, bx, by;

	result = true;

	for(y = 0; y < this->Tetromino->Size(); y++)
	{
		for(x = 0; x < this->Tetromino->Size(); x++)
		{
			TetBlock = this->Tetromino->GetBlock(x, y);

			if(TetBlock != BLOCK_EMPTY)
			{
				bx = this->Tetromino->X + x + 1;
				by = this->Tetromino->Y + y;
				BoardBlock = this->BoardColors->Block[bx][by];

				if((BoardBlock != BLOCK_EMPTY) || (BoardBlock == BLOCK_BORDER))
				{
					result = false;
					break;
				}
			}
		}

		if(result == false) break;
	}

	return result;
}

bool CGame::DetectDown()
{
	bool result;
	BLOCK_TYPE TetBlock, BoardBlock;
	unsigned int x, y, bx, by, lines;

	result = true;
	lines = 0;

	for(y = this->Tetromino->Size() - 1; y < 4294967295; y--)
	{
		for(x = 0; x < this->Tetromino->Size(); x++)
		{
			TetBlock = this->Tetromino->GetBlock(x, y);

			if(TetBlock != BLOCK_EMPTY)
			{
				bx = this->Tetromino->X + x;
				by = this->Tetromino->Y + y + 1;

				BoardBlock = this->BoardColors->Block[bx][by];

				if((BoardBlock != BLOCK_EMPTY) || (BoardBlock == BLOCK_BORDER))
				{
					result = false;
					this->LockCount++;
					break;
				}
			}
		}

		if(result == false) break;
	}

	if(result == false && this->LockCount > 1)
	{
		this->LockCount = 0;

		for(y = 0; y < this->Tetromino->Size(); y++)
		{
			for(x = 0; x < this->Tetromino->Size(); x++)
			{
				TetBlock = this->Tetromino->GetBlock(x, y);

				if(TetBlock != BLOCK_EMPTY)
				{
					bx = this->Tetromino->X + x;
					by = this->Tetromino->Y + y;

					this->Board->Block[bx][by] = 1;
					this->BoardColors->Block[bx][by] = TetBlock;
				}
			}
		}

		delete this->Tetromino;
		this->Tetromino = NULL;
		this->Interval = this->IntervalGame;

		by = this->DetectLine();

		while(by != 0)
		{
			lines++;
			this->numlines++;

			if(this->numlines%10 == 0) this->LevelUp();

			for(x = 1; x <= 10; x++)
			{
				this->Board->Block[x][y] = 0;
				this->BoardColors->Block[x][y] = BLOCK_EMPTY;
			}

			for(y = by; y > 0; y--)
			{
				for(x = 1; x <= 10; x++)
				{
					this->Board->Block[x][y] = this->Board->Block[x][y-1];
					this->BoardColors->Block[x][y] = this->BoardColors->Block[x][y-1];
				}
			}

			by = this->DetectLine();
		}

		if(lines != 0)
		{
			switch(lines)
			{
				case 1:
					this->score += 40 * (this->level + 1);
					PlaySound(PATH_AUDIO_CLEAR, NULL, SND_FILENAME/*|SND_ASYNC*/);
					break;
				case 2:
					this->score += 100 * (this->level + 1);
					PlaySound(PATH_AUDIO_CLEAR, NULL, SND_FILENAME);
					break;
				case 3:
					this->score += 300 * (this->level + 1);
					PlaySound(PATH_AUDIO_CLEAR, NULL, SND_FILENAME);
					break;
				case 4:
					this->score += 1200 * (this->level + 1);
					PlaySound(PATH_AUDIO_CLEAR4, NULL, SND_FILENAME);
					break;
            }
		}

		if(lines == 0) PlaySound(PATH_AUDIO_LOCK, NULL, SND_FILENAME|SND_ASYNC);
    }

	return result;
}

bool CGame::DetectRotation(bool RCCW)
{
	bool result;
	BLOCK_TYPE Block, BoardBlock;
	unsigned int x, y, bx, by;
	CTetromino *TetBlock;

	TetBlock = new CTetromino(this->Tetromino);
	result = true;

	if(RCCW == true)
	{
		TetBlock->RotateCCW();
	}
	else
	{
        TetBlock->RotateCW();
	}

	for(y = 0; y < TetBlock->Size(); y++)
	{
		for(x = 0; x < TetBlock->Size(); x++)
		{
			bx = x + TetBlock->X;
			by = y + TetBlock->Y;

			Block = TetBlock->GetBlock(x, y);
			BoardBlock = Block + this->BoardColors->Block[bx][by];

			if(Block != BoardBlock)
			{
				result = false;
				break;
			}
		}

		if(result == false) break;
	}

	return result;
}

bool CGame::DetectGameOver()
{
	unsigned int x, y, bx, by;
	BLOCK_TYPE Block, BoardBlock;
	bool result;

	result = false;

	for(y = 0; y < this->Tetromino->Size(); y++)
	{
		for(x = 0; x < this->Tetromino->Size(); x++)
		{
			bx = x + this->Tetromino->X;
			by = y + this->Tetromino->Y;

			Block = this->Tetromino->GetBlock(x, y);
			BoardBlock = Block + this->BoardColors->Block[bx][by];

			if(Block != BoardBlock)
			{
				result = true;
				break;
			}
		}

		if(result == true) break;
	}

	return result;
}

unsigned int CGame::DetectLine()
{
	unsigned int x, y, result, line;
	BLOCK_TYPE Block;

	result = 0;

	for(y = 19; y > 0; y--)
	{
		line = 1;

		for(x = 1; x <= 10; x++)
		{
			Block = this->Board->Block[x][y];
			line = line * Block;
		}

		if(line != 0)
		{
			result = y;
			break;
		}
	}

	return result;
}

void CGame::MoveDown()
{
	if(this->Tetromino == NULL) return;

	if(this->DetectDown())
	{
		this->Tetromino->Y = this->Tetromino->Y + 1;
	}
}

void CGame::LevelUp()
{
	this->level++;

	this->Interval = 1000 / ((this->level + 1) * (SPEED_MULTIPLIER));
	this->IntervalGame = 1000 / ((this->level + 1) * (SPEED_MULTIPLIER));

	PlaySound(PATH_AUDIO_LEVELUP, NULL, SND_FILENAME);
}

void CGame::RotateCW()
{
	if(this->Tetromino == NULL) return;

	if(this->DetectRotation(false))
	{
		this->Tetromino->RotateCW();
		PlaySound(PATH_AUDIO_ROTATE, NULL, SND_FILENAME|SND_ASYNC);
	}
}

void CGame::RotateCCW()
{
	if(this->Tetromino == NULL) return;

	if(this->DetectRotation(true))
	{
		this->Tetromino->RotateCCW();
		PlaySound(PATH_AUDIO_ROTATE, NULL, SND_FILENAME|SND_ASYNC);
	}
}

void CGame::MoveLeft()
{
	if(this->Tetromino == NULL) return;

	if(this->DetectLeft())
	{
		this->Tetromino->X = this->Tetromino->X - 1;
		this->LockCount = 0;
		PlaySound(PATH_AUDIO_SHIFT, NULL, SND_FILENAME|SND_ASYNC);
	}
}

void CGame::MoveRight()
{
	if(this->Tetromino == NULL) return;

	if(this->DetectRight())
	{
		this->Tetromino->X = this->Tetromino->X + 1;
		this->LockCount = 0;
		PlaySound(PATH_AUDIO_SHIFT, NULL, SND_FILENAME|SND_ASYNC);
	}
}

void CGame::FastDownStart()
{
	this->Interval = 25;
}

void CGame::FastDownStop()
{
	this->Interval = this->IntervalGame;
}

void CGame::Drop()
{
	//this->Interval = 1;
}

void CGame::ClearField()
{
	unsigned int x, y;

	for(y = 0; y < 20; y++)
	{
		for(x = 1; x < 11; x++)
		{
			this->Board->Block[x][y] = 0;
			this->BoardColors->Block[x][y] = BLOCK_EMPTY;
		}
	}

	if(this->Tetromino != NULL)
	{
		delete this->Tetromino;
		this->Tetromino = NULL;
    }
}

void CGame::GameStart()
{
	this->ClearField();
	this->Label->Visible = false;

	if(this->Tetromino != NULL)
	{
		delete this->Tetromino;
		this->Tetromino = NULL;
	}

	if(this->NextTetromino != NULL)
	{
		delete this->NextTetromino;
		this->NextTetromino = NULL;
	}

	this->Enabled = true;
	this->Running = true;
	this->score = 0;
	this->level = 0;
	this->numlines = 0;

	this->Interval = 1000 / ((this->level + 1) * (SPEED_MULTIPLIER));
	this->IntervalGame = 1000 / ((this->level + 1) * (SPEED_MULTIPLIER));

	this->OnTimerEvent(this->Owner);
}

bool CGame::GameRunning()
{
	return this->Running;
}

unsigned long long CGame::GetScore()
{
	return this->score;
}

unsigned int CGame::GetLevel()
{
	return this->level;
}

unsigned int CGame::GetLines()
{
    return this->numlines;
}

void __fastcall CGame::OnTimerEvent(TObject *Sender)
{
	//unsigned int random;

	if(this->Tetromino == NULL)
	{


		if(this->NextTetromino == NULL)
		{
			this->Tetromino = new CTetromino((rand() % 7) + 1);
			this->NextTetromino = new CTetromino((rand() % 7) + 1);
		}
		else
		{
			this->Tetromino = this->NextTetromino;
			this->NextTetromino = new CTetromino((rand() % 7) + 1);
		}

		this->DrawNext();
		this->Tetromino->X = 5;

		if(this->DetectGameOver())
		{
			this->Enabled = false;
			this->Running = false;
			this->Label->Visible = true;
			PlaySound(PATH_AUDIO_GAMEOVER, NULL, SND_FILENAME|SND_ASYNC);
        }
	}

	this->MoveDown();
}
