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
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLCDNumber>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Widget
{
public:
    QVBoxLayout *verticalLayout;
    QGroupBox *groupBox;
    QGridLayout *gridLayout;
    QSpinBox *spinBox;
    QPushButton *btnStart;
    QRadioButton *radioContinue;
    QLabel *label;
    QRadioButton *radioOneShot;
    QPushButton *btnStop;
    QPushButton *btnOneShot;
    QGroupBox *groupBox_2;
    QHBoxLayout *horizontalLayout;
    QRadioButton *radioPricese;
    QRadioButton *radioCoarse;
    QRadioButton *radioVeryCoarse;
    QGroupBox *groupBox_3;
    QHBoxLayout *horizontalLayout_2;
    QLCDNumber *lcdHour;
    QLCDNumber *lcdMin;
    QLCDNumber *lcdSec;
    QLabel *label_2;

    void setupUi(QWidget *Widget)
    {
        if (Widget->objectName().isEmpty())
            Widget->setObjectName("Widget");
        Widget->resize(800, 600);
        verticalLayout = new QVBoxLayout(Widget);
        verticalLayout->setObjectName("verticalLayout");
        groupBox = new QGroupBox(Widget);
        groupBox->setObjectName("groupBox");
        gridLayout = new QGridLayout(groupBox);
        gridLayout->setObjectName("gridLayout");
        spinBox = new QSpinBox(groupBox);
        spinBox->setObjectName("spinBox");
        spinBox->setMaximum(100000);
        spinBox->setValue(1000);

        gridLayout->addWidget(spinBox, 1, 2, 1, 1);

        btnStart = new QPushButton(groupBox);
        btnStart->setObjectName("btnStart");

        gridLayout->addWidget(btnStart, 0, 1, 1, 1);

        radioContinue = new QRadioButton(groupBox);
        radioContinue->setObjectName("radioContinue");
        radioContinue->setChecked(true);

        gridLayout->addWidget(radioContinue, 1, 3, 1, 1);

        label = new QLabel(groupBox);
        label->setObjectName("label");

        gridLayout->addWidget(label, 1, 1, 1, 1);

        radioOneShot = new QRadioButton(groupBox);
        radioOneShot->setObjectName("radioOneShot");

        gridLayout->addWidget(radioOneShot, 1, 4, 1, 1);

        btnStop = new QPushButton(groupBox);
        btnStop->setObjectName("btnStop");

        gridLayout->addWidget(btnStop, 0, 2, 1, 1);

        btnOneShot = new QPushButton(groupBox);
        btnOneShot->setObjectName("btnOneShot");

        gridLayout->addWidget(btnOneShot, 0, 3, 1, 2);


        verticalLayout->addWidget(groupBox);

        groupBox_2 = new QGroupBox(Widget);
        groupBox_2->setObjectName("groupBox_2");
        horizontalLayout = new QHBoxLayout(groupBox_2);
        horizontalLayout->setObjectName("horizontalLayout");
        radioPricese = new QRadioButton(groupBox_2);
        radioPricese->setObjectName("radioPricese");
        radioPricese->setChecked(true);

        horizontalLayout->addWidget(radioPricese);

        radioCoarse = new QRadioButton(groupBox_2);
        radioCoarse->setObjectName("radioCoarse");

        horizontalLayout->addWidget(radioCoarse);

        radioVeryCoarse = new QRadioButton(groupBox_2);
        radioVeryCoarse->setObjectName("radioVeryCoarse");

        horizontalLayout->addWidget(radioVeryCoarse);


        verticalLayout->addWidget(groupBox_2);

        groupBox_3 = new QGroupBox(Widget);
        groupBox_3->setObjectName("groupBox_3");
        horizontalLayout_2 = new QHBoxLayout(groupBox_3);
        horizontalLayout_2->setObjectName("horizontalLayout_2");
        lcdHour = new QLCDNumber(groupBox_3);
        lcdHour->setObjectName("lcdHour");
        lcdHour->setDigitCount(2);
        lcdHour->setProperty("value", QVariant(8.000000000000000));

        horizontalLayout_2->addWidget(lcdHour);

        lcdMin = new QLCDNumber(groupBox_3);
        lcdMin->setObjectName("lcdMin");
        lcdMin->setDigitCount(2);
        lcdMin->setProperty("value", QVariant(22.000000000000000));

        horizontalLayout_2->addWidget(lcdMin);

        lcdSec = new QLCDNumber(groupBox_3);
        lcdSec->setObjectName("lcdSec");
        lcdSec->setDigitCount(2);
        lcdSec->setProperty("value", QVariant(50.000000000000000));

        horizontalLayout_2->addWidget(lcdSec);


        verticalLayout->addWidget(groupBox_3);

        label_2 = new QLabel(Widget);
        label_2->setObjectName("label_2");

        verticalLayout->addWidget(label_2);


        retranslateUi(Widget);

        QMetaObject::connectSlotsByName(Widget);
    } // setupUi

    void retranslateUi(QWidget *Widget)
    {
        Widget->setWindowTitle(QCoreApplication::translate("Widget", "Widget", nullptr));
        groupBox->setTitle(QCoreApplication::translate("Widget", "\345\256\232\346\227\266\345\231\250", nullptr));
        spinBox->setSuffix(QCoreApplication::translate("Widget", " ms", nullptr));
        btnStart->setText(QCoreApplication::translate("Widget", "\345\274\200\345\247\213", nullptr));
        radioContinue->setText(QCoreApplication::translate("Widget", "\350\277\236\347\273\255\345\256\232\346\227\266", nullptr));
        label->setText(QCoreApplication::translate("Widget", "                                                     \345\256\232\346\227\266\345\221\250\346\234\237", nullptr));
        radioOneShot->setText(QCoreApplication::translate("Widget", "\345\215\225\346\254\241\345\256\232\346\227\266", nullptr));
        btnStop->setText(QCoreApplication::translate("Widget", "\345\201\234\346\255\242", nullptr));
        btnOneShot->setText(QCoreApplication::translate("Widget", "\345\212\250\346\200\201\345\210\233\345\273\272\345\215\225\346\254\241\345\256\232\346\227\266\345\231\250", nullptr));
        groupBox_2->setTitle(QCoreApplication::translate("Widget", "\345\256\232\346\227\266\345\231\250\347\262\276\345\272\246", nullptr));
        radioPricese->setText(QCoreApplication::translate("Widget", "PreciseTimer", nullptr));
        radioCoarse->setText(QCoreApplication::translate("Widget", "CoarseTimer", nullptr));
        radioVeryCoarse->setText(QCoreApplication::translate("Widget", "VeryCoarseTimer", nullptr));
        groupBox_3->setTitle(QCoreApplication::translate("Widget", "\345\275\223\345\211\215\346\227\266\351\227\264(\345\260\217\346\227\266 \357\274\232\345\210\206 \357\274\232\347\247\222)", nullptr));
        label_2->setText(QCoreApplication::translate("Widget", "\346\265\201\351\200\235\347\232\204\346\227\266\351\227\264\357\274\232", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Widget: public Ui_Widget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WIDGET_H
