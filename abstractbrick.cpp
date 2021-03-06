#include "abstractbrick.h"
#include<QPainter>

AbstractBrick::AbstractBrick(int totalHittingTime,QColor outlook, QGraphicsItem* parent):
  QGraphicsObject(parent),
  hittingTimeLeft(totalHittingTime),
  outlook(outlook)
{

}

AbstractBrick::~AbstractBrick()
{

}

QRectF AbstractBrick::boundingRect() const
{
  return QRectF(-20,-15,40,30);
}

QPainterPath AbstractBrick::shape() const
{
  QPainterPath path;
  path.addRect(this->boundingRect());
  return path;
}

void AbstractBrick::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget)
{
  Q_UNUSED(option)
  Q_UNUSED(widget)
  painter->setBrushOrigin(this->boundingRect().topLeft());
  painter->fillPath(this->shape(),this->outlook);
}

void AbstractBrick::collidingWithBall()
{
  hittingTimeLeft--;
  if(hittingTimeLeft==0)
  {
    this->deleteLater();
  }
}
