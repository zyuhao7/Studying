#include "mythread.h"
#include <QElapsedTimer>
#include <QDebug>
#include <QThread>

Generate::Generate(QObject *parent)
    : QObject{parent}
{

}



void Generate::working(int num)
{

    QVector<int> list;
    QElapsedTimer time;
    time.start();

    for(int i = 0; i < num; ++i)
    {
        list.push_back(rand() % 100000);
    }
    int milsec = time.elapsed();
    qDebug() << "生成" << num <<"个随机数总共用时: "<< milsec << "毫秒";

    emit sendArray(list);
}

BubbleSort::BubbleSort(QObject *parent)
    :QObject(parent)
{

}



void BubbleSort::working(QVector<int> list)
{
    qDebug()<<"冒泡排序函数线程的地址: "<<QThread::currentThread();
    QElapsedTimer time;
    time.start();

    int tmp;
    for(int i = 0; i < list.size() - 1; ++i)
    {
        for(int j = 0; j < list.size() - 1 - i; ++j)
        {
            if(list[j] > list[j + 1])
            {
                tmp = list[j];
                list[j] = list[j + 1];
                list[j + 1] = tmp;
            }
        }
    }

    int milsec = time.elapsed();
    qDebug() << "冒泡排序用时: " << milsec << "毫秒";
    emit finish(list);
}

QuickSort::QuickSort(QObject *parent)
    :QObject(parent)
{

}


void QuickSort::working(QVector<int> list)
{
    qDebug()<<"快速排序函数线程的地址: "<<QThread::currentThread();
    QElapsedTimer time;
    time.start();

    quickSort(list, 0, list.size() - 1);

    int milsec = time.elapsed();
    qDebug() << "快速排序用时: " << milsec << "毫秒";
    emit finish(list);
}

void QuickSort::quickSort(QVector<int>& q, int l, int r)
{
    if(l >= r) return;
    int i = l - 1, j = r + 1, x = q[(l + r) >> 1];
    while(i < j)
    {
        do ++i; while(q[i] < x);
        do --j; while(q[j] > x);
        if(i < j)
        {
            int t = q[i];
            q[i] = q[j];
            q[j] = t;
        }
    }
    quickSort(q, l, j);
    quickSort(q, j + 1, r);
}
