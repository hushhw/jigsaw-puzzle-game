#include "chooseScene.h"//自身的头文件
#include "startScene.h"
#include "gamelayer.h"
USING_NS_CC;


cocos2d::Scene*chooseScene::createscene()
{
	auto scene=Scene::create();
	auto layer=chooseScene::create();
	scene->addChild(layer);
	return scene;
}

bool chooseScene::init()
{
    if (!Layer::init())
	{
		return false;
	}
    
	
	//添加可滑动界面

	page_node_ = 0;
	cur_page_node_ = 0;

	for(int page=1; page<=6; page++)
	{
		layer = Layer::create();
		
		//背景
		auto sprite =Sprite::create("choose.jpg");
		sprite->setPosition(Point(size().width / 2, size().height / 2 ));
		layer->addChild(sprite);


		auto animation = Animation::create();
		for (int i = 1; i <= 2; ++i)
		{
			auto spr_name = String::createWithFormat("Card%d_%d.png", page,i);
			animation->addSpriteFrameWithFile(spr_name->getCString());
		}

		animation->setDelayPerUnit(0.2f);
		animation->setLoops(-1);

		auto spr_name = String::createWithFormat("Card%d_%d.png", page, 1);
		auto card_sprite = Sprite::create(spr_name->getCString());
		card_sprite->setPosition(size().width / 2, 2*size().height / 3);
		card_sprite->setScale(2);
		layer->addChild(card_sprite);
		//动作
		auto animate = Animate::create(animation);
		card_sprite->runAction(animate);

/*
 *	设置每一个Layer上的两个假按钮及响应的动画
 */
		auto dictionary = Dictionary::createWithContentsOfFile("fonts/text.xml");
		auto lab=(String*)(dictionary->objectForKey("choose"));
		btn_label = Label::createWithTTF(lab->getCString(),"fonts/fenshu.ttf",45);
		btn_label->setColor(Color3B(196,171,188));
		btn_label->setPosition(Point(size().width/2,size().height/3)); 
		layer->addChild(btn_label);

		auto ba=(String*)(dictionary->objectForKey("back"));//添加选择关卡按钮
		bac=Label::createWithTTF(ba->getCString(),"fonts/fenshu.ttf",45);
		bac->setColor(Color3B(196,171,188));  
		bac->setPosition(Point(size().width/2,size().height/5));
		layer->addChild(bac,2);

/*
 *	设置layer属性
 */
		layer->setContentSize(Size(size().width, size().width));
		layer->setPosition(Point(size().width * page_node_, 0));
		this->addChild(layer);

		page_node_++;
	}
	   

	

	auto touchListener = EventListenerTouchOneByOne::create();//创建一个单点触摸监听
	touchListener->setSwallowTouches(true);//吞噬为true，不让触摸往下传递
	//与回调函数绑定
	touchListener->onTouchBegan = CC_CALLBACK_2(chooseScene::onTouchBegan, this);
	touchListener->onTouchMoved = CC_CALLBACK_2(chooseScene::onTouchMoved, this);
	touchListener->onTouchEnded = CC_CALLBACK_2(chooseScene::onTouchEnded, this);
	//添加监听器到事件分发器中
	_eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener->clone(), btn_label);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener->clone(), bac);

    return true;
}  
  
bool chooseScene::onTouchBegan(Touch *touch, Event  *event)
{
	
	ismenu = false;
	isendmenuwithend = false;
	start = touch->getLocation();//按下去的那个点；
 	menusize = btn_label->getContentSize();
 	rect = Rect(size().width/2 - menusize.width/2, size().height/3 - menusize.height/2, menusize.width, menusize.height);
 	if(rect.containsPoint(start))
 	{
 		log("start");
 		ismenu = true;
 	}

	menuend = bac->getContentSize();
	endrect = Rect(size().width/2 - menuend.width/2, size().height/5 - menuend.height/2, menuend.width, menuend.height);
	if(endrect.containsPoint(start))
	{
		log("exitstart");
		ismenuwithend = true;
	}
	return true;
}


void chooseScene::onTouchEnded(Touch *touch, Event  *event)
{
	isendmenu = false;
	isendmenuwithend = false;
	end = touch->getLocation();//鼠标弹起时的位置

	//dis表示鼠标从按下去到弹起来拖过的距离
	auto dis = end.getDistance(start);

	if (dis >= 20 )//如果距离大于或等于最小滑动距离，表示滑动有效
	{
		ismenu = false;
		isendmenu = false;
		if (start.x > end.x) {//按下去的点的x轴大于起来的点的x轴
			//记录当前页
			++cur_page_node_;//表示在往左滑，所以cur_page_node_加1；
			if (page_node_ - 1 < cur_page_node_)
				cur_page_node_ = page_node_ - 1;//翻到头了就不翻了，cur_page_node_设置为最后一页
		}
		else if (start.x < end.x) {
			//记录当前页	
			--cur_page_node_;//反之减一
			if (cur_page_node_ < 0)
				cur_page_node_ = 0;//翻到头了就不翻了，cur_page_node_设置为第一页。
		}
		//播放滚动界面
		goToCurrNode();//执行滑动函数
	}

 	if(rect.containsPoint(end))
 	{
 		log("end");
 		isendmenu = true;
 	}
 	if(dis<=20 && ismenu && isendmenu)
 	{
		log("cur_page_node_:%d",cur_page_node_);
  		GameScene::setLevel(cur_page_node_+1);
		//donghua();
		Director::getInstance()->replaceScene(TransitionCrossFade::create(0.3,GameScene::createScene()));
	}

	if(endrect.containsPoint(start))
	{
		log("exitend");
		isendmenuwithend = true;
	}
	if(dis<=20 && ismenuwithend && isendmenuwithend)
	{
		//donghua();
		Director::getInstance()->replaceScene(TransitionCrossFade::create(0.3,startScene::createscene()));
	}
}

void chooseScene::donghua()
{
// 	log("donghua");
// 	auto blink=Blink::create(3.0f,5);  
// 	auto scaleto = ScaleTo::create(0.2f,1.5f);
// 	auto scalere = ScaleTo::create(0.5f,0.5f);
// 	auto delay = DelayTime::create(1.0f);
// 	auto sequence = Sequence::create(blink, scaleto, scalere, delay, NULL);
// 	btn_label->runAction(sequence);
}


void chooseScene::goToCurrNode()
{
	//滑动效果
	this->runAction(MoveTo::create(0.4f, Point(-cur_page_node_ * Director::getInstance()->getWinSize().width, 0)));
}


Size chooseScene::size()
{
	return Director::getInstance()->getWinSize();
}