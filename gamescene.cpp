#include "gamescene.h"
#include"bordersquare.h"
#include"abstractball.h"
#include"ballfactory.h"
#include<QKeyEvent>
#include"brickfactory.h"
#include"forbiddensquare.h"
#include"abstractsurprisingbrick.h"
#include"abstractplank.h"
#include"gamelevel.h"
#include"plankfactory.h"
#include<QDebug>
#include<QGraphicsSceneMouseEvent>
#include<QTime>
#include<QMediaPlayer>

//构造函数列表初始化
GameScene::GameScene(QObject* parent):
  QGraphicsScene(parent),
  plank(nullptr),
  //音乐音效
  brickCollidedPlayer(new QMediaPlayer(this)),
  brickDestroyedPlayer(new QMediaPlayer(this)),
  ballAddedPlayer(new QMediaPlayer(this)),
  plankCollidedPlayer(new QMediaPlayer(this)),
  //球的数量,砖的数量
  ballAmount(0),
  brickAmount(0),
  //游戏状态
  gameState(ready)
{
  qsrand(QTime::currentTime().msecsSinceStartOfDay());
  this->setSceneRect(0,0,550,500);
  this->initBorder();
  //设置音乐
  brickCollidedPlayer->setMedia(QUrl("qrc:/music/brickCollided.wav"));
  brickDestroyedPlayer->setMedia(QUrl("qrc:/music/brickDestroyed.wav"));
  ballAddedPlayer->setMedia(QUrl("qrc:/music/ballAdded.wav"));
  plankCollidedPlayer->setMedia(QUrl("qrc:/music/plankCollided.wav"));
}

void GameScene::selectGameLevel(int level)
{
  //场景长550，宽500
  const bool (*map)[12]=nullptr;
  switch ((level-1)%GameLevel::levelAmount+1) {
    case 1:
      map=GameLevel::leve1;
    break;
    case 2:
      map=GameLevel::leve2;
    break;
    case 3:
      map=GameLevel::leve3;
    break;
    case 4:
      map=GameLevel::leve4;
    break;
    case 5:
      map=GameLevel::leve5;
    break;
    case 6:
      map=GameLevel::leve6;
    break;
    case 7:
      map=GameLevel::leve7;
    break;
    case 8:
      map=GameLevel::leve8;
    break;
    default:
      qDebug()<<"error in math gameLevel"<<level;
    break;
  }

  //砖块长40，宽30
  //砖块待选位置 12 X 12   QRectF(35,10,480,360)
  QPointF topLeftPoint{35+20,25};
  for(int i=0;i<12;i++)
  {
    for(int j=0;j<12;j++)
    {
      if(map[j][i])
      {
        AbstractBrick *brick;
        switch (qrand()%(level*10)) {
          case 00:
            brick=BrickFactory::constructStretchPlankBrick();
          break;
          case 10:
            brick=BrickFactory::constructAcceleratePlankBrick();
          break;
          case 11:
          case 12:
            brick=BrickFactory::constructHardBrick();
          break;
          case 20:
          case 21:
          case 22:
          case 23:
          case 24:
            brick=BrickFactory::constructHarderBrick();
          break;
          case 30:
          case 31:
          case 32:
          case 33:
          case 34:
            brick=BrickFactory::constructShrinkPlankBrick();
          break;
          case 40:
          case 41:
          case 42:
          case 43:
          case 44:
          case 45:
          case 46:
          case 47:
          case 48:
          case 49:
            brick=BrickFactory::constructHarderBrick();
           break;
          case 50:
          case 51:
          case 52:
          case 53:
            brick=BrickFactory::constructDeceleratePlankBrick();
          break;
          default:
            if(level<8)
            {
              brick=qrand()%5?BrickFactory::constructNormalBrick():BrickFactory::constructAddBallBrick();
            }
            else
            {
              brick=qrand()%3?(rand()%2?BrickFactory::constructHarderBrick():BrickFactory::constructHardBrick())\
                  :BrickFactory::constructAddBallBrick();
            }
          break;
        }
        this->addBrick(brick,topLeftPoint+QPoint{40*i,30*j});
      }
    }
  }
  //初始状态设置球和板子
  auto ball=BallFactory::constructNormalBall();
  ball->stopMoving();
  this->addBall(ball,QPoint(255,460));
  this->plank=PlankFactory::constructNormalPlank();
  this->addItem(plank);
  plank->setPos(255,480);
  this->monitorPlank(plank);
  this->gameState=ready;
}

//void GameScene::gameStart()
//{
//  if(this->gameState==ready)
//  {
//    for(auto& i:this->items())
//    {
//      if(dynamic_cast<AbstractBall*>(i))
//      {
//        static_cast<AbstractBall*>(i)->startToMove();
//      }
//    }
//    this->gameState=start;
//  }
//}

//键盘动作控制板子的移动
void GameScene::keyPressEvent(QKeyEvent* e)
{
  switch (e->key()) {
    case Qt::Key_A:
    case Qt::Key_Left:
	  if(plank->isMovingState(AbstractPlank::notMove)||plank->isMovingState(AbstractPlank::moveToRight))
      {
        plank->setMovingState(AbstractPlank::moveToLeft);
        e->accept();
      }
    break;
    case Qt::Key_D:
    case Qt::Key_Right:
	  if(plank->isMovingState(AbstractPlank::notMove)||plank->isMovingState(AbstractPlank::moveToLeft))
      {
        plank->setMovingState(AbstractPlank::moveToRight);
        e->accept();
      }
    break;
    //使用空格游戏暂停
    case Qt::Key_Space:
      if(this->gameState==ready||this->gameState==pause)
      {
        emit this->gameContinue();
        this->gameState=start;
      }
      else if(this->gameState==this->start)
      {
        emit this->gamePause();
        this->gameState=pause;
      }
    break;
    case Qt::Key_1:
//      emit this->gameWin();
    break;
    case Qt::Key_3:
//      emit this->gameLose();
    break;
    default:
      e->ignore();
    break;
  }
}
//键盘事件
void GameScene::keyReleaseEvent(QKeyEvent* e)
{
  switch (e->key())
  {
    case Qt::Key_A:
    case Qt::Key_Left:
      if(plank->isMovingState(AbstractPlank::moveToLeft))
      {
        plank->setMovingState(AbstractPlank::notMove);
        e->accept();
      }
    break;
    case Qt::Key_D:
    case Qt::Key_Right:
      if(plank->isMovingState(AbstractPlank::moveToRight))
      {
        plank->setMovingState(AbstractPlank::notMove);
        e->accept();
      }
    break;
    default:
      e->ignore();
    break;
  }
}
//设置礼物
void GameScene::randSetGift()
{
  //x是浮点类型
	qreal x=qrand()%500;
	Gift *gift;
  //switch选择出现什么样的礼物
	switch(qrand()%10)
	{
		case 1:
		case 2:
			gift=new Gift(Gift::addOneSuperBall);
		break;
		default:
			gift=new Gift(Gift::addThreeNormalBall);
		break;
	}
	this->addItem(gift);
	gift->setPos(x+25,0);
	this->monitorGift(gift);
}

void GameScene::ballCollided(QList<QGraphicsItem*> items, AbstractBall* ball)
{
  //球的撞击
  //撞击的循环
  for(auto& i:items)
  {
    //指针类型转换
    if(dynamic_cast<AbstractPlank*>(i))
    {
      //播放音效
      plankCollidedPlayer->play();
      static_cast<AbstractPlank*>(i)->collidingWithBall(ball);
    }
    else if(dynamic_cast<AbstractBrick*>(i))
    {
      brickCollidedPlayer->play();
      static_cast<AbstractBrick*>(i)->collidingWithBall();
    }
    else if(dynamic_cast<ForbiddenSquare*>(i))
    {
      ForbiddenSquare::handleColliding(ball);
    }
  }
}

void GameScene::giftCollided(QList<QGraphicsItem*> items, Gift* gift)
{
  //撞击到礼物
  for(auto& i:items)
  {
    if(dynamic_cast<AbstractPlank*>(i))
    {
      this->analysisGift(gift);
      gift->accept();
      return;
    }
    else if(dynamic_cast<ForbiddenSquare*>(i))
    {
      ForbiddenSquare::handleColliding(gift);
      gift->accept();
    }
  }
}
//坐标,角度
void GameScene::offsetBall(qreal xOff, qreal yOff, QGraphicsItem* ball)
{
  static_cast<AbstractBall*>(ball)->offsetAngle(xOff,yOff);
}

void GameScene::monitorBall(AbstractBall* ball)
{
  //连接信号和槽
  //球没了
  this->connect(ball,SIGNAL(destroyed(QObject*)),this,SLOT(ballDestroyed()));
  //撞击到物体
  connect(ball,SIGNAL(collidingWithItem(QList<QGraphicsItem*>,AbstractBall*)),\
          this,SLOT(ballCollided(QList<QGraphicsItem*>,AbstractBall*)));
  //游戏开始
  connect(this,SIGNAL(gameContinue()),ball,SLOT(startToMove()));
  //游戏暂停
  connect(this,SIGNAL(gamePause()),ball,SLOT(stopMoving()));
}

void GameScene::monitorBrick(AbstractBrick* brick)
{
  //连接信号和槽
  //撞到砖块
  this->connect(brick,SIGNAL(destroyed(QObject*)),this,SLOT(brickDestroyed()));
  if(dynamic_cast<AbstractSurprisingBrick*>(brick))
  {
    //撞到有奖品的砖块
    this->connect(static_cast<AbstractSurprisingBrick*>(brick),SIGNAL(awardSent(Gift*)),\
                  this,SLOT(monitorGift(Gift*)));
  }
}

void GameScene::monitorPlank(AbstractPlank* plank)
{
  //板子上球的位置
  connect(plank,SIGNAL(setOffset(qreal,qreal,QGraphicsItem*)),\
          this,SLOT(offsetBall(qreal,qreal,QGraphicsItem*)));
  connect(this,SIGNAL(gameContinue()),plank,SLOT(startToMove()));
  connect(this,SIGNAL(gamePause()),plank,SLOT(stopMoving()));
}

void GameScene::monitorGift(Gift* gift)
{
  //撞到有奖品的板子
  this->connect(gift,SIGNAL(collidingWithItem(QList<QGraphicsItem*>,Gift*)),\
                this,SLOT(giftCollided(QList<QGraphicsItem*>,Gift*)));
  connect(this,SIGNAL(gameContinue()),gift,SLOT(startToMove()));
  connect(this,SIGNAL(gamePause()),gift,SLOT(stopMoving()));
}

//球没了
void GameScene::ballDestroyed()
{
  //球的数量减少
  ballAmount--;
  //数量为0,游戏失败
  if(ballAmount==0)
  {
    emit this->gameLose();
  }
}

//砖块被击碎
void GameScene::brickDestroyed()
{
  //播放音效
  brickDestroyedPlayer->play();
  //砖块的数量减少
  brickAmount--;
  //分数加100
  emit upScore(100);
  //砖的数量为0
  if(brickAmount==0)
  {
    //游戏胜利的信号
    emit this->gameWin();
  }
}

void GameScene::initBorder()
{
  //场景长550，宽500

  //边界方块长50，宽50
  for(int i=0;i<13;i++)
  {
    auto borderSquare=new BorderSquare;//上
    this->addItem(borderSquare);
    borderSquare->setPos(-25+i*50,-25);
    auto forbiddenSquare=new ForbiddenSquare;//下
    this->addItem(forbiddenSquare);
    forbiddenSquare->setPos(-25+i*50,525);
  }
  for(int i=0;i<10;i++)
  {
    auto borderSquare=new BorderSquare;//左
    this->addItem(borderSquare);
    borderSquare->setPos(-25,25+i*50);
    borderSquare=new BorderSquare;//右
    this->addItem(borderSquare);
    borderSquare->setPos(575,25+i*50);
  }
}

void GameScene::analysisGift(Gift* gift)
{
  switch (gift->information())
  {
    //QpointF类,可以用浮点的精度表示点的坐标
    case Gift::addOneNormalBall:
      addBall(BallFactory::constructNormalBall(),gift->pos()-QPointF{0,plank->boundingRect().height()});
    break;
    case Gift::addTwoNormalBall:
      addBall(BallFactory::constructNormalBall(),gift->pos()-QPointF{0,plank->boundingRect().height()});
      addBall(BallFactory::constructNormalBall(),gift->pos()-QPointF{0,plank->boundingRect().height()});
    break;
    //增加三个球
    case Gift::addThreeNormalBall:
      addBall(BallFactory::constructNormalBall(),gift->pos()-QPointF{0,plank->boundingRect().height()});
      addBall(BallFactory::constructNormalBall(),gift->pos()-QPointF{0,plank->boundingRect().height()});
      addBall(BallFactory::constructNormalBall(),gift->pos()-QPointF{0,plank->boundingRect().height()});
    break;
    case Gift::addOneFastBall:
      addBall(BallFactory::constructFastBall(),gift->pos()-QPointF{0,plank->boundingRect().height()});
    break;
    case Gift::addOneSlowBall:
      addBall(BallFactory::constructSlowBall(),gift->pos()-QPointF{0,plank->boundingRect().height()});
    break;
    case Gift::addOneBigBall:
      addBall(BallFactory::constructBigBall(),gift->pos()-QPointF{0,plank->boundingRect().height()});
    break;
    case Gift::addOneSmallBall:
      addBall(BallFactory::constructSmallBall(),gift->pos()-QPointF{0,plank->boundingRect().height()});
    break;
    case Gift::addOneSuperBall:
      addBall(BallFactory::constructSuperBall(),gift->pos()-QPointF{0,plank->boundingRect().height()});
    break;
    //对板子进行改变
    case Gift::shrinkPlank:
      this->convertPlank(PlankFactory::constructShorterPlank());
    break;
    case Gift::stretchPlank:
      this->convertPlank(PlankFactory::constructLongerPlank());
    break;
    case Gift::acceleratePlank:
      this->convertPlank(PlankFactory::constructFastPlank());
    break;
    case Gift::deceleratePlank:
      this->convertPlank(PlankFactory::constructSlowPlank());
    break;
    default:
      qDebug()<<"not matching gift information"<<gift->information();
    break;
  }
}

//增加球
void GameScene::addBall(AbstractBall* ball, QPointF pos)
{
  static int i=0;
  ballAddedPlayer->play();
  this->addItem(ball);
  ball->setPos(pos);
  this->offsetBall(-1+i++%3,-3,ball);
  this->monitorBall(ball);
  this->ballAmount++;
}
//增加砖块
void GameScene::addBrick(AbstractBrick* brick, QPointF pos)
{
  this->addItem(brick);
  brick->setPos(pos);
  this->brickAmount++;
  this->monitorBrick(brick);
}
//转换板子
void GameScene::convertPlank(AbstractPlank* newPlank)
{
  this->addItem(newPlank);
  newPlank->setPos(this->plank->pos());
  if(this->plank!=nullptr)
  {
    this->plank->deleteLater();
  }
  this->plank=newPlank;
  this->monitorPlank(newPlank);
}

