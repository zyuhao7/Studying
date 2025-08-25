#include "mybutton.h"

#include <QPainter>

MyButton::MyButton(QWidget *parent)
    : QWidget{parent}
{
    m_pixmap.load(":/build/ghost1.png");
    setFixedSize(m_pixmap.size());
}

void MyButton::mousePressEvent(QMouseEvent *ev)
{
    Q_UNUSED(ev);
     m_pixmap.load(":/build/ghost2.png");
    update();
     emit clicked();
}

void MyButton::mouseReleaseEvent(QMouseEvent *ev)
{
    Q_UNUSED(ev);
    m_pixmap.load(":/build/ghost1.png");
    update();
}

void MyButton::enterEvent(QEnterEvent *ev)
{
    Q_UNUSED(ev);
   m_pixmap.load(":/build/ghost3.png");
    update();
}

void MyButton::leaveEvent(QEvent *ev)
{
    Q_UNUSED(ev);
    m_pixmap.load(":/build/ghost1.png");
    update();
}

void MyButton::paintEvent(QPaintEvent *ev)
{
    Q_UNUSED(ev);
    QPainter p(this);
    p.drawPixmap(rect(), m_pixmap);

}
