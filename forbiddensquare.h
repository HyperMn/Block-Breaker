#ifndef FORBIDDENSQUARE_H
#define FORBIDDENSQUARE_H

#include<QGraphicsObject>

class ForbiddenSquare : public QGraphicsObject
{
  Q_OBJECT
public:
  ForbiddenSquare(QGraphicsItem* parent=nullptr);
  QRectF boundingRect()const override;
  QPainterPath shape()const override;
  void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
  static void handleColliding(QObject* object);
};

#endif // FORBIDDENSQUARE_H
