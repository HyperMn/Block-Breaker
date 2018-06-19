#ifndef GAMEWINDOW_H
#define GAMEWINDOW_H

#include <QWidget>

//声明Ui命名空间中的主窗口
namespace Ui {
  class GameWindow;
}
//前向声明
class GameScene;
class QMediaPlayer;

class GameWindow : public QWidget
{
  //信号和槽使用的宏
  Q_OBJECT

public:
  explicit GameWindow(QWidget *parent = 0);
  ~GameWindow();

private slots:
  //游戏状态,升级,重新开始,奖品,背景音乐
  void gameWin();
  void gameOver();
  void updataScore(int upScore);
  void updataLevel();
  void renewGame();
  void setAward();
  void backgroundControler(bool on);
  void setGameWindowFocus();

private:
  void startLevel();
  //定时器
  QTimer *timer;
  GameScene* scene;
  int gameLevel;
  int gameScore;
  int maxGameScore;
  int gameLife;
  Ui::GameWindow *ui;
  //音乐控制
  QMediaPlayer* backgroundPlayer;
  QMediaPlayer* gameWinPlayer;
  QMediaPlayer* gameLosePlayer;
};

#endif // GAMEWINDOW_H
