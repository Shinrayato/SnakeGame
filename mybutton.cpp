#include "mybutton.h"



MyButton::MyButton(const QString &text, QWidget *parent): QPushButton(text, parent)
{
    this->setStyleSheet("font-size:  40px; background-color: rgb( 34, 139, 34); border: 3px solid black; border-radius: 10px;");
    //this->setStyleSheet(" background-color: #3cbaa2");
    this->setMouseTracking(true);
}

MyButton::~MyButton()
{
  qDebug() << "destructor working";
}

void MyButton::enterEvent(QEnterEvent *event)
{
    this->setStyleSheet("font-size:  40px; background-color: rgb( 164, 139, 34); border: 3px solid black; border-radius: 10px;");
}

void MyButton::leaveEvent(QEvent *event)
{
    this->setStyleSheet("font-size:  40px; background-color: rgb( 34, 139, 34); border: 3px solid black; border-radius: 10px;");
}

void MyButton::mousePressEvent(QMouseEvent *event)
{
    this->setStyleSheet("font-size:  40px; background-color: red; border: 3px solid black; border-radius: 10px;");

}

void MyButton::mouseReleaseEvent(QMouseEvent *event)
{
    this->setStyleSheet("font-size:  40px; background-color: rgb( 164, 139, 34); border: 3px solid black; border-radius: 10px;");

    if (this->rect().contains(event->pos()))
    {
        emit clicked();
    }
}


