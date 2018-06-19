#ifndef GIFT_H
#define GIFT_H

//提供了图形的信号,槽和属性
//使用父项构造,删除其父对象时,本身也会被删除
#include<QGraphicsObject>
//QT中通用容器类,作用类似于QVector,和QVector不同的是,访问是基于索引的,而不是基于迭代器的
#include<QList>
//画刷类,用于绘图
//QBrush定义了QPainter的填充模式，具有样式、颜色、渐变以及纹理等属性。
//画刷的style()定义了填充的样式，使用Qt::BrushStyle枚举，默认值是Qt::NoBrush，也就是不进行任何填充。
//画刷的color()定义了填充模式的颜色。这个颜色可以是 Qt 预定义的颜色常量，也就是Qt::GlobalColor，也可以是任意QColor对象。
//画刷的gradient()定义了渐变填充。这个属性只有在样式是Qt::LinearGradientPattern、Qt::RadialGradientPattern或者Qt::ConicalGradientPattern之一时才有效。
#include<QBrush>

class Gift : public QGraphicsObject
{
    //用于声明使用信号和槽的宏
    //宏的实现位于moc中
  Q_OBJECT
public:
    //枚举
    //游戏中的各种奖励
  enum Information
  {
      //增加一个普通的球
    addOneNormalBall,
      //增加两个普通的球
    addTwoNormalBall,
      //增加三个普通的球
    addThreeNormalBall,
      //增加一个快速的球
    addOneFastBall,
      //增加一个慢的球
    addOneSlowBall,
      //增加一个大的球
    addOneBigBall,
      //增加一个小的球
    addOneSmallBall,
      //增加一个无敌的球
    addOneSuperBall,
      //使木板加速
    acceleratePlank,
      //使木板减速
    deceleratePlank,
      //使木板变长
    stretchPlank,
      //使木板变短
    shrinkPlank
  };

public:
  //GIft构造函数
  Gift(Information information,QGraphicsItem* parent=nullptr);

  Information information()const;
    //C++11标准,重载了基类中的同名函数,或者说是覆盖
  //与同名函数的方法名,参数,返回值都相同
  QRectF boundingRect()const override;
  //重载shape方法
  QPainterPath shape()const override;
  //
  void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

  //信号
signals:
  //碰撞信号
  void collidingWithItem(QList<QGraphicsItem*> items,Gift* sender);
  //公共槽
public slots:
  void accept();
  //停止移动槽
  void stopMoving();
  //开始移动槽
  void startToMove();
  //私有槽
private slots:
  //奖品掉落
  void dropDown();
  //私有变量
private:
  void handleColliding();
  void selectOutlook();

  const Information m_information;
  //一个定时器,用于控制出现奖品的时间
  //start开始,tiemout()结束,利用timeout()发出信号,连接给适当的槽
  //父对象被销毁时,会自动销毁
  QTimer* timer;
  //outlook画刷
  QBrush  outlook;
};

#endif // GIFT_H
