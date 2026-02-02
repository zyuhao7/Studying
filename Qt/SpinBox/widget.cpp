#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    connect(ui->spinNum, SIGNAL(valueChanged(int)), this, SLOT(on_btnCal_clicked()));
    connect(ui->spinPrice, SIGNAL(valueChanged(double)), this, SLOT(on_btnCal_clicked()));
}

Widget::~Widget()
{
    delete ui;
}

void Widget::on_btnCal_clicked()
{
    // 计算按钮
    int num = ui->spinNum->value();
    float price = ui->spinPrice->value();
    float total = num * price;
    ui->spinTotal->setValue(total);
}


void Widget::on_spinDec_valueChanged(int arg1)
{
    // "十进制" SpinBox
    qDebug(ui->spinDec->cleanText().toLocal8Bit().data());
    ui->spinBin->setValue(arg1);
    ui->spinHex->setValue(arg1);
}


void Widget::on_spinBin_valueChanged(int arg1)
{
    // 二进制 spinBox
    qDebug(ui->spinBin->cleanText().toLocal8Bit().data());
    ui->spinDec->setValue(arg1);
    ui->spinHex->setValue(arg1);
}



void Widget::on_spinHex_valueChanged(int arg1)
{
    // "十六进制" spinBox
    qDebug(ui->spinHex->cleanText().toLocal8Bit().data());
    ui->spinDec->setValue(arg1);
    ui->spinBin->setValue(arg1);
}

