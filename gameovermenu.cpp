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
    m_layout = new QVBoxLayout(this);
    m_layout->setAlignment(Qt::AlignCenter);


    //установка кнопок и лейблов в компоновку и установка компоновки в виджет
    this->setLayout(m_layout);
    m_layout->addWidget(m_game_over_label);
    m_layout->setSpacing(15);
    m_layout->addWidget(m_total_score_label);
    m_layout->setSpacing(15);
    m_layout->addWidget(m_retry_button);
    m_layout->setSpacing(50);
    m_layout->addWidget(m_show_records_button);
    m_layout->setSpacing(50);
    m_layout->addWidget(m_exit_game_button);
    m_layout->setSpacing(50);




    QPalette pal = QPalette();
    pal.setColor(QPalette::Window, Qt::darkGray);
    this->setAutoFillBackground((true));
    this->setPalette(pal);

}

MyButton *GameOverMenu::getExitButton()
{
    return m_exit_game_button;
}

void GameOverMenu::slot_game_over_menu(int score_count)
{
    std::string score_string = "Total Score: " + std::to_string(score_count);
    m_total_score_label->setText(score_string.c_str());
    this->show();

}
