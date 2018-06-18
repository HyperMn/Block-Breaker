#ifndef DECELERATEPLANKBRICK_H
#define DECELERATEPLANKBRICK_H

#include"abstractsurprisingbrick.h"

class DeceleratePlankBrick:public AbstractSurprisingBrick
{
  Q_OBJECT
public:
  DeceleratePlankBrick(QGraphicsItem* parent=nullptr);
  ~DeceleratePlankBrick();
  void setAward()override;
};

#endif // DECELERATEPLANKBRICK_H
