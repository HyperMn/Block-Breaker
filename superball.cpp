#include "superball.h"
#include"abstractbrick.h"
#include<QPainter>

const QImage SuperBall::outlook(":/Ball/image/ball/superBall.png");

SuperBall::SuperBall(QGraphicsItem* parent):
  AbstractBall(1,parent),
  collidingOutLookActiveTime(0)
{

}

QRectF SuperBall::boundingRect() const
{
  return QRectF(-10,-10,20,20);
}

void SuperBall::handleCollision()
{
  bool collidedWithBrick=false;
  for(auto& i:this->collidingItems(Qt::IntersectsItemBoundingRect))
  {
    if(dynamic_cast<AbstractBrick*>(i))
    {
      static_cast<AbstractBrick*>(i)->deleteLater();
      collidedWithBrick=true;
    }
  }
  if(!collidedWithBrick)
  {
    AbstractBall::handleCollision();
  }
}

void SuperBall::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget)
{
  static QBrush brush(outlook.scaled(this->boundingRect().size().toSize()));
  Q_UNUSED(option)
  Q_UNUSED(widget)
  if(collidingOutLookActiveTime>0)
  {
    painter->setOpacity(0.5);
    collidingOutLookActiveTime--;
  }
  else if(collidingState==collided)
  {
    collidingOutLookActiveTime=20;
  }
  painter->setRenderHint(QPainter::Antialiasing,true);
  painter->setBrushOrigin(this->boundingRect().topLeft());
  painter->fillRect(this->boundingRect(),brush);
}
