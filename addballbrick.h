#ifndef ADDBALLBRICK_H
#define ADDBALLBRICK_H

#include"abstractsurprisingbrick.h"

class AddBallBrick:public AbstractSurprisingBrick
{
  Q_OBJECT
public:
  AddBallBrick(QGraphicsItem* parent=nullptr);
  ~AddBallBrick();
  void setAward()override;
};

#endif // ADDBALLBRICK_H
