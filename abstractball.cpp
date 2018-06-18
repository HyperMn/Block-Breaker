#include "abstractball.h"
#include<QTimer>
#include"gift.h"
#include<QDebug>

AbstractBall::AbstractBall(qreal movingSpeed,QGraphicsItem* parent):
  QGraphicsObject(parent),
  collidingState(notCollided),
  timer(new QTimer(this)),
  movingAngle(0,-1),
  movingSpeed(movingSpeed)
{
  timer->setInterval(movingSpeed);
  this->connect(timer,SIGNAL(timeout()),this,SLOT(movingForward()));
  this->connect(this,SIGNAL(collidingWithItem(QList<QGraphicsItem*>,AbstractBall*)),this,SLOT(resetAngel(QList<QGraphicsItem*>)));
  timer->start();
}

AbstractBall::~AbstractBall()
{

}

QPainterPath AbstractBall::shape() const
{
 QPainterPath shape;
 shape.addEllipse(this->boundingRect());
 return shape;
}

void AbstractBall::offsetAngle(const qreal xOff, const qreal yOff)
{
  this->movingAngle+={xOff,yOff};
  movingAngle/=sqrt(movingAngle.x()*movingAngle.x()+movingAngle.y()*movingAngle.y());
  if(movingAngle.y()<0)//使得y轴反向的移动速度最小是0.3个单位/每祯
  {
    movingAngle.ry()=std::min(movingAngle.y(),-0.3);
  }
  else
  {
    movingAngle.ry()=std::max(movingAngle.y(),0.3);
  }
}

void AbstractBall::stopMoving()
{
  if(timer->isActive())
  {
    this->timer->stop();
  }
}

void AbstractBall::startToMove()
{
  if(!timer->isActive())
  {
    this->timer->start();
  }
}

void AbstractBall::resetAngel(QList<QGraphicsItem*> items)
{
  enum
  {
    topLeftFlag=0b1000,
    topRightFlag=0b0100,
    bottomLeftFlag=0b0010,
    bottomRightFlag=0b0001
  };

  auto boundingRect=this->boundingRect();
  auto topLeft=boundingRect.topLeft();
  auto topRight=boundingRect.topRight();
  auto bottomLeft=boundingRect.bottomLeft();
  auto bottomRight=boundingRect.bottomRight();

  int hitState{0b0000};
  for(auto& i:items)
  { 
    if(!(hitState&topLeftFlag)&&i->contains(i->mapFromItem(this,topLeft)))
    {
      hitState|=topLeftFlag;
    }
    if(!(hitState&topRightFlag)&&i->contains(i->mapFromItem(this,topRight)))
    {
      hitState|=topRightFlag;
    }
    if(!(hitState&bottomLeftFlag)&&i->contains(i->mapFromItem(this,bottomLeft)))
    {
      hitState|=bottomLeftFlag;
    }
    if(!(hitState&bottomRightFlag)&&i->contains(i->mapFromItem(this,bottomRight)))
    {
      hitState|=bottomRightFlag;
    }
  }
  switch(hitState)
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

void AbstractBall::movingForward()
{
  this->setPos(this->pos()+movingAngle);
  this->handleCollision();
}

void AbstractBall::handleCollision()
{
  auto collidingItems=this->collidingItems(Qt::IntersectsItemBoundingRect);

  for(auto& i:collidingItems)//球不与球碰撞,不与礼物碰撞
  {
    if(dynamic_cast<AbstractBall*>(i))
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

  if(collidingItems.empty())
  {
    collidingState=notCollided;
    justCollidedItems.clear();
  }
  else
  {
    collidingState=collided;
    justCollidedItems=collidingItems;
    emit collidingWithItem(justCollidedItems,this);
  }
}


