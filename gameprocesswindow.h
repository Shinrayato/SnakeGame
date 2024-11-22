#ifndef GAMEPROCESSWINDOW_H
#define GAMEPROCESSWINDOW_H
#include <QWidget>
#include <QLabel>
#include <QVBoxLayout>
#include "QGraphicsView"
#include "QHBoxLayout"

//my includes
#include "customgamescene.h"
#include "clock.h"


class GameProcessWindow : public QWidget
{
    Q_OBJECT
public:

    explicit GameProcessWindow(QWidget *parent = nullptr);
    ~GameProcessWindow();
    CustomGameScene* getCustomScene();

public slots:
    void slot_game_start();//слот старта игры
    void slot_set_score(int score_count);//слот обновления счетчика очков
    void slot_set_new_time(const int time_now_in_seconds);//слот для принятия игрового времени
    void slot_game_restart();//слот рестарта игры
    void slot_send_game_statistics();//слот отправки игровой статистики


signals:

    void signal_send_game_statistics_over(const GameStatistics& send_statistics);//сигнал для отправки статистики

private:

    QLabel* m_score_label;//лейбл набранных очков
    QLabel* m_time_label;//лейбл подсчета времени с старта игры игрового времени
    QHBoxLayout *m_layout_game_parametres;//компоновка для очков и времени
    QVBoxLayout* m_vLayout;//компановка для графического вида с сценой и лейблом
    CustomGameScene* m_custom_scene;//сцена игрового процесса
    QTimer *snake_speed_timer;//таймер по сигналу которого будет двигаться змея
    QGraphicsView* m_graphicsViev;//графический вид игрового процесса
    Clock m_clock;
    GameStatistics m_statistics;



};

#endif // GAMEPROCESSWINDOW_H
