#ifndef BALLFACTORY_H
#define BALLFACTORY_H

class AbstractBall;
class QGraphicsItem;

class BallFactory
{
public:
  BallFactory()=delete;
  static AbstractBall* constructNormalBall(QGraphicsItem* parent=nullptr);
  static AbstractBall* constructFastBall(QGraphicsItem* parent=nullptr);
  static AbstractBall* constructSlowBall(QGraphicsItem* parent=nullptr);
  static AbstractBall* constructBigBall(QGraphicsItem* parent=nullptr);
  static AbstractBall* constructSmallBall(QGraphicsItem* parent=nullptr);
  static AbstractBall* constructSuperBall(QGraphicsItem* parent=nullptr);
};

#endif // BALLFACTORY_H
