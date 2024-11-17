#ifndef MAINMENU_H
#define MAINMENU_H

#include <QVBoxLayout>
#include <QLabel>
#include "QHBoxLayout"
#include "QWidget"


//my includes
#include "mybutton.h"




class MainMenu : public QWidget
{
    Q_OBJECT
public:
    MainMenu(QWidget *parent = nullptr);
    ~MainMenu();
    MyButton* getStartButton();
    MyButton* getExitButton();


private:
//указатели на виджеты главного меню игры
    MyButton* m_gameStart_button;
    MyButton* m_showRecord_button;
    MyButton* m_exitGame_button;
    QLabel* m_name_of_game;
    QVBoxLayout *m_vLayout;

};

#endif // MAINMENU_H
