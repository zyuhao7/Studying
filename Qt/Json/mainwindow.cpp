#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    writeJsonFile();
    readJsonFile();

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::writeJsonFile()
{
    // 创建 JSON 对象
    QJsonObject jsonObject;
    jsonObject["name"] = "张三";
    jsonObject["age"] = 25;
    jsonObject["isStudent"] = false;

    // 创建 JSON 数组
    QJsonArray hobbiesArray;
    hobbiesArray.append("阅读");
    hobbiesArray.append("游泳");
    hobbiesArray.append("编程");
    jsonObject["hobbies"] = hobbiesArray;

    // 创建嵌套对象
    QJsonObject addressObject;
    addressObject["city"] = "北京";
    addressObject["street"] = "朝阳区";
    jsonObject["address"] = addressObject;

    // 创建 JSON 文档
    QJsonDocument jsonDoc(jsonObject);

    // 写入文件
    QFile file("data.json");
    if (file.open(QIODevice::WriteOnly)) {
        file.write(jsonDoc.toJson());
        file.close();
        qDebug() << "JSON 文件写入成功";
    }
}

void MainWindow::readJsonFile()
{
    QFile file("data.json");
    if (!file.open(QIODevice::ReadOnly)) {
        qWarning() << "无法打开文件";
        return;
    }

    QByteArray jsonData = file.readAll();
    file.close();

    QJsonDocument jsonDoc = QJsonDocument::fromJson(jsonData);

    if (jsonDoc.isNull() || !jsonDoc.isObject()) {
        qWarning() << "无效的 JSON 文档";
        return;
    }

    QJsonObject jsonObject = jsonDoc.object();

    // 读取基本值
    QString name = jsonObject["name"].toString();
    int age = jsonObject["age"].toInt();
    bool isStudent = jsonObject["isStudent"].toBool();

    qDebug() << "姓名:" << name;
    qDebug() << "年龄:" << age;
    qDebug() << "是否是学生:" << isStudent;

    // 读取数组
    QJsonArray hobbiesArray = jsonObject["hobbies"].toArray();
    qDebug() << "爱好:";
    for (const QJsonValue &value : hobbiesArray) {
        qDebug() << "  -" << value.toString();
    }

    // 读取嵌套对象
    QJsonObject addressObject = jsonObject["address"].toObject();
    QString city = addressObject["city"].toString();
    QString street = addressObject["street"].toString();
    qDebug() << "地址:" << "city: "<< city;
    qDebug()<<"stress: " << street << Qt::endl;
}


