#include "widget.h"
#include "ui_widget.h"
#include <QMenu>
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

void Widget::on_btnInitItems_clicked()
{
    // "初始化列表" 按钮
    QIcon icon;
    icon.addFile(":/images/icons/aim.ico");
    ui->comboBox_2->clear();
    for(int i = 0; i < 20; ++i)
        ui->comboBox_2->addItem(icon, QString("Item %1").arg(i));
}


void Widget::on_pushButton_2_clicked()
{
    // "初始化城市 + 区号" 按钮
    QMap<QString, int> City_Zone;
    City_Zone.insert("北京", 10);
    City_Zone.insert("西安", 16);
    City_Zone.insert("兰州", 18);
    City_Zone.insert("海南", 21);
    City_Zone.insert("福州", 50);
    City_Zone.insert("威海", 27);
    City_Zone.insert("吉林", 26);
    City_Zone.insert("福州", 12);
    City_Zone.insert("长沙", 13);
    City_Zone.insert("成都", 0);
    foreach(const QString &str, City_Zone.keys())
        ui->comboBox->addItem(str, City_Zone.value(str));
}


void Widget::on_comboBox_2_currentTextChanged(const QString &arg1)
{
    ui->plainTextEdit->appendPlainText(arg1);
}


void Widget::on_comboBox_currentIndexChanged(int index)
{
    Q_UNUSED(index);
    QString city = ui->comboBox->currentText();
    QString zone = ui->comboBox->currentData().toString();
    ui->plainTextEdit->appendPlainText(city + ":区号 = " + zone);
}


void Widget::on_btnClearText_clicked()
{
    // "清空文本框"
    ui->plainTextEdit->clear();
}




void Widget::on_btnClearItems_clicked()
{
    // "清空列表"
    ui->comboBox_2->clear();
}



void Widget::on_chkBoxEditable_clicked(bool checked)
{
    // "可编辑" checkBox
    ui->comboBox_2->setEditable(checked);
}


void Widget::on_plainTextEdit_customContextMenuRequested(const QPoint &pos)
{
    // 创建并显示标准弹出式菜单
    QMenu* menu = ui->plainTextEdit->createStandardContextMenu();
    menu->exec(pos);
}

