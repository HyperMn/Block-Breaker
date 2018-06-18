#include "slowplank.h"
#include<QPainter>

const QImage SlowPlank::outlook{QImage(":/plank/image/plank/slowPlank.png")};

SlowPlank::SlowPlank(QGraphicsItem* parent):
  AbstractPlank(parent,8)
{

}

QRectF SlowPlank::boundingRect() const
{
  return QRectF(-80,-10,160,20);
}

void SlowPlank::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget)
{
  static QBrush brush(outlook.scaled(this->boundingRect().size().toSize()));
  Q_UNUSED(option)
  Q_UNUSED(widget)
  painter->setBrushOrigin(this->boundingRect().topLeft());
  painter->fillPath(this->shape(),brush);
}

