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
#include "recordswindow.h"
#include "fstream"



QT_BEGIN_NAMESPACE
namespace Ui {
class SnakeGameWindow;
}
QT_END_NAMESPACE

class SnakeGameWindow : public QMainWindow
{
    Q_OBJECT

public:
    SnakeGameWindow(QApplication* app, QWidget *parent = nullptr);
    ~SnakeGameWindow();

signals:

    void signal_update_records(const std::list<GameStatistics>& m_records_list);

public slots:
    void slot_update_records(const GameStatistics& send_statistics);
    void slot_exit_game();


private:
    Ui::SnakeGameWindow *ui;
    class MainMenu *m_main_menu;//указатель на виджет главного меню игры
    GameProcessWindow * m_game_process_window;//указатель виджет игрового процесса
    class GameOverMenu *m_game_over_menu;
    RecordsWindow *m_records_window;
    std::list<GameStatistics> m_records_list;

    QApplication* m_app;

    QVBoxLayout* vlaout;//компоновка для установки в всех игровых виджетов


};
#endif // SNAKEGAMEWINDOW_H
