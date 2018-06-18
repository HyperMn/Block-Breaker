#include "longerplank.h"
#include<QPainter>

const QImage LongerPlank::outlook{QImage(":/plank/image/plank/longerPlank.png")};

LongerPlank::LongerPlank(QGraphicsItem* parent):
  AbstractPlank(parent)
{

}

QRectF LongerPlank::boundingRect() const
{
  return QRectF(-100,-10,200,20);
}

void LongerPlank::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget)
{
  static QBrush brush(outlook.scaled(this->boundingRect().size().toSize()));
  Q_UNUSED(option)
  Q_UNUSED(widget)
  painter->setBrushOrigin(this->boundingRect().topLeft());
  painter->fillPath(this->shape(),brush);
}


