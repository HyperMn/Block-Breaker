#include "abstractball.h"//包含头文件
#include<QTimer>
#include"gift.h"
#include<QDebug>

//Abstract类的构造函数
AbstractBall::AbstractBall(qreal movingSpeed,QGraphicsItem* parent)://冒号初始化
  QGraphicsObject(parent),//QGraphicsObject是一个构造函数
  //利用parent作为参数进行构造
  collidingState(notCollided),//碰撞态这个变量是一个非碰撞态
  timer(new QTimer(this)),//QObject作为参数初始化timer
  movingAngle(0,-1),//初始化角度
  movingSpeed(movingSpeed)//输入的movingSpeed参数
{
  timer->setInterval(movingSpeed);//Interval是一个int类型类成员
  //Interval是一个以毫秒计的时间间隔
  //涉及强制类型转换
  //QObject类里的connect函数，这个函数有多个不同参数的重载版本
  //将sender，signal和method关联起来
  this->connect(timer,SIGNAL(timeout()),this,SLOT(movingForward()));
  //timer是sender，用参数timeout定义一个SIGNAL，方法SLOT
  this->connect(this,SIGNAL(collidingWithItem(QList<QGraphicsItem*>,AbstractBall*)),this,SLOT(resetAngel(QList<QGraphicsItem*>)));
  timer->start();//开始计时
}

//~AbstractBall是一个虚基类
AbstractBall::~AbstractBall(){
	
}

//shape的构造函数
QPainterPath AbstractBall::shape() const
{
 QPainterPath shape;
 shape.addEllipse(this->boundingRect());//boundingRect是一个Qpainterpath的方法
 //Ellipse椭圆，创造一个椭圆
 return shape;
}

//出射角的设置函数，槽函数
void AbstractBall::offsetAngle(const qreal xOff, const qreal yOff){
  this->movingAngle+={xOff,yOff};
  movingAngle/=sqrt(movingAngle.x()*movingAngle.x()+movingAngle.y()*movingAngle.y());
  if(movingAngle.y()<0)//使得y轴反向的移动速度最小是0.3个单位/每祯
  //防止一次消掉过多横向的砖块
  {
    movingAngle.ry()=std::min(movingAngle.y(),-0.3);//重置y方向
  }
  else
  {
    movingAngle.ry()=std::max(movingAngle.y(),0.3);
  }
}

//停止球的运动，槽函数
void AbstractBall::stopMoving()
{
  if(timer->isActive())//返回timer是否在运行
  {
    this->timer->stop();//停止计时
  }
}

//开始球的运动，槽函数
void AbstractBall::startToMove()
{
  if(!timer->isActive())
  {
    this->timer->start();//start the timer
  }
}

//重新设置角度，槽函数
void AbstractBall::resetAngel(QList<QGraphicsItem*> items)
{
  enum//枚举类型
  {
    topLeftFlag=0b1000,//8
    topRightFlag=0b0100,//4
    bottomLeftFlag=0b0010,//2
    bottomRightFlag=0b0001//1
  };
  //boudingRect(ation)函数计算矩形的最小面积
  auto boundingRect=this->boundingRect();//计算this的最小矩形面积
  auto topLeft=boundingRect.topLeft();//左上角
  auto topRight=boundingRect.topRight();//右上角
  auto bottomLeft=boundingRect.bottomLeft();//左下角
  auto bottomRight=boundingRect.bottomRight();//右下角

  //碰撞过程的相关方法
  int hitState{0b0000};//hitState碰撞状态记作0
  for(auto& i:items)//所有items中的元素，QGraphicsItem类指针
  { 
	  //(hitState和topLeftFlag的与计算的非)&&()
    if(!(hitState&topLeftFlag)&&i->contains(i->mapFromItem(this,topLeft)))
    {
      hitState|=topLeftFlag;//将hitState和topLeftFlag求或，状态为8
    }
    if(!(hitState&topRightFlag)&&i->contains(i->mapFromItem(this,topRight)))
    {
      hitState|=topRightFlag;//hit状态为4
    }
    if(!(hitState&bottomLeftFlag)&&i->contains(i->mapFromItem(this,bottomLeft)))
    {
      hitState|=bottomLeftFlag;//hit状态为2
    }
    if(!(hitState&bottomRightFlag)&&i->contains(i->mapFromItem(this,bottomRight)))
    {
      hitState|=bottomRightFlag;//hit状态为1
    }
  }
  switch(hitState)//根据hitState来重置角度，碰撞后的反弹效果
	  //四种碰撞之后的offsetAngle，对出射角进行重新设置
  {
    case topLeftFlag:
    case topLeftFlag|topRightFlag|bottomLeftFlag:
      this->offsetAngle(sqrt(2)*2,sqrt(2)*2);
    break;
    case topRightFlag:
    case topLeftFlag|topRightFlag|bottomRightFlag:
      this->offsetAngle(-sqrt(2)*2,sqrt(2)*2);
    break;
    case bottomLeftFlag:
    case topLeftFlag|bottomLeftFlag|bottomRightFlag:
      this->offsetAngle(sqrt(2)*2,-sqrt(2)*2);
    break;
    case bottomRightFlag:
    case topRightFlag|bottomLeftFlag|bottomRightFlag:
      this->offsetAngle(-sqrt(2)*2,-sqrt(2)*2);
    break;
    case topLeftFlag|topRightFlag:
    case bottomLeftFlag|bottomRightFlag:
      this->offsetAngle(0,-2*movingAngle.y());
    break;
    case topLeftFlag|bottomLeftFlag:
    case topRightFlag|bottomRightFlag:
      this->offsetAngle(-2*movingAngle.x(),0);
    break;
    default:
      static int i=0;
      qDebug()<<"error in matching state"<<i++;
    break;
  }
}

//槽函数
void AbstractBall::movingForward()
{
  this->setPos(this->pos()+movingAngle);//pos是一个const QPointF
  this->handleCollision();//下面定义了handleCollision方法
}

//碰撞的相关控制，槽函数
void AbstractBall::handleCollision()
{
  auto collidingItems=this->collidingItems(Qt::IntersectsItemBoundingRect);
  //collidingItems是this的collidingItems
  for(auto& i:collidingItems)//球不与球碰撞,不与礼物碰撞
  {
    if(dynamic_cast<AbstractBall*>(i))
		//强制类型转换，将collidingItems转换成指向AbstractBall的指针
    {
      collidingItems.removeOne(i);
    }
    else if(dynamic_cast<Gift*>(i))
    {
      collidingItems.removeOne(i);
    }
  }

  if(collidingItems==justCollidedItems)//排除相同元素连续碰撞的情况
  {
    return;
  }

  if(collidingItems.empty())//没有碰撞物体
  {
    collidingState=notCollided;//改变collidingState
    justCollidedItems.clear();//清除掉刚才碰过的物体
  }
  else
  {
    collidingState=collided;//改变碰撞状态
    justCollidedItems=collidingItems;
    emit collidingWithItem(justCollidedItems,this);
  }
}


