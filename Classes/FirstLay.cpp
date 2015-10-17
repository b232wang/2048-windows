#include "FirstLay.h"
#include "HelloWorldScene.h"
#include "Depot.h"
USING_NS_CC;


CCScene* FirstLay::scene()
{
    // 'scene' is an autorelease object
    CCScene *scene = CCScene::create();
    
    // 'layer' is an autorelease object
    FirstLay *layer = FirstLay::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}



// on "init" you need to initialize your instance
bool FirstLay::init(){
    //////////////////////////////
    // 1. super init first
    if ( !CCLayer::init() )
    {
        return false;
    }
    
    CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
    CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();

    /////////////////////////////
    // 2. add a menu item with "X" image, which is clicked to quit the program
    //    you may modify it.

    // add a "close" icon to exit the progress. it's an autorelease object
	CCMenuItemImage *pCloseItem = CCMenuItemImage::create(
		"greenButton.png",
		"greenButton2.png",
		this,
		menu_selector(FirstLay::startGame1));
    
	pCloseItem->setPosition(ccp(150,300));

	CCMenuItemImage *pCloseItem2 = CCMenuItemImage::create(
		"blueButton.png",
		"blueButton2.png",
		this,
		menu_selector(FirstLay::startGame2));

	pCloseItem2->setPosition(ccp(150,200));

    // create menu, it's an autorelease object
    CCMenu* pMenu = CCMenu::create(pCloseItem, NULL);
	CCMenu* pMenu2 = CCMenu::create(pCloseItem2, NULL);
    pMenu->setPosition(CCPointZero);
	pMenu2->setPosition(CCPointZero);
    this->addChild(pMenu, 1);
	this->addChild(pMenu2, 1);

	//CCLabelTTF* pLabel = CCLabelTTF::create("2048", "Arial", 128);
	//pLabel->setColor(ccGRAY);
	//pLabel->setPosition(ccp(400,500));
	//this->addChild(pLabel, 1);

    // add "FirstLay" splash screen"
    CCSprite* pSprite = CCSprite::create("FirstLayPic.jpg");

    // position the sprite on the center of the screen
    pSprite->setPosition(ccp(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));

    // add the sprite as a child to this layer
    this->addChild(pSprite, 0);

	CCSprite* pTital = CCSprite::create("tital.png");

	// position the sprite on the center of the screen
	pTital->setPosition(ccp(250,500));

	// add the sprite as a child to this layer
	this->addChild(pTital, 0);
 
    return true;
}



void FirstLay::startGame1(CCObject* pSender){
	Depot::getADepot()->isRetractAble = false;
	CCScene *scene2=HelloWorld::scene();
	CCTransitionScene *s=CCTransitionSplitCols::create(1,scene2);
	CCDirector::sharedDirector()->replaceScene(s);
}

void FirstLay::startGame2(CCObject* pSender){
	Depot::getADepot()->isRetractAble = true;
	CCScene *scene2=HelloWorld::scene();
	CCTransitionScene *s=CCTransitionSplitCols::create(1,scene2);
	CCDirector::sharedDirector()->replaceScene(s);
}