#include "adminverifywindow.h"
#include <QLabel>
#include <QPushButton>
#include <QLineEdit>
#include <QString>
#include <QDebug>
#include <QFile>
#include <QMessageBox>

adminverifywindow::adminverifywindow(QWidget *parent) : QMainWindow(parent)
{   
    QString name[100];
    QString code[100];

    setFixedSize(800, 500);

    QLabel *labelTitle = new QLabel("管理员登陆", this);
    labelTitle->move(330, 10);
    labelTitle->resize(200, 50);
    QFont ft;
    ft.setPointSize(20);
    labelTitle->setFont(ft);

    QLabel *labelUserName = new QLabel("管理员名", this);
    QLabel *labelUserCode = new QLabel("密码", this);
    labelUserName->move(250, 100);
    labelUserCode->move(250, 200);

    QPushButton *btnReturnTeam = new QPushButton("返回主界面", this);
    btnReturnTeam->move(700, 430);
    btnReturnTeam->resize(100, 50);

    connect(btnReturnTeam, &QPushButton::clicked, [=](){
        emit this->adminVerifWindowBack();
    });

    QLineEdit *userName = new QLineEdit(this);
    QLineEdit *userCode = new QLineEdit(this);
    userName->move(320, 100);
    userCode->move(320, 200);
    userName->resize(150, 30);
    userCode->resize(150, 30);
    userName->setEchoMode(QLineEdit::Normal);
    userCode->setEchoMode(QLineEdit::Password);

    QPushButton *btnGetText = new QPushButton("登陆", this);
    btnGetText->move(340, 300);
    btnGetText->resize(100, 50);

    int index = 0;
    QFile fileNameCode("/Users/yangqinjiang/Desktop/qt_project/data/AdministratorInformation.txt");
    if (fileNameCode.open(QIODevice::ReadOnly | QIODevice::Text)){
        QByteArray bytesIn;
        int flag = 0;
        while (!fileNameCode.atEnd()){
            bytesIn = fileNameCode.readLine();
            if (flag == 0){
                name[index].prepend(bytesIn);
                name[index] = name[index].mid(0, name[index].length() - 1);
                flag = 1;
                continue;
            }
            if (flag == 1){
                code[index].prepend(bytesIn);
                code[index] = code[index].mid(0, code[index].length() - 1);
                flag = 0;
                index++;
                continue;
            }
        }
        fileNameCode.close();
    }
    index--;
    connect(btnGetText, &QPushButton::clicked, this, [=](){
        QString strUserName, strUserCode;
        strUserName = userName->text();
        strUserCode = userCode->text();
        int i = 0;
        int flag = 0;
        while (flag == 0){
            if (i > index){
                flag = 2;
                break;
            }
            if ((name[i] == strUserName) && (code[i] == strUserCode)){
                flag = 1;
            }
            i++;
        }
        if (flag == 1){
            userName->clear();
            userCode->clear();
            emit this->adminVerifSucceed();
        }
        if (flag == 2){
            QMessageBox *qmb = new QMessageBox();
            qmb->information(this, "错误", "管理员名或者密码输入错误！");
            userName->clear();
            userCode->clear();
        }
    });

}
