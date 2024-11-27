#include "snakegamewindow.h"
#include "ui_snakegamewindow.h"
#include "qDebug"//;
#include "QPoint"

SnakeGameWindow::SnakeGameWindow(QApplication* app, QWidget *parent) : QMainWindow(parent), ui(new Ui::SnakeGameWindow)
{
    ui->setupUi(this);
    this->resize(500, 600);
    this->setFixedSize(500, 600);
    m_app = app;

    vlaout = new QVBoxLayout(this);//компоновка для установки в всех игровых виджетов
    m_game_process_window = new GameProcessWindow(this);//выделение памяти под виджет игрового процесса
    m_main_menu = new class MainMenu(this); //выделение памяти под виджет главного меню игры
    m_game_over_menu = new class GameOverMenu(this);//выделение памяти под виджет главного меню игры

    //установка компоновки для всех игровых виджетов в форму
    ui->centralwidget->setLayout(vlaout);

    //добавление в компоновку всех игровых виджетов
    vlaout->addWidget(m_main_menu);
    vlaout->addWidget(m_game_process_window);
    vlaout->addWidget(m_game_over_menu);


    m_game_over_menu->hide();
    m_game_process_window->hide();//скрываем виджет игрового процесса по началу
    //m_main_menu->hide();

    std::ifstream file_input;

    file_input.open("Record.txt");

    if(file_input.peek() == EOF)
    {
        for (int i = 0; i < 10; ++i)
        {
            GameStatistics record;
            record.score = 0;
            record.time = 0;
            m_records_list.push_back(record);
        }
    }
    else
    {
        GameStatistics record;
        while(file_input.read((char*)&record, sizeof(GameStatistics)))
        {
          m_records_list.push_back(record);
        }

    }

    file_input.close();

    m_records_window = new RecordsWindow(m_records_list, this);
    vlaout->addWidget(m_records_window);
    m_records_window->hide();

    //установка цвета фона виджета
    //QPalette pal = QPalette();
    //pal.setColor(QPalette::Window, Qt::darkGray);
    //this->setAutoFillBackground((true));
    //this->setPalette(pal);

    this->setStyleSheet("background-color: darkGray");


    //соединяем сигнал от кнопки старта игры с методом сокрытия окна
    connect(m_main_menu->getStartButton(), &MyButton::clicked, m_main_menu, &MainMenu::hide);
    //соединяем сигнал от кнопки старта игры с слотом старта игры у окна игрового процесса
    connect(m_main_menu->getStartButton(), &MyButton::clicked, m_game_process_window, &GameProcessWindow::slot_game_start);
    //соединяем сигнал от кнопки завершения игры из главного меню с методом закрытия приложения
    connect(m_main_menu->getExitButton(), &MyButton::clicked, this, &SnakeGameWindow::slot_exit_game);
    //соединяем сигнал от кнопки завершения игры из меню конца игры с методом закрытия приложения
    connect(m_game_over_menu->getExitButton(), &MyButton::clicked, this, &SnakeGameWindow::slot_exit_game);
    //соединяем сигнал от сцены о завершении игры с методом закрытия окна
    connect(m_game_process_window->getCustomScene(), &CustomGameScene::signal_game_over, m_game_process_window, &GameProcessWindow::hide);
    //соединяем сигнал от кнопки рестарта с сокрытия окна
    connect(m_game_over_menu->getRestartButton(), &MyButton::clicked, m_game_over_menu, &GameOverMenu::hide);
    //соединяем сигнал от кнопки рестарта с слотом рестарта игры
    connect(m_game_over_menu->getRestartButton(), &MyButton::clicked, m_game_process_window, &GameProcessWindow::slot_game_restart);
    //соединяем сигнал отправки статисти от игрового окна к слоту установки игровой статистики в окне завершения игры
    connect(m_game_process_window, &GameProcessWindow::signal_send_game_statistics_over, m_game_over_menu, &GameOverMenu::slot_game_over_menu);
    //соединяем сигнал от кнопки рекорды главного меню с слотом вызова окна рекордов
    //connect(m_main_menu->getRecordButton(), &MyButton::clicked, m_main_menu, &MainMenu::hide);
    //соединяем сигнал от кнопки рекорды главного меню с слотом показа окна рекордов
    //connect(m_main_menu->getRecordButton(), &MyButton::clicked, m_records_window, &RecordsWindow::slot_show_records);
    //соединяем сигнал отправки статистики с слотом обновления статистики рекордов
    connect(m_game_process_window, &GameProcessWindow::signal_send_game_statistics_over, this, &SnakeGameWindow::slot_update_records);
    //сигнал обновления рекордов соединяем с слотом обновления рекордов у окна с рекордами
    connect(this, &SnakeGameWindow::signal_update_records, m_records_window, &RecordsWindow::slot_udate_records_table);
    //сигнал от окна рекордов о возврате в главное меню соединяем с методом показа окна главного меню
    connect(m_records_window, &RecordsWindow::signal_return_main_menu, m_main_menu, &MainMenu::show);
    //сигнал от окна рекордов о возврате в меню конца игры соединяем с методом показа окна конца игры
    connect(m_records_window, &RecordsWindow::signal_return_game_over_menu, m_game_over_menu, &GameOverMenu::show);
    //сионал от главного меню с слотом вызова окна реукордов
    connect(m_main_menu, &MainMenu::signal_call_record_menu, m_records_window, &RecordsWindow::slot_show_records);
    //сигнал от меню конца игры с слотом вызоаа окна рекордов
    connect(m_game_over_menu, &GameOverMenu::signal_call_record_menu, m_records_window, &RecordsWindow::slot_show_records);
}

SnakeGameWindow::~SnakeGameWindow()
{
    delete ui;
}

void SnakeGameWindow::slot_update_records(const GameStatistics &send_statistics)
{

    m_records_list.back() = send_statistics;



    for (auto records = m_records_list.begin(); records != m_records_list.end(); ++records)
    {
        if(records->score < send_statistics.score || records->score == send_statistics.score && records->time < send_statistics.time)
        {
            m_records_list.insert(records, send_statistics);
            m_records_list.pop_back();
            break;
        }
    }

    emit signal_update_records(m_records_list);
}

void SnakeGameWindow::slot_exit_game()
{
    std::ofstream fileout;

    fileout.open("Record.txt");

    for (auto records = m_records_list.begin(); records != m_records_list.end(); ++records)
    {
        fileout.write((char*)&*records, sizeof(GameStatistics));
    }

    fileout.close();
    m_app->closeAllWindows();

}



