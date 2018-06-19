//包括了gift头文件,定时器和画笔类
#include "gift.h"
#include<QTimer>
#include<QPainter>

//以下是奖励使用的图标
const QImage addBallOutlook(":/gift/image/gift/addBallGift.png");
const QImage acceleratePlankOutlook(":/gift/image/gift/acceleratePlankBGift.png");
const QImage deceleratePlankOutlook(":/gift/image/gift/deceleratePlankGift.png");
const QImage shrinkPlankOutlook(":/gift/image/gift/shrinkPlankGift.png");
const QImage stretchPlankOutlook(":/gift/image/gift/stretchPlankGift.png");

//构造函数的实现
Gift::Gift(Information information, QGraphicsItem* parent):
  QGraphicsObject(parent),
  m_information(information),
  timer(new QTimer(this))
{
    //设置时间,自动循环
  timer->setInterval(20);
  //开始计时
  timer->start();
  //连接信号和槽
  //出现超时信号时,连接到奖品掉落的槽
  this->connect(timer,SIGNAL(timeout()),this,SLOT(dropDown()));
  //调用
  selectOutlook();
}

//其他成员函数的实现
Gift::Information Gift::information() const
{
  return this->m_information;
}

QRectF Gift::boundingRect() const
{
    //实现矩形
    //是一个QPoint对象和一个QSize对象的组合,QPoint对象是它的左上角的坐标,QSize对象则是它的大小
    //前两个参数是左上角的横纵坐标,后两个参数是宽度和高度
  return QRectF(-10,-10,20,20);
}

QPainterPath Gift::shape() const
{
    //QPainterPath类,主要是一些图形组成的对象,可以保存已经绘制好的图形
    //这里声明了一个path类的path
    QPainterPath path;
  //添加一个刚才实现了的矩形
  path.addRect(this->boundingRect());
  return path;
}

void Gift::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget)
{
    //Q_UNUSED用于避免编译器警告
  Q_UNUSED(option)
  Q_UNUSED(widget)
    //设定画刷的原点
  painter->setBrushOrigin(this->boundingRect().topLeft());
   //对路径进行填充
  painter->fillPath(this->shape(),outlook);
}

void Gift::stopMoving()
{
    //定时器停止
  this->timer->stop();
}

void Gift::startToMove()
{
    //定时器开始
  this->timer->start();
}

void Gift::accept()
{
    //获得了奖品
    //删除礼物父对象及其子对象
  this->deleteLater();
}

void Gift::dropDown()
{
    //奖品落下
  this->setPos(this->pos()+={0,4});
  this->handleColliding();
}

void Gift::handleColliding()
{
    //检测碰撞
    //GraphicsScene类方法collidingItems会返回一个在这个Scene中与传入的item有碰撞的所有其它item的一个列表QList<QGraphicsItem *>,不包括这个item
    //这里的碰撞检测是当被检测物的包含矩形和检测物有交集的时候,触发碰撞
    //其他的检测模式有形状被包含,形状有交集,矩形被包含
  auto collidingItems=this->collidingItems(Qt::IntersectsItemBoundingRect);
  //如果当前场景中有其他的item
  if(!collidingItems.empty())
  {
      //则释放了碰撞的信号
      //emit相当于将这个信号connect了对应的槽
    emit collidingWithItem(collidingItems,this);
  }
}

void Gift::selectOutlook()
{
    //使用switch进行随机选择,选择出现的奖品
  switch (this->m_information)
  {
  //增加球的奖品
    case Gift::addOneNormalBall:
    case Gift::addTwoNormalBall:
    case Gift::addThreeNormalBall:
    case Gift::addOneFastBall:
    case Gift::addOneSlowBall:
    case Gift::addOneBigBall:
    case Gift::addOneSmallBall:
    case Gift::addOneSuperBall:
      //使用画刷增加了一个球
      //scaled根据指定的宽和高,将图像按比例进行转换
      //添加了QImage指定的对象
      this->outlook=QBrush(addBallOutlook.scaled(this->boundingRect().size().toSize()));
    break;
      //缩短板子
    case Gift::shrinkPlank:
      this->outlook=QBrush(shrinkPlankOutlook.scaled(this->boundingRect().size().toSize()));
    break;
      //加长板子
    case Gift::stretchPlank:
      this->outlook=QBrush(stretchPlankOutlook.scaled(this->boundingRect().size().toSize()));
    break;
      //加速板子
    case Gift::acceleratePlank:
      this->outlook=QBrush(acceleratePlankOutlook.scaled(this->boundingRect().size().toSize()));
    break;
      //减速板子
    case Gift::deceleratePlank:
      this->outlook=QBrush(deceleratePlankOutlook.scaled(this->boundingRect().size().toSize()));
    break;
  }
}
