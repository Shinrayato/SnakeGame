#include "recordswindow.h"

RecordsWindow::RecordsWindow(const std::list<GameStatistics> &records_list, QWidget *parent): m_back_button("Back"),  QWidget(parent)
{
    //записываем в лейблы текс и задаем стиль
    m_records_label.setText("Records");
    m_records_label.setStyleSheet("font-size: 45px;");
    m_records_label.setAlignment(Qt::AlignCenter);

    m_score_stats_label.setText("Score");
    m_score_stats_label.setStyleSheet("font-size: 35px;");
    m_score_stats_label.setAlignment(Qt::AlignCenter);

    m_time_stats_label.setText("Time");
    m_time_stats_label.setStyleSheet("font-size: 35px;");
    m_time_stats_label.setAlignment(Qt::AlignCenter);

    //устанавливаем лейблы в их компоновки
    m_main_vert_layout.addWidget(&m_records_label, Qt::AlignCenter);//рекорды в главную вертикальную
    //лейблы статистики в горизонтальный лейбл для них
    m_layout_stats_name.addWidget(&m_score_stats_label);
    m_layout_stats_name.addSpacing(160);
    m_layout_stats_name.addWidget(&m_time_stats_label);
    m_layout_stats_name.setAlignment(Qt::AlignCenter);


    //в главный вертикальный, компоновку с наименованием колонки статистики
    m_main_vert_layout.addLayout(&m_layout_stats_name);

    //в компоновку для лейблов со всеми рекордами установка самих лейблов
    m_layout_results.addWidget(&m_score_allRec_label);
    m_layout_results.addSpacing(81);
    m_layout_results.addWidget(&m_time_allRec_label);
    m_layout_results.addSpacing(70);


    //в главный компоновку со всеми рекордами
    m_main_vert_layout.addLayout(&m_layout_results);

    //добавление в главную компоновку кнопки возврата
    m_main_vert_layout.addWidget(&m_back_button);

    //устанавливаем главную компоновку в этот виджет
    this->setLayout(&m_main_vert_layout);

    m_score_allRec_label.setStyleSheet("font-size: 25px;");
    m_score_allRec_label.setAlignment(Qt::AlignRight);
    m_time_allRec_label.setStyleSheet("font-size: 25px;");
    m_time_allRec_label.setAlignment(Qt::AlignRight);

    foreach (const auto record, records_list)
    {
        std::string score = std::to_string(record.score);

        int seconds = record.time;

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

        m_score_allRec_label.setText(m_score_allRec_label.text() + score.c_str() + "\n");
        m_time_allRec_label.setText(m_time_allRec_label.text() + time.c_str() + "\n");

    }

    //устанавливаем откуда изначально было вызвано окно рекордов
    m_calledForm = CalledFrom::MainMenu;

    connect(&m_back_button, &MyButton::clicked, this, &RecordsWindow::slot_return_in_menu);
}

void RecordsWindow::slot_return_in_menu()
{
    this->hide();//скрываем виджет
    //возврат в меню из которого было вызвано это окно
    if(m_calledForm == CalledFrom::MainMenu){emit signal_return_main_menu();}
    else {emit signal_return_game_over_menu();};

}

void RecordsWindow::slot_show_records(CalledFrom menu_where_called)
{
    m_calledForm = menu_where_called;
    this->show();
}

void RecordsWindow::slot_udate_records_table(const std::list<GameStatistics> &records_list)
{
    m_score_allRec_label.clear();
    m_time_allRec_label.clear();

    foreach (const auto record, records_list)
    {
        std::string score = std::to_string(record.score);

        int seconds = record.time;

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

        m_score_allRec_label.setText(m_score_allRec_label.text() + score.c_str() + "\n");
        m_time_allRec_label.setText(m_time_allRec_label.text() + time.c_str() + "\n");
    }
}
