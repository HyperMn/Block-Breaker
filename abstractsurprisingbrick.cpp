#include "abstractsurprisingbrick.h"
#include<QDebug>

AbstractSurprisingBrick::AbstractSurprisingBrick(int hittingTimeLeft, QColor outlook, QGraphicsItem* parent):
  AbstractBrick(hittingTimeLeft,outlook,parent)
{

}

AbstractSurprisingBrick::~AbstractSurprisingBrick()
{

}
