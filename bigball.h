#ifndef BIGBALL_H
#define BIGBALL_H

#include"abstractball.h"

class BigBall : public AbstractBall
{
public:
  BigBall(QGraphicsItem *parent=nullptr);
  QRectF boundingRect()const override;
protected:
  void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget=nullptr)override;
private:
  int collidingOutLookActiveTime;
  const static QImage outlook;
};

#endif // BIGBALL_H
