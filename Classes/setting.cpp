#include "setting.h"
#include "startScene.h"
USING_NS_CC;

Scene* Setting::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = Setting::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool Setting::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
	Size visibleSize=Director::getInstance()->getVisibleSize();
	auto spr_bg=Sprite::create("about.jpg");//游戏的背景
	spr_bg->setPosition(Point(visibleSize.width/2,visibleSize.height/2));
	this->addChild(spr_bg);

	auto dic=Dictionary::createWithContentsOfFile("fonts/text.xml");//读取xml(不能直接显示汉字)
	auto ba=(String*)(dic->objectForKey("back"));

	auto bac=Label::createWithTTF(ba->getCString(),"fonts/fenshu.ttf",45);
	bac->setColor(Color3B(77,126,138));  
	auto bac1=MenuItemLabel::create(bac,CC_CALLBACK_1(Setting::backto,this));
	bac1->setPosition(Point(visibleSize.width/2,visibleSize.height/5));

	auto menu=Menu::create(bac1,NULL);
	menu->setPosition(Point::ZERO);  //位置
	this->addChild(menu);

    return true;
}

void Setting::backto(Ref*ref)
{
	Director::getInstance()->replaceScene(TransitionCrossFade::create(0.3f,startScene::createscene()));	//切换到首界面
}

