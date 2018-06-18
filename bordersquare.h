#ifndef BORDERSQUARE_H
#define BORDERSQUARE_H

#include<QGraphicsObject>
class BorderSquare : public QGraphicsObject
{
public:
  BorderSquare(QGraphicsItem *parent=nullptr);
  QRectF boundingRect()const override;
  QPainterPath shape()const override;
  void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)override;
};

#endif // BORDERSQUARE_H
