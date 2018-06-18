#ifndef ACCELERATEPLANKBRICK_H
#define ACCELERATEPLANKBRICK_H

#include"abstractsurprisingbrick.h"

class AcceleratePlankBrick:public AbstractSurprisingBrick
{
  Q_OBJECT
public:
  AcceleratePlankBrick(QGraphicsItem* parent=nullptr);
  ~AcceleratePlankBrick();
  void setAward()override;
};

#endif // ACCELERATEPLANKBRICK_H
