#ifndef HEAD_H
#define HEAD_H

#include <QObject>
#include <QGraphicsItem>
#include <QPainter>
#include <QKeyEvent>

//my includes
#include "primitives.h" //подключение заголовка с перечислениями выбора направления

class Head : public QObject, public QGraphicsItem
{
    Q_OBJECT
public:
    explicit Head(const QPointF& head_pos,QObject *parent = nullptr);
    ~Head();
    const QPointF& Move();
    void setPreviousPos(const QPointF &previous_pos);
    const QPointF& getPreviousPos();


private:
    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)override;
    //переопределение событий нажатия кнопок для головы змеи, голова отвечает за выбор направления движения
    void keyPressEvent(QKeyEvent *event) override;
    void keyReleaseEvent(QKeyEvent *event) override;
    void checkDirUp();//функция проверки позиции при движении вверх
    void checkDirDown();//функция проверки позиции при движении вниз
    void checkDirLeft();//функция проверки позиции при движении влево
    void checkDirRight();//функция проверки позиции при движении вправо




    //направление движение змеи в данный момент
    Dir m_dir_now;
    //предыдущая позиция головы, для передачи хвосту и проверки при движении
    QPointF m_previous_pos;

signals:

    void signal_apple_eating();
    void signal_tail_eating();

};

#endif // HEAD_H
