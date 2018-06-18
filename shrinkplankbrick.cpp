#include "shrinkplankbrick.h"
#include<QGraphicsScene>

ShrinkPlankBrick::ShrinkPlankBrick(QGraphicsItem* parent):
  AbstractSurprisingBrick(1,QColor(200,50,50,100),parent)
{

}

ShrinkPlankBrick::~ShrinkPlankBrick()
{
  this->setAward();
}

void ShrinkPlankBrick::setAward()
{
  Gift *gift=new Gift(Gift::shrinkPlank);
  this->scene()->addItem(gift);
  gift->setPos(this->pos());
  emit this->awardSent(gift);
}

