#ifndef MYBUTTON_H
#define MYBUTTON_H

#include <QPaintEvent>
#include <QPixmap>
#include <QWidget>

class MyButton : public QWidget
{
    Q_OBJECT
public:
    explicit MyButton(QWidget *parent = nullptr);
protected:
    void mousePressEvent(QMouseEvent* ev);
    void mouseReleaseEvent(QMouseEvent* ev);
    void enterEvent(QEnterEvent* ev);
    void leaveEvent(QEvent* ev);
    void paintEvent(QPaintEvent* ev);
signals:
    void clicked();
private:
    QPixmap m_pixmap;

};

#endif // MYBUTTON_H
