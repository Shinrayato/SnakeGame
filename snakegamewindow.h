#ifndef SNAKEGAMEWINDOW_H
#define SNAKEGAMEWINDOW_H

#include <QMainWindow>
#include "QGraphicsScene"
#include "QGraphicsView"
#include "QVBoxLayout"


//my includes
#include "mainmenu.h"
#include "gameprocesswindow.h"
#include "gameovermenu.h"



QT_BEGIN_NAMESPACE
namespace Ui {
class SnakeGameWindow;
}
QT_END_NAMESPACE

class SnakeGameWindow : public QMainWindow
{
    Q_OBJECT

public:
    SnakeGameWindow(const QApplication* app, QWidget *parent = nullptr);
    ~SnakeGameWindow();


private:
    Ui::SnakeGameWindow *ui;
    MainMenu *m_main_menu;//указатель на виджет главного меню игры
    GameProcessWindow * m_game_process_window;//указатель виджет игрового процесса
    GameOverMenu *m_game_over_menu;

    QVBoxLayout* vlaout;//компоновка для установки в всех игровых виджетов


};
#endif // SNAKEGAMEWINDOW_H
