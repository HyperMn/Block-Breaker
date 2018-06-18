#ifndef PLANKFACTORY_H
#define PLANKFACTORY_H

class AbstractPlank;

class PlankFactory
{
public:
  PlankFactory()=delete;
  static AbstractPlank* constructNormalPlank();
  static AbstractPlank* constructShorterPlank();
  static AbstractPlank* constructLongerPlank();
  static AbstractPlank* constructFastPlank();
  static AbstractPlank* constructSlowPlank();
};

#endif // PLANKFACTORY_H
