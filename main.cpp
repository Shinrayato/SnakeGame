#include "snakegamewindow.h"

#include <QApplication>



//змейка план:
//сделать главное меню

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    SnakeGameWindow w(&a);
    w.show();


    return a.exec();
}
