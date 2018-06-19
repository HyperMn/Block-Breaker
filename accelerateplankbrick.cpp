#include "accelerateplankbrick.h"
#include<QGraphicsScene>

AcceleratePlankBrick::AcceleratePlankBrick(QGraphicsItem* parent):
  AbstractSurprisingBrick(1,QColor(0,191,255,100),parent)
{

}

AcceleratePlankBrick::~AcceleratePlankBrick()
{
  this->setAward();
}

void AcceleratePlankBrick::setAward()
{
  Gift *gift=new Gift(Gift::acceleratePlank);
  this->scene()->addItem(gift);
  gift->setPos(this->pos());
  emit this->awardSent(gift);
}
