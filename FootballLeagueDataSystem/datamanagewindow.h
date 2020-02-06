#ifndef DATAMANAGEWINDOW_H
#define DATAMANAGEWINDOW_H

#include <QMainWindow>
#include "playerdatawindow.h"
#include <QTableWidget>
#include <QPushButton>
#include <QComboBox>

//struct player_m{
//    QString name; //姓名
//    QString nation; //国籍
//    QString postion; //场上位置
//    QString team; //所属球队
//    int age; //年龄
//    int id; //场上号码
//    int numberStage; //出场数
//    int numberGoal; //进球数
//    int numberAssist; //助攻数
//    int numberSave; //扑救数
//};

//struct team_m{
//    QString name; //球队名
//    int fraction; //积分
//    int ranking; //排名
//    int numberGoal; //进球数
//    int numberLose; //失球数
//    QList<QString> playerNames;
//};

//struct matchKind_m{
//    int matchTeamA, matchTeamB;
//    int fractionA, fractionB;
//};

class datamanagewindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit datamanagewindow(QWidget *parent = nullptr);
    void getData(QList<QString> teamNames, struct player players[], struct team teams[], QList<struct matchKind> matchs[]);
    void manageTableShow();
    void playerAndTeamManageTableShow(int indexTeam);
    void playerAndTeamUpdateDataBTN(int indexTeam);
    void tableInit();
    void setIfChangable(int flag);

signals:
    void dataManageWindowBack();

public slots:

private:
    bool flag;
    int indexTeamBtn;
    QList<QString> teamNames;
    struct player players[1000];
    struct team teams[1000];
    QList<struct matchKind> matchs[38];
    struct teamAndFraction teamFractionTemp[20];
    QTableWidget *playerDataManageShow = new QTableWidget(this);
    QTableWidget *teamDataManageShow = new QTableWidget(this);
    QTableWidget *scheduleDataManageShow = new QTableWidget(this);
    QTabWidget *manageAll = new QTabWidget(this);
    QComboBox *interfaceSelect = new QComboBox(this);
    bool changable;
};

#endif // DATAMANAGEWINDOW_H
