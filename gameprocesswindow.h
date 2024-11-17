#ifndef GAMEPROCESSWINDOW_H
#define GAMEPROCESSWINDOW_H
#include <QWidget>
#include <QLabel>
#include <QVBoxLayout>
#include "QGraphicsView"

//my includes
#include "customgamescene.h"

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


signals:

private:

    QLabel* m_score_label;//лейбл набранных очков
    QVBoxLayout* m_vLayout;//компановка для графического вида с сценой и лейблом
    CustomGameScene* m_custom_scene;//сцена игрового процесса
    QTimer *snake_speed_timer;//таймер по сигналу которого будет двигаться змея
    QGraphicsView* m_graphicsViev;

};

#endif // GAMEPROCESSWINDOW_H
