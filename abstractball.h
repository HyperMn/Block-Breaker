#ifndef ABSTRACTBALL_H//头文件的ifndef和define
#define ABSTRACTBALL_H

#include<QGraphicsObject>//QT库的包含
#include<QList>

class Gift;//Gift类

class AbstractBall:public QGraphicsObject//类的定义，public:公有继承
//AbstractBall是QGraphicsObject类的派生类，且所有的访问关系不变
{
//class类默认为private
  Q_OBJECT//qt声明关键字，生命之后才能使用qt的内容
protected:
  enum CollidingState//enum枚举出一个CollidingState变量，枚举出球的两种状态
  {
    notCollided,//非碰撞态
    collided//碰撞态
  };

public:  
//Abstract类的构造函数
  AbstractBall(qreal movingSpeed,QGraphicsItem *parent=nullptr);//在windows中qreal相当于double类型
//速度movingspeed是一个double类型
//形状parent是一个QGraphicsItem类，可以用来描绘形状，是一个空指针
  virtual ~AbstractBall();//一个虚基类，用于继承
  QPainterPath shape()const override;//override覆盖从基类继承来的定义(QGraphicsObject类中的一个虚函数)
//创建一个QpainterPath类shape，提供容器进行绘图操作，
signals://signals关键字指出进入了信号声明区
//某个信号对其客户或者所有者发生的内部状态发生改变，信号被当作一个对象发射
  collidingWithItem(QList<QGraphicsItem*> items,AbstractBall* sender);
//定义了信号collidingWithItem
//items是一个QList容器，包含了指向QGraphicsItem类的指针，也就是描绘形状的parent
//sender是一个指向AbstractBall的指针
public slots://槽函数slots有三种类型，这里是public slots
//在这个区内声明的槽意味着任何对象都可将信号与其相连
//槽是普通的C++成员函数，可以被正常调用，其特殊性在于很多信号可以与他关联
//当其关联的信号被发射时，这个槽就会被调用
  void offsetAngle(const qreal xOff,const qreal yOff);//定义出射角
  void stopMoving();//停止移动
  void startToMove();//开始移动
protected slots://这个区内的声明槽意味着当前类及其子类可以将信号与之相连接
  virtual void handleCollision();
private slots://这个区内的槽意味着只有类自己可以将信号与之相连结
  void movingForward();//向前移动
  void resetAngel(QList<QGraphicsItem*> items);//重置角度
private:

protected:
  CollidingState collidingState;//collidingState是一个CollidingState类型的变量
private://一些私有的状态
  QTimer *timer;//timer是一个指向QTimer类的指针
  QPointF movingAngle;//movingAngle是一个QPointF类
//QPointF的构造函数是QPointF(qreal x,qreal y)
  qreal movingSpeed;//移动速度是一个double类型变量
  QList<QGraphicsItem*> justCollidedItems;//刚才与之碰撞的元素
};

#endif //结束对头文件ABSTRACTBALL_H的定义，头文件名全大写
//ifdef/ifndef和endif配套使用


//形状parent
//速度movingspeed
//碰撞态collidingState
//计时器timer
//移动的角度movingAngle
//球的运行轨迹shape