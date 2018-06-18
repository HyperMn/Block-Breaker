#include "shorterplank.h"

#include<QPainter>

const QImage ShorterPlank::outlook{QImage(":/plank/image/plank/shorterPlank.png")};

ShorterPlank::ShorterPlank(QGraphicsItem* parent):
  AbstractPlank(parent)
{

}

QRectF ShorterPlank::boundingRect() const
{
  return QRectF(-70,-10,140,20);
}

void ShorterPlank::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget)
{
  static QBrush brush(outlook.scaled(this->boundingRect().size().toSize()));
  Q_UNUSED(option)
  Q_UNUSED(widget)
  painter->setBrushOrigin(this->boundingRect().topLeft());
  painter->fillPath(this->shape(),brush);
}
