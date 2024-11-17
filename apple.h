#ifndef APPLE_H
#define APPLE_H

#include <QObject>
#include <QGraphicsItem>
#include <QPainter>

class Apple : public QObject, public QGraphicsItem
{
    Q_OBJECT
public:
    explicit Apple(QObject *parent = nullptr);
    ~Apple();
signals:

private:
    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)override;
};

#endif // APPLE_H
