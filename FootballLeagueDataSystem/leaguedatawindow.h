#ifndef LEAGUEDATAWINDOW_H
#define LEAGUEDATAWINDOW_H

#include <QMainWindow>
#include "playerdatawindow.h"
#include <QTableWidget>

//struct player_l{
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

//struct team_l{
//    QString name; //球队名
//    int fraction; //积分
//    int ranking; //排名
//    int numberGoal; //进球数
//    int numberLose; //失球数
//    QList<QString> playerNames;
//};

class Leaguedatawindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit Leaguedatawindow(QWidget *parent = nullptr);
    QString getTeamSelect();
    QString getPlayerSelect();
    void getData(QList<QString> teamNames, struct player players[], struct team teams[]);
    void showTable();
    void doTeamRankingShow();
    void doTeamLoseShow();
    void doTeamGoalShow();
    void doPlayerGoalShow();
    void doPlayerAssistShow();
    void doPlayerSaveShow();
    void doPlayerOnStageShow();
    void setCurrentSeason(QString season);

signals:
    void leagueDataWindowBack();
    void teamDataWindowShowAndGetTeam();
    void scheduleWindowShow();
    void playerDataWindowShowAndGetPlayer();

public slots:

private:
    QList<QString> teamNames;
    struct player players[1000];
    struct team teams[1000];
    QString nameSelect;
    QString playerNameSelect;
    QTableWidget *teamShow = new QTableWidget(this);
    QTableWidget *loseShow = new QTableWidget(this);
    QTableWidget *goalShow = new QTableWidget(this);
    QTableWidget *pgoalShow = new QTableWidget(this);
    QTableWidget *passistShow = new QTableWidget(this);
    QTableWidget *psaveShow = new QTableWidget(this);
    QTableWidget *ponstageShow = new QTableWidget(this);
    struct teamAndRanking teamTemp[20];
    struct teamAndLose loseTemp[20];
    struct teamAndGoal goalTemp[20];
    struct playerAndGoal pgoalTemp[1000];
    struct playerAndAssist passistTemp[1000];
    struct playerAndSave psaveTemp[1000];
    struct playerAndOnStage ponstageTemp[1000];
    QString currentSeason;
    QTableWidget *currentSeasonShow = new QTableWidget(this);
};

#endif // LEAGUEDATAWINDOW_H
