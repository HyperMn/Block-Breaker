#include "bigball.h"
#include<QPainter>

const QImage BigBall::outlook(":/Ball/image/ball/bigBall.png");

BigBall::BigBall(QGraphicsItem* parent):
  AbstractBall(5,parent),
  collidingOutLookActiveTime(0)
{

}

QRectF BigBall::boundingRect() const
{
  return QRectF(-14,-14,28,28);
}

void BigBall::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget)
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
