#ifndef FASTBALL_H
#define FASTBALL_H

#include"abstractball.h"

class FastBall : public AbstractBall
{
public:
  FastBall(QGraphicsItem *parent=nullptr);
  QRectF boundingRect()const override;

protected:
  void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget=nullptr);
private:
  int collidingOutLookActiveTime;
  const static QImage outlook;
};

#endif // FASTBALL_H
