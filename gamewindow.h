#ifndef GAMEWINDOW_H
#define GAMEWINDOW_H

#include <QWidget>

namespace Ui {
  class GameWindow;
}

class GameScene;
class QMediaPlayer;

class GameWindow : public QWidget
{
  Q_OBJECT

public:
  explicit GameWindow(QWidget *parent = 0);
  ~GameWindow();

private slots:
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

  QTimer *timer;
  GameScene* scene;
  int gameLevel;
  int gameScore;
  int maxGameScore;
  int gameLife;
  Ui::GameWindow *ui;
  QMediaPlayer* backgroundPlayer;
  QMediaPlayer* gameWinPlayer;
  QMediaPlayer* gameLosePlayer;
};

#endif // GAMEWINDOW_H
