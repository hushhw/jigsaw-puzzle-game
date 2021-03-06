# jigsaw-puzzle-game



## 概述

此项目为『游戏架构与设计』课程实践完成的基于 Cocos2d-x 游戏引擎的游戏作品『植物拼图』，由两人合作完成。

> 游戏名称：植物拼图
>
> 游戏平台：Android/IOS
>
> 游戏画风：卡通
>
> 作者：胡松、张静
>
> Cocos2d-x 引擎版本：3.6
>
> github: https://github.com/hushhw/jigsaw-puzzle-game

![](https://photo.hushhw.cn/images/Snipaste_2019-03-13_08-58-51.png)

![](https://photo.hushhw.cn/images/Snipaste_2019-03-13_09-03-17.png)



​          

## 界面结构

![](https://photo.hushhw.cn/images/game.png)

​          

## 说明

* 使用 progressTimer 实现一个进度条功能，使用计时器来调用函数让进度条加载，加载完毕后即停止计时器，切换场景。

![](https://photo.hushhw.cn/images/game1.png)

![](https://photo.hushhw.cn/images/game2.png)



* ChooseScene 场景中，对切换场景按钮的优化。由原先的按钮改成触摸监听触摸监听分发器绑定到两个 label 上，对其位置进行判断并执行响应。



* CuttingPhotos 实体类的实现：

  用二维vector存储方块切割的每一个小方块精灵，通过 createWithTexture 对图片进行切割随机打乱方块。



* 游戏胜利的判断逻辑：

  先用 vector< int > 存储一遍初始化的时候每个方块的位置的序号，再随机打乱方块时，再新建一个 vector< int > 来存储每一个位置的编号，最后对其进行比较，每个位置上两个容器是否相等。

  其中在随机的时候实现的逻辑是新建一个 vector< sprite > 来读出之前所有的精灵，随机一个 vector 内的数字来随机取精灵，并存入之前的 vector 中，把当前精灵从新建的 vector< sprite > 中 eraseobject 掉，让容器 size 变小，但是这里出现的问题是 vector< int > 容器中删除对象用到 erase() ，用到迭代器来实现，但在迭代器中执行 erase() 来删除最后实现的效果是最后无论如何都剩下 4 个，最后采用了不删除任何数据，通过控制随机数来实现。

![](https://photo.hushhw.cn/images/game3.png)

 

​	胜利判断逻辑采用的是计时器时刻检测是否胜利，如果胜利的话，执行一段动画且切换场景

![](https://photo.hushhw.cn/images/game4.png)

 

* 方块的触摸监听部分：

  原先要实现的是点击和滑动都可以实现移动，但是因为无法对两者进行区分判断，导致点击方块和移动方块同步进行，所以去掉了点击的方法。

 

* Gamescene 场景中层的响应吞并 setSwallowTouches

![](https://photo.hushhw.cn/images/game5.png)

 

* 颜色混合合成图片

![](https://photo.hushhw.cn/images/game6.png)

 

* 背景音乐及开关

![](https://photo.hushhw.cn/images/game7.png)

 

