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

void Widget::on_btnAlign_Left_clicked()
{
    // 居左 按钮
    ui->lineEdit->setAlignment(Qt::AlignLeft);
}


void Widget::on_btnAlign_Center_clicked()
{
    // 居中 按钮
    ui->lineEdit->setAlignment(Qt::AlignCenter);
}


void Widget::on_btnAlign_Right_clicked()
{
    // 居右 按钮
    ui->lineEdit->setAlignment(Qt::AlignRight);
}


void Widget::on_btnFont_Bold_clicked(bool checked)
{
    // 粗体 按钮
    QFont font = ui->lineEdit->font();
    font.setBold(checked);
    ui->lineEdit->setFont(font);
}




void Widget::on_btnFont_Italic_clicked(bool checked)
{
    // 斜体 按钮
    QFont font = ui->lineEdit->font();
    font.setItalic(checked);
    ui->lineEdit->setFont(font);
}


void Widget::on_btnFont_UnderLine_clicked(bool checked)
{
    // 下划线 按钮
    QFont font = ui->lineEdit->font();
    font.setUnderline(checked);
    ui->lineEdit->setFont(font);
}


void Widget::on_chkBox_Readonly_clicked(bool checked)
{
    // Readonly 复选框
    ui->lineEdit->setReadOnly(checked);
}


void Widget::on_chkBox_Enable_clicked(bool checked)
{
    // Enable 复选框
    ui->lineEdit->setEnabled(checked);
}


void Widget::on_chkBox_ClearButton_clicked(bool checked)
{
    // ClearButtonEnabled 复选框
    ui->lineEdit->setClearButtonEnabled(checked);
}


void Widget::on_radioBlack_clicked()
{
    // black 单选按钮
    QPalette plet = ui->lineEdit->palette();
    plet.setColor(QPalette::Text, Qt::black);
    ui->lineEdit->setPalette(plet);
}


void Widget::on_radioRed_clicked()
{
    // red 单选按钮
    QPalette plet = ui->lineEdit->palette();
    plet.setColor(QPalette::Text, Qt::red);
    ui->lineEdit->setPalette(plet);
}


void Widget::on_radioBlue_clicked()
{
    // blue 单选按钮
    QPalette plet = ui->lineEdit->palette();
    plet.setColor(QPalette::Text, Qt::blue);
    ui->lineEdit->setPalette(plet);
}

