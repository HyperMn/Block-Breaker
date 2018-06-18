#ifndef FASTPLANK_H
#define FASTPLANK_H

#include"abstractplank.h"

class FastPlank:public AbstractPlank
{
public:
  FastPlank(QGraphicsItem* parent=nullptr);
  QRectF boundingRect()const override;
  void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)override;
private:
  static const QImage outlook;
};

#endif // FASTPLANK_H
