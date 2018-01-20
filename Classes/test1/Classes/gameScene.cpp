#include "startScene.h"
#include "chooseScene.h"
#include"gameScene.h"
#include"about.h"

USING_NS_CC;

cocos2d::Scene*gameScene::createscence()
{
	auto scene=Scene::create();
	auto layer=gameScene::create();
	scene->addChild(layer);
	return scene;
}

bool gameScene::init()
{
	if(!Layer::init())
		return false;

	Size visibleSize=Director::getInstance()->getVisibleSize();
	auto spr_bg=Sprite::create("main.jpg");//游戏的背景
	spr_bg->setPosition(Point(visibleSize.width/2,visibleSize.height/2));
	this->addChild(spr_bg);

	label = LabelTTF::create("", "", 1);
	label->setPosition(Point(visibleSize.width/2,visibleSize.height/2));
	label->setHorizontalAlignment(TextHAlignment::CENTER);
	this->addChild(label);

	_plusItem = MenuItemImage::create("ButtonStar.png","");
    _minusItem = MenuItemImage::create("ButtonStarSel.png","");
    MenuItemToggle *toggleItem = MenuItemToggle::createWithCallback(CC_CALLBACK_1(gameScene::plusMinusButtonCallback, this), _plusItem, _minusItem, NULL);

    auto toggleMenu = Menu::create(toggleItem, NULL);
    toggleMenu->setPosition(visibleSize.width/2,visibleSize.height/18);
    this->addChild(toggleMenu, 1);

	return true; 
} 

void gameScene::plusMinusButtonCallback(Object* pSender)
{
	Size visibleSize=Director::getInstance()->getVisibleSize();
    MenuItemToggle *toggleItem = (CCMenuItemToggle *)pSender;
    if (toggleItem->selectedItem() == _plusItem){
        //移除层
		aboutlayer->removeFromParent();
    }


    else if (toggleItem->selectedItem() == _minusItem){
        //添加层
		aboutlayer = LayerColor::create( Color4B(255,255,255,100),visibleSize.width, visibleSize.height);
		aboutlayer->ignoreAnchorPointForPosition(false);
		aboutlayer->setAnchorPoint(Point(0.5,0.5));
		aboutlayer->setPosition(Point(Director::getInstance()->getWinSize().width/2 , Director::getInstance()->getWinSize().height/2));
		this->addChild(aboutlayer);

		auto backmenu = MenuItemImage::create("back.png","", CC_CALLBACK_1(gameScene::backbtn, this));
		backmenu->setPosition(Point(aboutlayer->getContentSize().width/5, aboutlayer->getContentSize().height/10+10));
		auto backMenu = Menu::create(backmenu, NULL);
		backMenu->setPosition(Point::ZERO);
		aboutlayer->addChild(backMenu);

		sound_on = MenuItemImage::create("sound-on.png","");
		sound_off = MenuItemImage::create("sound-off.png","");
		MenuItemToggle *soundItem = MenuItemToggle::createWithCallback(CC_CALLBACK_1(gameScene::setsound, this),sound_on,sound_off,NULL);
		auto soundMenu = Menu::create(soundItem,NULL);
		soundMenu->setPosition(Point(aboutlayer->getContentSize().width*2/5, aboutlayer->getContentSize().height/10+40));
		aboutlayer->addChild(soundMenu);

		auto aboutmenu = MenuItemImage::create("about.png","", CC_CALLBACK_1(gameScene::about,this));
		aboutmenu->setPosition(Point(aboutlayer->getContentSize().width*3/5, aboutlayer->getContentSize().height/10+40));
		auto aboutMenu = Menu::create(aboutmenu, NULL);
		aboutMenu->setPosition(Point::ZERO);
		aboutlayer->addChild(aboutMenu);

		auto restarttmenu = MenuItemImage::create("restart.png","", CC_CALLBACK_1(gameScene::restart,this));
		restarttmenu->setPosition(Point(aboutlayer->getContentSize().width*4/5, aboutlayer->getContentSize().height/10+10));
		auto restartMenu = Menu::create(restarttmenu, NULL);
		restartMenu->setPosition(Point::ZERO);
		aboutlayer->addChild(restartMenu);
    }
}

void gameScene::backbtn(Object* pSender)
{
	Director::getInstance()->replaceScene(TransitionCrossFade::create(0.3,startScene::createscence()));	//切换到选择关卡场景
}

void gameScene::setsound(Object* pSender)
{
	MenuItemToggle *soundItem = (CCMenuItemToggle *)pSender;
	if (soundItem->selectedItem() ==sound_on){
        //移除层
		        label->setString("Visible button: on");
    }

	else if (soundItem->selectedItem() ==sound_off){
		        label->setString("Visible button: off");
	}
}

void gameScene::about(Object* pSender)
{
	Director::getInstance()->replaceScene(TransitionCrossFade::create(0.3,aboutScene::createscence()));	//切换到关于场景
}

void gameScene::restart(Object* pSender)
{
	Director::getInstance()->replaceScene(TransitionCrossFade::create(0.3,gameScene::createscence()));	//切换到当前场景
}