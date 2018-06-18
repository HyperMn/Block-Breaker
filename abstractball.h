#ifndef ABSTRACTBALL_H
#define ABSTRACTBALL_H

#include<QGraphicsObject>
#include<QList>

class Gift;

class AbstractBall:public QGraphicsObject
{
  Q_OBJECT
protected:
  enum CollidingState
  {
    notCollided,
    collided
  };

public:  
  AbstractBall(qreal movingSpeed,QGraphicsItem *parent=nullptr);
  virtual ~AbstractBall();
  QPainterPath shape()const override;
signals:
  collidingWithItem(QList<QGraphicsItem*> items,AbstractBall* sender);
public slots:
  void offsetAngle(const qreal xOff,const qreal yOff);
  void stopMoving();
  void startToMove();
protected slots:
  virtual void handleCollision();
private slots:
  void movingForward();
  void resetAngel(QList<QGraphicsItem*> items);
private:

protected:
  CollidingState collidingState;
private:
  QTimer *timer;
  QPointF movingAngle;
  qreal movingSpeed;
  QList<QGraphicsItem*> justCollidedItems;//刚才与之碰撞的元素
};

#endif // ABSTRACTBALL_H
