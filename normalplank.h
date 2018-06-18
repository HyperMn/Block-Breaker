#ifndef NORMALPLANK_H
#define NORMALPLANK_H

#include"abstractplank.h"

class NormalPlank:public AbstractPlank
{
public:
  NormalPlank(QGraphicsItem* parent=nullptr);
  QRectF boundingRect()const override;
  void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)override;
private:
  static const QImage outlook;
};

#endif // NORMALPLANK_H
