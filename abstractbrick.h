#ifndef ABSTRACTBRICK_H
#define ABSTRACTBRICK_H

#include<QGraphicsObject>

class AbstractBrick : public QGraphicsObject
{
  Q_OBJECT
public:
  AbstractBrick(int totalHittingTime, QColor outlook, QGraphicsItem* parent=nullptr);
  virtual ~AbstractBrick();
  QRectF boundingRect()const override;
  QPainterPath shape()const override;
  void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)override;
  virtual void collidingWithBall();
private:
  int hittingTimeLeft;
  QColor outlook;
};

#endif // ABSTRACTBRICK_H
