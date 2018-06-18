#ifndef LONGERPLANK_H
#define LONGERPLANK_H

#include"abstractplank.h"

class LongerPlank:public AbstractPlank
{
public:
  LongerPlank(QGraphicsItem* parent=nullptr);
  QRectF boundingRect()const override;
  void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)override;
private:
  static const QImage outlook;
};

#endif // LONGERPLANK_H
