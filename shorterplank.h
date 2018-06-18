#ifndef SHORTERPLANK_H
#define SHORTERPLANK_H

#include"abstractplank.h"

class ShorterPlank:public AbstractPlank
{
public:
  ShorterPlank(QGraphicsItem* parent=nullptr);
  QRectF boundingRect()const override;
  void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)override;
private:
  static const QImage outlook;
};

#endif // SHORTERPLANK_H
