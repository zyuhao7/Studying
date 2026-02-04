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
#include <QtWidgets/QDial>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QProgressBar>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QScrollBar>
#include <QtWidgets/QSlider>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Widget
{
public:
    QVBoxLayout *verticalLayout;
    QGroupBox *groupBox;
    QHBoxLayout *horizontalLayout;
    QDial *dial;
    QGridLayout *gridLayout;
    QLabel *label;
    QLabel *label_2;
    QSlider *slider;
    QScrollBar *scrollBar;
    QGroupBox *groupBox_2;
    QVBoxLayout *verticalLayout_2;
    QFrame *frame;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label_3;
    QProgressBar *progressBar;
    QFrame *frame_2;
    QGridLayout *gridLayout_2;
    QSlider *horizontalSlider;
    QCheckBox *chkBox_Visible;
    QCheckBox *chkBox_Inverted;
    QRadioButton *radio_Percent;
    QRadioButton *radio_Value;

    void setupUi(QWidget *Widget)
    {
        if (Widget->objectName().isEmpty())
            Widget->setObjectName("Widget");
        Widget->resize(600, 600);
        Widget->setMaximumSize(QSize(600, 600));
        verticalLayout = new QVBoxLayout(Widget);
        verticalLayout->setObjectName("verticalLayout");
        groupBox = new QGroupBox(Widget);
        groupBox->setObjectName("groupBox");
        horizontalLayout = new QHBoxLayout(groupBox);
        horizontalLayout->setObjectName("horizontalLayout");
        dial = new QDial(groupBox);
        dial->setObjectName("dial");

        horizontalLayout->addWidget(dial);

        gridLayout = new QGridLayout();
        gridLayout->setObjectName("gridLayout");
        label = new QLabel(groupBox);
        label->setObjectName("label");

        gridLayout->addWidget(label, 1, 0, 1, 1);

        label_2 = new QLabel(groupBox);
        label_2->setObjectName("label_2");

        gridLayout->addWidget(label_2, 0, 0, 1, 1);

        slider = new QSlider(groupBox);
        slider->setObjectName("slider");
        slider->setMaximum(200);
        slider->setOrientation(Qt::Orientation::Horizontal);
        slider->setTickPosition(QSlider::TickPosition::TicksAbove);
        slider->setTickInterval(10);

        gridLayout->addWidget(slider, 0, 1, 1, 1);

        scrollBar = new QScrollBar(groupBox);
        scrollBar->setObjectName("scrollBar");
        scrollBar->setMaximum(200);
        scrollBar->setOrientation(Qt::Orientation::Horizontal);

        gridLayout->addWidget(scrollBar, 1, 1, 1, 1);


        horizontalLayout->addLayout(gridLayout);


        verticalLayout->addWidget(groupBox);

        groupBox_2 = new QGroupBox(Widget);
        groupBox_2->setObjectName("groupBox_2");
        verticalLayout_2 = new QVBoxLayout(groupBox_2);
        verticalLayout_2->setObjectName("verticalLayout_2");
        frame = new QFrame(groupBox_2);
        frame->setObjectName("frame");
        frame->setFrameShape(QFrame::Shape::StyledPanel);
        frame->setFrameShadow(QFrame::Shadow::Raised);
        horizontalLayout_2 = new QHBoxLayout(frame);
        horizontalLayout_2->setObjectName("horizontalLayout_2");
        label_3 = new QLabel(frame);
        label_3->setObjectName("label_3");

        horizontalLayout_2->addWidget(label_3);

        progressBar = new QProgressBar(frame);
        progressBar->setObjectName("progressBar");
        progressBar->setMaximum(200);
        progressBar->setValue(24);

        horizontalLayout_2->addWidget(progressBar);


        verticalLayout_2->addWidget(frame);

        frame_2 = new QFrame(groupBox_2);
        frame_2->setObjectName("frame_2");
        frame_2->setFrameShape(QFrame::Shape::StyledPanel);
        frame_2->setFrameShadow(QFrame::Shadow::Raised);
        gridLayout_2 = new QGridLayout(frame_2);
        gridLayout_2->setObjectName("gridLayout_2");
        horizontalSlider = new QSlider(frame_2);
        horizontalSlider->setObjectName("horizontalSlider");
        horizontalSlider->setOrientation(Qt::Orientation::Horizontal);

        gridLayout_2->addWidget(horizontalSlider, 0, 0, 1, 2);

        chkBox_Visible = new QCheckBox(frame_2);
        chkBox_Visible->setObjectName("chkBox_Visible");

        gridLayout_2->addWidget(chkBox_Visible, 1, 0, 1, 1);

        chkBox_Inverted = new QCheckBox(frame_2);
        chkBox_Inverted->setObjectName("chkBox_Inverted");

        gridLayout_2->addWidget(chkBox_Inverted, 1, 1, 1, 1);

        radio_Percent = new QRadioButton(frame_2);
        radio_Percent->setObjectName("radio_Percent");

        gridLayout_2->addWidget(radio_Percent, 2, 0, 1, 1);

        radio_Value = new QRadioButton(frame_2);
        radio_Value->setObjectName("radio_Value");

        gridLayout_2->addWidget(radio_Value, 2, 1, 1, 1);


        verticalLayout_2->addWidget(frame_2);


        verticalLayout->addWidget(groupBox_2);


        retranslateUi(Widget);

        QMetaObject::connectSlotsByName(Widget);
    } // setupUi

    void retranslateUi(QWidget *Widget)
    {
        Widget->setWindowTitle(QCoreApplication::translate("Widget", "Widget", nullptr));
        groupBox->setTitle(QCoreApplication::translate("Widget", "\346\273\221\345\212\250\350\276\223\345\205\245", nullptr));
        label->setText(QCoreApplication::translate("Widget", "\345\215\267\346\273\232\346\235\241", nullptr));
        label_2->setText(QCoreApplication::translate("Widget", "\346\273\221\345\212\250\346\235\241", nullptr));
        groupBox_2->setTitle(QCoreApplication::translate("Widget", "ProgressBar\346\230\276\347\244\272\344\270\216\350\256\276\347\275\256", nullptr));
        label_3->setText(QCoreApplication::translate("Widget", "\350\277\233\345\272\246\346\235\241", nullptr));
        chkBox_Visible->setText(QCoreApplication::translate("Widget", "textVisble", nullptr));
        chkBox_Inverted->setText(QCoreApplication::translate("Widget", "invertedAppearance", nullptr));
        radio_Percent->setText(QCoreApplication::translate("Widget", "\346\230\276\347\244\272\346\240\274\345\274\217--\347\231\276\345\210\206\346\257\224", nullptr));
        radio_Value->setText(QCoreApplication::translate("Widget", "\346\230\276\347\244\272\346\240\274\345\274\217--\345\275\223\345\211\215\345\200\274", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Widget: public Ui_Widget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WIDGET_H
