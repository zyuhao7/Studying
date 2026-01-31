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

void Widget::showBoolInfo(QString str, bool b)
{
    if(b)
        ui->plainTextEdit->appendPlainText(str + "= true");
    else
        ui->plainTextEdit->appendPlainText(str + "= false");
}

// front & back
void Widget::on_pushButton_2_clicked()
{
    // front() 函数获取字符串的第一个字符
    ui->plainTextEdit->appendPlainText("\n>>> front() & back()函数测试 <<<");

    QString str1 = ui->comboBox->currentText();
    ui->plainTextEdit->appendPlainText("str1= " + str1);

    QChar ch = str1.front();
    QString str2 = QString(ch);
    ui->plainTextEdit->appendPlainText("front()= " + str2);

    ch = str1.back();
    str2 = QString(ch);
    ui->plainTextEdit->appendPlainText("back()= " + str2);
}

// left & right
void Widget::on_pushButton_clicked()
{
    ui->plainTextEdit->appendPlainText("\n>>> left() & right()函数测试 <<<");

    QString str1 = ui->comboBox->currentText();
    ui->plainTextEdit->appendPlainText("str1= " + str1);

    QString str2 = str1.left(2);
    ui->plainTextEdit->appendPlainText("left(2)= " + str2);

    str2 = str1.right(6);
    ui->plainTextEdit->appendPlainText("right(6)= " + str2);
}

// first & last
void Widget::on_pushButton_4_clicked()
{
    ui->plainTextEdit->appendPlainText("\n>>> first() & last()函数测试 <<<");
    QString str1 = ui->comboBox->currentText();
    QString str2 = ui->comboBox_2->currentText();

    ui->plainTextEdit->appendPlainText("str1= " + str1);
    ui->plainTextEdit->appendPlainText("str2= " + str2);

    int N = str1.lastIndexOf(str2); // str2 最后出现的位置
    QString str3= str1.first(N + 1);
    ui->plainTextEdit->appendPlainText(str3);

    str3 = str1.last(str1.length() - N - 1);
    ui->plainTextEdit->appendPlainText(str3);
}

// section
void Widget::on_pushButton_3_clicked()
{
    ui->plainTextEdit->appendPlainText("\n>>> section() 函数测试 <<<");
    QString str1 = ui->comboBox->currentText();
    int N = ui->spinBox->value();
    QString str2 = ui->comboBox_2->currentText();

    QString str3;
    if(QString::compare(str2, "\\", Qt::CaseInsensitive) == 0)
        str3 = str1.section('\\', N, N);
    else
        str3 = str1.section(str2, N, N);
    ui->plainTextEdit->appendPlainText(str3);
}


// isNull 和 isEmpty
void Widget::on_pushButton_5_clicked()
{
    ui->plainTextEdit->appendPlainText("\n>>> isNull & isEmpty 函数测试 <<<");
    QString str1, str2 = "";

    ui->plainTextEdit->appendPlainText("QString str1, str2=\"\"");
    showBoolInfo("str1.isNull()", str1.isNull());
    showBoolInfo("str1.isEmpty()", str1.isEmpty());

    showBoolInfo("\nstr2.isNull()", str2.isNull());
    showBoolInfo("str2.isEmpty()", str2.isEmpty());

    str2.clear();
    ui->plainTextEdit->appendPlainText("\n str2.clear()后:");
    showBoolInfo("\nstr2.isNull()", str2.isNull());
    showBoolInfo("str2.isEmpty()", str1.isEmpty());


}

// resize 函数
void Widget::on_pushButton_6_clicked()
{
    ui->plainTextEdit->appendPlainText("\n>>> resize()函数测试 <<<");
    QString str1;
    str1.resize(5, '0');

    ui->plainTextEdit->appendPlainText(str1);
    str1.resize(10, QChar(0x54C8));
    ui->plainTextEdit->appendPlainText(str1);
}

// count length size 函数
void Widget::on_pushButton_7_clicked()
{
    ui->plainTextEdit->appendPlainText("\n>>> count(), size(), length() 函数测试 <<<");

    QString str1 = ui->comboBox->currentText();
    ui->plainTextEdit->appendPlainText(str1);

    int N = str1.size();
    ui->plainTextEdit->appendPlainText(QString::asprintf("size()=%d", N));

    N = str1.count();
    ui->plainTextEdit->appendPlainText(QString::asprintf("count()=%d", N));

    N = str1.length();
    ui->plainTextEdit->appendPlainText(QString::asprintf("length()=%d", N));
}

// fill 函数
void Widget::on_pushButton_8_clicked()
{
    ui->plainTextEdit->appendPlainText("\n>>> fill() 函数测试 <<<");

    QString str1 = "Hello";
    str1.fill('X');

    ui->plainTextEdit->appendPlainText("str1= " + str1);
    str1.fill('A', 2);
    ui->plainTextEdit->appendPlainText("str1.fill('A',2)后: " + str1);

    str1.fill(QChar(0x54C8), 3);
    ui->plainTextEdit->appendPlainText("str1.fill(QChar(0x54C8),3)后: " + str1);
}

// indexOf & lastIndexOf 函数
void Widget::on_pushButton_9_clicked()
{
    ui->plainTextEdit->appendPlainText("\n>>> indexOf() & lastIndexOf() 函数测试 <<<");

    QString str1 = ui->comboBox->currentText();
    QString str2 = ui->comboBox_2->currentText();
    ui->plainTextEdit->appendPlainText("str1 = " + str1);
    ui->plainTextEdit->appendPlainText("str2 = " + str2);

    int n = str1.indexOf(str2);
    QString info = QString::asprintf("indexOf() = %d", n);
    ui->plainTextEdit->appendPlainText(info);

    n = str1.lastIndexOf(str2);
    info = QString::asprintf("lastIndexOf() = %d", n);
    ui->plainTextEdit->appendPlainText(info);

}


// contains函数
void Widget::on_pushButton_10_clicked()
{
    ui->plainTextEdit->appendPlainText("\n>>> contains() 函数测试 <<<");
    QString str1 = ui->comboBox->currentText();
    QString str2 = ui->comboBox_2->currentText();
    ui->plainTextEdit->appendPlainText(str1);
    ui->plainTextEdit->appendPlainText(str2);

    bool chk = str1.contains(str2);
    showBoolInfo("contains() = ", chk);

}

// endsWith & startsWith 函数
void Widget::on_pushButton_11_clicked()
{
    ui->plainTextEdit->appendPlainText("\n>>> endsWith() & startsWith() 函数测试 <<<");
    QString str1 = ui->comboBox->currentText();
    QString str2 = ui->comboBox_2->currentText();

    ui->plainTextEdit->appendPlainText("str1 = " + str1);
    ui->plainTextEdit->appendPlainText("str2 = " + str2);

    bool chk = str1.endsWith(str2);
    showBoolInfo("endsWith = ", chk);

    chk = str1.startsWith(str2);
    showBoolInfo("startsWith = ", chk);
}

// count()
void Widget::on_pushButton_12_clicked()
{
    ui->plainTextEdit->appendPlainText("\n>>> count()统计子字符串出现的次数  <<<");
    QString str1 = ui->comboBox->currentText();
    QString str2 = ui->comboBox_2->currentText();

    ui->plainTextEdit->appendPlainText("str1 = " + str1);
    ui->plainTextEdit->appendPlainText("str2 = " + str2);

    int N = str1.count(str2, Qt::CaseSensitive);
    ui->plainTextEdit->appendPlainText(QString::asprintf("count() = %d", N));
}

// trimmed & simplified 函数
void Widget::on_pushButton_13_clicked()
{
    ui->plainTextEdit->appendPlainText("\n>>> trimmed() & simplified() 函数测试  <<<");
    QString str1 = ui->comboBox->currentText();
    ui->plainTextEdit->appendPlainText("str1 = " + str1);

    QString str2 = str1.trimmed();
    ui->plainTextEdit->appendPlainText("trimmed() = " + str2);

    str2 = str1.simplified();
    ui->plainTextEdit->appendPlainText("simplified() = " + str2);
}

// insert 函数
void Widget::on_pushButton_14_clicked()
{
    ui->plainTextEdit->appendPlainText("\n>>> insert() 函数测试  <<<");
    QString str1 = "it      is great";
    ui->plainTextEdit->appendPlainText("str1 = " + str1);

    int n = str1.lastIndexOf(" "); // 最后一个空格, 不是从后往前算第一个空格。。
    str1.insert(n, "n't");
    ui->plainTextEdit->appendPlainText(str1);
}

// remove 函数
void Widget::on_pushButton_15_clicked()
{
    ui->plainTextEdit->appendPlainText("\n>>> remove() 移除特定的字符  <<<");

    QString str1 = "我们, 你们, 他们";
    ui->plainTextEdit->appendPlainText("str1 = " + str1);

    QString DeStr = "们";
    QChar DeChar = QChar(DeStr[0].unicode());
    str1.remove(DeChar);
    ui->plainTextEdit->appendPlainText("str1 = " + str1);

    ui->plainTextEdit->appendPlainText("\n>>> remove() 移除右侧 N 个字符 <<<");
    str1 = "G:\\Qt6Book\\QtSamples\\widget.cpp";
    ui->plainTextEdit->appendPlainText(str1);

    int n = str1.lastIndexOf("\\");
    str1.remove(n + 1, 20);
    ui->plainTextEdit->appendPlainText(str1);
}

// replace 函数
void Widget::on_pushButton_16_clicked()
{
    ui->plainTextEdit->appendPlainText("\n>>> replace() 替换指定的字符  <<<");
    QString str1 = "goooogle";
    ui->plainTextEdit->appendPlainText(str1);

    str1.replace('o', 'e');
    ui->plainTextEdit->appendPlainText(str1);

    ui->plainTextEdit->appendPlainText("\n>>> replace() 替换字符串  <<<");

    str1 = "It is great";
    int n = str1.lastIndexOf(" ");
    ui->plainTextEdit->appendPlainText(str1);

    QString subStr = "wonderful";
    str1.replace(n + 1, subStr.size(), subStr);
    ui->plainTextEdit->appendPlainText(str1);

    str1.replace(n + 1, subStr.size(), "OK!");
    qDebug()<< str1.toLocal8Bit().data();
    ui->plainTextEdit->appendPlainText(str1);


}


void Widget::on_pushButton_17_clicked()
{
    ui->plainTextEdit->clear();
}

