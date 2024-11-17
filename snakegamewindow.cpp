#include "snakegamewindow.h"
#include "ui_snakegamewindow.h"
#include "qDebug"//;
#include "QPoint"

SnakeGameWindow::SnakeGameWindow(const QApplication* app, QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::SnakeGameWindow)
{
    ui->setupUi(this);
    this->resize(500, 600);

    vlaout = new QVBoxLayout(this);//компоновка для установки в всех игровых виджетов
    m_game_process_window = new GameProcessWindow(this);//выделение памяти под виджет игрового процесса
    m_main_menu = new MainMenu(this); //выделение памяти под виджет главного меню игры
    m_game_over_menu = new GameOverMenu(this);//выделение памяти под виджет главного меню игры

    //установка компоновки для всех игровых виджетов в форму
    ui->centralwidget->setLayout(vlaout);

    //добавление в компоновку всех игровых виджетов
    vlaout->addWidget(m_main_menu);
    vlaout->addWidget(m_game_process_window);
    vlaout->addWidget(m_game_over_menu);

    m_game_over_menu->hide();
    m_game_process_window->hide();//скрываем виджет игрового процесса по началу
    //m_main_menu->hide();


    //соединяем сигнал от кнопки старта игры с методом сокрытия окна
    connect(m_main_menu->getStartButton(), &MyButton::clicked, m_main_menu, &MainMenu::hide);
    //соединяем сигнал от кнопки старта игры с слотом старта игры у окна игрового процесса
    connect(m_main_menu->getStartButton(), &MyButton::clicked, m_game_process_window, &GameProcessWindow::slot_game_start);
    //соединяем сигнал от кнопки завершения игры из главного меню с методом закрытия приложения
    connect(m_main_menu->getExitButton(), &MyButton::clicked, app, &QApplication::closeAllWindows);
    //соединяем сигнал от кнопки завершения игры из меню конца игры с методом закрытия приложения
    connect(m_game_over_menu->getExitButton(), &MyButton::clicked, app, &QApplication::closeAllWindows);
    //соединяем сигнал от сцены о завершении игры с методом закрытия окна
    connect(m_game_process_window->getCustomScene(), &CustomGameScene::signal_game_over, m_game_process_window, &GameProcessWindow::hide);
    //соединяем сигнал от сцены о завершении игры с слотом вывода окна завершения игры
    connect(m_game_process_window->getCustomScene(), &CustomGameScene::signal_game_over, m_game_over_menu, &GameOverMenu::slot_game_over_menu);
}

SnakeGameWindow::~SnakeGameWindow()
{
    delete ui;
}



