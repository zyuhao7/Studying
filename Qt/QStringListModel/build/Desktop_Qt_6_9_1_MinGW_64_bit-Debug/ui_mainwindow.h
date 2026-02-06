/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.9.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QListView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPlainTextEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QHBoxLayout *horizontalLayout_2;
    QWidget *widget;
    QHBoxLayout *horizontalLayout;
    QGroupBox *groupBox;
    QVBoxLayout *verticalLayout;
    QGridLayout *gridLayout_2;
    QPushButton *btnListSort;
    QPushButton *btnListMoveDown;
    QPushButton *btnListInsert;
    QPushButton *btnInitList;
    QCheckBox *chkEditable;
    QPushButton *btnListAppend;
    QPushButton *btnListMoveUp;
    QPushButton *btnListDelete;
    QPushButton *btnListClear;
    QListView *listView;
    QGroupBox *groupBox_2;
    QVBoxLayout *verticalLayout_3;
    QVBoxLayout *verticalLayout_2;
    QPushButton *pushButton;
    QPushButton *pushButton_2;
    QPlainTextEdit *plainTextEdit;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(580, 350);
        MainWindow->setMaximumSize(QSize(580, 370));
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        horizontalLayout_2 = new QHBoxLayout(centralwidget);
        horizontalLayout_2->setObjectName("horizontalLayout_2");
        widget = new QWidget(centralwidget);
        widget->setObjectName("widget");
        horizontalLayout = new QHBoxLayout(widget);
        horizontalLayout->setObjectName("horizontalLayout");
        groupBox = new QGroupBox(widget);
        groupBox->setObjectName("groupBox");
        verticalLayout = new QVBoxLayout(groupBox);
        verticalLayout->setObjectName("verticalLayout");
        gridLayout_2 = new QGridLayout();
        gridLayout_2->setObjectName("gridLayout_2");
        btnListSort = new QPushButton(groupBox);
        btnListSort->setObjectName("btnListSort");
        btnListSort->setCheckable(true);

        gridLayout_2->addWidget(btnListSort, 2, 2, 1, 1);

        btnListMoveDown = new QPushButton(groupBox);
        btnListMoveDown->setObjectName("btnListMoveDown");

        gridLayout_2->addWidget(btnListMoveDown, 2, 1, 1, 1);

        btnListInsert = new QPushButton(groupBox);
        btnListInsert->setObjectName("btnListInsert");

        gridLayout_2->addWidget(btnListInsert, 1, 1, 1, 1);

        btnInitList = new QPushButton(groupBox);
        btnInitList->setObjectName("btnInitList");

        gridLayout_2->addWidget(btnInitList, 0, 0, 1, 1);

        chkEditable = new QCheckBox(groupBox);
        chkEditable->setObjectName("chkEditable");
        chkEditable->setChecked(true);

        gridLayout_2->addWidget(chkEditable, 0, 2, 1, 1);

        btnListAppend = new QPushButton(groupBox);
        btnListAppend->setObjectName("btnListAppend");

        gridLayout_2->addWidget(btnListAppend, 1, 0, 1, 1);

        btnListMoveUp = new QPushButton(groupBox);
        btnListMoveUp->setObjectName("btnListMoveUp");

        gridLayout_2->addWidget(btnListMoveUp, 2, 0, 1, 1);

        btnListDelete = new QPushButton(groupBox);
        btnListDelete->setObjectName("btnListDelete");

        gridLayout_2->addWidget(btnListDelete, 1, 2, 1, 1);

        btnListClear = new QPushButton(groupBox);
        btnListClear->setObjectName("btnListClear");

        gridLayout_2->addWidget(btnListClear, 0, 1, 1, 1);


        verticalLayout->addLayout(gridLayout_2);

        listView = new QListView(groupBox);
        listView->setObjectName("listView");

        verticalLayout->addWidget(listView);


        horizontalLayout->addWidget(groupBox);

        groupBox_2 = new QGroupBox(widget);
        groupBox_2->setObjectName("groupBox_2");
        verticalLayout_3 = new QVBoxLayout(groupBox_2);
        verticalLayout_3->setObjectName("verticalLayout_3");
        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName("verticalLayout_2");
        pushButton = new QPushButton(groupBox_2);
        pushButton->setObjectName("pushButton");

        verticalLayout_2->addWidget(pushButton);

        pushButton_2 = new QPushButton(groupBox_2);
        pushButton_2->setObjectName("pushButton_2");

        verticalLayout_2->addWidget(pushButton_2);


        verticalLayout_3->addLayout(verticalLayout_2);

        plainTextEdit = new QPlainTextEdit(groupBox_2);
        plainTextEdit->setObjectName("plainTextEdit");

        verticalLayout_3->addWidget(plainTextEdit);


        horizontalLayout->addWidget(groupBox_2);


        horizontalLayout_2->addWidget(widget);

        MainWindow->setCentralWidget(centralwidget);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName("statusbar");
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        groupBox->setTitle(QCoreApplication::translate("MainWindow", "ListView", nullptr));
        btnListSort->setText(QCoreApplication::translate("MainWindow", "\346\216\222\345\272\217", nullptr));
        btnListMoveDown->setText(QCoreApplication::translate("MainWindow", "\344\270\213\347\247\273", nullptr));
        btnListInsert->setText(QCoreApplication::translate("MainWindow", "\346\217\222\345\205\245\351\241\271", nullptr));
        btnInitList->setText(QCoreApplication::translate("MainWindow", "\346\201\242\345\244\215\345\210\227\350\241\250", nullptr));
        chkEditable->setText(QCoreApplication::translate("MainWindow", "\345\205\201\350\256\270\347\274\226\350\276\221", nullptr));
        btnListAppend->setText(QCoreApplication::translate("MainWindow", "\346\267\273\345\212\240\351\241\271", nullptr));
        btnListMoveUp->setText(QCoreApplication::translate("MainWindow", "\344\270\212\347\247\273", nullptr));
        btnListDelete->setText(QCoreApplication::translate("MainWindow", "\345\210\240\351\231\244\351\241\271", nullptr));
        btnListClear->setText(QCoreApplication::translate("MainWindow", "\346\270\205\351\231\244\345\210\227\350\241\250", nullptr));
        groupBox_2->setTitle(QCoreApplication::translate("MainWindow", "PlainTextEdit", nullptr));
        pushButton->setText(QCoreApplication::translate("MainWindow", "\346\270\205\347\251\272\346\226\207\346\234\254", nullptr));
        pushButton_2->setText(QCoreApplication::translate("MainWindow", "\346\230\276\347\244\272\346\225\260\346\215\256\346\250\241\345\236\213\347\232\204StringList", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
