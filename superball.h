#ifndef SUPERBALL_H
#define SUPERBALL_H

#include"abstractball.h"

class SuperBall : public AbstractBall
{
public:
  SuperBall(QGraphicsItem *parent=nullptr);
  QRectF boundingRect()const override;
protected:
  void handleCollision()override;
  void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget=nullptr)override;
private:
  int collidingOutLookActiveTime;
  const static QImage outlook;
};

#endif // SUPERBALL_H
