#ifndef MYBUTTON_H
#define MYBUTTON_H

#include <QPushButton>
#include <QMouseEvent>

class MyButton : public QPushButton
{
    Q_OBJECT
public:
    MyButton(const QString &text, QWidget *parent = nullptr);
    ~MyButton();

    void enterEvent(QEnterEvent *event) override;

    void leaveEvent(QEvent *event) override;

    void mousePressEvent(QMouseEvent *event) override;

    void mouseReleaseEvent(QMouseEvent *event) override;

    void updateColorButton();
};

#endif // MYBUTTON_H
