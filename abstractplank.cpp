#include "abstractplank.h"
#include"bordersquare.h"
#include<QGraphicsScene>
#include<QTimer>

AbstractPlank::AbstractPlank(QGraphicsItem* parent,qreal movingSpeed):
  QGraphicsObject(parent),
  timer(new QTimer(this)),
  movingState(notMove),
  collidingEffect{0.0,0.0}
{
  timer->setInterval(movingSpeed);
  this->connect(timer,SIGNAL(timeout()),this,SLOT(movingForward()));
  timer->start();
}

AbstractPlank::~AbstractPlank()
{

}

QPainterPath AbstractPlank::shape() const
{
  QPainterPath path;
  path.addRect(this->boundingRect());
  return path;
}

bool AbstractPlank::isMovingState(AbstractPlank::MovingState state)
{
  return state==this->movingState;
}

void AbstractPlank::setMovingState(AbstractPlank::MovingState state)
{
  this->movingState=state;
}

void AbstractPlank::collidingWithBall(QGraphicsItem* sender)
{
  emit setOffset(this->collidingEffect.x(),this->collidingEffect.y(),sender);
}

void AbstractPlank::startToMove()
{
  if(!this->timer->isActive())
  {
    this->timer->start();
  }
}

void AbstractPlank::stopMoving()
{
  if(this->timer->isActive())
  {
    this->timer->stop();
  }
}

void AbstractPlank::movingForward()
{
  static const qreal movingOffset=2.0;
  static const qreal effect=1.0;

  if(this->movingState==notMove)
  {
    this->collidingEffect/=2;
    if(collidingEffect.x()<0.3)
    {
      collidingEffect.rx()=0;
    }
    return;
  }

  const qreal xOff=this->boundingRect().width()/2;
  auto oldPos=this->pos();
  switch (movingState) {
    case moveToLeft:
      if(!dynamic_cast<BorderSquare*>(this->scene()->itemAt(oldPos+QPointF{-xOff-movingOffset,0},this->transform())))
      {
        this->collidingEffect={-effect,0};
        this->setPos(oldPos+QPointF(-movingOffset,0));
      }
    break;
    case moveToRight:
      if(!dynamic_cast<BorderSquare*>(this->scene()->itemAt(oldPos+QPointF{xOff+movingOffset,0},this->transform())))
      {
        this->collidingEffect={effect,0};
        this->setPos(oldPos+QPointF(movingOffset,0));
      }
    break;
    default:
    break;
  }
}
