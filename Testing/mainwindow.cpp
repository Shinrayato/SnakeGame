#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QGraphicsScene"
#include "QGraphicsView"
#include "QVBoxLayout"
#include "QHBoxLayout"
#include "QPushButton"
#include "QPalette"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QGraphicsView *viev = new QGraphicsView(this);
    QGraphicsScene *scene = new QGraphicsScene(this);
    QVBoxLayout* vlayout =new QVBoxLayout (this);
    QPushButton* button = new QPushButton("button", this);
     QVBoxLayout* vlayout2 =new QVBoxLayout (this);
    this->resize(500,500);
    viev->resize(this->size());



    scene->addRect(viev->rect(), QPen(Qt::gray), QBrush(Qt::gray));
    viev->setLayout(vlayout);
    viev->setScene(scene);
    vlayout->addWidget(button);
    ui->centralwidget->setLayout(vlayout2);
    ui->gridLayout->addWidget(viev);

    //button->setAutoFillBackground(true);
   //QPalette palette = button->palette();
   //palette.setColor(QPalette::Button,Qt::green);
   //palette.setColor(QPalette::Button, Qt::blue);
    //button->setPalette(palette);

   button->setStyleSheet("background-color: rgb(179, 35, 250); border: 3px solid;  border-radius: 10px;");
    button->resize(100,50);



}

MainWindow::~MainWindow()
{
    delete ui;
}
