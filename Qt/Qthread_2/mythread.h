#ifndef MYTHREAD_H
#define MYTHREAD_H


#include <QVector>
#include <QObject>
#include <QRandomGenerator>

class Generate : public QObject
{
    Q_OBJECT
public:
    explicit Generate(QObject *parent = nullptr);

    void working(int num);

signals:
    void sendArray(QVector<int> num);

};

class BubbleSort : public QObject
{
    Q_OBJECT
public:
    explicit BubbleSort(QObject *parent = nullptr);

    void working(QVector<int> list);

signals:
    void finish(QVector<int> num);


};

class QuickSort : public QObject
{
    Q_OBJECT
public:
    explicit QuickSort(QObject *parent = nullptr);

     void working(QVector<int> list);

private:
    void quickSort(QVector<int>& q, int l, int r);

signals:
    void finish(QVector<int> num);
};

#endif // MYTHREAD_H
