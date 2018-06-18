#ifndef SMALLBALL_H
#define SMALLBALL_H

#include"abstractball.h"

class SmallBall : public AbstractBall
{
public:
  SmallBall(QGraphicsItem *parent=nullptr);
  QRectF boundingRect()const override;
protected:
  void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget=nullptr)override;
private:
  int collidingOutLookActiveTime;
  const static QImage outlook;
};

#endif // SMALLBALL_H
