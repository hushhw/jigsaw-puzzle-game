#include "loadScene.h"
#include "setting.h"
#include "gamelayer.h"
#include "startScene.h"
#include "SimpleAudioEngine.h"
USING_NS_CC;
using namespace CocosDenshion;

Scene* LoadScene::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = LoadScene::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool LoadScene::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    Size size = Director::getInstance()->getVisibleSize();

	auto spr_bg=Sprite::create("load.jpg");//ÓÎÏ·µÄ±³¾°
	spr_bg->setPosition(Point(size.width/2,size.height/2));
	this->addChild(spr_bg);

// 	auto labelLoading = Label::createWithTTF("Loading...", "fonts/Marker Felt.ttf", 50);
// 	labelLoading->setPosition(Vec2(size.width/2, size.height/2));
// 	this->addChild(labelLoading);

	auto cache = SpriteFrameCache::getInstance();
	cache->addSpriteFramesWithFile("loadsprite.plist","loadsprite.png");
	Vector <SpriteFrame* > spriteFrames;
	char key[25];
	for(int i=1;i<=6;i++)
	{
		sprintf(key,"load1_%d.png",i);
		auto frame = cache->getSpriteFrameByName(key);
		spriteFrames.pushBack(frame);
	}

	auto animation=Animation::createWithSpriteFrames(spriteFrames,0.7f);
	auto animate=Animate::create(animation);
	auto spritedong=Sprite::create();
	spritedong->setPosition(size.width/2, size.height/2);
	auto delay=DelayTime::create(1.0f);
	auto sequence_zu=Sequence::create(delay,animate,NULL);
	spritedong->runAction(sequence_zu);
	this->addChild(spritedong,10);


	auto bg = Sprite::create("loading1.png");
	auto sprite = Sprite::create("loading0.png");

	bg->setPosition(Vec2(size.width/2, size.height*0.4));
	addChild(bg);

	auto progress = ProgressTimer::create(sprite);
	progress->setPosition(Vec2(size.width/2, size.height*0.4));
	addChild(progress);

	progress->setType(ProgressTimer::Type::BAR);
    progress->setBarChangeRate(Vec2(1, 0));
	progress->setMidpoint(Vec2(0, 0));
	progress->setTag(100);

	schedule(schedule_selector(LoadScene::scheduleFunc), 0.1f);

/*
 *	»º´æÒôÀÖ
 */
	SimpleAudioEngine::getInstance()->preloadBackgroundMusic("kaishi.mp3");

	return true;
}

void LoadScene::scheduleFunc(float dt)
{
	auto progress = (ProgressTimer*)getChildByTag(100);
	progress->setPercentage(progress->getPercentage()+2);
	if(progress->getPercentage()>=100)
	{
		unscheduleAllSelectors();
		replacescene();
	}
}

void LoadScene::replacescene()
{
	Director::getInstance()->replaceScene(startScene::createscene());
}

