#ifndef RECORDSWINDOW_H
#define RECORDSWINDOW_H

#include <QWidget>
#include "QVBoxLayout"
#include "QHBoxLayout"
#include "QLabel"
#include "QListWidget"

//my inclues
#include "mybutton.h"
#include "primitives.h"
class RecordsWindow : public QWidget
{
    Q_OBJECT
public:
    explicit RecordsWindow(const std::list<GameStatistics>& records_list, QWidget *parent = nullptr);

signals:

    void signal_return_main_menu();
    void signal_return_game_over_menu();

public slots:

    void slot_return_in_menu();
    void slot_show_records(CalledFrom menu_where_called);
    void slot_udate_records_table(const std::list<GameStatistics>& records_list);

private:

    //лейблы заголовки
    QLabel m_records_label;
    QLabel m_score_stats_label;
    QLabel m_time_stats_label;
    QLabel m_score_allRec_label;
    QLabel m_time_allRec_label;

    QVBoxLayout m_main_vert_layout;//самый главный лайаут
    QHBoxLayout m_layout_stats_name;//лайаут для лейблов заголовков колонок статистики
    QHBoxLayout m_layout_results;//лайаут для двух списков с результатами

    MyButton m_back_button;//кнопка возврата в предыдущее меню;

    std::list<GameStatistics> m_records_list;
    CalledFrom m_calledForm;


};

#endif // RECORDSWINDOW_H
