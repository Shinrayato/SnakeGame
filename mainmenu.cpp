#include "mainmenu.h"


MainMenu::MainMenu(QWidget *parent): QWidget(parent)
{
    //выделение памяти под все виджеты меню
    m_gameStart_button = new MyButton("Game Start", this);
    m_showRecord_button = new MyButton("Show Records", this);
    m_exitGame_button = new MyButton("Exit Game", this);
    m_name_of_game = new QLabel("Snake the Game", this );
    m_vLayout = new QVBoxLayout(this); //компоновка для объединения компоновки с кнопками и названием игры
    m_vLayout->setAlignment(Qt::AlignCenter);


    m_name_of_game->setStyleSheet("font-size: 45px;");

    //установка их в компоновку главного меню игры

    m_vLayout->addWidget(m_name_of_game);
    m_vLayout->setSpacing(50);
    m_vLayout->addWidget(m_gameStart_button);
    m_vLayout->setSpacing(50);
    m_vLayout->addWidget(m_showRecord_button);
    m_vLayout->setSpacing(50);
    m_vLayout->addWidget(m_exitGame_button);
    m_vLayout->setSpacing(50);

    this->setLayout(m_vLayout);


    //соединяем сингнал клика по кнопке рекордов с слотом вызова меню рекордов
    connect(m_showRecord_button, &MyButton::clicked, this, &MainMenu::slot_call_record_menu);


}

MainMenu::~MainMenu()
{

}

MyButton *MainMenu::getStartButton()
{
    return m_gameStart_button;
}

MyButton *MainMenu::getRecordButton()
{
    return m_showRecord_button;
}

MyButton *MainMenu::getExitButton()
{
    return m_exitGame_button;
}

void MainMenu::slot_call_record_menu()
{
    this->hide();//скрываем окно
    emit signal_call_record_menu(CalledFrom::MainMenu);//излучаем сигнал для таблицы рекордов
}
