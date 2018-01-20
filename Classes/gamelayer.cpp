#include "gamelayer.h"
#include "cuttingphotos.h"
#include "startScene.h"
#include "about.h"
#include "SimpleAudioEngine.h"
USING_NS_CC;
using namespace CocosDenshion;

void GameScene::setLevel(int value)
{
	level = value;
}

Scene* GameScene::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = GameScene::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool GameScene::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
	Size visibleSize = Director::getInstance()->getWinSize();

	

/*
 * 设置背景layer的颜色
 */
	auto bglayer = LayerColor::create
		(Color4B(140,162,175,255),
		visibleSize.width,visibleSize.height
		);
	bglayer->ignoreAnchorPointForPosition(false);  
	bglayer->setAnchorPoint(Point(0.5,0.5));  

	bglayer->setPosition(Point(visibleSize.width/2, visibleSize.height/2));  
	this->addChild(bglayer);


	auto spr_bg=Sprite::create("main.jpg");//游戏的背景
	spr_bg->setPosition(Point(visibleSize.width/2,visibleSize.height/2));
	bglayer->addChild(spr_bg);

// 	label = Label::createWithTTF("1-1", "fonts/Marker Felt.ttf", 1);
// 	label->setColor(Color3B::WHITE);
// 	label->setPosition(Point(visibleSize.width/2,visibleSize.height - 50));
// 	label->setHorizontalAlignment(TextHAlignment::CENTER);
// 	spr_bg->addChild(label);

/*
 *	菜单按钮
 */
	_plusItem = MenuItemImage::create("ButtonStar.png","",CC_CALLBACK_1(GameScene::plusMinusButtonCallback, this));
	_plusItem->setPosition(visibleSize.width/2,visibleSize.height/18);

	

/*
 *	设置boxlayer
 */
	boxlayer = LayerColor::create
		(Color4B(229,229,229,0),
		visibleSize.width-50,visibleSize.height/2
		);
	boxlayer->ignoreAnchorPointForPosition(false);  
	boxlayer->setAnchorPoint(Point(0.5,0.5));  

	boxlayer->setPosition(Point(visibleSize.width/2, 3*visibleSize.height/5)); 
	bglayer->addChild(boxlayer);

/*
 *	左右滑动切换level
 */

	left1 = Sprite::create("left.png");
	right1 = Sprite::create("right.png");
	leftmenu = MenuItemSprite::create(left1, NULL, CC_CALLBACK_0(GameScene::priviouslevel, this));
	rightmenu = MenuItemSprite::create(right1, NULL, CC_CALLBACK_0(GameScene::nextlevel, this));
	leftmenu->setPosition(left1->getContentSize().width/2 + 50, visibleSize.height/18);
	rightmenu->setPosition(visibleSize.width - right1->getContentSize().width/2 - 50, visibleSize.height/18);
	

	auto toggleMenu = Menu::create(_plusItem, leftmenu, rightmenu, NULL);
	toggleMenu->setPosition(Vec2::ZERO);
	bglayer->addChild(toggleMenu);

/*
 * 调用cuttingPhotos实体类生成切割图片
 */
	img = String::createWithFormat("level_%d.png",level)->_string;
	int a;
	if(level<=2)
		a = 3;
	else
		a = 4;
    photo = CuttingPhotos::create(img.c_str(),a,a);
	photo->setAnchorPoint(Vec2(0,0));
	auto size = photo->getContentSize();
	photo->setScaleX((visibleSize.width-50)/size.width);
	photo->setScaleX((visibleSize.height/2)/size.height);
	photo->setPosition(0,0);
	boxlayer->addChild(photo);

	scheduleUpdate();

	if(!SimpleAudioEngine::getInstance()->isBackgroundMusicPlaying())
	{
		SimpleAudioEngine::getInstance()->playBackgroundMusic("kaishi.mp3",true);
	}
	

	auto listener1 = EventListenerKeyboard::create();
	listener1->onKeyReleased = CC_CALLBACK_2(GameScene::onKeyReleased, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener1, this);

    return true;
}

void GameScene::onKeyReleased(EventKeyboard::KeyCode keyCode, Event* event)
{
	switch(keyCode)     
	{         //监听返回键        
	case EventKeyboard::KeyCode::KEY_ESCAPE:              
		Director::getInstance()->end();             
		break;         
		//监听menu键        
	case EventKeyboard::KeyCode::KEY_MENU:             
		break;     
	} 
}

void GameScene::update(float delta)
{
	if(photo->isWin())
	{
		log("win??");
		this->unscheduleUpdate();
		auto fadein = FadeIn::create(2.0f);
		//auto bink = Blink::create(0.3f,2);
		auto fadeout = FadeOut::create(2.0f);
		auto callfunc = CallFunc::create(CC_CALLBACK_0(GameScene::nextlevel, this));
		auto action = Sequence::create(fadein, fadeout, callfunc, NULL);

		auto sprite = Sprite::create(img);
		sprite->setAnchorPoint(Vec2(0.5,0.5));
		sprite->setPosition(Vec2(sprite->getContentSize().width/2, sprite->getContentSize().height/2));
		boxlayer->addChild(sprite);
		sprite->runAction(action);
		
	}
}

void GameScene::plusMinusButtonCallback(Ref*ref)
{
	Size visibleSize=Director::getInstance()->getVisibleSize();
		//添加层
		aboutlayer = LayerColor::create( Color4B(189,185,183,200),visibleSize.width, visibleSize.height);
		aboutlayer->ignoreAnchorPointForPosition(false);
		aboutlayer->setAnchorPoint(Point(0.5,0.5));
		aboutlayer->setPosition(Point(Director::getInstance()->getWinSize().width/2 , Director::getInstance()->getWinSize().height/2));
		this->addChild(aboutlayer);

		auto smenu = Sprite::create("ButtonStarSel.png");
		smenu->setPosition(visibleSize.width/2,visibleSize.height/18);
		aboutlayer->addChild(smenu);

		auto listener = EventListenerTouchOneByOne::create();
		listener->setSwallowTouches(true);
		listener->onTouchBegan=[&](Touch *touch,Event *event){
			ismenu =false;
			auto start = touch->getLocation();
			plusitem = _plusItem->getContentSize();
			rect = Rect(Director::getInstance()->getWinSize().width/2 - plusitem.width/2, Director::getInstance()->getWinSize().height/18 - plusitem.height/2, plusitem.width, plusitem.height);
			if(rect.containsPoint(start))
			{
				ismenu = true;
			}
			return true;
		};
		listener->onTouchEnded=[&](Touch *touch,Event *event){
			if(rect.containsPoint(touch->getLocation()) && ismenu)
			{
				aboutlayer->removeFromParent();
			}
		};
		_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, aboutlayer);

		//返回按钮
		auto backmenu = MenuItemImage::create("back.png","", CC_CALLBACK_1(GameScene::backbtn, this));
		backmenu->setPosition(Point(aboutlayer->getContentSize().width/5, aboutlayer->getContentSize().height/10+10));
		//音量切换按钮
		sound_on = MenuItemImage::create("sound-on.png","");
		sound_off = MenuItemImage::create("sound-off.png","");
		auto soundItem = MenuItemToggle::createWithCallback(CC_CALLBACK_1(GameScene::setsound, this),sound_on,sound_off,NULL);
		soundItem->setPosition(Point(aboutlayer->getContentSize().width*2/5, aboutlayer->getContentSize().height/10+40));
		//关于按钮
		back1 = MenuItemImage::create("about.png","");
		back2 = MenuItemImage::create("about5.png","");
		auto aboutmenu = MenuItemToggle::createWithCallback(CC_CALLBACK_1(GameScene::about, this), back1, back2, NULL);
		aboutmenu->setPosition(Point(aboutlayer->getContentSize().width*3/5, aboutlayer->getContentSize().height/10+40));
		//重新开始按钮
		auto restarttmenu = MenuItemImage::create("restart.png","", CC_CALLBACK_0(GameScene::restart,this));
		restarttmenu->setPosition(Point(aboutlayer->getContentSize().width*4/5, aboutlayer->getContentSize().height/10+10));
		
		auto menu = Menu::create(backmenu, soundItem, aboutmenu, restarttmenu, NULL);
		menu->setPosition(Point::ZERO);
		aboutlayer->addChild(menu);
}

void GameScene::backbtn(Ref*ref)
{
	Director::getInstance()->replaceScene(TransitionCrossFade::create(0.3f,startScene::createscene()));	//切换到选择关卡场景
}

void GameScene::setsound(Ref*ref)
{
	MenuItemToggle *soundItem = (MenuItemToggle *)ref;
	if (soundItem->getSelectedItem() ==sound_on){
		SimpleAudioEngine::getInstance()->resumeBackgroundMusic();
	}

	else if (soundItem->getSelectedItem() ==sound_off){

		SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
	}
}

void GameScene::about(Ref*ref)
{
	MenuItemToggle *aboutmenu = (MenuItemToggle *)ref;
	if (aboutmenu->getSelectedItem() == back1){
		backlayer->removeFromParent();
	}

	else if (aboutmenu->getSelectedItem() == back2){
		
		backlayer = LayerColor::create( Color4B(0,255,255,0),540, 540);
		backlayer->ignoreAnchorPointForPosition(false);
		backlayer->setAnchorPoint(Point(0.5,0.5));
		backlayer->setPosition(Point(Director::getInstance()->getWinSize().width/2 , Director::getInstance()->getWinSize().height/2));
		aboutlayer->addChild(backlayer);

		backsprite = Sprite::create("about4.png");
		backsprite->setPosition(Point(backlayer->getContentSize().width / 2, backlayer->getContentSize().height/2));
		backlayer->addChild(backsprite , 2);

		auto maskSprite = Sprite::create("circle_mask.png");
		maskSprite->setPosition(Vec2(maskSprite->getContentSize().width/2 , maskSprite->getContentSize().height/2));
		auto sprite = Sprite::create(img);
		sprite->setScale(0.8f);
		sprite->setPosition(Vec2(sprite->getContentSize().width/2 , sprite->getContentSize().height/2));
		auto renderTexture = RenderTexture::create(maskSprite->getContentSize().width, maskSprite->getContentSize().height);
		
		BlendFunc tmpmask = {GL_ONE, GL_ZERO};
		BlendFunc tmpsprite = {GL_DST_ALPHA, GL_ZERO};
		maskSprite->setBlendFunc(tmpmask);
		sprite->setBlendFunc(tmpsprite);

		renderTexture->begin();  
		maskSprite->visit();  
		sprite->visit();  
		renderTexture->end();

		auto retval = Sprite::createWithTexture(renderTexture->getSprite()->getTexture());
		retval->setFlipY(true);
		retval->setAnchorPoint(Vec2(0.5,0.5));
		retval->setPosition(Vec2(backlayer->getContentSize().width/2, backlayer->getContentSize().height/2));
		backlayer->addChild(retval);
		
	}
	
}

void GameScene::restart()
{
	Director::getInstance()->replaceScene(TransitionCrossFade::create(0.3f,GameScene::createScene()));	//切换到当前场景
}

void GameScene::nextlevel()
{
	level++;
	if(level==7)
		level = 1;
	Director::getInstance()->replaceScene(TransitionCrossFade::create(0.3f,GameScene::createScene()));
}

void GameScene::priviouslevel()
{
	level--;
	if(level==0)
		level = 6;
	Director::getInstance()->replaceScene(TransitionCrossFade::create(0.3f,GameScene::createScene()));
}