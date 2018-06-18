#ifndef SLOWPLANK_H
#define SLOWPLANK_H

#include"abstractplank.h"

class SlowPlank:public AbstractPlank
{
public:
  SlowPlank(QGraphicsItem* parent=nullptr);
  QRectF boundingRect()const override;
  void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)override;
private:
  static const QImage outlook;
};

#endif // SLOWPLANK_H
