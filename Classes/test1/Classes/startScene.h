#ifndef __STARTSCENE_H__
#define __STARTSCENE_H__

#include "cocos2d.h"

USING_NS_CC;

using namespace std;
class startScene:public cocos2d::Layer
{
public:
	static cocos2d::Scene*createscence();
	virtual bool init();
	CREATE_FUNC(startScene);
public:
	void start(Ref*ref);//开始游戏按钮
	void exit(Ref*ref);//退出游戏按钮
	void setting(Ref*ref);//退出游戏按钮
	void about(Ref*ref);//关于
	Layer*aboutlayer;
	MenuItemLabel*backmenu;
};

#endif