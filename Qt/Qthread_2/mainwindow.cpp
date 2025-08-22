#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "mythread.h"
#include <QString>
#include <QThread>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QThread* t1 = new QThread;
    QThread* t2 = new QThread;
    QThread* t3= new QThread;


    Generate *gen = new Generate;
    BubbleSort * bubble = new BubbleSort;
    QuickSort* quick = new QuickSort;

    gen->moveToThread(t1);
    bubble->moveToThread(t2);
    quick->moveToThread(t3);


    connect(this, &MainWindow::starting, gen, &Generate::working);

    connect(ui->startBtn, &QPushButton::clicked, this,[=](){
        emit starting(10000);
        t1->start();
    });

    connect(gen, &Generate::sendArray, bubble, &BubbleSort::working);
    connect(gen, &Generate::sendArray, quick, &QuickSort::working);

    connect(gen, &Generate::sendArray, this, [=](QVector<int> list){
        t2->start();
        t3->start();
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
        t1->quit();
        t1->wait();
        t1->deleteLater();

        t2->quit();
        t2->wait();
        t2->deleteLater();

        t3->quit();
        t3->wait();
        t3->deleteLater();

        gen->deleteLater();
        bubble->deleteLater();
        quick->deleteLater();
    });
}

MainWindow::~MainWindow()
{
    delete ui;
}
