#ifndef GAMEOVERMENU_H
#define GAMEOVERMENU_H

#include <QWidget>
#include <QVBoxLayout>
#include <QLabel>
#include "QHBoxLayout"

//my includes
#include "mybutton.h"
#include "primitives.h"

class GameOverMenu : public QWidget
{
    Q_OBJECT
public:
    explicit GameOverMenu(QWidget *parent = nullptr);
    MyButton* getExitButton();
    MyButton* getRestartButton();

signals:
     void signal_call_record_menu(CalledFrom this_window);

public slots:

    void slot_call_record_menu();
    void slot_game_over_menu(const GameStatistics& accepted_statistics);

private:

    MyButton *m_retry_button;//кнопка рестарта игры
    MyButton *m_show_records_button;//кнопка показа рекордов игрока
    MyButton *m_exit_game_button;//кнопка выхода из игры
    QLabel   *m_game_over_label;//лейбл для отображения надписи о конце игры
    QLabel   *m_total_score_label;//лейбл для вывода очков на экран
    QLabel   *m_time_label;//лейбл для отображения итогового времени игры
    QVBoxLayout *m_layout;
    QHBoxLayout *m_layout_for_game_stats;
    QHBoxLayout *m_hlayout_for_buttons;
    QVBoxLayout *m_vlayout_for_buttons;

};

#endif // GAMEOVERMENU_H
