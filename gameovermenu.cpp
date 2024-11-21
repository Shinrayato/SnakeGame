#include "gameovermenu.h"

GameOverMenu::GameOverMenu(QWidget *parent): QWidget(parent)
{
    this->setFixedSize(500, 600);
    //выделение памяти под все виджеты меню
    m_retry_button = new MyButton("Retry", this);
    m_show_records_button = new MyButton("Records", this);
    m_exit_game_button = new MyButton("Exit", this);
    m_game_over_label = new QLabel("Game Over", this);
    m_game_over_label->setStyleSheet("font-size: 45px;");
    m_total_score_label = new QLabel("Total Score: 0", this);
    m_total_score_label->setStyleSheet("font-size: 35px;");
    m_time_label = new QLabel("Time 0 : 0 : 0", this);
    m_time_label->setStyleSheet("font-size: 35px;");
    m_layout = new QVBoxLayout(this);
    m_layout_for_game_stats = new QHBoxLayout(this);
    m_game_over_label->setAlignment(Qt::AlignCenter);
    m_hlayout_for_buttons = new QHBoxLayout(this);
    m_layout->setAlignment(Qt::AlignCenter);
    m_vlayout_for_buttons = new QVBoxLayout(this);




    //установка кнопок и лейблов в компоновку и установка компоновки в виджет
    this->setLayout(m_layout);
    m_layout->addWidget(m_game_over_label);
    m_layout->setSpacing(15);

    m_layout_for_game_stats->addWidget(m_total_score_label);
    m_layout_for_game_stats->addWidget(m_time_label);
    m_layout->addLayout(m_layout_for_game_stats);
    m_layout->setSpacing(40);

    m_hlayout_for_buttons->addSpacing(80);
    m_hlayout_for_buttons->addLayout(m_vlayout_for_buttons);
    m_hlayout_for_buttons->addSpacing(80);

    m_vlayout_for_buttons->addWidget(m_retry_button);
    m_vlayout_for_buttons->setSpacing(50);
    m_vlayout_for_buttons->addWidget(m_show_records_button);
    m_vlayout_for_buttons->setSpacing(50);
    m_vlayout_for_buttons->addWidget(m_exit_game_button);
    m_vlayout_for_buttons->setSpacing(50);

    m_layout->addLayout(m_hlayout_for_buttons);



    QPalette pal = QPalette();
    pal.setColor(QPalette::Window, Qt::darkGray);
    this->setAutoFillBackground((true));
    this->setPalette(pal);
}

MyButton *GameOverMenu::getExitButton()
{
    return m_exit_game_button;
}

MyButton *GameOverMenu::getRestartButton()
{
    return m_retry_button;
}

void GameOverMenu::slot_game_over_menu(int score_count)
{
    std::string score_string = "Total Score: " + std::to_string(score_count);
    m_total_score_label->setText(score_string.c_str());
    this->show();

}
