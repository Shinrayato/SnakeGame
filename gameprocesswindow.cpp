#include "gameprocesswindow.h"
#include "QTimer"



GameProcessWindow::GameProcessWindow(QWidget *parent): QWidget{parent}
{
    m_vLayout = new QVBoxLayout(this);//компоновка для лейблпа и графического вида
    m_score_label = new QLabel(this);//лейбл отображения очков игрока
    m_graphicsViev = new QGraphicsView(this);//графический вид игрового процесса
    m_graphicsViev->resize(500,500);//заданы размеры графического вида
    //заданы размеры графической сцены
    m_custom_scene = new CustomGameScene(m_graphicsViev->width()-100, m_graphicsViev->height()-100, m_graphicsViev);

    m_graphicsViev->setRenderHint(QPainter::Antialiasing);//добавлено сглаживание

    this->setLayout(m_vLayout);//установка компановки
    m_score_label->setText("SCORE " + QString::number(0));//текс лейбла с очками
    m_score_label->setStyleSheet("font-size: 20px;");//размер шрифта
    m_vLayout->addWidget(m_score_label);//установка лейбла с очками в компоновку
    m_graphicsViev->setScene(m_custom_scene);//установка сцены в графический вид
    m_vLayout->addWidget(m_graphicsViev);//установка графического вида в компоновку
    m_vLayout->setAlignment(Qt::AlignCenter);

    snake_speed_timer = new QTimer(this);//создание таймера скорости змеи

    //соединяем таймер с слотом движения змеи
    connect(snake_speed_timer, &QTimer::timeout, m_custom_scene, &CustomGameScene::slot_snake_Move);
    //соединяем сигнал обновления количества очков с слотом установки очков в лейбл
    connect(m_custom_scene, &CustomGameScene::signal_score_refresh, this, &GameProcessWindow::slot_set_score);
    //соединяем сигнал останоки змеи от сцены с сигналом останоки таймера
    connect(m_custom_scene, &CustomGameScene::signal_stop_snake, snake_speed_timer, &QTimer::stop);

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
    m_custom_scene->getSnake()->GetHead()->grabKeyboard();
    m_graphicsViev->setFocus();
}

void GameProcessWindow::slot_set_score(int score_count)//слот обновления счетчика очков
{
    //обновление счетчика очков
    std::string value = "SCORE " + std::to_string(score_count);
    m_score_label->setText(value.c_str());
}
