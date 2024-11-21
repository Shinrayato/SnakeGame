#include "customgamescene.h"
#include "QTimer"


CustomGameScene::CustomGameScene(int width, int height, QObject *parent): QGraphicsScene{parent}
{
    //начальное колчество очков
    m_score = 0;
    //создание рамки сцены
    this->printScene(width,height);
    //зарисовка решетки
    this->drawSharp(width,height);
    //запонение списка всех возможных позиций на сцене
    this->fillAllPosesList();
    //создание яблока
    m_aplle = new Apple();
    //добавление яблока на сцену
    this->addItem(m_aplle);
    //установка яблока в позицию на сцене выбранную из списка всех позиций
    m_aplle->setPos(this->m_all_poses.at(400/3));
    //создание змеи
    m_snake = std::make_unique<Snake>(this->m_all_poses.at(400/2 + 10), this->m_all_poses.at(400/2 + 9));
    //добавление головы на сцену
    this->addItem(m_snake->GetHead());
    //добавление хвоста на сцену
    this->addItem(&m_snake->GetTail()->getTailList().front());

    //соединяем сигнал от головы о поедании яблока с слотом поедания яблока
    connect(m_snake->GetHead(), &Head::signal_apple_eating, this, &CustomGameScene::slot_apple_eating);

    //соединяем сигнал от головы о поедании хвоста с слотом завершения игры
    connect(m_snake->GetHead(), &Head::signal_tail_eating, this, &CustomGameScene::slot_game_over);
}

CustomGameScene::~CustomGameScene()
{

}

void CustomGameScene::fillAllPosesList()//заполнение контейнра всех возможных позиций на поле
{
    int pos_coordinate_count = side_of_rect_pos * side_of_rect_pos;

    for (int y = side_of_rect_pos/2; y < pos_coordinate_count; y+= side_of_rect_pos)
    {
        for (int x = side_of_rect_pos/2; x < pos_coordinate_count; x+= side_of_rect_pos)
        {
            m_all_poses.push_back(QPointF(x,y));
        }
    }
}

void CustomGameScene::printScene(int width, int height)//отрисовка рамки и заднего фона сцены
{
    //создание рамки сцены
    this->addRect(0,0,width, height, QPen(Qt::black), QBrush(Qt::gray));
    this->addLine(0,0, width,0, QPen(Qt::black));
    this->addLine(0,height, width,height, QPen(Qt::black));
    this->addLine(0,0, 0,height,QPen(Qt::black));
    this->addLine(width,0, width,height,QPen(Qt::black));
}

void CustomGameScene::drawSharp(int width, int height)//отрисвка решетки
{
    //зарисовка решетки
    side_of_rect_pos = width/20;

    for (int i = side_of_rect_pos; i < height; i+=side_of_rect_pos)
    {
        this->addLine(0,i, width,i, QPen(Qt::black));
        this->addLine(i,0, i,height, QPen(Qt::black));
    }
}

QList<QPointF> &CustomGameScene::getAllPosesList()
{
    return this->m_all_poses;
}

void CustomGameScene::changeApplePos()
{

    while(true)
    {
        //новая позиция для яблока
        auto i = m_all_poses.begin();
        i+=(rand()% m_all_poses.size());
        m_aplle->setPos(*i);

        //проверка позиции на совпадение с головой и всеми элементами хвоста
        if(m_aplle->pos() == m_snake->GetHead()->pos())
        {
            continue;
        }

        for (auto it = m_snake->GetTail()->getTailList().begin(); it != m_snake->GetTail()->getTailList().end(); ++it)
        {
            if(it->pos() ==  m_aplle->pos())
            {
                continue;
            }
        }

        break;
    }

}

Snake* CustomGameScene::getSnake()
{
    return &*m_snake;
}

void CustomGameScene::setupSartObjPos()
{

    //очистка сцены от элементов хвоста
    for (auto i =  m_snake->GetTail()->getTailList().begin(); i != m_snake->GetTail()->getTailList().end(); ++i)
    {
        this->removeItem(&*i);
    }

    m_snake->GetTail()->getTailList().clear();//удаление хвоста змеи

    //установка объектов яблока и змени в начальное положение
    m_snake->GetHead()->setPos(m_all_poses.at(400/2 + 10));
    m_snake->GetTail()->getTailList().emplace_back(m_all_poses.at(400/2 + 9));
    this->addItem(m_snake->GetTail()->getEndofTail());
    m_aplle->setPos(this->m_all_poses.at(400/3));

}

int& CustomGameScene::getScore()
{
    return m_score;
}

void CustomGameScene::slot_snake_Move()
{
    m_snake->moveSnake(m_aplle->pos());
}

void CustomGameScene::slot_apple_eating()
{ 
    //добавление на сцену нового элемента хвоста
    this->addItem(this->m_snake->GetTail()->getEndofTail());
    changeApplePos();
    //излучение сигнала обновления очков
    emit signal_score_refresh(m_score+=1);
}

void CustomGameScene::slot_game_over()
{
    emit signal_stop_snake();
    //излучение сигнала окончания игры, передача количества очков лейблу с набранными очками
    emit signal_game_over(m_score);
    //излучение сигнала остановки таймера подсчета времени
    emit signal_stop_timer();
}


