#ifndef STRETCHPLANKBRICK_H
#define STRETCHPLANKBRICK_H

#include"abstractsurprisingbrick.h"

class StretchPlankBrick:public AbstractSurprisingBrick
{
  Q_OBJECT
public:
  StretchPlankBrick(QGraphicsItem* parent=nullptr);
  ~StretchPlankBrick();
  void setAward()override;
};

#endif // STRETCHPLANKBRICK_H
