#ifndef TAILPART_H
#define TAILPART_H

#include <QObject>
#include <QGraphicsItem>
#include <QPainter>

class TailPart: public QObject, public QGraphicsItem
{
    Q_OBJECT
public:
    explicit TailPart(const QPointF &pos, QObject *parent = nullptr);
    ~TailPart();


private:
    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)override;
};

#endif // TAILPART_H
