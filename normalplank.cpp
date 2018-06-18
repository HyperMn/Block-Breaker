#include "normalplank.h"
#include<QPainter>

const QImage NormalPlank::outlook{QImage(":/plank/image/plank/normalPlank.png")};

NormalPlank::NormalPlank(QGraphicsItem* parent):
  AbstractPlank(parent)
{

}

QRectF NormalPlank::boundingRect() const
{
  return QRectF(-80,-10,160,20);
}

void NormalPlank::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget)
{
  static QBrush brush(outlook.scaled(this->boundingRect().size().toSize()));
  Q_UNUSED(option)
  Q_UNUSED(widget)
  painter->setBrushOrigin(this->boundingRect().topLeft());
  painter->fillPath(this->shape(),brush);
}

