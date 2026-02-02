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
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Widget
{
public:
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QPushButton *btnAlign_Left;
    QPushButton *btnAlign_Center;
    QPushButton *btnAlign_Right;
    QHBoxLayout *horizontalLayout_2;
    QPushButton *btnFont_Bold;
    QPushButton *btnFont_Italic;
    QPushButton *btnFont_UnderLine;
    QGroupBox *groupBox;
    QHBoxLayout *horizontalLayout_3;
    QCheckBox *chkBox_Readonly;
    QCheckBox *chkBox_Enable;
    QCheckBox *chkBox_ClearButton;
    QGroupBox *groupBox_2;
    QHBoxLayout *horizontalLayout_4;
    QRadioButton *radioBlack;
    QRadioButton *radioRed;
    QRadioButton *radioBlue;
    QLineEdit *lineEdit;

    void setupUi(QWidget *Widget)
    {
        if (Widget->objectName().isEmpty())
            Widget->setObjectName("Widget");
        Widget->resize(600, 600);
        Widget->setMaximumSize(QSize(600, 16777215));
        verticalLayout = new QVBoxLayout(Widget);
        verticalLayout->setObjectName("verticalLayout");
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName("horizontalLayout");
        btnAlign_Left = new QPushButton(Widget);
        btnAlign_Left->setObjectName("btnAlign_Left");
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/images/508.bmp"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        btnAlign_Left->setIcon(icon);

        horizontalLayout->addWidget(btnAlign_Left);

        btnAlign_Center = new QPushButton(Widget);
        btnAlign_Center->setObjectName("btnAlign_Center");
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/images/510.bmp"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        btnAlign_Center->setIcon(icon1);

        horizontalLayout->addWidget(btnAlign_Center);

        btnAlign_Right = new QPushButton(Widget);
        btnAlign_Right->setObjectName("btnAlign_Right");
        QIcon icon2;
        icon2.addFile(QString::fromUtf8(":/images/512.bmp"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        btnAlign_Right->setIcon(icon2);

        horizontalLayout->addWidget(btnAlign_Right);


        verticalLayout->addLayout(horizontalLayout);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName("horizontalLayout_2");
        btnFont_Bold = new QPushButton(Widget);
        btnFont_Bold->setObjectName("btnFont_Bold");
        QIcon icon3;
        icon3.addFile(QString::fromUtf8(":/images/500.bmp"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        btnFont_Bold->setIcon(icon3);
        btnFont_Bold->setCheckable(true);

        horizontalLayout_2->addWidget(btnFont_Bold);

        btnFont_Italic = new QPushButton(Widget);
        btnFont_Italic->setObjectName("btnFont_Italic");
        QIcon icon4;
        icon4.addFile(QString::fromUtf8(":/images/502.bmp"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        btnFont_Italic->setIcon(icon4);
        btnFont_Italic->setCheckable(true);
        btnFont_Italic->setChecked(false);

        horizontalLayout_2->addWidget(btnFont_Italic);

        btnFont_UnderLine = new QPushButton(Widget);
        btnFont_UnderLine->setObjectName("btnFont_UnderLine");
        QIcon icon5;
        icon5.addFile(QString::fromUtf8(":/images/504.bmp"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        btnFont_UnderLine->setIcon(icon5);
        btnFont_UnderLine->setCheckable(true);

        horizontalLayout_2->addWidget(btnFont_UnderLine);


        verticalLayout->addLayout(horizontalLayout_2);

        groupBox = new QGroupBox(Widget);
        groupBox->setObjectName("groupBox");
        groupBox->setMaximumSize(QSize(16777215, 200));
        horizontalLayout_3 = new QHBoxLayout(groupBox);
        horizontalLayout_3->setObjectName("horizontalLayout_3");
        chkBox_Readonly = new QCheckBox(groupBox);
        chkBox_Readonly->setObjectName("chkBox_Readonly");

        horizontalLayout_3->addWidget(chkBox_Readonly);

        chkBox_Enable = new QCheckBox(groupBox);
        chkBox_Enable->setObjectName("chkBox_Enable");

        horizontalLayout_3->addWidget(chkBox_Enable);

        chkBox_ClearButton = new QCheckBox(groupBox);
        chkBox_ClearButton->setObjectName("chkBox_ClearButton");

        horizontalLayout_3->addWidget(chkBox_ClearButton);


        verticalLayout->addWidget(groupBox);

        groupBox_2 = new QGroupBox(Widget);
        groupBox_2->setObjectName("groupBox_2");
        groupBox_2->setMaximumSize(QSize(16777215, 200));
        horizontalLayout_4 = new QHBoxLayout(groupBox_2);
        horizontalLayout_4->setObjectName("horizontalLayout_4");
        radioBlack = new QRadioButton(groupBox_2);
        radioBlack->setObjectName("radioBlack");

        horizontalLayout_4->addWidget(radioBlack);

        radioRed = new QRadioButton(groupBox_2);
        radioRed->setObjectName("radioRed");

        horizontalLayout_4->addWidget(radioRed);

        radioBlue = new QRadioButton(groupBox_2);
        radioBlue->setObjectName("radioBlue");

        horizontalLayout_4->addWidget(radioBlue);


        verticalLayout->addWidget(groupBox_2);

        lineEdit = new QLineEdit(Widget);
        lineEdit->setObjectName("lineEdit");
        lineEdit->setMaximumSize(QSize(600, 200));

        verticalLayout->addWidget(lineEdit);


        retranslateUi(Widget);

        QMetaObject::connectSlotsByName(Widget);
    } // setupUi

    void retranslateUi(QWidget *Widget)
    {
        Widget->setWindowTitle(QCoreApplication::translate("Widget", "Widget", nullptr));
        btnAlign_Left->setText(QCoreApplication::translate("Widget", "\345\261\205\345\267\246", nullptr));
        btnAlign_Center->setText(QCoreApplication::translate("Widget", "\345\261\205\344\270\255", nullptr));
        btnAlign_Right->setText(QCoreApplication::translate("Widget", "\345\261\205\345\217\263", nullptr));
        btnFont_Bold->setText(QCoreApplication::translate("Widget", "\347\262\227\344\275\223", nullptr));
        btnFont_Italic->setText(QCoreApplication::translate("Widget", "\346\226\234\344\275\223", nullptr));
        btnFont_UnderLine->setText(QCoreApplication::translate("Widget", "\344\270\213\345\210\222\347\272\277", nullptr));
        groupBox->setTitle(QString());
        chkBox_Readonly->setText(QCoreApplication::translate("Widget", "ReadOnly", nullptr));
        chkBox_Enable->setText(QCoreApplication::translate("Widget", "Enabled", nullptr));
        chkBox_ClearButton->setText(QCoreApplication::translate("Widget", "ClearButtonEnabled", nullptr));
        groupBox_2->setTitle(QString());
        radioBlack->setText(QCoreApplication::translate("Widget", "Black", nullptr));
        radioRed->setText(QCoreApplication::translate("Widget", "Red", nullptr));
        radioBlue->setText(QCoreApplication::translate("Widget", "Blue", nullptr));
        lineEdit->setText(QCoreApplication::translate("Widget", "\346\265\213\350\257\225\346\230\276\347\244\272\346\226\207\346\234\254", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Widget: public Ui_Widget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WIDGET_H
