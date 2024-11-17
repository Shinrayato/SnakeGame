#ifndef CUSTOMGAMESCENE_H
#define CUSTOMGAMESCENE_H

#include <QGraphicsScene>
#include <QList>
#include "memory"

//my includes
#include "apple.h"
#include "snake.h"

class CustomGameScene : public QGraphicsScene
{
    Q_OBJECT
public:
    explicit CustomGameScene(int width, int height, QObject *parent = nullptr);
    ~CustomGameScene();
    void fillAllPosesList();//заполнение контейнра всех возможных позиций на поле
    void printScene(int width, int height);//отрисовка рамки и заднего фона сцены
    void drawSharp(int width, int height);//отрисвка решетки
    QList<QPointF>& getAllPosesList();//геттер для листа всех позиций
    void changeApplePos();//смена позиции яблока после съедения
    Snake* getSnake();

public slots:

    void slot_snake_Move();//слот движения змеи
    void slot_apple_eating();//слот поедания яблока
    void slot_game_over();//слот завершения игры

signals:

    void signal_score_refresh(int score_count);//сигнал обновления счетчика очков
    void signal_game_over(int score_count);//сигнал завершения игры
    void signal_stop_snake();//сигнал остановки змеи

private:

    QList<QPointF> m_all_poses;//лист со всеми возможными позициями на доске
    int side_of_rect_pos;//сторона одной клеточки
    Apple *m_aplle;//яблоко
    std::unique_ptr<Snake> m_snake;//змея
    int m_score;//очки набранные игроком за эту игру

};

#endif // CUSTOMGAMESCENE_H
