#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__
#include "cocos-ext.h"
#include "cocos2d.h"
#include "Board.h"
#include "math.h"

#define position_remove -1000
#define distance_x 250
#define distance_y 250

#define coor_r 21

#define coor_left_x 641
#define coor_left_y 419

#define coor_top_x 690
#define coor_top_y 478

#define coor_bot_x 690
#define coor_bot_y 358

#define coor_right_x 738
#define coor_right_y 419

#define retract_length 82 
#define retract_x 602
#define retract_y 216
#define replay_x 687
#define replay_y 134

#define score_x 684
#define score_y 543

#define winPosition_x 300
#define winPosition_y 0

#define gameover_score_x 435
#define gameover_score_y 285


USING_NS_CC;
USING_NS_CC_EXT;

class HelloWorld : public cocos2d::CCLayer
{
	bool isRetractAble;

	UIImageView *image_board;
	UILayer *layer;


	UILabel *test[board_x*board_y];
	UILabel *test_score;
public:
	// Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
	virtual bool init();  

	// there's no 'id' in cpp, so we recommend returning the class instance pointer
	static cocos2d::CCScene* scene();


	// a selector callback
	void menuCallback(CCObject* pSender);
	virtual bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);

	void showNum();

	float getFontsize(int num);

	char* intTranChar(int i);
	int getButton(int x,int y);
	void playAgain();

    // implement the "static node()" method manually
    CREATE_FUNC(HelloWorld);
	Board *myBoard;
};

#endif // __HELLOWORLD_SCENE_H__
