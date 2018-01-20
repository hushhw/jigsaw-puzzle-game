#ifndef __GAMESCENE_H__
#define __GAMESCENE_H__

#include "cocos2d.h"

USING_NS_CC;

using namespace std;
class gameScene:public cocos2d::Layer
{
public:
	static cocos2d::Scene*createscence();
	virtual bool init();
	CREATE_FUNC(gameScene);
public:
	void plusMinusButtonCallback(Object* pSender);
	void backbtn(Object* pSender);
	void setsound(Object* pSender);
	void about(Object* pSender);
	void restart(Object* pSender);
	MenuItemImage *_plusItem;
	MenuItemImage *_minusItem;
	MenuItemImage *sound_on;
	MenuItemImage *sound_off;
	void remov();
	
	Layer*aboutlayer;
	LabelTTF* label;
	Sprite*aboutsprite;
	Sprite*soundsprite;
	Sprite*backsprite;
	Sprite*restartsprite;
	MenuItemLabel*backmenu;
};

#endif