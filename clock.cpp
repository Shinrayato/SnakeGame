#include "clock.h"

Clock::Clock()
{
    connect(&m_timer, &QTimer::timeout, this, &Clock::slot_set_new_time);
    m_second_count = 0;


}

void Clock::startClockTimer()
{
   m_timer.start(1000);
}

void Clock::updateSecondCount()
{
    m_second_count = 0;
}

void Clock::slot_set_new_time()
{
    emit signal_set_new_time(++m_second_count);
}

void Clock::slot_timer_stop()
{
    m_timer.stop();
}
