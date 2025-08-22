#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "mythread.h"
#include <QString>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    Generate *gen = new Generate;
    BubbleSort * bubble = new BubbleSort;
    QuickSort* quick = new QuickSort;

    connect(this, &MainWindow::starting, gen, &Generate::recvNum);

    connect(ui->startBtn, &QPushButton::clicked, this,[=](){
        emit starting(10000);
        gen->start();
    });

    connect(gen, &Generate::sendArray, bubble, &BubbleSort::recvArray);
    connect(gen, &Generate::sendArray, quick, &QuickSort::recvArray);

    connect(gen, &Generate::sendArray, this, [=](QVector<int> list){
        bubble->start();
        quick->start();
        for(int i = 0; i < list.size(); ++i)
        {
            ui->randomList->addItem(QString::number(list.at(i)));
        }
    });

    connect(bubble, &BubbleSort::finish, this, [=](QVector<int> list){
        for(int i = 0; i < list.size(); ++i)
        {
            ui->bubbleList->addItem(QString::number(list.at(i)));
        }
    });


    connect(quick, &QuickSort::finish, this, [=](QVector<int> list){
        for(int i = 0; i < list.size(); ++i)
        {
            ui->quickList->addItem(QString::number(list.at(i)));
        }
    });

    connect(this, &MainWindow::destroyed, this,[=](){
        gen->quit();
        gen->wait();
        gen->deleteLater();

        bubble->quit();
        bubble->wait();
        bubble->deleteLater();

        quick->quit();
        quick->wait();
        quick->deleteLater();
    });

}

MainWindow::~MainWindow()
{
    delete ui;
}
