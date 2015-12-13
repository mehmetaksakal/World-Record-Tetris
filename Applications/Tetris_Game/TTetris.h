//---------------------------------------------------------------------------

#ifndef TTetrisH
#define TTetrisH
//---------------------------------------------------------------------------

#define SPEED_MULTIPLIER		1.2

#define BOARD_BORDER_LEFT_RIGHT 2
#define BOARD_BORDER_BOTTOM		1
#define BOARD_NUM_TOPLINES		0
#define BOARD_X					10
#define BOARD_Y					20

#define BOARD_MAX_X				BOARD_X + BOARD_BORDER_LEFT_RIGHT
#define BOARD_MAX_Y 			BOARD_Y + BOARD_NUM_TOPLINES + BOARD_BORDER_BOTTOM
#define NEXT_MAX_XY				4

#define TETROMINO_I 		0x01
#define TETROMINO_O 		0x02
#define TETROMINO_S 		0x03
#define TETROMINO_Z 		0x04
#define TETROMINO_J 		0x05
#define TETROMINO_L 		0x06
#define TETROMINO_T 		0x07

#define BLOCK_EMPTY 		0x00
#define BLOCK_CYAN 			0x01
#define BLOCK_YELLOW		0x02
#define BLOCK_GREEN			0x03
#define BLOCK_RED			0x04
#define BLOCK_BLUE			0x05
#define BLOCK_ORANGE		0x06
#define BLOCK_PURPLE		0x07
#define BLOCK_BORDER		0x08

#define PATH_BLOCK_BORDER	"./Images/border.bmp"
#define PATH_BLOCK_CYAN		"./Images/cyan.bmp"
#define PATH_BLOCK_YELLOW	"./Images/yellow.bmp"
#define PATH_BLOCK_GREEN 	"./Images/green.bmp"
#define PATH_BLOCK_RED		"./Images/red.bmp"
#define PATH_BLOCK_BLUE		"./Images/blue.bmp"
#define PATH_BLOCK_ORANGE	"./Images/orange.bmp"
#define PATH_BLOCK_PURPLE	"./Images/purple.bmp"
#define PATH_BLOCK_EMPTY	"./Images/empty.bmp"

#define PATH_AUDIO_LOOP			L"./Audio/tetris-loop.wav"
#define PATH_AUDIO_LOOP_MUSIC1	L"./Audio/tetris-music1-loop.wav"
#define PATH_AUDIO_LOOP_MUSIC2	L"./Audio/tetris-music2-loop.wav"
#define PATH_AUDIO_LOOP_MUSIC3	L"./Audio/tetris-music3-loop.wav"
#define PATH_AUDIO_LOCK			L"./Audio/lock.wav"
#define PATH_AUDIO_ROTATE		L"./Audio/rotate.wav"
#define PATH_AUDIO_SHIFT		L"./Audio/shift.wav"
#define PATH_AUDIO_LEVELUP		L"./Audio/levelup.wav"
#define PATH_AUDIO_CLEAR		L"./Audio/clear.wav"
#define PATH_AUDIO_CLEAR4		L"./Audio/clear4.wav"
#define PATH_AUDIO_GAMEOVER		L"./Audio/gameover.wav"



typedef unsigned char	TETROMINO_TYPE;
typedef unsigned char	BLOCK_TYPE;

#endif