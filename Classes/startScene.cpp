#include "startScene.h"
#include "AppDelegate.h"
#include "chooseScene.h"
#include "about.h"
#include "setting.h"
#include "SimpleAudioEngine.h"
USING_NS_CC;
using namespace CocosDenshion;

cocos2d::Scene*startScene::createscene()
{
	auto scene=Scene::create();
	auto layer=startScene::create();
	scene->addChild(layer);
	return scene;
}

bool startScene::init()
{
	if(!Layer::init())
		return false;

	Size visibleSize=Director::getInstance()->getVisibleSize();

/*
 *	背景图片
 */
	auto spr_bg=Sprite::create("start1.jpg");//游戏的背景
	spr_bg->setPosition(Point(visibleSize.width/2,visibleSize.height/2));
	this->addChild(spr_bg);

/*
 *	读取xml文件，添加labelmenu
 */
	auto dic=Dictionary::createWithContentsOfFile("fonts/text.xml");//读取xml(不能直接显示汉字)
	auto ex=(String*)(dic->objectForKey("exit"));//添退出游戏按钮
	auto exi=Label::create(ex->getCString(),"fonts/fenshu.ttf",45);
	exi->setColor(Color3B(109,133,90));  
	auto exi2=MenuItemLabel::create(exi,CC_CALLBACK_1(startScene::exit,this));
	exi2->setPosition(Point(visibleSize.width/2,visibleSize.height/4)); 

	auto pl=(String*)(dic->objectForKey("start"));//添加选择关卡按钮
	auto pla=Label::create(pl->getCString(),"fonts/fenshu.ttf",45);
	pla->setColor(Color3B(109,133,90));  
	auto start_menu=MenuItemLabel::create(pla,CC_CALLBACK_1(startScene::start,this));
	start_menu->setPosition(Point(visibleSize.width/2,visibleSize.height/2)); 


	auto abou=(String*)(dic->objectForKey("about"));//添加关于按钮
	auto ab=Label::create(abou->getCString(),"fonts/fenshu.ttf",45);
	ab->setColor(Color3B(109,133,90));  
	auto abo=MenuItemLabel::create(ab,CC_CALLBACK_1(startScene::about,this));
	abo->setPosition(Point(visibleSize.width/2,5*visibleSize.height/12)); 

	auto sett=(String*)(dic->objectForKey("setting"));//添加设置按钮
	auto se=Label::create(sett->getCString(),"fonts/fenshu.ttf",45);
	se->setColor(Color3B(109,133,90));  
	auto setti=MenuItemLabel::create(se,CC_CALLBACK_1(startScene::setting,this));
	setti->setPosition(Point(visibleSize.width/2,visibleSize.height/3)); 

	auto menu=Menu::create(start_menu,exi2,abo,setti,NULL);
	menu->setPosition(Point::ZERO);  //位置
	this->addChild(menu);


	return true; 
} 

void startScene::start(Ref*ref)
{
	Director::getInstance()->replaceScene(TransitionCrossFade::create(0.3,chooseScene::createscene()));	//切换到选择关卡场景
}

void startScene::exit(Ref*ref)
{
	Director::getInstance()->end();
}

void startScene::setting(Ref*ref)
{
	Director::getInstance()->replaceScene(TransitionCrossFade::create(0.3,Setting::createScene()));
}

void startScene::about(Ref*ref)
{
	Director::getInstance()->replaceScene(TransitionCrossFade::create(0.3,aboutScene::createscence()));
}

void startScene::remov()
{
	aboutlayer->removeAllChildren();
}
