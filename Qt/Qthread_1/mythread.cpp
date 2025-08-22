#include "mythread.h"
#include <QElapsedTimer>
#include <QDebug>

Generate::Generate(QObject *parent)
    : QThread{parent}
{

}

void Generate::recvNum(int num)
{
    m_num = num;
}

void Generate::run()
{
    qDebug()<<"生成随机数函数线程的地址: "<<QThread::currentThread();

    QVector<int> list;
    QElapsedTimer time;
    time.start();

    for(int i = 0; i < m_num; ++i)
    {
        list.push_back(rand() % 100000);
    }
    int milsec = time.elapsed();
    qDebug() << "生成" << m_num <<"个随机数总共用时: "<< milsec << "毫秒";

    emit sendArray(list);
}

BubbleSort::BubbleSort(QObject *parent)
    :QThread(parent)
{

}

void BubbleSort::recvArray(QVector<int> list)
{
    m_list = list;
}

void BubbleSort::run()
{
    qDebug()<<"冒泡排序函数线程的地址: "<<QThread::currentThread();
    QElapsedTimer time;
    time.start();

    int tmp;
    for(int i = 0; i < m_list.size() - 1; ++i)
    {
        for(int j = 0; j < m_list.size() - 1 - i; ++j)
        {
            if(m_list[j] > m_list[j + 1])
            {
                tmp = m_list[j];
                m_list[j] = m_list[j + 1];
                m_list[j + 1] = tmp;
            }
        }
    }

    int milsec = time.elapsed();
    qDebug() << "冒泡排序用时: " << milsec << "毫秒";
    emit finish(m_list);
}

QuickSort::QuickSort(QObject *parent)
    :QThread(parent)
{

}

void QuickSort::recvArray(QVector<int> list)
{
    m_list = list;
}

void QuickSort::run()
{
    qDebug()<<"快速排序函数线程的地址: "<<QThread::currentThread();
    QElapsedTimer time;
    time.start();

    quickSort(m_list, 0, m_list.size() - 1);

    int milsec = time.elapsed();
    qDebug() << "快速排序用时: " << milsec << "毫秒";
    emit finish(m_list);
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
