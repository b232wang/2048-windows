#include "WinPosition.h"
#include "FirstLay.h"
#include "Depot.h"
USING_NS_CC;

CCScene* WinPosition::scene()
{
    // 'scene' is an autorelease object
    CCScene *scene = CCScene::create();
    
    // 'layer' is an autorelease object
    WinPosition *layer = WinPosition::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool WinPosition::init()
{
    if ( !CCLayer::init() )
    {
        return false;
    }
    
	CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
	CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();
    CCMenuItemImage *pCloseItem = CCMenuItemImage::create(
                                        "CloseNormal.png",
                                        "CloseSelected.png",
                                        this,
                                        menu_selector(WinPosition::menuCallback));
    
	pCloseItem->setPosition(ccp(origin.x + visibleSize.width - pCloseItem->getContentSize().width/2 ,
                                origin.y + pCloseItem->getContentSize().height/2));

    // create menu, it's an autorelease object
    CCMenu* pMenu = CCMenu::create(pCloseItem, NULL);
    pMenu->setPosition(CCPointZero);
    this->addChild(pMenu, 1);

    
    CCLabelTTF* pLabel = CCLabelTTF::create("Game Over", "Arial", 80);
    pLabel->setColor(ccRED);
    pLabel->setPosition(ccp(300,500));
	this->addChild(pLabel, 1);

	

    // add "WinPosition" splash screen"
	CCSprite* pSprite = CCSprite::create("winPosition.jpg");
	pSprite->setPosition(ccp(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));
	this->addChild(pSprite, 0);
    
	CCSprite* pScore = CCSprite::create("score.png");
	pScore->setPosition(ccp(130,260));
	this->addChild(pScore, 0);

	char tp[256];  
	itoa(Depot::getADepot()->score ,tp,10);
	CCLabelTTF* pLabel2 = CCLabelTTF::create(tp, "Arial", 36);
	pLabel2->setFontSize(400);
	pLabel2->setScale(Depot::getADepot()->score_size );
	pLabel2->setColor(ccRED);
	pLabel2->setPosition(ccp(130,260));
	this->addChild(pLabel2, 1);

    return true;
}




void WinPosition::menuCallback(CCObject* pSender)
{
	CCScene *scene2=FirstLay::scene();
	CCTransitionScene *s=CCTransitionSplitCols::create(1,scene2);
	CCDirector::sharedDirector()->replaceScene(s);
}
