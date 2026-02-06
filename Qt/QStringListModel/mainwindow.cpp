#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    m_strList << "北京" << "上海" << "深圳" << "广州" << "山东" << "陕西" << "四川" << "河南";
    m_model = new QStringListModel(this);
    m_model->setStringList(m_strList);
    ui->listView->setModel(m_model);
    ui->chkEditable->setCheckable(true);
    ui->listView->setEditTriggers(QAbstractItemView::DoubleClicked | QAbstractItemView::SelectedClicked);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_btnInitList_clicked()
{
    // "恢复列表" 按钮
    m_model->setStringList(m_strList);
}



void MainWindow::on_btnListClear_clicked()
{
    // "清除列表" 按钮
    m_model->removeRows(0, m_model->rowCount());
}


void MainWindow::on_btnListAppend_clicked()
{
    // "添加项" 按钮
    m_model->insertRow(m_model->rowCount());
    QModelIndex idx = m_model->index(m_model->rowCount() - 1, 0); // 获取刚插入项的模型索引
    m_model->setData(idx, "new item", Qt::DisplayRole);
    ui->listView->setCurrentIndex(idx);
}


void MainWindow::on_btnListInsert_clicked()
{
    // "插入项" 按钮
    QModelIndex idx = ui->listView->currentIndex();
    m_model->insertRow(idx.row());
    m_model->setData(idx, "inserted item", Qt::DisplayRole);
    ui->listView->setCurrentIndex(idx);
}


void MainWindow::on_btnListDelete_clicked()
{
    // "删除项" 按钮
    QModelIndex idx = ui->listView->currentIndex(); // 获取当前项的模型索引
    m_model->removeRow(idx.row());
}


void MainWindow::on_btnListMoveUp_clicked()
{
    // "上移" 按钮
    int curRow = ui->listView->currentIndex().row();
    QModelIndex idx = QModelIndex();
    m_model->moveRow(idx, curRow, idx, curRow - 1);
}


void MainWindow::on_btnListMoveDown_clicked()
{
    // "下移" 按钮
    int curRow = ui->listView->currentIndex().row();
    QModelIndex idx = QModelIndex();
    m_model->moveRow(idx, curRow, idx, curRow + 2);
}





void MainWindow::on_btnListSort_clicked(bool checked)
{
    // "排序" 按钮
    if(checked)
        m_model->sort(0, Qt::AscendingOrder); // 升序
    else
        m_model->sort(0, Qt::DescendingOrder);
}


void MainWindow::on_chkEditable_clicked(bool checked)
{
    // "允许编辑" 复选框
    if(checked)
        ui->listView->setEditTriggers(QAbstractItemView::DoubleClicked | QAbstractItemView::SelectedClicked);
    else
        ui->listView->setEditTriggers(QAbstractItemView::NoEditTriggers);
}





void MainWindow::on_listView_clicked(const QModelIndex &index)
{
    //  组件listView的 clicked() 信号的槽函数
    QString str1 = QString::asprintf("模型索引: row = %d, column = %d. ", index.row(), index.column());
    QVariant var = m_model->data(index, Qt::DisplayRole);
    QString str2 = var.toString();
    ui->statusbar->showMessage(str1 + str2);
}


void MainWindow::on_pushButton_clicked()
{
    ui->plainTextEdit->clear();
}


void MainWindow::on_pushButton_2_clicked()
{
    // "显示数据模型的 StringList" 按钮
    QStringList tmpList = m_model->stringList();
    ui->plainTextEdit->clear();
    for(int i = 0; i < tmpList.size(); ++i)
        ui->plainTextEdit->appendPlainText(tmpList.at(i));
}

