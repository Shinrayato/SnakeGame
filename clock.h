#ifndef CLOCK_H
#define CLOCK_H


#include "QTimer"
#include "QObject"

class Clock: public QObject
{

    Q_OBJECT

public:

    Clock();
    void startClockTimer();//метод запуска часов

    void updateSecondCount();

signals:

    void signal_set_new_time(const int time);//сигнал передающий время


public slots:

    void slot_set_new_time();//слот для подсчета времени по таймеру
    void slot_timer_stop();

private:

    QTimer m_timer;//структура отвечающая за время, секунды, минуты, часы
    int m_second_count;//количество секунд

};

#endif // CLOCK_H
