/********************************************************************************
** Form generated from reading UI file 'widget.ui'
**
** Created by: Qt User Interface Compiler version 6.9.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_WIDGET_H
#define UI_WIDGET_H

#include <QtCore/QDate>
#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCalendarWidget>
#include <QtWidgets/QDateEdit>
#include <QtWidgets/QDateTimeEdit>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTimeEdit>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Widget
{
public:
    QHBoxLayout *horizontalLayout;
    QGroupBox *groupBox;
    QGridLayout *gridLayout_2;
    QPushButton *pushButton;
    QLabel *label_2;
    QLabel *label_3;
    QTimeEdit *timeEdit;
    QLineEdit *editTime;
    QPushButton *btnDebugTime;
    QPushButton *btnSetTime;
    QLabel *label_4;
    QDateEdit *dateEdit;
    QLineEdit *editDate;
    QPushButton *btnDebugDate;
    QPushButton *btnSetDate;
    QLabel *label;
    QDateTimeEdit *dateTimeEdit;
    QLineEdit *editDateTime;
    QPushButton *btnDebugDateTime;
    QPushButton *btnSetDateTime;
    QGroupBox *groupBox_2;
    QGridLayout *gridLayout;
    QLabel *label_5;
    QLineEdit *lineEdit;
    QCalendarWidget *calendarWidget;

    void setupUi(QWidget *Widget)
    {
        if (Widget->objectName().isEmpty())
            Widget->setObjectName("Widget");
        Widget->resize(800, 600);
        horizontalLayout = new QHBoxLayout(Widget);
        horizontalLayout->setObjectName("horizontalLayout");
        groupBox = new QGroupBox(Widget);
        groupBox->setObjectName("groupBox");
        gridLayout_2 = new QGridLayout(groupBox);
        gridLayout_2->setObjectName("gridLayout_2");
        pushButton = new QPushButton(groupBox);
        pushButton->setObjectName("pushButton");

        gridLayout_2->addWidget(pushButton, 0, 0, 1, 2);

        label_2 = new QLabel(groupBox);
        label_2->setObjectName("label_2");

        gridLayout_2->addWidget(label_2, 0, 2, 1, 1);

        label_3 = new QLabel(groupBox);
        label_3->setObjectName("label_3");

        gridLayout_2->addWidget(label_3, 1, 0, 1, 1);

        timeEdit = new QTimeEdit(groupBox);
        timeEdit->setObjectName("timeEdit");
        timeEdit->setTime(QTime(8, 31, 0));

        gridLayout_2->addWidget(timeEdit, 1, 1, 1, 1);

        editTime = new QLineEdit(groupBox);
        editTime->setObjectName("editTime");
        editTime->setMaxLength(8);

        gridLayout_2->addWidget(editTime, 1, 2, 1, 1);

        btnDebugTime = new QPushButton(groupBox);
        btnDebugTime->setObjectName("btnDebugTime");

        gridLayout_2->addWidget(btnDebugTime, 2, 1, 1, 1);

        btnSetTime = new QPushButton(groupBox);
        btnSetTime->setObjectName("btnSetTime");

        gridLayout_2->addWidget(btnSetTime, 2, 2, 1, 1);

        label_4 = new QLabel(groupBox);
        label_4->setObjectName("label_4");

        gridLayout_2->addWidget(label_4, 3, 0, 1, 1);

        dateEdit = new QDateEdit(groupBox);
        dateEdit->setObjectName("dateEdit");
        dateEdit->setTime(QTime(0, 0, 0));
        dateEdit->setDate(QDate(2026, 2, 7));

        gridLayout_2->addWidget(dateEdit, 3, 1, 1, 1);

        editDate = new QLineEdit(groupBox);
        editDate->setObjectName("editDate");

        gridLayout_2->addWidget(editDate, 3, 2, 1, 1);

        btnDebugDate = new QPushButton(groupBox);
        btnDebugDate->setObjectName("btnDebugDate");

        gridLayout_2->addWidget(btnDebugDate, 4, 1, 1, 1);

        btnSetDate = new QPushButton(groupBox);
        btnSetDate->setObjectName("btnSetDate");

        gridLayout_2->addWidget(btnSetDate, 4, 2, 1, 1);

        label = new QLabel(groupBox);
        label->setObjectName("label");

        gridLayout_2->addWidget(label, 5, 0, 1, 1);

        dateTimeEdit = new QDateTimeEdit(groupBox);
        dateTimeEdit->setObjectName("dateTimeEdit");
        dateTimeEdit->setDateTime(QDateTime(QDate(2026, 2, 7), QTime(8, 40, 0)));
        dateTimeEdit->setDate(QDate(2026, 2, 7));

        gridLayout_2->addWidget(dateTimeEdit, 5, 1, 1, 1);

        editDateTime = new QLineEdit(groupBox);
        editDateTime->setObjectName("editDateTime");

        gridLayout_2->addWidget(editDateTime, 5, 2, 1, 1);

        btnDebugDateTime = new QPushButton(groupBox);
        btnDebugDateTime->setObjectName("btnDebugDateTime");

        gridLayout_2->addWidget(btnDebugDateTime, 6, 1, 1, 1);

        btnSetDateTime = new QPushButton(groupBox);
        btnSetDateTime->setObjectName("btnSetDateTime");

        gridLayout_2->addWidget(btnSetDateTime, 6, 2, 1, 1);


        horizontalLayout->addWidget(groupBox);

        groupBox_2 = new QGroupBox(Widget);
        groupBox_2->setObjectName("groupBox_2");
        gridLayout = new QGridLayout(groupBox_2);
        gridLayout->setObjectName("gridLayout");
        label_5 = new QLabel(groupBox_2);
        label_5->setObjectName("label_5");

        gridLayout->addWidget(label_5, 0, 0, 1, 1);

        lineEdit = new QLineEdit(groupBox_2);
        lineEdit->setObjectName("lineEdit");

        gridLayout->addWidget(lineEdit, 0, 1, 1, 1);

        calendarWidget = new QCalendarWidget(groupBox_2);
        calendarWidget->setObjectName("calendarWidget");

        gridLayout->addWidget(calendarWidget, 1, 0, 1, 2);


        horizontalLayout->addWidget(groupBox_2);


        retranslateUi(Widget);

        QMetaObject::connectSlotsByName(Widget);
    } // setupUi

    void retranslateUi(QWidget *Widget)
    {
        Widget->setWindowTitle(QCoreApplication::translate("Widget", "Widget", nullptr));
        groupBox->setTitle(QCoreApplication::translate("Widget", "\346\227\245\346\234\237\346\227\266\351\227\264", nullptr));
        pushButton->setText(QCoreApplication::translate("Widget", "\350\257\273\345\217\226\345\275\223\345\211\215\346\227\245\346\234\237\346\227\266\351\227\264", nullptr));
        label_2->setText(QCoreApplication::translate("Widget", "                            \345\255\227\347\254\246\344\270\262\346\230\276\347\244\272", nullptr));
        label_3->setText(QCoreApplication::translate("Widget", "\346\227\266\351\227\264", nullptr));
        editTime->setInputMask(QCoreApplication::translate("Widget", "99:99:99;_", nullptr));
        editTime->setText(QCoreApplication::translate("Widget", "::", nullptr));
        btnDebugTime->setText(QCoreApplication::translate("Widget", "qDebug--Time", nullptr));
        btnSetTime->setText(QCoreApplication::translate("Widget", "\350\256\276\347\275\256\346\227\266\351\227\264fromString", nullptr));
        label_4->setText(QCoreApplication::translate("Widget", "\346\227\245\346\234\237", nullptr));
        dateEdit->setDisplayFormat(QCoreApplication::translate("Widget", "yyyy\345\271\264M\346\234\210d\346\227\245", nullptr));
        editDate->setInputMask(QCoreApplication::translate("Widget", "9999-99-99", nullptr));
        editDate->setText(QCoreApplication::translate("Widget", "--", nullptr));
        btnDebugDate->setText(QCoreApplication::translate("Widget", "qDebug--Date", nullptr));
        btnSetDate->setText(QCoreApplication::translate("Widget", "\350\256\276\347\275\256\346\227\245\346\234\237fromString", nullptr));
        label->setText(QCoreApplication::translate("Widget", "\346\227\245\346\234\237\346\227\266\351\227\264", nullptr));
        dateTimeEdit->setDisplayFormat(QCoreApplication::translate("Widget", "yyyy-MM-dd HH:mm:ss", nullptr));
        editDateTime->setInputMask(QCoreApplication::translate("Widget", "9999-99-99 99:99:99", nullptr));
        editDateTime->setText(QCoreApplication::translate("Widget", "-- ::", nullptr));
        btnDebugDateTime->setText(QCoreApplication::translate("Widget", "qDebug--DateTime", nullptr));
        btnSetDateTime->setText(QCoreApplication::translate("Widget", "\346\227\245\346\234\237\346\227\266\351\227\264fromString", nullptr));
        groupBox_2->setTitle(QCoreApplication::translate("Widget", "\346\227\245\345\216\206\351\200\211\346\213\251", nullptr));
        label_5->setText(QCoreApplication::translate("Widget", "\351\200\211\346\213\251\347\232\204\346\227\245\346\234\237:", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Widget: public Ui_Widget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WIDGET_H
