#include "apple.h"
#include "qDebug"

Apple::Apple(QObject *parent) : QObject(parent), QGraphicsItem()
{

}

Apple::~Apple()
{
    //qDebug() << "destructor working";
}

QRectF Apple::boundingRect() const
{
    return QRectF(-10,-10,20,20);
}

void Apple::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->setBrush(Qt::red);
    painter->drawEllipse(-10,-10,20,20);
    painter->setRenderHint(QPainter::Antialiasing);
    Q_UNUSED(option);
    Q_UNUSED(widget);
}


