#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
signals:
    void startConnect(unsigned short, QString);
    void sendFile(QString);
private slots:
    void on_connectSrv_clicked();

    void on_chooseFile_clicked();

    void on_sendFile_clicked();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
