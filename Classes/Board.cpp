
#include <stdlib.h>
#include "Board.h"
#include <time.h>  




void Board::getRandomNum(){
	while(1){
		int rX = rand()%board_x;
		int rY = rand()%board_y;
		if(Board::board[rX][rY]==0){
			inputNum(rX,rY);

			new_x=rX;
			new_y=rY;
			break;
		}
	}

}

void Board::inputNum(int x,int y){
	srand( (unsigned)time( NULL ) ); 
	int p = rand()%10;
	if(p==0){
		Board::board[x][y]=2;
	}else{
		Board::board[x][y]=1;
	}
}

void Board::moveLeftRight(){
	for(int i = 0;i<board_y;i++){
		int *p= new int[board_x];
		for(int j=0;j<board_x;j++){
			p[j]=Board::board[board_x-1-j][i];
		}
		int *p2=Board::moveLine(p,board_x);
		for(int k =0;k<board_x;k++){
			Board::board[k][i]=p2[board_x-k-1];
		}
	}
}

void Board::moveRightLeft(){
	for(int i = 0;i<board_y;i++){
		int *p= new int[board_x];
		for(int j=0;j<board_x;j++){
			p[j]=Board::board[j][i];
		}
		int *p2=Board::moveLine(p,board_x);
		for(int k = 0;k<board_x;k++){
			Board::board[k][i]=p2[k];
		}
	}
}

void Board::moveTopBot(){
	for(int i = 0;i<board_x;i++){
		int *p= new int[board_y];
		for(int j=0;j<board_y;j++){
			p[j]=Board::board[i][j];
		}
		int *p2=Board::moveLine(p,board_y);
		for(int k = 0;k<board_y;k++){
			Board::board[i][k]=p2[k];
		}
	}
}

void Board::moveBotTop(){
	for(int i = 0;i<board_x;i++){
		int *p= new int[board_y];
		for(int j=0;j<board_y;j++){
			p[j]=Board::board[i][board_y-1-j];
		}
		int *p2=Board::moveLine(p,board_y);
		for(int k = 0;k<board_y;k++){
			Board::board[i][k]=p2[board_y-k-1];
		}
	}
}

bool Board::checkBlock(){
	int newScore = score;
	
	int new_Board[board_x][board_y];
	for(int x = 0; x < board_x ; x ++){
		for(int y = 0; y < board_y ; y ++){
			new_Board[x][y]=Board::board[x][y];		
		}
	}
	if(mainBoard(1)&&mainBoard(2)&&mainBoard(3)&&mainBoard(4)){
		score = newScore;
		return false;//堵死
	}
	score = newScore;
	for(int x = 0; x < board_x ; x ++){
		for(int y = 0; y < board_y ; y ++){
			Board::board[x][y] =new_Board[x][y];		
		}
	}

	return true;//没有堵死
}

int* Board::moveLine(int *p,int num){
	int *s =new int[num];
	for(int i = 0; i< num;i++){
		s[i]=0;
	}
	int c1 = 0;
	int j = 0;
	for(int i = 0;i<num;i++){
		if(p[i]!=0){
			if(c1==0){
				c1 = p[i];
			}else if (c1==p[i]){
				s[j]=c1+1;
				score += 1<<s[j];
				j++;
				c1=0;
			}else{
				s[j]=c1;
				j++;
				c1 = p[i];

			}
			} 
		
		if((i+1)== num){
			s[j]=c1;
		}
	}
	return s;
}

bool Board::mainBoard(int s){
	for(int x = 0; x < board_x ; x ++){
		for(int y = 0; y < board_y ; y ++){
			newBoard[x][y]=Board::board[x][y];		
		}
	}
	switch(s){
	case 1: moveLeftRight(); break;
	case 2: moveRightLeft(); break;
	case 3: moveTopBot(); break;
	case 4: moveBotTop(); break;
	}
	int a=0;
	for(int x = 0; x < board_x ; x ++){
		for(int y = 0; y < board_y ; y ++){
			if(newBoard[x][y]!=Board::board[x][y]){
				a=1;
				break;
			}		
		}
	}
	if(a==0){
		return true; //无法移动
	}else{
		return false;//可以移动
	}

}
bool Board::snapBackup(){
	for(int x = 0; x < board_x ; x ++){
		for(int y = 0; y < board_y ; y ++){
			snapBoard[x][y]=Board::board[x][y];		
		}
	}
	snap_xy[0]=new_x;
	snap_xy[1]=new_y;
	return true;
}

void Board::backUp(){
	for(int t = 0; t<(retract_num-1);t++){
		old_xy[t][0]=old_xy[t+1][0];
		old_xy[t][1]=old_xy[t+1][1];
		for(int x = 0; x < board_x ; x ++){
			for(int y = 0; y < board_y ; y ++){
				oldBoard[t][x][y]=oldBoard[t+1][x][y];		
			}
		}
	}

	for(int x = 0; x < board_x ; x ++){
		for(int y = 0; y < board_y ; y ++){
			oldBoard[retract_num-1][x][y]=snapBoard[x][y];		
		}
	}
	old_xy[retract_num-1][0]=snap_xy[0];
	old_xy[retract_num-1][1]=snap_xy[1];
}
void Board::retract(){
	for (int i = 0; i< board_x ; i++){
		for (int j=0;j<board_y;j++){
			board[i][j]=oldBoard[retract_num-1][i][j];
		}
	}
	new_x = old_xy[retract_num-1][0];
	new_y = old_xy[retract_num-1][1];

	for(int i = (retract_num-1);i>0;i--){
		old_xy[i][0]=old_xy[i-1][0];
		old_xy[i][1]=old_xy[i-1][1];
		for(int x = 0; x < board_x ; x ++){
			for(int y = 0; y < board_y ; y ++){
				oldBoard[i][x][y]=oldBoard[i-1][x][y];	
			}
		}
	}
}

Board::Board(void)
{
	playerAgain();	
}

Board::~Board(void)
{
}

void Board::playerAgain(){
	score = 0;
	for(int t = 0; t<retract_num;t++){
		for(int i=0;i<board_x;i++){
			for(int j=0;j<board_y;j++){
				Board::board[i][j] = 0; 
				oldBoard[t][i][j]=0;
			}		
		}
	}
}