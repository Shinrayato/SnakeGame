#include "tailpart.h"

TailPart::TailPart(const QPointF &pos, QObject* parent):QObject(parent), QGraphicsItem()
{
    this->setPos(pos);
}

TailPart::~TailPart()
{
 qDebug() << "Destructor tail part";
}


QRectF TailPart::boundingRect() const
{
return QRectF(-10,-10,20,20);
}

void TailPart::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->setBrush(Qt::darkGreen);
    painter->drawRect(-10,-10,20,20);
    painter->setRenderHint(QPainter::Antialiasing);
    Q_UNUSED(option);
    Q_UNUSED(widget);
}
