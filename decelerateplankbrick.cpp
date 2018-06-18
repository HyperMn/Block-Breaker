#include "decelerateplankbrick.h"
#include<QGraphicsScene>

DeceleratePlankBrick::DeceleratePlankBrick(QGraphicsItem* parent):
  AbstractSurprisingBrick(1,QColor(200,200,50,100),parent)
{

}

DeceleratePlankBrick::~DeceleratePlankBrick()
{
  this->setAward();
}

void DeceleratePlankBrick::setAward()
{
  Gift *gift=new Gift(Gift::acceleratePlank);
  this->scene()->addItem(gift);
  gift->setPos(this->pos());
  emit this->awardSent(gift);
}
