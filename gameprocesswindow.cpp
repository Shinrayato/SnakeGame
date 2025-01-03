#include "gameprocesswindow.h"
#include "QTimer"



GameProcessWindow::GameProcessWindow(QWidget *parent): QWidget{parent}
{
    m_vLayout = new QVBoxLayout(this);//компоновка для лейблпа и графического вида
    m_layout_game_parametres = new QHBoxLayout(this);//компоновка для очков и времени
    m_time_label = new QLabel(this);//лейбл подсчета времени с старта игры игрового времени
    m_score_label = new QLabel(this);//лейбл отображения очков игрока
    m_graphicsViev = new QGraphicsView(this);//графический вид игрового процесса
    m_graphicsViev->resize(500,500);//заданы размеры графического вида
    //заданы размеры графической сцены
    m_custom_scene = new CustomGameScene(m_graphicsViev->width()-100, m_graphicsViev->height()-100, m_graphicsViev);

    m_graphicsViev->setRenderHint(QPainter::Antialiasing);//добавлено сглаживание
    m_graphicsViev->setBackgroundBrush(QBrush(Qt::darkGray));



    this->setLayout(m_vLayout);//установка компановки
    m_score_label->setText("SCORE " + QString::number(0));//текст лейбла с очками
    m_score_label->setStyleSheet("font-size: 20px;");//размер шрифта

    m_time_label->setText("0 : 0 : 0");//текст лейбла со временем
    m_time_label->setStyleSheet("font-size: 20px;");//размер шрифта

    m_graphicsViev->setScene(m_custom_scene);//установка сцены в графический вид

    m_layout_game_parametres->addWidget(m_score_label);//установка в компоновку игровых параметров лейбла с очками
    m_layout_game_parametres->addWidget(m_time_label);//установка в компоновку игровых параметров лейбла со вреименем
    m_vLayout->addLayout(m_layout_game_parametres);//установка лейбла с очками в компоновку
    m_vLayout->addWidget(m_graphicsViev);//установка графического вида в компоновку
    m_vLayout->setAlignment(Qt::AlignCenter);//выранивание по центру

    snake_speed_timer = new QTimer(this);//создание таймера скорости змеи

    //соединяем таймер с слотом движения змеи
    connect(snake_speed_timer, &QTimer::timeout, m_custom_scene, &CustomGameScene::slot_snake_Move);
    //соединяем сигнал обновления количества очков с слотом установки очков в лейбл
    connect(m_custom_scene, &CustomGameScene::signal_score_refresh, this, &GameProcessWindow::slot_set_score);
    //соединяем сигнал останоки змеи от сцены с сигналом останоки таймера
    connect(m_custom_scene, &CustomGameScene::signal_stop_snake, snake_speed_timer, &QTimer::stop);
    //соединяем сигнал подсчета времени с слотом установки времени в лайбл
    connect(&m_clock, &Clock::signal_set_new_time, this, &GameProcessWindow::slot_set_new_time);
    //соединяем сигнал остановки подсчета времени с слотом остановки времени
    connect(m_custom_scene, &CustomGameScene::signal_stop_timer, &m_clock, &Clock::slot_timer_stop);
    //соединяем сигнал о завершении игры от сцены с сигралом с слотом отправки ировой статистики
    connect(m_custom_scene, &CustomGameScene::signal_game_over, this, &GameProcessWindow::slot_send_game_statistics);

    m_statistics.time = 0;
    m_statistics.score = 0;


}

GameProcessWindow::~GameProcessWindow()
{

}

CustomGameScene *GameProcessWindow::getCustomScene()
{
    return m_custom_scene;
}

void GameProcessWindow::slot_game_start()//слот старта игры
{
    this->show();//отображение виджета игрового процесса в главном окне
    snake_speed_timer->start(300);//запуск таймера скорости
    //установка фокуса
    m_custom_scene->getSnake()->GetHead()->grabKeyboard();
    m_graphicsViev->setFocus();
    m_clock.startClockTimer();//запуск таймера часов
}

void GameProcessWindow::slot_set_score(int score_count)//слот обновления счетчика очков
{
    m_statistics.score += score_count;
    //обновление счетчика очков
    std::string value = "SCORE " + std::to_string(m_statistics.score);
    m_score_label->setText(value.c_str());
}

void GameProcessWindow::slot_set_new_time(const int time_now_in_seconds)
{
    m_statistics.time = time_now_in_seconds;//обновляем статистику времени

    int seconds = time_now_in_seconds;

    int time_in_h = 0;
    int time_in_m = 0;
    int time_in_s = 0;

    std::string time;

    if(seconds >= 3600)
    {
        time_in_h = seconds/3600;
        seconds %= 3600;
    }
    if(seconds >= 60)
    {
        time_in_m = seconds/60;
        seconds %= 60;
    }
    if(seconds < 60)
    {
        time_in_s = seconds;
    }

    time = std::to_string(time_in_h) + " : " + std::to_string(time_in_m) + " : " + std::to_string(time_in_s);

    this->m_time_label->setText(time.c_str());
}

void GameProcessWindow::slot_game_restart()//слот рестарта игры
{
    this->show();//вызываем отображение окна в главном виджете
    //установка фокуса
    m_custom_scene->getSnake()->GetHead()->grabKeyboard();
    m_graphicsViev->setFocus();

    //обнуление игрового времени и очков
    m_statistics.time = 0;
    m_statistics.score = 0;

    m_clock.updateSecondCount();//обновление счетчиа времени
    m_custom_scene->setupSartObjPos();//обновление позиций

    m_score_label->setText("SCORE " + QString::number(0));//обнуление счетчика очков

    m_time_label->setText("0 : 0 : 0");//обнуление счетска времени


    snake_speed_timer->start();//запуск таймера передвижения змеи
    m_clock.startClockTimer();//запуск таймера подсчета игрового времени



}

void GameProcessWindow::slot_send_game_statistics()
{
    emit signal_send_game_statistics_over(m_statistics);
}
