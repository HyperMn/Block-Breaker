#include "ballfactory.h"
#include"normalball.h"
#include"fastball.h"
#include"slowball.h"
#include"bigball.h"
#include"smallball.h"
#include"superball.h"

AbstractBall* BallFactory::constructNormalBall(QGraphicsItem* parent)
{
  return new NormalBall(parent);
}

AbstractBall* BallFactory::constructFastBall(QGraphicsItem* parent)
{
  return new FastBall(parent);
}

AbstractBall*BallFactory::constructSlowBall(QGraphicsItem* parent)
{
  return new SlowBall(parent);
}

AbstractBall*BallFactory::constructBigBall(QGraphicsItem* parent)
{
  return new BigBall(parent);
}

AbstractBall*BallFactory::constructSmallBall(QGraphicsItem* parent)
{
  return new SmallBall(parent);
}

AbstractBall*BallFactory::constructSuperBall(QGraphicsItem* parent)
{
  return new SuperBall(parent);
}
