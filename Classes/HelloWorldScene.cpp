#include "HelloWorldScene.h"
#include "cocos-ext.h"
#include "cocos2d.h"
#include "FirstLay.h"
#include "WinPosition.h"
#include "Depot.h"



USING_NS_CC;
USING_NS_CC_EXT;


 
CCScene* HelloWorld::scene()
{
    // 'scene' is an autorelease object
    CCScene *scene = CCScene::create();
    
    // 'layer' is an autorelease object
    HelloWorld *layer = HelloWorld::create();

    // add layer as a child to scene
    scene->addChild(layer);
	
    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
	myBoard=new Board();
    if ( !CCLayer::init() )
    {
        return false;
    }
    
	isRetractAble = Depot::getADepot()->isRetractAble;
	CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
	CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();



	layer = UILayer::create(); //
	layer->addWidget(CCUIHELPER->createWidgetFromJsonFile("my2048project/my2048project_1.json"));//
	layer->setPosition(ccp(0,0));
	this->addChild(layer);
	CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this,0,true);
	
	// set ÎÄ±¾¿ò
	char a[10];
	for(int i = 0; i< board_x*board_y ; i++){
		sprintf(a,"test%d",i);
		test[i]=dynamic_cast<UILabel *>(layer->getWidgetByName(a));
		test[i]->setFontName("Î¢ÈíÑÅºÚ");
		test[i]->setFontSize(800);
	}
	test_score=dynamic_cast<UILabel *>(layer->getWidgetByName("score"));
	test_score->setText("0");
	test_score->setPosition(ccp(score_x/0.6,score_y/0.6));
	test_score->setFontName("Î¢ÈíÑÅºÚ");
	test_score->setFontSize(600);


	myBoard->getRandomNum();
	showNum();
    /////////////////////////////
    // 2. add a menu item with "X" image, which is clicked to quit the program
    //    you may modify it.

    // add a "close" icon to exit the progress. it's an autorelease object
    CCMenuItemImage *pCloseItem = CCMenuItemImage::create(
                                        "CloseNormal.png",
                                        "CloseSelected.png",
                                        this,
										menu_selector(HelloWorld::menuCallback));

	pCloseItem->setPosition(ccp(750,15));
    // create menu, it's an autorelease object
    CCMenu* pMenu = CCMenu::create(pCloseItem, NULL);
    pMenu->setPosition(CCPointZero);
    this->addChild(pMenu, 1);

	return true;
}

bool HelloWorld::ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent){
	double real_x = pTouch->getLocation().x;
	double real_y = pTouch->getLocation().y;

	int p=getButton(real_x,real_y);
	if(p==0){
		CCLOG("wrong !");
	}else if(isRetractAble &&p ==5){
		myBoard->retract();
		CCLOG("retract");
	}else if(p==6){
		playAgain();
		CCLOG("replay");
	}else if(myBoard->snapBackup()&&myBoard->mainBoard(p)){
		CCLOG("Again");
	}else{
		myBoard->backUp();
		CCLOG("p=%d",p);		
		myBoard->getRandomNum();
	}
	showNum();
	if(!myBoard->checkBlock()){
		CCDirector::sharedDirector()->getTouchDispatcher()->removeAllDelegates();
		Depot::getADepot()->score = myBoard->score;
		Depot::getADepot()->score_size = getFontsize(myBoard->score);
		CCScene *scene2=WinPosition::scene();
		CCTransitionScene *s=CCTransitionSplitCols::create(1,scene2);
		CCDirector::sharedDirector()->replaceScene(s);
	}
	CCLOG("x= %f , y= %f",real_x,real_y);
	return true;
}

void HelloWorld::showNum(){	

	char scoreNum[256];
	itoa(myBoard->score,scoreNum,10);
	test_score->setText(scoreNum);
	test_score->setScale(getFontsize(myBoard->score));


	for(int i=0;i<board_x;i++){
		for(int j=0;j<board_y;j++){
			int num_xy = i*board_x + j;
			if(myBoard->board[i][j]==0){
				test[num_xy]->setPosition(ccp(position_remove,position_remove));
			}else{
				char tp[256];  
				itoa((1<<myBoard->board[i][j]),tp,10);
				test[num_xy]->setText(tp);
				test[num_xy]->setScale(getFontsize(1<<myBoard->board[i][j]));			
				test[num_xy]->setPosition(ccp((i*distance_x+distance_x/2),(j*distance_y+distance_y/2)));			
				
				if(i==myBoard->new_x && j==myBoard->new_y){
					test[num_xy]->setColor(ccRED);
				}else{
					test[num_xy]->setColor(ccBLACK);
				}
			}

		}
	}

}
void HelloWorld::playAgain(){

	myBoard->playerAgain();
	myBoard->getRandomNum();
	showNum();
}

float HelloWorld::getFontsize(int num){
	int p=0;
	for(int i = 5 ; i>-1;i--){
		if( (int)(num/pow((float)10,i))>0){
			p=i;
			break;
		}
	}
	switch(p){
	case 0: return 0.17;
	case 1: return 0.16;
	case 2: return 0.145;
	case 3: return 0.12;
	case 4: return 0.1;
	case 5: return 0.08;
	}
}

int HelloWorld::getButton(int x, int y){
	//right
	float t1 =  sqrt((float)((coor_right_x - x)*(coor_right_x - x) + (coor_right_y - y)*(coor_right_y - y)));
	//left
	float t2 =  sqrt((float)((coor_left_x - x)*(coor_left_x - x) + (coor_left_y - y)*(coor_left_y - y)));
	//bot
	float t3 =  sqrt((float)((coor_bot_x - x)*(coor_bot_x - x) + (coor_bot_y - y)*(coor_bot_y - y)));
	//top
	float t4 =  sqrt((float)((coor_top_x - x)*(coor_top_x - x) + (coor_top_y - y)*(coor_top_y - y)));
	if(t1<=coor_r){
		return 1;
	}else if(t2<=coor_r){
		return 2;
	}else if(t3<=coor_r){
		return 3;
	}else if(t4<=coor_r){
		return 4;
	}else if(x>=retract_x && x<=(retract_x+retract_length) && y>=retract_y && y<=(retract_y+retract_length)){
		return 5;
	}else if(x>=replay_x && x<=(replay_x+retract_length) && y>=replay_y && y<=(replay_y+retract_length)){
		return 6;
	}else{
		return 0;
	}

}

void HelloWorld::menuCallback(CCObject* pSender)
{
	CCScene *scene2=FirstLay::scene();
	CCTransitionScene *s=CCTransitionSplitCols::create(1,scene2);
	CCDirector::sharedDirector()->replaceScene(s);
}
