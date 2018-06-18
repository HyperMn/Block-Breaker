#include "bordersquare.h"
#include<QPainter>
#include<QDebug>

BorderSquare::BorderSquare(QGraphicsItem* parent):
  QGraphicsObject(parent)
{

}

QRectF BorderSquare::boundingRect() const
{
  return QRectF(-25,-25,50,50);
}

QPainterPath BorderSquare::shape() const
{
  QPainterPath path;
  path.addRect(this->boundingRect());
  return path;
}

void BorderSquare::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget)
{
  Q_UNUSED(option)
  Q_UNUSED(widget)
  painter->setPen(Qt::NoPen);
  painter->drawRect(this->boundingRect());
}
