#include "widget.h"
#include "ui_widget.h"

#include <QTimer>
#include <QTime>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    m_timer = new QTimer(this); // 创建定时器
    m_timer->stop();
    m_timer->setTimerType(Qt::PreciseTimer);

    ui->radioPricese->setCheckable(true);
    connect(m_timer, SIGNAL(timeout()), this, SLOT(do_timer_timeout()));
}

Widget::~Widget()
{
    delete ui;
}

void Widget::on_btnStart_clicked()
{
    // "开始" 按钮
    m_timer->setInterval(ui->spinBox->value());
    if(ui->radioContinue->isChecked())
        m_timer->setSingleShot(false); // 设置为连续定时
    else
        m_timer->setSingleShot(true);
    // 设置定时器精度
    if(ui->radioPricese->isChecked())
        m_timer->setTimerType(Qt::PreciseTimer);
    else if(ui->radioCoarse->isChecked())
        m_timer->setTimerType(Qt::CoarseTimer);
    else
        m_timer->setTimerType(Qt::VeryCoarseTimer);
    m_timer->start();
    m_counter.start();
    ui->btnStart->setEnabled(false);
    ui->btnOneShot->setEnabled(false);
    ui->btnStop->setEnabled(true);
}


void Widget::on_btnStop_clicked()
{
    // "停止" 按钮
    m_timer->stop();
    int tmMsec = m_counter.elapsed(); // 流逝的时间, 单位: ms
    int ms = tmMsec % 1000; // 毫秒
    int sec = tmMsec / 1000; // 秒
    QString str = QString("流逝的时间: %1 秒, %2毫秒 ").arg(sec).arg(ms, 3, 10, QChar('0'));
    ui->label_2->setText(str);
    ui->btnStart->setEnabled(true);
    ui->btnOneShot->setEnabled(true);
    ui->btnStop->setEnabled(false);
}


void Widget::on_btnOneShot_clicked()
{
    // 动态创建单次定时器
    int intv = ui->spinBox->value();
    QTimer::singleShot(intv, Qt::PreciseTimer, this, &Widget::do_timer_shot);
    m_counter.start(); // 启动定时器
    ui->btnOneShot->setEnabled(false);
}



void Widget::do_timer_timeout()
{
    // 与定时器 timeout() 信号关联的槽函数
    QApplication::beep(); // "嘀" 一声
    QTime curTime = QTime::currentTime();
    ui->lcdHour->display(curTime.hour());
    ui->lcdMin->display(curTime.minute());
    ui->lcdSec->display(curTime.second());

    if(m_timer->isSingleShot()) // 如果是单次定时, 显示流逝的时间
    {
        int tmMsec = m_counter.elapsed();
        QString str = QString("流逝的时间: %1 毫秒").arg(tmMsec);
        ui->label_2->setText(str);
        ui->btnStart->setEnabled(true);
        ui->btnOneShot->setEnabled(true);
        ui->btnStop->setEnabled(false);
    }
}



void Widget::do_timer_shot()
{
    // 与动态创建的单次定时器的 timeout() 信号关联的槽函数
    QApplication::beep();
    int tmMsec = m_counter.elapsed();
    QString str = QString("流逝的时间: %1 毫秒").arg(tmMsec);
    ui->label_2->setText(str);
    ui->btnOneShot->setEnabled(true);

}

