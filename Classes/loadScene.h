#ifndef __LOAD_SCENE_H__
#define __LOAD_SCENE_H__

#include "cocos2d.h"
USING_NS_CC;
using namespace std;

class LoadScene : public cocos2d::Layer
{
public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();

    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();

	void scheduleFunc(float dt);

	void replacescene();
    
    // implement the "static create()" method manually
    CREATE_FUNC(LoadScene);

};

#endif 
