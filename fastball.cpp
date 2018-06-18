#include "fastball.h"
#include<QPainter>

const QImage FastBall::outlook(":/Ball/image/ball/fastBall.png");

FastBall::FastBall(QGraphicsItem* parent):
  AbstractBall(3,parent),
  collidingOutLookActiveTime(0)
{

}

QRectF FastBall::boundingRect() const
{
  return QRectF(-8,-8,16,16);
}

void FastBall::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget)
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
    collidingOutLookActiveTime=10;
  }
  painter->setBrushOrigin(this->boundingRect().topLeft());
  painter->fillRect(this->boundingRect(),brush);
}
