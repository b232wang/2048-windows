#pragma once

#include "cocos2d.h"

class FirstLay : public cocos2d::CCLayer
{
public:
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
	virtual bool init();  

	void startGame1(CCObject* pSender);
	void startGame2(CCObject* pSender);
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::CCScene* scene();
    
	// a selector callback
    
    // implement the "static node()" method manually
	CREATE_FUNC(FirstLay);
};

