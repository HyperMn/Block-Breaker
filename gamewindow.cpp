#include "gamewindow.h"
#include "ui_gamewindow.h"
#include"gamescene.h"
#include"QTimer"
#include<QDebug>
#include<QMediaPlayer>
#include<QMediaPlaylist>

//构造函数列表初始化
GameWindow::GameWindow(QWidget *parent) :
	QWidget(parent),
	timer(new QTimer(this)),
	scene(new GameScene(this)),
	gameLevel(0),
	gameScore(0),
	maxGameScore(0),
	gameLife(3),
	ui(new Ui::GameWindow),
	backgroundPlayer(new QMediaPlayer(this)),
	gameWinPlayer(new QMediaPlayer(this)),
	gameLosePlayer(new QMediaPlayer(this))
{
	ui->setupUi(this);
	ui->GameView->setScene(scene);
	timer->setInterval(1000);
	this->setFixedSize(this->size());
	this->renewGame();
	//调色板控制颜色
	QPalette palette;
	palette.setBrush(this->backgroundRole(),QBrush(QImage(":/background/image/background/background.png").scaled(this->size())));
	this->setPalette(palette);
	ui->GameView->setStyleSheet("background: transparent;border:0px");
	//音乐播放
	auto list=new QMediaPlaylist(this);
	list->addMedia(QUrl("qrc:/music/background.mp3"));
	list->setPlaybackMode(QMediaPlaylist::Loop);
	backgroundPlayer->setPlaylist(list);
	backgroundPlayer->setVolume(8);
	  backgroundPlayer->play();
	gameWinPlayer->setMedia(QUrl("qrc:/music/gameWin.mp3"));
	gameLosePlayer->setMedia(QUrl("qrc:/music/gameLose.mp3"));
	//连接信号和槽
	//定时器时间到,出现奖品
	connect(timer,SIGNAL(timeout()),this,SLOT(setAward()));
	connect(ui->backgroundCheckBox,SIGNAL(clicked(bool)),this,SLOT(backgroundControler(bool)));
	//控制音量的单选框
	connect(ui->backgroundCheckBox,SIGNAL(clicked(bool)),this,SLOT(setGameWindowFocus()));
}

GameWindow::~GameWindow()
{
	delete ui;
}

//游戏胜利
void GameWindow::gameWin()
{
	//中断信号和槽的联系
	this->disconnect(scene,SIGNAL(gameWin()),this,SLOT(gameWin()));
	this->disconnect(scene,SIGNAL(gameLose()),this,SLOT(gameOver()));
	this->disconnect(scene,SIGNAL(upScore(int)),this,SLOT(updataScore(int)));
	this->disconnect(scene,SIGNAL(gameContinue()),this->timer,SLOT(start()));
	this->disconnect(scene,SIGNAL(gamePause()),this->timer,SLOT(stop()));
	//增加游戏等级
	gameLevel++;
	gameWinPlayer->play();
	this->startLevel();
}

void GameWindow::gameOver()
{
	//游戏失败
	this->disconnect(scene,SIGNAL(gameWin()),this,SLOT(gameWin()));
	this->disconnect(scene,SIGNAL(gameLose()),this,SLOT(gameOver()));
	this->disconnect(scene,SIGNAL(upScore(int)),this,SLOT(updataScore(int)));
	this->disconnect(scene,SIGNAL(gameContinue()),this->timer,SLOT(start()));
	this->disconnect(scene,SIGNAL(gamePause()),this->timer,SLOT(stop()));
	gameLosePlayer->play();
	switch (gameLife--)
	{
	case 0:
		this->renewGame();
	break;
	case 1:
		ui->life1->hide();
		this->startLevel();
	break;
	case 2:
		ui->life2->hide();
		this->startLevel();
	break;
	case 3:
		ui->life3->hide();
		this->startLevel();
	break;
	}
}

//分数
void GameWindow::updataScore(int upScore)
{
	//QT字符串
	this->gameScore+=upScore;
	ui->score->setText(QString("得分:\n"
							   "    %1").arg(gameScore));
	if(this->gameScore>maxGameScore)
	{
		maxGameScore=gameScore;
		ui->maxScore->setText(QString("最高得分:\n"
									  "    %1").arg(gameScore));
	}
}

void GameWindow::updataLevel()
{
	//关卡
	ui->level->setText(QString("   第 %1 关").arg(gameLevel));
}

//重新开始
void GameWindow::renewGame()
{
	this->gameLevel=1;
	this->gameScore=0;
	this->gameLife=3;
	ui->life1->show();
	ui->life2->show();
	ui->life3->show();
	this->startLevel();
}
//奖品
void GameWindow::setAward()
{
	auto nextVal=ui->awardProgressBar->value()+sqrt(gameLevel)+1;
	if(nextVal>=100)
	{
		nextVal=0;
		this->scene->randSetGift();
	}
	ui->awardProgressBar->setValue(nextVal);
}

//开始游戏
void GameWindow::startLevel()
{
	//把UI界面的奖励进度条重置
	ui->awardProgressBar->setValue(0);
	updataLevel();
	//分数为0
	updataScore(0);
	//定时停止
	this->timer->stop();
	//建立新场景
	scene->deleteLater();
	scene=new GameScene(this);
	scene->selectGameLevel(gameLevel);
	ui->GameView->setScene(scene);
	//连接信号和槽
	this->connect(scene,SIGNAL(gameWin()),this,SLOT(gameWin()));
	this->connect(scene,SIGNAL(gameLose()),this,SLOT(gameOver()));
	this->connect(scene,SIGNAL(upScore(int)),this,SLOT(updataScore(int)));
	this->connect(scene,SIGNAL(gamePause()),this->timer,SLOT(stop()));
	this->connect(scene,SIGNAL(gameContinue()),this->timer,SLOT(start()));
	this->connect(scene,SIGNAL(gameContinue()),this->timer,SLOT(start()));
	this->connect(scene,SIGNAL(gamePause()),this->timer,SLOT(stop()));
}

//控制背景音乐的复选框
void GameWindow::backgroundControler(bool on)
{
	if(on)
	{
		backgroundPlayer->play();
	}
	else
	{
		backgroundPlayer->stop();
	}
}

void GameWindow::setGameWindowFocus()
{
	ui->GameView->setFocus();
}
