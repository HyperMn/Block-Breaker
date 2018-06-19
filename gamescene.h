#ifndef GAMESCENE_H
#define GAMESCENE_H

#include<QGraphicsScene>
#include<QList>

#include"gift.h"

//前向声明
class QMediaPlayer;
class AbstractPlank;
class AbstractBall;
class AbstractBrick;

class GameScene : public QGraphicsScene
{
  Q_OBJECT
  //游戏状态
  enum GameState
  {
    ready,
    start,
    pause
  };

public:
  //场景
  GameScene(QObject* parent=nullptr);
signals:
  //信号
  void gameWin();
  void gameLose();
  void gamePause();
  void gameContinue();
  void upScore(int score);

//槽
public slots:
  void selectGameLevel(int level);
  void randSetGift();
protected:
  //键盘按键事件
  void keyPressEvent(QKeyEvent *e)override;
  void keyReleaseEvent(QKeyEvent *e)override;
private slots:
//  void gameStart();
  //
  void ballCollided(QList<QGraphicsItem*> items,AbstractBall* ball);
  void giftCollided(QList<QGraphicsItem*> items, Gift* gift);
  void offsetBall(qreal xOff,qreal yOff,QGraphicsItem* ball);
  //控制球,砖块,板子和礼物
  void monitorBall(AbstractBall* ball);
  void monitorBrick(AbstractBrick *brick);
  void monitorPlank(AbstractPlank* plank);
  void monitorGift(Gift* gift);
  //球消失,砖块被击碎
  void ballDestroyed();
  void brickDestroyed();

private:
  
  void analysisGift(Gift* gift);
  //增加球,增加砖块
  void addBall(AbstractBall* ball,QPointF pos);
  void addBrick(AbstractBrick* brick,QPointF pos);
  void convertPlank(AbstractPlank* newPlank);
  //初始化边界
  void initBorder();

  AbstractPlank *plank;
  //音效和音乐
  QMediaPlayer * brickCollidedPlayer;
  QMediaPlayer * brickDestroyedPlayer;
  QMediaPlayer * ballAddedPlayer;
  QMediaPlayer * plankCollidedPlayer;

  //球和砖的数量,游戏状态
  int ballAmount;
  int brickAmount;
  GameState gameState;
};

#endif // GAMESCENE_H
