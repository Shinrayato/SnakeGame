#ifndef GAMEOVERMENU_H
#define GAMEOVERMENU_H

#include <QWidget>
#include <QVBoxLayout>
#include <QLabel>
#include "QHBoxLayout"

//my includes
#include "mybutton.h"

class GameOverMenu : public QWidget
{
    Q_OBJECT
public:
    explicit GameOverMenu(QWidget *parent = nullptr);
    MyButton* getExitButton();

signals:

public slots:

    void slot_game_over_menu(int score_count);

private:

    MyButton *m_retry_button;
    MyButton *m_show_records_button;
    MyButton *m_exit_game_button;
    QLabel   *m_game_over_label;
    QLabel   *m_total_score_label;
    QVBoxLayout *m_layout;

};

#endif // GAMEOVERMENU_H
