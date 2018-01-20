#ifndef _CUTTING_PHOTOS__
#define _CUTTING_PHOTOS__

#include "cocos2d.h"
#include <vector>
#include <map>
using namespace std;
USING_NS_CC;

class CuttingPhotos : public Layer
{
public:
	static CuttingPhotos* create(const char* photo, unsigned int rows=3, unsigned int columns=3);

	virtual bool initWithPhoto(const char* photo,unsigned int rows,unsigned int columns);

	bool initSlice(const char* photo);//初始化切片数组

	void initTouchEventlistener();//初始化触摸事件

	void move(int x,int y);//移动指定位置的卡片
	void movewithdir(char dir);
	void restart();//随机布置卡片
	bool judge(int num);
	bool isWin();
	void setWin();
	void nextScene();

	bool iswin;
	int _rows; //行数
	int _columns; //列数
	int _sliceWidth; //格子宽度
	int _sliceHeight; //格子高度
	//int _blocknumber; //方块数字
	Vec2 start;
	Vec2 end;
	bool beginismove;
	std::vector<std::vector<Sprite*>> _slices;
	std::vector<int> blocknum;
	std::vector<int> placenum;
	int randnum[101];
	
};

#endif