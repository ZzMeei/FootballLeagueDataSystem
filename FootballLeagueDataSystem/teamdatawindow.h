#ifndef TEAMDATAWINDOW_H
#define TEAMDATAWINDOW_H

#include <QMainWindow>
#include "playerdatawindow.h"
#include <QTabWidget>
#include <QTableWidget>
#include <QComboBox>

//struct player_t{
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

//struct team_t{
//    QString name; //球队名
//    int fraction; //积分
//    int ranking; //排名
//    int numberGoal; //进球数
//    int numberLose; //失球数
//    QList<QString> playerNames;
//};

//struct matchKind_t{
//    int matchTeamA, matchTeamB;
//    int fractionA, fractionB;
//};

class teamdatawindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit teamdatawindow(QWidget *parent = nullptr);
    void setTeamNameNow(int index);
    void showTable();
    void getData(struct player players[], struct team teams[], QList<struct matchKind> matchs[]);
    QString getPlayerSelect();
    void showAttributes();
    void showAll();
    void showRankingAll();
    void rankingTableInit();
    void teamScheduleShow();
    void teamScheduleInit();
    void clearAllTableWidget();
    void hideAllTabWidget();

signals:
    void teamDataWindowBackToLeague();
    void teamDataWindowBackToSchedule();
    void playerDataWindowShowAndGetPlayer();

public slots:

private:
    bool flag;
    int indexTeam;
    struct player players[1000];
    struct team teams[1000];
    QList<struct matchKind> matchs[38];
    QString playerSelect;
    QTabWidget *playerAll = new QTabWidget(this);
    QTableWidget *playerShowForWard = new QTableWidget(this);
    QTableWidget *playerShowMidfield = new QTableWidget(this);
    QTableWidget *playerShowDefender = new QTableWidget(this);
    QTableWidget *playerShowGoalkeeper = new QTableWidget(this);
    QTableWidget *attributesTable = new QTableWidget(this);
    QComboBox *interfaceSelect = new QComboBox(this);
    QTabWidget *rankingAll = new QTabWidget(this);
    QTableWidget *playerGoalRanking = new QTableWidget(this);
    QTableWidget *playerAssistRanking = new QTableWidget(this);
    QTableWidget *playerSaveRanking = new QTableWidget(this);
    QTableWidget *playerOnstageRanking = new QTableWidget(this);
    QTabWidget *scheduleAll = new QTabWidget(this);
    QTableWidget *teamSchedule = new QTableWidget(this);
    struct playerAndGoal pgoalTemp[1000];
    struct playerAndAssist passistTemp[1000];
    struct playerAndSave psaveTemp[1000];
    struct playerAndOnStage ponstageTemp[1000];
};

#endif // TEAMDATAWINDOW_H
