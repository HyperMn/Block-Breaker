#ifndef GAMESCENE_H
#define GAMESCENE_H

#include<QGraphicsScene>
#include<QList>

#include"gift.h"

class QMediaPlayer;
class AbstractPlank;
class AbstractBall;
class AbstractBrick;

class GameScene : public QGraphicsScene
{
  Q_OBJECT
  enum GameState
  {
    ready,
    start,
    pause
  };

public:
  GameScene(QObject* parent=nullptr);
signals:
  void gameWin();
  void gameLose();
  void gamePause();
  void gameContinue();
  void upScore(int score);

public slots:
  void selectGameLevel(int level);
  void randSetGift();
protected:
  void keyPressEvent(QKeyEvent *e)override;
  void keyReleaseEvent(QKeyEvent *e)override;
private slots:
//  void gameStart();

  void ballCollided(QList<QGraphicsItem*> items,AbstractBall* ball);
  void giftCollided(QList<QGraphicsItem*> items, Gift* gift);
  void offsetBall(qreal xOff,qreal yOff,QGraphicsItem* ball);

  void monitorBall(AbstractBall* ball);
  void monitorBrick(AbstractBrick *brick);
  void monitorPlank(AbstractPlank* plank);
  void monitorGift(Gift* gift);

  void ballDestroyed();
  void brickDestroyed();

private:
  void analysisGift(Gift* gift);
  void addBall(AbstractBall* ball,QPointF pos);
  void addBrick(AbstractBrick* brick,QPointF pos);
  void convertPlank(AbstractPlank* newPlank);
  void initBorder();

  AbstractPlank *plank;

  QMediaPlayer * brickCollidedPlayer;
  QMediaPlayer * brickDestroyedPlayer;
  QMediaPlayer * ballAddedPlayer;
  QMediaPlayer * plankCollidedPlayer;

  int ballAmount;
  int brickAmount;
  GameState gameState;
};

#endif // GAMESCENE_H
