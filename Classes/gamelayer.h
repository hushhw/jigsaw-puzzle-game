#ifndef __GAME_SCENE_H__
#define __GAME_SCENE_H__

#include "cocos2d.h"
#include "cuttingphotos.h"
USING_NS_CC;
using namespace std;

static int level;

class GameScene : public cocos2d::Layer
{
public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();

    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();

    // implement the "static create()" method manually
    CREATE_FUNC(GameScene);

	static void setLevel(int level);
	void update(float delta);

	void plusMinusButtonCallback(Ref*ref);
	void plusMinusButtonCallbackto(Ref*ref);
	void backbtn(Ref*ref);
	void setsound(Ref*ref);
	void about(Ref*ref);
	void restart();
	void nextlevel();
	void priviouslevel();
	void onKeyReleased(EventKeyboard::KeyCode keyCode, Event* event);

	MenuItemSprite* leftmenu;
	MenuItemSprite* rightmenu;
	Sprite* left1;
	Sprite* right1;

	CuttingPhotos* photo;
	MenuItemImage* _plusItem;
	MenuItemImage* sound_on;
	MenuItemImage* sound_off;
	MenuItemImage* back1;
	MenuItemImage* back2;

	string img;
	LayerColor* boxlayer;
	LayerColor* backlayer;
	Layer* aboutlayer;
	Label* label;
	Sprite*aboutsprite;
	Sprite*soundsprite;
	Sprite*backsprite;
	Sprite*restartsprite;
	MenuItemLabel*backmenu;

	Size plusitem;
	Rect rect;
	bool ismenu;

};

#endif // __HELLOWORLD_SCENE_H__
