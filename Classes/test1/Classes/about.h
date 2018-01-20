#ifndef __ABOUT_H__
#define __ABOUT_H__

#include "cocos2d.h"

USING_NS_CC;

using namespace std;
class aboutScene:public cocos2d::Layer
{
public:
	static cocos2d::Scene*createscence();
	virtual bool init();
	CREATE_FUNC(aboutScene);
public:
	void backto(Ref*ref);//·µ»Ø²Ëµ¥°´Å¥

	MenuItemLabel*backmenu;
	
	void remov();
};

#endif