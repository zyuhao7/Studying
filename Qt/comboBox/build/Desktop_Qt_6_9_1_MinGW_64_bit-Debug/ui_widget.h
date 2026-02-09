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
#include <QtWidgets/QComboBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QPlainTextEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Widget
{
public:
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QGroupBox *groupBox_2;
    QGridLayout *gridLayout;
    QCheckBox *chkBoxEditable;
    QPushButton *btnInitItems;
    QPushButton *btnClearItems;
    QComboBox *comboBox_2;
    QGroupBox *groupBox_3;
    QVBoxLayout *verticalLayout_2;
    QPushButton *pushButton_2;
    QComboBox *comboBox;
    QGroupBox *groupBox;
    QVBoxLayout *verticalLayout_3;
    QPushButton *btnClearText;
    QPlainTextEdit *plainTextEdit;

    void setupUi(QWidget *Widget)
    {
        if (Widget->objectName().isEmpty())
            Widget->setObjectName("Widget");
        Widget->resize(800, 600);
        verticalLayout = new QVBoxLayout(Widget);
        verticalLayout->setObjectName("verticalLayout");
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName("horizontalLayout");
        groupBox_2 = new QGroupBox(Widget);
        groupBox_2->setObjectName("groupBox_2");
        gridLayout = new QGridLayout(groupBox_2);
        gridLayout->setObjectName("gridLayout");
        chkBoxEditable = new QCheckBox(groupBox_2);
        chkBoxEditable->setObjectName("chkBoxEditable");

        gridLayout->addWidget(chkBoxEditable, 0, 2, 1, 1);

        btnInitItems = new QPushButton(groupBox_2);
        btnInitItems->setObjectName("btnInitItems");

        gridLayout->addWidget(btnInitItems, 0, 0, 1, 1);

        btnClearItems = new QPushButton(groupBox_2);
        btnClearItems->setObjectName("btnClearItems");

        gridLayout->addWidget(btnClearItems, 0, 1, 1, 1);

        comboBox_2 = new QComboBox(groupBox_2);
        QIcon icon;
        icon.addFile(QString::fromUtf8("icons/aim.ico"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        comboBox_2->addItem(icon, QString());
        QIcon icon1(QIcon::fromTheme(QIcon::ThemeIcon::AddressBookNew));
        comboBox_2->addItem(icon1, QString());
        comboBox_2->setObjectName("comboBox_2");

        gridLayout->addWidget(comboBox_2, 1, 0, 1, 3);


        horizontalLayout->addWidget(groupBox_2);

        groupBox_3 = new QGroupBox(Widget);
        groupBox_3->setObjectName("groupBox_3");
        verticalLayout_2 = new QVBoxLayout(groupBox_3);
        verticalLayout_2->setObjectName("verticalLayout_2");
        pushButton_2 = new QPushButton(groupBox_3);
        pushButton_2->setObjectName("pushButton_2");

        verticalLayout_2->addWidget(pushButton_2);

        comboBox = new QComboBox(groupBox_3);
        comboBox->addItem(QString::fromUtf8(""));
        comboBox->setObjectName("comboBox");

        verticalLayout_2->addWidget(comboBox);


        horizontalLayout->addWidget(groupBox_3);


        verticalLayout->addLayout(horizontalLayout);

        groupBox = new QGroupBox(Widget);
        groupBox->setObjectName("groupBox");
        verticalLayout_3 = new QVBoxLayout(groupBox);
        verticalLayout_3->setObjectName("verticalLayout_3");
        btnClearText = new QPushButton(groupBox);
        btnClearText->setObjectName("btnClearText");

        verticalLayout_3->addWidget(btnClearText);

        plainTextEdit = new QPlainTextEdit(groupBox);
        plainTextEdit->setObjectName("plainTextEdit");

        verticalLayout_3->addWidget(plainTextEdit);


        verticalLayout->addWidget(groupBox);


        retranslateUi(Widget);

        QMetaObject::connectSlotsByName(Widget);
    } // setupUi

    void retranslateUi(QWidget *Widget)
    {
        Widget->setWindowTitle(QCoreApplication::translate("Widget", "Widget", nullptr));
        groupBox_2->setTitle(QCoreApplication::translate("Widget", "\347\256\200\345\215\225ComboBox", nullptr));
        chkBoxEditable->setText(QCoreApplication::translate("Widget", "\345\217\257\347\274\226\350\276\221", nullptr));
        btnInitItems->setText(QCoreApplication::translate("Widget", "\345\210\235\345\247\213\345\214\226\345\210\227\350\241\250", nullptr));
        btnClearItems->setText(QCoreApplication::translate("Widget", "\346\270\205\347\251\272\345\210\227\350\241\250", nullptr));
        comboBox_2->setItemText(0, QCoreApplication::translate("Widget", "\345\244\251\346\264\245\345\270\202", nullptr));
        comboBox_2->setItemText(1, QCoreApplication::translate("Widget", "\345\214\227\344\272\254\345\270\202", nullptr));

        groupBox_3->setTitle(QCoreApplication::translate("Widget", "\347\224\261\347\224\250\346\210\267\346\225\260\346\215\256\347\232\204ComboBox", nullptr));
        pushButton_2->setText(QCoreApplication::translate("Widget", "\345\210\235\345\247\213\345\214\226\345\237\216\345\270\202 + \345\214\272\345\217\267", nullptr));

#if QT_CONFIG(tooltip)
        comboBox->setToolTip(QString());
#endif // QT_CONFIG(tooltip)
        comboBox->setPlaceholderText(QCoreApplication::translate("Widget", "\350\257\267\351\200\211\346\213\251\344\270\200\344\270\252\345\237\216\345\270\202", nullptr));
        groupBox->setTitle(QCoreApplication::translate("Widget", "\344\277\241\346\201\257\346\230\276\347\244\272", nullptr));
        btnClearText->setText(QCoreApplication::translate("Widget", "\346\270\205\347\251\272\346\226\207\346\234\254\346\241\206", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Widget: public Ui_Widget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WIDGET_H
