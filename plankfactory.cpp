#include "plankfactory.h"
#include"normalplank.h"
#include"shorterplank.h"
#include"longerplank.h"
#include"fastplank.h"
#include"slowplank.h"

AbstractPlank* PlankFactory::constructNormalPlank()
{
  return new NormalPlank;
}

AbstractPlank* PlankFactory::constructShorterPlank()
{
  return new ShorterPlank;
}

AbstractPlank*PlankFactory::constructLongerPlank()
{
  return new LongerPlank;
}

AbstractPlank*PlankFactory::constructFastPlank()
{
  return new FastPlank;
}

AbstractPlank*PlankFactory::constructSlowPlank()
{
  return new SlowPlank;
}
