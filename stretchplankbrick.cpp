#include"stretchplankbrick.h"
#include<QGraphicsScene>

StretchPlankBrick::StretchPlankBrick(QGraphicsItem* parent):
  AbstractSurprisingBrick(1,QColor(0,100,50,100),parent)
{

}

StretchPlankBrick::~StretchPlankBrick()
{
  this->setAward();
}

void StretchPlankBrick::setAward()
{
  Gift *gift=new Gift(Gift::stretchPlank);
  this->scene()->addItem(gift);
  gift->setPos(this->pos());
  emit this->awardSent(gift);
}
