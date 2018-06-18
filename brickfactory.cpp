#include"brickfactory.h"
#include"addballbrick.h"
#include"shrinkplankbrick.h"
#include"normalbrick.h"
#include"stretchplankbrick.h"
#include"decelerateplankbrick.h"
#include"hardbrick.h"
#include"harderbrick.h"
#include"hardestbrick.h"
#include"accelerateplankbrick.h"

AbstractBrick* BrickFactory::constructAddBallBrick()
{
  return new AddBallBrick;
}

AbstractBrick* BrickFactory::constructShrinkPlankBrick()
{
  return new ShrinkPlankBrick;
}

AbstractBrick* BrickFactory::constructNormalBrick()
{
  return new NormalBrick;
}

AbstractBrick* BrickFactory::constructStretchPlankBrick()
{
  return new StretchPlankBrick;
}

AbstractBrick* BrickFactory::constructAcceleratePlankBrick()
{
  return new AcceleratePlankBrick;
}

AbstractBrick* BrickFactory::constructDeceleratePlankBrick()
{
  return new DeceleratePlankBrick;
}

AbstractBrick* BrickFactory::constructHardBrick()
{
  return new HardBrick;
}

AbstractBrick* BrickFactory::constructHarderBrick()
{
  return new HarderBrick;
}

AbstractBrick* BrickFactory::constructHardestBrick()
{
  return new HardestBrick;
}

