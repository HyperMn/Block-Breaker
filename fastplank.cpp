#include "fastplank.h"
#include<QPainter>

const QImage FastPlank::outlook{QImage(":/plank/image/plank/fastPlank.png")};

FastPlank::FastPlank(QGraphicsItem* parent):
  AbstractPlank(parent,3)
{

}

QRectF FastPlank::boundingRect() const
{
  return QRectF(-80,-10,160,20);
}

void FastPlank::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget)
{
  static QBrush brush(outlook.scaled(this->boundingRect().size().toSize()));
  Q_UNUSED(option)
  Q_UNUSED(widget)
  painter->setBrushOrigin(this->boundingRect().topLeft());
  painter->fillPath(this->shape(),brush);
}
