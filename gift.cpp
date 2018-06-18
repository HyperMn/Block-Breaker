#include "gift.h"
#include<QTimer>
#include<QPainter>

const QImage addBallOutlook(":/gift/image/gift/addBallGift.png");
const QImage acceleratePlankOutlook(":/gift/image/gift/acceleratePlankBGift.png");
const QImage deceleratePlankOutlook(":/gift/image/gift/deceleratePlankGift.png");
const QImage shrinkPlankOutlook(":/gift/image/gift/shrinkPlankGift.png");
const QImage stretchPlankOutlook(":/gift/image/gift/stretchPlankGift.png");

Gift::Gift(Information information, QGraphicsItem* parent):
  QGraphicsObject(parent),
  m_information(information),
  timer(new QTimer(this))
{
  timer->setInterval(20);
  timer->start();
  this->connect(timer,SIGNAL(timeout()),this,SLOT(dropDown()));
  selectOutlook();
}

Gift::Information Gift::information() const
{
  return this->m_information;
}

QRectF Gift::boundingRect() const
{
  return QRectF(-10,-10,20,20);
}

QPainterPath Gift::shape() const
{
  QPainterPath path;
  path.addRect(this->boundingRect());
  return path;
}

void Gift::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget)
{
  Q_UNUSED(option)
  Q_UNUSED(widget)
  painter->setBrushOrigin(this->boundingRect().topLeft());
  painter->fillPath(this->shape(),outlook);
}

void Gift::stopMoving()
{
  this->timer->stop();
}

void Gift::startToMove()
{
  this->timer->start();
}

void Gift::accept()
{
  this->deleteLater();
}

void Gift::dropDown()
{
  this->setPos(this->pos()+={0,4});
  this->handleColliding();
}

void Gift::handleColliding()
{
  auto collidingItems=this->collidingItems(Qt::IntersectsItemBoundingRect);
  if(!collidingItems.empty())
  {
    emit collidingWithItem(collidingItems,this);
  }
}

void Gift::selectOutlook()
{
  switch (this->m_information)
  {
    case Gift::addOneNormalBall:
    case Gift::addTwoNormalBall:
    case Gift::addThreeNormalBall:
    case Gift::addOneFastBall:
    case Gift::addOneSlowBall:
    case Gift::addOneBigBall:
    case Gift::addOneSmallBall:
    case Gift::addOneSuperBall:
      this->outlook=QBrush(addBallOutlook.scaled(this->boundingRect().size().toSize()));
    break;
    case Gift::shrinkPlank:
      this->outlook=QBrush(shrinkPlankOutlook.scaled(this->boundingRect().size().toSize()));
    break;
    case Gift::stretchPlank:
      this->outlook=QBrush(stretchPlankOutlook.scaled(this->boundingRect().size().toSize()));
    break;
    case Gift::acceleratePlank:
      this->outlook=QBrush(acceleratePlankOutlook.scaled(this->boundingRect().size().toSize()));
    break;
    case Gift::deceleratePlank:
      this->outlook=QBrush(deceleratePlankOutlook.scaled(this->boundingRect().size().toSize()));
    break;
  }
}
