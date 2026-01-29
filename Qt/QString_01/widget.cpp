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

void Widget::on_btnGetChars_clicked()
{
    QString str = ui->editStr->text();
    // 读取输入的字符串
    if(str.isEmpty()) return;
    ui->plainTextEdit->clear();
    for(qint16 i = 0; i < str.size(); i++)
    {
        QChar ch = str.at(i); // 获取单个字符
        char16_t uniCode = ch.unicode(); // 获取 QChar字符的 UTF16 编码
        QString chStr(ch); // 将 QChar 转换为 QString字符串
        QString info = chStr + QString::asprintf("\t, Unicode编码=0x%X", uniCode);
        ui->plainTextEdit->appendPlainText(info);
    }
}


void Widget::on_btnCharJudge_clicked()
{
    QString str = ui->editChar->text();
    if(str.isEmpty()) return;

    QChar ch = str[0]; // 只提取第一个字符
    char16_t unicode = ch.unicode();
    QString chStr(ch); // 将 QChar 转换为 QString字符串
    QString info = chStr + QString::asprintf("\t, Unicode编码=0x%X", unicode);
    ui->plainTextEdit->appendPlainText(info);

    ui->chkDigit->setChecked(ch.isDigit());
    ui->chkLetter->setChecked(ch.isLetter());
    ui->chkLetterOrNumber->setChecked(ch.isLetterOrNumber());
    ui->chkUpper->setChecked(ch.isUpper());
    ui->chkLower->setChecked(ch.isLower());
    ui->chkMark->setChecked(ch.isMark());
    ui->chkSpace->setChecked(ch.isSpace());
    ui->chkSymbol->setChecked(ch.isSymbol());
    ui->chkPunct->setChecked(ch.isPunct());

}


void Widget::on_btnConvLatin1_clicked()
{
    // "与 Latin1 的转换" 按钮
    QString str = "Dimple";
    ui->plainTextEdit->clear();
    ui->plainTextEdit->appendPlainText(str);

    QChar chP = QChar::fromLatin1('P');
    str[0] = chP;
    ui->plainTextEdit->appendPlainText("\n" + str);
}


void Widget::on_btnConvUTF16_clicked()
{
    // "与 UTF16的转换"
    QString str = "Hello 北京";
    ui->plainTextEdit->clear();
    ui->plainTextEdit->appendPlainText(str);

    str[6] = QChar(0x9752); // '青;
    str[7] = QChar::fromUcs2(0x5C9B); // '岛'
    ui->plainTextEdit->appendPlainText("\n" + str);
}


void Widget::on_btnCompare_clicked()
{
    // "QChar的比较与替换"
    QString str = "他们来自河南或河北";
    ui->plainTextEdit->clear();
    ui->plainTextEdit->appendPlainText(str);

    QString HuStr = "河to湖";
    QChar He = QChar::fromUcs2(HuStr[0].unicode()); // 获取 河 的UTF16编码, 在转换为 QChar 字符
    QChar Hu = QChar::fromUcs2(HuStr[3].unicode());

    for(qint16 i = 0; i < str.size(); i++)
    {
        if(str.at(i) == He)
            str[i] = Hu;
    }
    ui->plainTextEdit->appendPlainText("\n" + str);

}


void Widget::on_btnClear_clicked()
{
    ui->plainTextEdit->clear();
}

