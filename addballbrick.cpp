#include "addballbrick.h"
#include<QGraphicsScene>

AddBallBrick::AddBallBrick(QGraphicsItem* parent):
  AbstractSurprisingBrick(1,QColor(0,250,50,100),parent)
{

}

AddBallBrick::~AddBallBrick()
{
  this->setAward();
}

void AddBallBrick::setAward()
{
  Gift *gift;
  switch(qrand()%20+1)
  {
    case 1:
    case 2:
      gift=new Gift(Gift::addOneNormalBall);
    break;
    case 3:
    case 4:
      gift=new Gift(Gift::addThreeNormalBall);
    break;
    case 5:
    case 6:
    case 7:
    case 8:
      gift=new Gift(Gift::addOneFastBall);
    break;
    case 9:
    case 10:
      gift=new Gift(Gift::addOneSlowBall);
    break;
    case 11:
    case 12:
      gift=new Gift(Gift::addOneSuperBall);
    break;
    case 13:
      gift=new Gift(Gift::addOneSmallBall);
    break;
    default:
      gift=new Gift(Gift::addTwoNormalBall);
    break;
  }
  this->scene()->addItem(gift);
  gift->setPos(this->pos());
  emit this->awardSent(gift);
}
