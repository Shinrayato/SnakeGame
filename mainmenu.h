#ifndef MAINMENU_H
#define MAINMENU_H

#include <QVBoxLayout>
#include <QLabel>
#include "QHBoxLayout"
#include "QWidget"


//my includes
#include "mybutton.h"
#include "primitives.h"




class MainMenu : public QWidget
{
    Q_OBJECT
public:
    MainMenu(QWidget *parent = nullptr);
    ~MainMenu();
    MyButton* getStartButton();
    MyButton* getRecordButton();
    MyButton* getExitButton();

public slots:

    void slot_call_record_menu();
signals:

    void signal_call_record_menu(CalledFrom this_window);



private:
//указатели на виджеты главного меню игры
    MyButton* m_gameStart_button;
    MyButton* m_showRecord_button;
    MyButton* m_exitGame_button;
    QLabel* m_name_of_game;
    QVBoxLayout *m_vLayout;

};

#endif // MAINMENU_H
