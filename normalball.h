#ifndef NORMALBALL_H
#define NORMALBALL_H

#include"abstractball.h"

class NormalBall : public AbstractBall
{
public:
  NormalBall(QGraphicsItem *parent=nullptr);
  ~NormalBall();
  QRectF boundingRect()const override;

protected:
  void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget=nullptr)override;
private:
  int collidingOutLookActiveTime;
  const static QImage outlook;
};

#endif // NORMALBALL_H
