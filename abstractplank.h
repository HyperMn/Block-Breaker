#ifndef ABSTRACTPLANK_H
#define ABSTRACTPLANK_H

#include<QGraphicsObject>

class AbstractPlank : public QGraphicsObject
{
  Q_OBJECT
public:
  enum MovingState
  {
    moveToLeft,
    moveToRight,
    notMove
  };

public:
  AbstractPlank(QGraphicsItem *parent=nullptr, qreal movingSpeed=4);
  virtual ~AbstractPlank();
  QPainterPath shape()const override;
  bool isMovingState(MovingState state);

signals:
  void setOffset(qreal xOff,qreal yOff,QGraphicsItem *receiver);
public slots:
  virtual void collidingWithBall(QGraphicsItem *sender);
  void startToMove();
  void stopMoving();
  void setMovingState(MovingState state);
private slots:
  void movingForward();
private:
  QTimer *timer;
  MovingState movingState;
  QPointF collidingEffect;
};

#endif // ABSTRACTPLANK_H
