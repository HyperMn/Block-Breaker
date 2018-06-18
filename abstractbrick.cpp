#include "abstractbrick.h"
#include<QPainter>

AbstractBrick::AbstractBrick(int totalHittingTime,QColor outlook, QGraphicsItem* parent):
  QGraphicsObject(parent),
  hittingTimeLeft(totalHittingTime),
  outlook(outlook)
{

}
//void play()
//{
//  QMediaPlayer *play=new QMediaPlayer;
//  play->setMedia(QUrl::fromLocalFile("C:\\Users\\lx\\Desktop\\11000游戏常用音效-toggleoff_爱给网_2gei_com.wav"));
//  play->setVolume(10);
//  play->play();
//  QObject::connect(play,SIGNAL(mediaStatusChanged(QMediaPlayer::MediaStatus)),play,SLOT(deleteLater()));
//}

AbstractBrick::~AbstractBrick()
{
//  QMediaPlayer *play=new QMediaPlayer;
//  play->setMedia(QUrl::fromLocalFile("C:\\Users\\lx\\Desktop\\11000游戏常用音效-toggleoff_爱给网_2gei_com.wav"));
//  play->setVolume(10);
//  play->play();
//  QSound::play(":/music/C:/Users/lx/Pictures/游戏素材/BlockBreaker/music/brickDestroyed.wav");
//  QtConcurrent::run(play);
}

QRectF AbstractBrick::boundingRect() const
{
  return QRectF(-20,-15,40,30);
}

QPainterPath AbstractBrick::shape() const
{
  QPainterPath path;
  path.addRect(this->boundingRect());
  return path;
}

void AbstractBrick::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget)
{
  Q_UNUSED(option)
  Q_UNUSED(widget)
  painter->setBrushOrigin(this->boundingRect().topLeft());
  painter->fillPath(this->shape(),this->outlook);
}

void AbstractBrick::collidingWithBall()
{
  hittingTimeLeft--;
  if(hittingTimeLeft==0)
  {
    this->deleteLater();
  }
}
