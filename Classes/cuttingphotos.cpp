#include "cuttingphotos.h"
#include "gamelayer.h"

CuttingPhotos* CuttingPhotos::create(const char* photo, unsigned int rows/* =3 */, unsigned int columns/* =3 */)
{
	CuttingPhotos *cp = new CuttingPhotos();

	if(cp && cp->initWithPhoto(photo,rows,columns)){
		cp->autorelease();
		return cp;
	}
	CC_SAFE_DELETE(cp);

	return nullptr;
}

bool CuttingPhotos::initWithPhoto(const char* photo,unsigned int rows,unsigned int columns)
{
	bool result = false;//初始化是否成功

	if(Layer::init())
	{
		_rows = rows;
		_columns = columns;

		if(initSlice(photo))
		{
			initTouchEventlistener();
			restart();
			result = true;
		}
		else
			return false;
	}
	return result;
}

bool CuttingPhotos::initSlice(const char* photo)
{
	Texture2D *texture = Director::getInstance()->getTextureCache()->addImage(photo);
	if(texture==nullptr)
		return false;

	//初始化存储行列的列表
	for(int w=0; w<_rows; ++w)
	{
		std::vector<Sprite*> row;
		for(int h=0; h<_columns; ++h)
		{
			row.push_back(nullptr);
		}
		_slices.push_back(row);
	}

	//计算图片每列的宽度
	auto size = texture->getContentSize();
	_sliceWidth = size.width/_rows;
	_sliceHeight = size.height/_columns;

	this->setContentSize(size);//设置Layer大小

	//最后一块
	auto endSlice = Sprite::createWithTexture(texture,Rect(_sliceWidth*(_rows-1),_sliceHeight*(_columns-1),_sliceWidth,_sliceHeight));
	endSlice->setAnchorPoint(Vec2(0,0));
	endSlice->setPosition((_rows-1)*_sliceWidth,0);
	endSlice->setOpacity(100);
	this->addChild(endSlice);

	_slices[_rows-1][_columns-1]=nullptr;//设为空，表示这个格子可以移入

	//创建切片
	for(int w=0; w<_rows; ++w)
		for(int h=0; h<_columns; ++h)
		{
			if(w==_rows-1 && h==_columns-1)
				break;

			auto slice = Sprite::createWithTexture(texture,Rect(_sliceWidth*w,_sliceHeight*h,_sliceWidth,_sliceHeight));
			slice->setAnchorPoint(Vec2(0,0));
			slice->setPosition(w*_sliceWidth,size.height-(h+1)*_sliceHeight);
			this->addChild(slice);

			_slices[w][h] = slice;
		}
	return true;
}

void CuttingPhotos::initTouchEventlistener()
{
	
	auto listener = EventListenerTouchOneByOne::create();
		
	listener->onTouchBegan = [&](Touch *touch,Event *event){
		beginismove = false;
		start = touch->getLocation();
		Point locationInNode = this->convertToNodeSpace(start);
		Size s = this->getContentSize();
		Rect rect = Rect(0, 0, s.width, s.height);
		int x=static_cast<int>(floor(locationInNode.x/this->_sliceWidth));
		int y=static_cast<int>(floor(locationInNode.y/this->_sliceHeight));
		log("bx:%d, by:%d",x,y);

		//Point targetblock = _slices[x][_columns-y-1]->getContentSize();

		if (rect.containsPoint(locationInNode) )
		{
			//if(rect.containsPoint(targetblock))
			//{
			//	this->move(x, y);
			//	beginismove = true;
			//	log("touchpoint in x,y");
			//}
				return true;
		}else{
			return false;
		}
	};

	listener->onTouchEnded=[&](Touch *touch,Event *event){
		Point locationInNode = this->convertToNodeSpace(touch->getLocation());

		end = touch->getLocation();
		float deltaX = start.x - end.x;
		float deltaY = start.y - end.y;
		float value = deltaY / deltaX;
		float slope = value > 0 ? value : -value;

		if(slope > 1 && !beginismove)
		{
			if(deltaY>0)
			{
				if(deltaY < 10) return;
				movewithdir('D');
	
			}else{
				if(deltaY > -10) return;
				movewithdir('U');

			}
		} else if(slope<1 && !beginismove){
			if(deltaX > 0)
			{
				if(deltaX < 10) return;
				movewithdir('L');

			} else {
				if(deltaX > -10) return;
				movewithdir('R');

			}
		}
	};

	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

}

void CuttingPhotos::setWin()
{
	iswin = false;
}

bool CuttingPhotos::isWin(){
	for(int w=0; w<_rows; ++w){
		for(int h=0; h<_columns; ++h)
		{
			if((w*_rows+h)<_rows*_columns-1 && (placenum.at(w*_rows+h) != w*_rows+h+1))
				return false;
		}
	}
		return true;
}

void CuttingPhotos::movewithdir(char dir)
{
	int x,y;
	for(int w=0; w<_rows; ++w){
		for(int h=0; h<_columns; ++h)
		{
			if(_slices[w][h]==nullptr)
			{
				x=w;
				y=h;
				log("x:%d y:%d",x,y);
			}
		}
	}

	bool isFind=false;
	Point targetPos;
	int targetnum;
	if(dir=='U' && y< _columns-1)
	{
		targetPos.x=x;
		targetPos.y=y+1;
		targetnum = targetPos.x*_rows + targetPos.y;
		isFind=true;
	}else if (dir=='D' && y > 0) {//d
		targetPos.x=x;
		targetPos.y=y-1;
		targetnum = targetPos.x*_rows + targetPos.y;
		isFind=true;
	}else if (dir=='L' && x < _rows-1) {//r
		targetPos.x=x+1;
		targetPos.y=y;
		targetnum = targetPos.x*_rows + targetPos.y;
		isFind=true;
	}else if (dir=='R' && x > 0) {//l
		targetPos.x=x-1;
		targetPos.y=y;
		targetnum = targetPos.x*_rows + targetPos.y;
		isFind=true;
	}

	if (isFind==false) {
		return;
	}

	_slices[targetPos.x][targetPos.y]->runAction(MoveTo::create(0.25, Vec2(x*_sliceWidth,_sliceHeight*_columns-(y+1)*_sliceHeight)));
	_slices[x][y]=_slices[targetPos.x][targetPos.y];
	_slices[targetPos.x][targetPos.y]=nullptr;

	int index = placenum.at(targetnum);
	placenum.at(x*_rows+y) = index;
	placenum.at(targetnum) = 0;
	
}

void CuttingPhotos::move(int x,int y)
{

	y=_columns-y-1;
	auto slice=_slices[x][y];

	if (slice==nullptr) {
		return;
	}

	//查找周围是否有空白的区域
	bool isFind=false;
	Point targetPos;
	if (y<_columns-1 && _slices[x][y+1]==nullptr) {//u
		targetPos.x=x;
		targetPos.y=y+1;
		isFind=true;
	}else if (y>0 && _slices[x][y-1]==nullptr) {//d
		targetPos.x=x;
		targetPos.y=y-1;
		isFind=true;
	}else if (x<_rows-1 && _slices[x+1][y]==nullptr) {//r
		targetPos.x=x+1;
		targetPos.y=y;
		isFind=true;
	}else if (x>0 && _slices[x-1][y]==nullptr) {//l
		targetPos.x=x-1;
		targetPos.y=y;
		isFind=true;
	}

	if (isFind==false) {
		return;
	}

	slice->runAction(MoveTo::create(0.25, Vec2(targetPos.x*_sliceWidth,_sliceHeight*_columns-(targetPos.y+1)*_sliceHeight)));
	_slices[targetPos.x][targetPos.y]=slice;
	_slices[x][y]=nullptr;

}

void CuttingPhotos::restart()
{
	iswin = true;
	//取出所有切片
	cocos2d::Vector<Sprite*> list;

	for (int w=0; w<_rows; ++w) {
		for (int h=0; h<_columns; ++h) {
			auto slice= _slices[w][h];
			if (slice!=nullptr) {
				int value = _rows*w + h +1;
				blocknum.push_back(value);
				list.pushBack(slice);
				//log("value:%d",value);
			}
		}
	}
	blocknum.push_back(0);

	//随机布置到每一个位置
	for (int w=0; w<_rows; ++w) {
		for (int h=0; h<_columns; ++h) {

			if (w==_rows-1 && h==_columns-1) {
				//最后一块不需要
				_slices[w][h]=nullptr;
				break;
			}

			auto length= list.size(); //vector总大小
			int randnumber;
			do{
				randnumber= static_cast<int>(CCRANDOM_0_1()*length); //从length中随机一个数字
			//log("b randnumber:%d",randnumber);
			}while(judge(randnumber));
			log("a randnumber:%d",randnumber);

			randnum[w*_rows+h]=randnumber;

			auto num =blocknum.at(randnumber);
			log("num:%d",num);
			placenum.push_back(num);

			

			auto slice=list.at(randnumber); // 找到list中在value的方块，并存在slice中
			//list.eraseObject(slice);   //从List中删除该方块
			//list.insert(randnumber,nullptr);
			_slices[w][h]=slice;      //将其替换放入vector中

			slice->setPosition(w*_sliceWidth,_sliceHeight*_columns-(h+1)*_sliceHeight);
		}
	}
	placenum.push_back(0);
}

bool CuttingPhotos::judge(int num)
{
	int i=-1;
	while(i<_columns*_rows)
	{
		i++;
		//log("i:%d randnum[i]:%d",i,randnum[i]);
		if(randnum[i]==num)
			return true;
	}
	return false;
}
