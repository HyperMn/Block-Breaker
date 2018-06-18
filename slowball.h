#ifndef SLOWBALL_H
#define SLOWBALL_H

#include"abstractball.h"

class SlowBall : public AbstractBall
{
public:
  SlowBall(QGraphicsItem *parent=nullptr);
  QRectF boundingRect()const override;

protected:
  void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget=nullptr);
private:
  int collidingOutLookActiveTime;
  const static QImage outlook;
};

#endif // SLOWBALL_H
