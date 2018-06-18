#include "normalball.h"
#include<QPainter>
#include<QDebug>
const QImage NormalBall::outlook(":/Ball/image/ball/normalBall.png");

NormalBall::NormalBall(QGraphicsItem* parent):
  AbstractBall(5,parent),
  collidingOutLookActiveTime(0)
{

}

NormalBall::~NormalBall()
{

}

QRectF NormalBall::boundingRect() const
{
  return QRectF(-5,-5,10,10);
}

void NormalBall::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget)
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
