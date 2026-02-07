#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
}

Widget::~Widget()
{
    delete ui;
}

void Widget::on_btnDebugTime_clicked()
{
    QTime tm1(8,51,5);
    QString str = tm1.toString("HH:mm:ss"); // 时分秒
    qDebug("Original time = %s", str.toLocal8Bit().data());

    QTime tm2 = tm1.addSecs(150); // 延后150s
    str = tm2.toString("HH:mm:ss");
    qDebug("150s later, time = %s", str.toLocal8Bit().data());

    tm2 = QTime::currentTime(); // 获取当前时间
    str = tm2.toString("HH:mm:ss zzz");
    qDebug("Current time = %s", str.toLocal8Bit().data());
    qDebug("Hour = %d", tm2.hour());
    qDebug("Minute = %d", tm2.minute());
    qDebug("Second = %d", tm2.second());
    qDebug("MSecond = %d", tm2.msec());
}


void Widget::on_btnDebugDate_clicked()
{
    QDate dt1(2026,2,7);
    QString str = dt1.toString("yyyy-MM-dd");
    qDebug("DT1 = %s", str.toLocal8Bit().data());

    QDate dt2;
    dt2.setDate(2026,8,15);
    str = dt2.toString("yyyy-MM-dd");
    qDebug("DT2 = %s", str.toLocal8Bit().data());
    qDebug("Days between dt2 and dt1 = %d", dt1.daysTo(dt2));

    dt2 = QDate::currentDate();
    str = dt2.toString("yyyy-MM-dd");
    qDebug("Current date = %s", str.toLocal8Bit().data());
    qDebug("Year = %d", dt2.year());
    qDebug("Month = %d", dt2.month());
    qDebug("Day = %d", dt2.day());
    qDebug("Day of week = %d", dt2.dayOfWeek());

}


void Widget::on_btnDebugDateTime_clicked()
{
    QDateTime dt1 = QDateTime::currentDateTime();
    QString str = dt1.toString("yyyy-MM-dd hh:mm:ss");
    qDebug("dt1 = %s", str.toLocal8Bit().data());

    QDate dt = dt1.date();
    str = dt.toString("yyyy-MM-dd");
    qDebug("dt1.date() = %s", str.toLocal8Bit().data());
    QTime tm = dt1.time();
    str = tm.toString("hh:mm:ss zzz");
    qDebug("dt1.time() = %s", str.toLocal8Bit().data());

    qint64 ms = dt1.toSecsSinceEpoch(); // 转换为秒数
    qDebug("dt1.toSecsSinceEpoch() = %lld", ms);

    ms += 120;
    dt1.setSecsSinceEpoch(ms);
    str = dt1.toString("yyyy-MM-dd hh:mm:ss");
    qDebug("dt1 + 120s = %s", str.toLocal8Bit().data());
}


void Widget::on_pushButton_clicked()
{
    // "读取当前日期" 按钮
    QDateTime curDateTime = QDateTime::currentDateTime();
    ui->timeEdit->setTime(curDateTime.time());
    ui->editTime->setText(curDateTime.toString("hh:mm:ss"));
    ui->dateEdit->setDate(curDateTime.date());
    ui->editDate->setText(curDateTime.toString("yyyy-MM-dd"));
    ui->dateTimeEdit->setDateTime(curDateTime);
    ui->editDateTime->setText(curDateTime.toString("yyyy-MM-dd hh:mm:ss"));
}


void Widget::on_btnSetTime_clicked()
{
    // "设置时间 fromString" 按钮
    QString str = ui->editTime->text();
    str = str.trimmed(); // 去掉多于的空格
    if(!str.isEmpty())
    {
        QTime tm = QTime::fromString(str, "hh:mm:ss");
        ui->timeEdit->setTime(tm);
    }
}


void Widget::on_btnSetDate_clicked()
{
    // "设置日期 fromString" 按钮
    QString str = ui->editDate->text();
    str = str.trimmed(); // 去掉多于的空格
    if(!str.isEmpty())
    {
        QDate dt = QDate::fromString(str, "yyyy-MM-dd");
        ui->dateEdit->setDate(dt);
    }
}


void Widget::on_btnSetDateTime_clicked()
{
    // "设置日期时间 fromString" 按钮
    QString str = ui->editDateTime->text();
    str = str.trimmed(); // 去掉多于的空格
    if(!str.isEmpty())
    {
        QDateTime dt = QDateTime::fromString(str, "yyyy-MM-dd hh:mm:ss");
        ui->dateTimeEdit->setDateTime(dt);
    }
}


void Widget::on_calendarWidget_selectionChanged()
{
    // 日历组件的 selectionChanged() 信号的槽函数
    QDate dt = ui->calendarWidget->selectedDate();
    QString str = dt.toString("yyyy 年 M 月d 日");
    ui->lineEdit->setText(str);
}

