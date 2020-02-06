#ifndef SCHEDULEWINDOW_H
#define SCHEDULEWINDOW_H

#include <QMainWindow>
#include "playerdatawindow.h"
#include <QTableWidget>
#include <QTabWidget>

//struct team_s{
//    QString name; //球队名
//    int fraction; //积分
//    int ranking; //排名
//    int numberGoal; //进球数
//    int numberLose; //失球数
//    QList<QString> playerNames;
//};

//struct matchKind_s{
//    int matchTeamA, matchTeamB;
//    int fractionA, fractionB;
//};

class scheduleWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit scheduleWindow(QWidget *parent = nullptr);
    void showSchedule();
    void getData(struct team teams[], QList<struct matchKind> matchs[]);
    QString getTeamSelect();
    void addScheduleTurn(QTableWidget *scheduleShow, int i);

signals:
    void scheduleWindowBack();
    void teamDataWindowShowAndGetTeam();

public slots:

private:
    struct team teams[1000];
    QList<struct matchKind> matchs[38];
    QString nameSelect;
    QTabWidget *scheduleAll = new QTabWidget(this);
    QTableWidget *scheduleShow1 = new QTableWidget(this);
    QTableWidget *scheduleShow2 = new QTableWidget(this);
    QTableWidget *scheduleShow3 = new QTableWidget(this);
    QTableWidget *scheduleShow4 = new QTableWidget(this);
    QTableWidget *scheduleShow5 = new QTableWidget(this);
    QTableWidget *scheduleShow6 = new QTableWidget(this);
    QTableWidget *scheduleShow7 = new QTableWidget(this);
    QTableWidget *scheduleShow8 = new QTableWidget(this);
};

#endif // SCHEDULEWINDOW_H
