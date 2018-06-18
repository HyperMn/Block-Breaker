#include "smallball.h"
#include<QPainter>

const QImage SmallBall::outlook(":/Ball/image/ball/smallBall.png");

SmallBall::SmallBall(QGraphicsItem* parent):
  AbstractBall(5,parent),
  collidingOutLookActiveTime(0)
{

}

QRectF SmallBall::boundingRect() const
{
  return QRectF(-3,-3,6,6);
}

void SmallBall::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget)
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
