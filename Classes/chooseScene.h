
#ifndef __CHOOSESCENE__
#define __CHOOSESCENE__

#include <iostream>
#include "cocos2d.h"
using namespace std;
USING_NS_CC;

class chooseScene : public cocos2d::Layer
{
public:  
	static cocos2d::Scene*createscene();
    virtual bool init();  
	CREATE_FUNC(chooseScene);

	bool onTouchBegan(Touch *touch, Event  *event);
	void onTouchEnded(Touch *touch, Event  *event);
	void goToCurrNode();
	Size size();
	void donghua();

	Sprite* sprite1;
	int page_node_; 
	int cur_page_node_; //当前页面
	Point start;//点击时为止
	Point end; //抬起时为止
	float size_x;//页面宽
	float size_y;//高
	Layer* layer;
 	Label* btn_label;
	Label* bac;
	//进入游戏触摸判断
 	bool ismenu;
 	bool isendmenu;
	Rect rect;
	Size menusize;
	//退出主菜单触摸判断
	Size menuend;
	Rect endrect;
	bool ismenuwithend;
	bool isendmenuwithend;
	

}; 
#endif
