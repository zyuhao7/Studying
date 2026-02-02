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
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
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
    QLabel *label;
    QSpinBox *spinNum;
    QLabel *label_2;
    QDoubleSpinBox *spinPrice;
    QLabel *label_3;
    QDoubleSpinBox *spinTotal;
    QPushButton *btnCal;
    QGroupBox *groupBox_2;
    QGridLayout *gridLayout_2;
    QLabel *label_4;
    QSpinBox *spinDec;
    QLabel *label_5;
    QSpinBox *spinBin;
    QLabel *label_6;
    QSpinBox *spinHex;

    void setupUi(QWidget *Widget)
    {
        if (Widget->objectName().isEmpty())
            Widget->setObjectName("Widget");
        Widget->resize(516, 600);
        Widget->setMaximumSize(QSize(516, 16777215));
        verticalLayout = new QVBoxLayout(Widget);
        verticalLayout->setObjectName("verticalLayout");
        groupBox = new QGroupBox(Widget);
        groupBox->setObjectName("groupBox");
        gridLayout = new QGridLayout(groupBox);
        gridLayout->setObjectName("gridLayout");
        label = new QLabel(groupBox);
        label->setObjectName("label");
        label->setMaximumSize(QSize(50, 16777215));

        gridLayout->addWidget(label, 0, 0, 1, 1);

        spinNum = new QSpinBox(groupBox);
        spinNum->setObjectName("spinNum");
        spinNum->setValue(4);

        gridLayout->addWidget(spinNum, 0, 1, 1, 1);

        label_2 = new QLabel(groupBox);
        label_2->setObjectName("label_2");

        gridLayout->addWidget(label_2, 0, 2, 1, 1);

        spinPrice = new QDoubleSpinBox(groupBox);
        spinPrice->setObjectName("spinPrice");
        spinPrice->setToolTipDuration(-1);
        spinPrice->setValue(11.570000000000000);

        gridLayout->addWidget(spinPrice, 0, 3, 1, 1);

        label_3 = new QLabel(groupBox);
        label_3->setObjectName("label_3");

        gridLayout->addWidget(label_3, 1, 2, 1, 1);

        spinTotal = new QDoubleSpinBox(groupBox);
        spinTotal->setObjectName("spinTotal");
        spinTotal->setMaximum(65535.000000000000000);

        gridLayout->addWidget(spinTotal, 1, 3, 1, 1);

        btnCal = new QPushButton(groupBox);
        btnCal->setObjectName("btnCal");

        gridLayout->addWidget(btnCal, 1, 1, 1, 1);


        verticalLayout->addWidget(groupBox);

        groupBox_2 = new QGroupBox(Widget);
        groupBox_2->setObjectName("groupBox_2");
        gridLayout_2 = new QGridLayout(groupBox_2);
        gridLayout_2->setObjectName("gridLayout_2");
        label_4 = new QLabel(groupBox_2);
        label_4->setObjectName("label_4");
        label_4->setMaximumSize(QSize(50, 16777215));

        gridLayout_2->addWidget(label_4, 0, 0, 1, 1);

        spinDec = new QSpinBox(groupBox_2);
        spinDec->setObjectName("spinDec");
        spinDec->setMaximum(65535);
        spinDec->setValue(12);

        gridLayout_2->addWidget(spinDec, 0, 1, 1, 1);

        label_5 = new QLabel(groupBox_2);
        label_5->setObjectName("label_5");

        gridLayout_2->addWidget(label_5, 1, 0, 1, 1);

        spinBin = new QSpinBox(groupBox_2);
        spinBin->setObjectName("spinBin");
        spinBin->setWrapping(false);
        spinBin->setMaximum(65535);
        spinBin->setValue(12);
        spinBin->setDisplayIntegerBase(2);

        gridLayout_2->addWidget(spinBin, 1, 1, 1, 1);

        label_6 = new QLabel(groupBox_2);
        label_6->setObjectName("label_6");

        gridLayout_2->addWidget(label_6, 2, 0, 1, 1);

        spinHex = new QSpinBox(groupBox_2);
        spinHex->setObjectName("spinHex");
        spinHex->setMaximum(65535);
        spinHex->setValue(12);
        spinHex->setDisplayIntegerBase(16);

        gridLayout_2->addWidget(spinHex, 2, 1, 1, 1);


        verticalLayout->addWidget(groupBox_2);


        retranslateUi(Widget);

        QMetaObject::connectSlotsByName(Widget);
    } // setupUi

    void retranslateUi(QWidget *Widget)
    {
        Widget->setWindowTitle(QCoreApplication::translate("Widget", "Widget", nullptr));
        groupBox->setTitle(QCoreApplication::translate("Widget", "\346\225\260\345\200\274\350\276\223\345\205\245\350\276\223\345\207\272", nullptr));
        label->setText(QCoreApplication::translate("Widget", "     \346\225\260\351\207\217", nullptr));
        spinNum->setSuffix(QCoreApplication::translate("Widget", " kg", nullptr));
        label_2->setText(QCoreApplication::translate("Widget", "                                                \345\215\225\344\273\267", nullptr));
        spinPrice->setPrefix(QCoreApplication::translate("Widget", "$ ", nullptr));
        label_3->setText(QCoreApplication::translate("Widget", "                                                \346\200\273\344\273\267", nullptr));
        spinTotal->setPrefix(QCoreApplication::translate("Widget", "$ ", nullptr));
        btnCal->setText(QCoreApplication::translate("Widget", "\350\256\241\347\256\227", nullptr));
        groupBox_2->setTitle(QCoreApplication::translate("Widget", "\350\277\233\345\210\266\350\275\254\346\215\242", nullptr));
        label_4->setText(QCoreApplication::translate("Widget", "\345\215\201 \350\277\233 \345\210\266", nullptr));
        spinDec->setPrefix(QCoreApplication::translate("Widget", "Dec   ", nullptr));
        label_5->setText(QCoreApplication::translate("Widget", "\344\272\214 \350\277\233 \345\210\266", nullptr));
        spinBin->setPrefix(QCoreApplication::translate("Widget", "Bin  ", nullptr));
        label_6->setText(QCoreApplication::translate("Widget", "\345\215\201 \345\205\255 \350\277\233 \345\210\266", nullptr));
        spinHex->setPrefix(QCoreApplication::translate("Widget", "Hex  ", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Widget: public Ui_Widget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WIDGET_H
