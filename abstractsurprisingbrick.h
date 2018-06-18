#ifndef ABSTRACTSURINGBRICK_H
#define ABSTRACTSURINGBRICK_H

#include"abstractbrick.h"
#include"gift.h"

class AbstractSurprisingBrick : public AbstractBrick
{
  Q_OBJECT
public:
  AbstractSurprisingBrick(int hittingTimeLeft,QColor outlook,QGraphicsItem* parent=nullptr);
  virtual ~AbstractSurprisingBrick();
signals:
  void awardSent(Gift* gift);
protected slots:
  virtual void setAward()=0;
};

#endif // ABSTRACTSURINGBRICK_H
