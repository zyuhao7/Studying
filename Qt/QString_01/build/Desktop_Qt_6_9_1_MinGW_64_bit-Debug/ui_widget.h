/********************************************************************************
** Form generated from reading UI file 'widget.ui'
**
** Created by: Qt User Interface Compiler version 6.9.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_WIDGET_H
#define UI_WIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPlainTextEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Widget
{
public:
    QVBoxLayout *verticalLayout;
    QGridLayout *gridLayout;
    QLineEdit *editStr;
    QLineEdit *editChar;
    QLabel *label_2;
    QPushButton *btnCharJudge;
    QLabel *label;
    QPushButton *btnGetChars;
    QGroupBox *groupBox;
    QGridLayout *gridLayout_2;
    QPushButton *btnConvUTF16;
    QPushButton *btnConvLatin1;
    QPushButton *btnClear;
    QPushButton *btnCompare;
    QHBoxLayout *horizontalLayout_4;
    QGroupBox *groupBox_3;
    QVBoxLayout *verticalLayout_3;
    QPlainTextEdit *plainTextEdit;
    QGroupBox *groupBox_2;
    QVBoxLayout *verticalLayout_2;
    QCheckBox *chkDigit;
    QCheckBox *chkLetter;
    QCheckBox *chkLetterOrNumber;
    QCheckBox *chkLower;
    QCheckBox *chkMark;
    QCheckBox *chkPunct;
    QCheckBox *chkSpace;
    QCheckBox *chkSymbol;
    QCheckBox *chkUpper;

    void setupUi(QWidget *Widget)
    {
        if (Widget->objectName().isEmpty())
            Widget->setObjectName("Widget");
        Widget->resize(800, 600);
        verticalLayout = new QVBoxLayout(Widget);
        verticalLayout->setObjectName("verticalLayout");
        gridLayout = new QGridLayout();
        gridLayout->setObjectName("gridLayout");
        editStr = new QLineEdit(Widget);
        editStr->setObjectName("editStr");

        gridLayout->addWidget(editStr, 0, 1, 1, 1);

        editChar = new QLineEdit(Widget);
        editChar->setObjectName("editChar");

        gridLayout->addWidget(editChar, 1, 1, 1, 1);

        label_2 = new QLabel(Widget);
        label_2->setObjectName("label_2");

        gridLayout->addWidget(label_2, 1, 0, 1, 1);

        btnCharJudge = new QPushButton(Widget);
        btnCharJudge->setObjectName("btnCharJudge");

        gridLayout->addWidget(btnCharJudge, 1, 2, 1, 1);

        label = new QLabel(Widget);
        label->setObjectName("label");

        gridLayout->addWidget(label, 0, 0, 1, 1);

        btnGetChars = new QPushButton(Widget);
        btnGetChars->setObjectName("btnGetChars");

        gridLayout->addWidget(btnGetChars, 0, 2, 1, 1);


        verticalLayout->addLayout(gridLayout);

        groupBox = new QGroupBox(Widget);
        groupBox->setObjectName("groupBox");
        gridLayout_2 = new QGridLayout(groupBox);
        gridLayout_2->setObjectName("gridLayout_2");
        btnConvUTF16 = new QPushButton(groupBox);
        btnConvUTF16->setObjectName("btnConvUTF16");

        gridLayout_2->addWidget(btnConvUTF16, 0, 1, 1, 1);

        btnConvLatin1 = new QPushButton(groupBox);
        btnConvLatin1->setObjectName("btnConvLatin1");

        gridLayout_2->addWidget(btnConvLatin1, 0, 0, 1, 1);

        btnClear = new QPushButton(groupBox);
        btnClear->setObjectName("btnClear");

        gridLayout_2->addWidget(btnClear, 2, 1, 1, 1);

        btnCompare = new QPushButton(groupBox);
        btnCompare->setObjectName("btnCompare");

        gridLayout_2->addWidget(btnCompare, 2, 0, 1, 1);


        verticalLayout->addWidget(groupBox);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName("horizontalLayout_4");
        groupBox_3 = new QGroupBox(Widget);
        groupBox_3->setObjectName("groupBox_3");
        verticalLayout_3 = new QVBoxLayout(groupBox_3);
        verticalLayout_3->setObjectName("verticalLayout_3");
        plainTextEdit = new QPlainTextEdit(groupBox_3);
        plainTextEdit->setObjectName("plainTextEdit");

        verticalLayout_3->addWidget(plainTextEdit);


        horizontalLayout_4->addWidget(groupBox_3);

        groupBox_2 = new QGroupBox(Widget);
        groupBox_2->setObjectName("groupBox_2");
        verticalLayout_2 = new QVBoxLayout(groupBox_2);
        verticalLayout_2->setObjectName("verticalLayout_2");
        chkDigit = new QCheckBox(groupBox_2);
        chkDigit->setObjectName("chkDigit");

        verticalLayout_2->addWidget(chkDigit);

        chkLetter = new QCheckBox(groupBox_2);
        chkLetter->setObjectName("chkLetter");

        verticalLayout_2->addWidget(chkLetter);

        chkLetterOrNumber = new QCheckBox(groupBox_2);
        chkLetterOrNumber->setObjectName("chkLetterOrNumber");

        verticalLayout_2->addWidget(chkLetterOrNumber);

        chkLower = new QCheckBox(groupBox_2);
        chkLower->setObjectName("chkLower");

        verticalLayout_2->addWidget(chkLower);

        chkMark = new QCheckBox(groupBox_2);
        chkMark->setObjectName("chkMark");

        verticalLayout_2->addWidget(chkMark);

        chkPunct = new QCheckBox(groupBox_2);
        chkPunct->setObjectName("chkPunct");

        verticalLayout_2->addWidget(chkPunct);

        chkSpace = new QCheckBox(groupBox_2);
        chkSpace->setObjectName("chkSpace");

        verticalLayout_2->addWidget(chkSpace);

        chkSymbol = new QCheckBox(groupBox_2);
        chkSymbol->setObjectName("chkSymbol");

        verticalLayout_2->addWidget(chkSymbol);

        chkUpper = new QCheckBox(groupBox_2);
        chkUpper->setObjectName("chkUpper");

        verticalLayout_2->addWidget(chkUpper);


        horizontalLayout_4->addWidget(groupBox_2);


        verticalLayout->addLayout(horizontalLayout_4);


        retranslateUi(Widget);

        QMetaObject::connectSlotsByName(Widget);
    } // setupUi

    void retranslateUi(QWidget *Widget)
    {
        Widget->setWindowTitle(QCoreApplication::translate("Widget", "Widget", nullptr));
        editStr->setText(QCoreApplication::translate("Widget", "Hello,\351\235\222\345\262\233", nullptr));
        editChar->setText(QCoreApplication::translate("Widget", "a", nullptr));
        label_2->setText(QCoreApplication::translate("Widget", "\350\276\223\345\205\245\345\215\225\344\270\252\345\255\227\347\254\246", nullptr));
        btnCharJudge->setText(QCoreApplication::translate("Widget", "\345\215\225\344\270\252\345\255\227\347\254\246\347\211\271\346\200\247\345\210\244\346\226\255", nullptr));
        label->setText(QCoreApplication::translate("Widget", "\350\276\223\345\205\245\345\255\227\347\254\246\344\270\262", nullptr));
        btnGetChars->setText(QCoreApplication::translate("Widget", "\346\257\217\344\270\252\345\255\227\347\254\246\347\232\204Unicode", nullptr));
        groupBox->setTitle(QCoreApplication::translate("Widget", "\345\205\266\344\273\226\346\265\213\350\257\225\344\270\216\345\212\237\350\203\275", nullptr));
        btnConvUTF16->setText(QCoreApplication::translate("Widget", "\344\270\216UTF-16\347\232\204\350\275\254\346\215\242", nullptr));
        btnConvLatin1->setText(QCoreApplication::translate("Widget", "\344\270\216Latin1\347\232\204\350\275\254\346\215\242", nullptr));
        btnClear->setText(QCoreApplication::translate("Widget", "\346\270\205\347\251\272\346\226\207\346\234\254\346\241\206", nullptr));
        btnCompare->setText(QCoreApplication::translate("Widget", "QChar\346\257\224\350\276\203\344\270\216\346\233\277\346\215\242", nullptr));
        groupBox_3->setTitle(QCoreApplication::translate("Widget", "\347\273\223\346\236\234\346\230\276\347\244\272", nullptr));
        groupBox_2->setTitle(QCoreApplication::translate("Widget", "QChar\347\211\271\346\200\247\345\210\244\346\226\255", nullptr));
        chkDigit->setText(QCoreApplication::translate("Widget", "chkDigit", nullptr));
        chkLetter->setText(QCoreApplication::translate("Widget", "chkLetter", nullptr));
        chkLetterOrNumber->setText(QCoreApplication::translate("Widget", "chkLetterOrNumber", nullptr));
        chkLower->setText(QCoreApplication::translate("Widget", "chkLower", nullptr));
        chkMark->setText(QCoreApplication::translate("Widget", "chkMark", nullptr));
        chkPunct->setText(QCoreApplication::translate("Widget", "chkPunct", nullptr));
        chkSpace->setText(QCoreApplication::translate("Widget", "chkSpace", nullptr));
        chkSymbol->setText(QCoreApplication::translate("Widget", "chkSymbol", nullptr));
        chkUpper->setText(QCoreApplication::translate("Widget", "chkUpper", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Widget: public Ui_Widget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WIDGET_H
