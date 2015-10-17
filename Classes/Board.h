#pragma once
#define board_x 4
#define board_y 4
#define retract_num 10

class Board
{
	
public:
	//记录新出数字的位置
	int new_x;
	int new_y;
	//保存该位置
	int old_xy[10][2];
	int snap_xy[2];
	int score;

	void playerAgain();

	int board[board_x][board_y];
	int newBoard[board_x][board_y];
	int oldBoard[10][board_x][board_y];
	int snapBoard[board_x][board_y];

	void getRandomNum();
	void inputNum(int x, int y);

	bool snapBackup();

	void moveLeftRight();
	void moveRightLeft();
	void moveTopBot();
	void moveBotTop();
	void printBoard();
	void retract();
	void backUp();

	bool checkBlock();
	bool checkLineBlock(int *p, int num);

	bool mainBoard(int s);

	int* moveLine(int* p, int num);
	Board(void);
	~Board(void);
};

