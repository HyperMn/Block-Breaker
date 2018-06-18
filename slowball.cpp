#include "slowball.h"
#include<QPainter>

const QImage SlowBall::outlook(":/Ball/image/ball/slowBall.png");

SlowBall::SlowBall(QGraphicsItem* parent):
  AbstractBall(8,parent),
  collidingOutLookActiveTime(0)
{

}

QRectF SlowBall::boundingRect() const
{
  return QRectF(-8,-8,16,16);
}

void SlowBall::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget)
{
  static QBrush brush(outlook.scaled(this->boundingRect().size().toSize()));
  Q_UNUSED(option)
  Q_UNUSED(widget)
  if(collidingOutLookActiveTime>0)
  {
    painter->setOpacity(0.5);
    collidingOutLookActiveTime--;
  }
  else if(collidingState==collided)
  {
    collidingOutLookActiveTime=20;
  }
  painter->setBrushOrigin(this->boundingRect().topLeft());
  painter->fillRect(this->boundingRect(),brush);
}
