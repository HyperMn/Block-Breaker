#ifndef SHRINKPLANKBRICK_H
#define SHRINKPLANKBRICK_H

#include<abstractsurprisingbrick.h>

class ShrinkPlankBrick:public AbstractSurprisingBrick
{
    Q_OBJECT
public:
  ShrinkPlankBrick(QGraphicsItem* parent=nullptr);
  ~ShrinkPlankBrick();
  void setAward()override;
};

#endif // SHRINKPLANKBRICK_H
