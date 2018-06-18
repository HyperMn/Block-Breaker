#include "forbiddensquare.h"
#include<Qtimer>
#include<QPainter>

ForbiddenSquare::ForbiddenSquare(QGraphicsItem* parent):
  QGraphicsObject(parent)
{
}

QRectF ForbiddenSquare::boundingRect() const
{
  return QRectF(-25,-25,50,50);
}

QPainterPath ForbiddenSquare::shape() const
{
  QPainterPath path;
  path.addRect(this->boundingRect());
  return path;
}

void ForbiddenSquare::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget)
{
  Q_UNUSED(option)
  Q_UNUSED(widget)
  painter->setPen(Qt::NoPen);
  painter->drawRect(this->boundingRect());
}

void ForbiddenSquare::handleColliding(QObject* object)
{
  object->deleteLater();
}
