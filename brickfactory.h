#ifndef BRICKFACTORY_H
#define BRICKFACTORY_H

class AbstractBrick;

class BrickFactory
{
public:
  BrickFactory()=delete;
  static AbstractBrick* constructAddBallBrick();
  static AbstractBrick* constructShrinkPlankBrick();
  static AbstractBrick* constructNormalBrick();
  static AbstractBrick* constructStretchPlankBrick();
  static AbstractBrick* constructAcceleratePlankBrick();
  static AbstractBrick* constructDeceleratePlankBrick();
  static AbstractBrick* constructHardBrick();
  static AbstractBrick* constructHarderBrick();
  static AbstractBrick* constructHardestBrick();
};

#endif // BRICKFACTORY_H
