#ifndef GIFT_H
#define GIFT_H

#include<QGraphicsObject>
#include<QList>
#include<QBrush>

class Gift : public QGraphicsObject
{
  Q_OBJECT
public:
  enum Information
  {
    addOneNormalBall,
    addTwoNormalBall,
    addThreeNormalBall,
    addOneFastBall,
    addOneSlowBall,
    addOneBigBall,
    addOneSmallBall,
    addOneSuperBall,
    acceleratePlank,
    deceleratePlank,
    stretchPlank,
    shrinkPlank
  };

public:
  Gift(Information information,QGraphicsItem* parent=nullptr);
  Information information()const;
  QRectF boundingRect()const override;
  QPainterPath shape()const override;
  void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
signals:
  void collidingWithItem(QList<QGraphicsItem*> items,Gift* sender);
public slots:
  void accept();
  void stopMoving();
  void startToMove();
private slots:
  void dropDown();
private:
  void handleColliding();
  void selectOutlook();

  const Information m_information;
  QTimer* timer;
  QBrush  outlook;
};

#endif // GIFT_H
