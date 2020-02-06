#include "leaguedatawindow.h"
#include <QLabel>
#include <QPushButton>
#include <QDebug>
#include <QList>
#include <QTableWidget>
#include <QTableWidgetItem>
#include <QTabWidget>
#include <QHeaderView>
#include <algorithm>

using namespace std;

Leaguedatawindow::Leaguedatawindow(QWidget *parent) : QMainWindow(parent)
{
    setFixedSize(800, 500);

    QLabel *labelTitle = new QLabel("联赛数据", this);
    labelTitle->move(330, 10);
    labelTitle->resize(200, 50);
    QFont ft;
    ft.setPointSize(20);
    labelTitle->setFont(ft);

    QPushButton *btnReturn = new QPushButton("返回主界面", this);
    btnReturn->move(700, 430);
    btnReturn->resize(100, 50);

    QPushButton *btnSchedule = new QPushButton("赛程", this);
    btnSchedule->move(650, 80);
    btnSchedule->resize(100, 50);

    connect( btnReturn, &QPushButton::clicked, [=](){
        emit this->leagueDataWindowBack();
    });

    connect( btnSchedule, &QPushButton::clicked, [=](){
        emit this->scheduleWindowShow();
    });
}

QString Leaguedatawindow::getTeamSelect(){
    return this->nameSelect;
}

QString Leaguedatawindow::getPlayerSelect(){
    return this->playerNameSelect;
}

void Leaguedatawindow::getData(QList<QString> teamNames, struct player players[], struct team teams[]){
    this->teamNames = teamNames;
    for (int i = 0; i < 1000; i++){
        this->players[i].id = players[i].id;
        this->players[i].age = players[i].age;
        this->players[i].name = players[i].name;
        this->players[i].team = players[i].team;
        this->players[i].nation = players[i].nation;
        this->players[i].postion = players[i].postion;
        this->players[i].numberGoal = players[i].numberGoal;
        this->players[i].numberSave = players[i].numberSave;
        this->players[i].numberStage = players[i].numberStage;
        this->players[i].numberAssist = players[i].numberAssist;
        this->teams[i].name = teams[i].name;
        this->teams[i].ranking = teams[i].ranking;
        this->teams[i].fraction = teams[i].fraction;
        this->teams[i].numberGoal = teams[i].numberGoal;
        this->teams[i].numberLose = teams[i].numberLose;
        this->teams[i].playerNames = teams[i].playerNames;
    }
}

void Leaguedatawindow::showTable(){
    QTabWidget *tableShow = new QTabWidget(this);
    tableShow->resize(533, 380);
    tableShow->move(100, 70);
    tableShow->setUsesScrollButtons(true);

    currentSeasonShow->resize(172, 32);
    currentSeasonShow->move(50,20);
    currentSeasonShow->setColumnCount(2);
    currentSeasonShow->setRowCount(1);
    currentSeasonShow->setColumnWidth(0, 70);
    currentSeasonShow->setColumnWidth(1, 100);
    currentSeasonShow->verticalHeader()->setVisible(false);
    currentSeasonShow->horizontalHeader()->setVisible(false);
    currentSeasonShow->setEditTriggers(QAbstractItemView::NoEditTriggers);
    currentSeasonShow->setItem(0, 0, new QTableWidgetItem("当前赛季"));
    currentSeasonShow->setItem(0, 1, new QTableWidgetItem(currentSeason));
    currentSeasonShow->item(0, 0)->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    currentSeasonShow->item(0, 1)->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);

    this->doTeamRankingShow();
    tableShow->addTab(this->teamShow, "球队积分");

    this->doTeamGoalShow();
    tableShow->addTab(this->goalShow, "球队进球");

    this->doTeamLoseShow();
    tableShow->addTab(this->loseShow, "球队失球");

    this->doPlayerGoalShow();
    tableShow->addTab(this->pgoalShow, "球员进球");

    this->doPlayerAssistShow();
    tableShow->addTab(this->passistShow, "球员助攻");

    this->doPlayerSaveShow();
    tableShow->addTab(this->psaveShow, "球员扑救");

    this->doPlayerOnStageShow();
    tableShow->addTab(this->ponstageShow, "球员出场");
}

//显示球队积分榜
void Leaguedatawindow::doTeamRankingShow(){
    QList<QString>::iterator itor;
    int count = 0;
    QStringList strs = {"排名", "球队", "进球", "失球", "积分"};

    for (itor = this->teamNames.begin(); itor != this->teamNames.end(); itor++){
        this->teamTemp[count].teamName = *itor;
        this->teamTemp[count].teamRanking = this->teams[findTeam(teams, *itor, 1)].ranking;
        count++;
    }
    sort(this->teamTemp, this->teamTemp + 20, compareTeamRanking);

    this->teamShow->setColumnCount(5);
    this->teamShow->setRowCount(20);
    this->teamShow->setColumnWidth(0, 50);
    this->teamShow->setColumnWidth(1, 160);
    this->teamShow->setColumnWidth(2, 100);
    this->teamShow->setColumnWidth(3, 100);
    this->teamShow->setColumnWidth(4, 100);
    this->teamShow->verticalHeader()->setVisible(false);
    this->teamShow->setHorizontalHeaderLabels(strs);

    for (int i = 0; i < 20; i++){
        this->teamShow->setItem(i, 0, new QTableWidgetItem(QString::number(teamTemp[i].teamRanking)));
        this->teamShow->setItem(i, 1, new QTableWidgetItem(teamTemp[i].teamName));
        this->teamShow->setItem(i, 2, new QTableWidgetItem(QString::number(this->teams[findTeam(teams, teamTemp[i].teamName, 1)].numberGoal)));
        this->teamShow->setItem(i, 3, new QTableWidgetItem(QString::number(this->teams[findTeam(teams, teamTemp[i].teamName, 1)].numberLose)));
        this->teamShow->setItem(i, 4, new QTableWidgetItem(QString::number(this->teams[findTeam(teams, teamTemp[i].teamName, 1)].fraction)));
        this->teamShow->item(i, 0)->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
        this->teamShow->item(i, 1)->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
        this->teamShow->item(i, 2)->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
        this->teamShow->item(i, 3)->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
        this->teamShow->item(i, 4)->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    }

    this->teamShow->setSelectionBehavior(QAbstractItemView::SelectRows);
    this->teamShow->setSelectionMode(QAbstractItemView::SingleSelection);
    this->teamShow->setEditTriggers(QAbstractItemView::NoEditTriggers);

    connect( this->teamShow, &QAbstractItemView::doubleClicked, this, [=](){
        int row = this->teamShow->currentItem()->row();
        this->nameSelect = teamTemp[row].teamName;
        emit this->teamDataWindowShowAndGetTeam();
    });
}

//显示球队失球榜
void Leaguedatawindow::doTeamLoseShow(){
    QList<QString>::iterator itor;
    int count = 0;
    QStringList strs = {"排名", "球队", "失球"};

    for (itor = this->teamNames.begin(); itor != this->teamNames.end(); itor++){
        this->loseTemp[count].teamName = *itor;
        this->loseTemp[count].lose = this->teams[findTeam(teams, *itor, 1)].numberLose;
        count++;
    }
    sort(this->loseTemp, this->loseTemp + 20, compareTeamLose);

    this->loseShow->setColumnCount(3);
    this->loseShow->setRowCount(20);
    this->loseShow->setColumnWidth(0, 50);
    this->loseShow->setColumnWidth(1, 240);
    this->loseShow->setColumnWidth(2, 220);
    this->loseShow->verticalHeader()->setVisible(false);
    this->loseShow->setHorizontalHeaderLabels(strs);

    for (int i = 0; i < 20; i++){
        this->loseShow->setItem(i, 0, new QTableWidgetItem(QString::number(i + 1)));
        this->loseShow->setItem(i, 1, new QTableWidgetItem(this->loseTemp[i].teamName));
        this->loseShow->setItem(i, 2, new QTableWidgetItem(QString::number(this->loseTemp[i].lose)));
        this->loseShow->item(i, 0)->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
        this->loseShow->item(i, 1)->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
        this->loseShow->item(i, 2)->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    }

    this->loseShow->setSelectionBehavior(QAbstractItemView::SelectRows);
    this->loseShow->setSelectionMode(QAbstractItemView::SingleSelection);
    this->loseShow->setEditTriggers(QAbstractItemView::NoEditTriggers);

    connect( this->loseShow, &QAbstractItemView::doubleClicked, this, [=](){
        int row = this->loseShow->currentItem()->row();
        this->nameSelect = loseTemp[row].teamName;
        emit this->teamDataWindowShowAndGetTeam();
    });
}

//显示球队进球榜
void Leaguedatawindow::doTeamGoalShow(){
    QList<QString>::iterator itor;
    int count = 0;
    QStringList strs = {"排名", "球队", "进球"};

    for (itor = this->teamNames.begin(); itor != this->teamNames.end(); itor++){
        this->goalTemp[count].teamName = *itor;
        this->goalTemp[count].goal = this->teams[findTeam(teams, *itor, 1)].numberGoal;
        count++;
    }
    sort(this->goalTemp, this->goalTemp + 20, compareTeamGoal);

    this->goalShow->setColumnCount(3);
    this->goalShow->setRowCount(20);
    this->goalShow->setColumnWidth(0, 50);
    this->goalShow->setColumnWidth(1, 240);
    this->goalShow->setColumnWidth(2, 220);
    this->goalShow->verticalHeader()->setVisible(false);
    this->goalShow->setHorizontalHeaderLabels(strs);

    for (int i = 0; i < 20; i++){
        this->goalShow->setItem(i, 0, new QTableWidgetItem(QString::number(i + 1)));
        this->goalShow->setItem(i, 1, new QTableWidgetItem(this->goalTemp[i].teamName));
        this->goalShow->setItem(i, 2, new QTableWidgetItem(QString::number(this->goalTemp[i].goal)));
        this->goalShow->item(i, 0)->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
        this->goalShow->item(i, 1)->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
        this->goalShow->item(i, 2)->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    }

    this->goalShow->setSelectionBehavior(QAbstractItemView::SelectRows);
    this->goalShow->setSelectionMode(QAbstractItemView::SingleSelection);
    this->goalShow->setEditTriggers(QAbstractItemView::NoEditTriggers);

    connect( this->goalShow, &QAbstractItemView::doubleClicked, this, [=](){
        int row = this->goalShow->currentItem()->row();
        this->nameSelect = goalTemp[row].teamName;
        emit this->teamDataWindowShowAndGetTeam();
    });
}

//显示球员进球榜
void Leaguedatawindow::doPlayerGoalShow(){
    QList<QString>::iterator itor;
    int count = 0;
    QStringList strs = {"排名", "球员", "进球"};

    for (itor = this->teamNames.begin(); itor != this->teamNames.end(); itor++){
        int index = findTeam(teams, *itor, 1);
        for (QList<QString>::iterator i = teams[index].playerNames.begin(); i != teams[index].playerNames.end(); i++){
            this->pgoalTemp[count].playerName = *i;
            this->pgoalTemp[count].goal = players[findPlayer(players, *i, 1)].numberGoal;
            count++;
        }
    }

    sort(this->pgoalTemp, this->pgoalTemp + count, comparePlayerGoal);

    this->pgoalShow->setColumnCount(3);
    this->pgoalShow->setRowCount(count);
    this->pgoalShow->setColumnWidth(0, 50);
    this->pgoalShow->setColumnWidth(1, 240);
    this->pgoalShow->setColumnWidth(2, 220);
    this->pgoalShow->verticalHeader()->setVisible(false);
    this->pgoalShow->setHorizontalHeaderLabels(strs);

    for (int i = 0; i < count; i++){
        this->pgoalShow->setItem(i, 0, new QTableWidgetItem(QString::number(i + 1)));
        this->pgoalShow->setItem(i, 1, new QTableWidgetItem(this->pgoalTemp[i].playerName));
        this->pgoalShow->setItem(i, 2, new QTableWidgetItem(QString::number(this->pgoalTemp[i].goal)));
        this->pgoalShow->item(i, 0)->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
        this->pgoalShow->item(i, 1)->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
        this->pgoalShow->item(i, 2)->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    }

    this->pgoalShow->setSelectionBehavior(QAbstractItemView::SelectRows);
    this->pgoalShow->setSelectionMode(QAbstractItemView::SingleSelection);
    this->pgoalShow->setEditTriggers(QAbstractItemView::NoEditTriggers);

    connect( this->pgoalShow, &QAbstractItemView::doubleClicked, this, [=](){
        int row = this->pgoalShow->currentItem()->row();
        this->playerNameSelect = pgoalTemp[row].playerName;
        emit this->playerDataWindowShowAndGetPlayer();;
    });
}

//显示球员助攻榜
void Leaguedatawindow::doPlayerAssistShow(){
    QList<QString>::iterator itor;
    int count = 0;
    QStringList strs = {"排名", "球员", "助攻"};

    for (itor = this->teamNames.begin(); itor != this->teamNames.end(); itor++){
        int index = findTeam(teams, *itor, 1);
        for (QList<QString>::iterator i = teams[index].playerNames.begin(); i != teams[index].playerNames.end(); i++){
            this->passistTemp[count].playerName = *i;
            this->passistTemp[count].assist = players[findPlayer(players, *i, 1)].numberAssist;
            count++;
        }
    }
    sort(this->passistTemp, this->passistTemp + count, comparePlayerAssist);

    this->passistShow->setColumnCount(3);
    this->passistShow->setRowCount(count);
    this->passistShow->setColumnWidth(0, 50);
    this->passistShow->setColumnWidth(1, 240);
    this->passistShow->setColumnWidth(2, 220);
    this->passistShow->verticalHeader()->setVisible(false);
    this->passistShow->setHorizontalHeaderLabels(strs);

    for (int i = 0; i < count; i++){
        this->passistShow->setItem(i, 0, new QTableWidgetItem(QString::number(i + 1)));
        this->passistShow->setItem(i, 1, new QTableWidgetItem(this->passistTemp[i].playerName));
        this->passistShow->setItem(i, 2, new QTableWidgetItem(QString::number(this->passistTemp[i].assist)));
        this->passistShow->item(i, 0)->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
        this->passistShow->item(i, 1)->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
        this->passistShow->item(i, 2)->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    }

    this->passistShow->setSelectionBehavior(QAbstractItemView::SelectRows);
    this->passistShow->setSelectionMode(QAbstractItemView::SingleSelection);
    this->passistShow->setEditTriggers(QAbstractItemView::NoEditTriggers);

    connect( this->passistShow, &QAbstractItemView::doubleClicked, this, [=](){
        int row = this->passistShow->currentItem()->row();
        this->playerNameSelect = passistTemp[row].playerName;
        emit this->playerDataWindowShowAndGetPlayer();;
    });
}

//显示球员扑救榜
void Leaguedatawindow::doPlayerSaveShow(){
    QList<QString>::iterator itor;
    int count = 0;
    QStringList strs = {"排名", "球员", "扑救"};

    for (itor = this->teamNames.begin(); itor != this->teamNames.end(); itor++){
        int index = findTeam(teams, *itor, 1);
        for (QList<QString>::iterator i = teams[index].playerNames.begin(); i != teams[index].playerNames.end(); i++){
            this->psaveTemp[count].playerName = *i;
            this->psaveTemp[count].save = players[findPlayer(players, *i, 1)].numberSave;
            count++;
        }
    }
    sort(this->psaveTemp, this->psaveTemp + count, comparePlayerSave);

    this->psaveShow->setColumnCount(3);
    this->psaveShow->setRowCount(count);
    this->psaveShow->setColumnWidth(0, 50);
    this->psaveShow->setColumnWidth(1, 240);
    this->psaveShow->setColumnWidth(2, 220);
    this->psaveShow->verticalHeader()->setVisible(false);
    this->psaveShow->setHorizontalHeaderLabels(strs);

    for (int i = 0; i < count; i++){
        this->psaveShow->setItem(i, 0, new QTableWidgetItem(QString::number(i + 1)));
        this->psaveShow->setItem(i, 1, new QTableWidgetItem(this->psaveTemp[i].playerName));
        this->psaveShow->setItem(i, 2, new QTableWidgetItem(QString::number(this->psaveTemp[i].save)));
        this->psaveShow->item(i, 0)->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
        this->psaveShow->item(i, 1)->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
        this->psaveShow->item(i, 2)->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    }

    this->psaveShow->setSelectionBehavior(QAbstractItemView::SelectRows);
    this->psaveShow->setSelectionMode(QAbstractItemView::SingleSelection);
    this->psaveShow->setEditTriggers(QAbstractItemView::NoEditTriggers);

    connect( this->psaveShow, &QAbstractItemView::doubleClicked, this, [=](){
        int row = this->psaveShow->currentItem()->row();
        this->playerNameSelect = psaveTemp[row].playerName;
        emit this->playerDataWindowShowAndGetPlayer();;
    });
}

//显示球员出场榜
void Leaguedatawindow::doPlayerOnStageShow(){
    QList<QString>::iterator itor;
    int count = 0;
    QStringList strs = {"排名", "球员", "出场"};

    for (itor = this->teamNames.begin(); itor != this->teamNames.end(); itor++){
        int index = findTeam(teams, *itor, 1);
        for (QList<QString>::iterator i = teams[index].playerNames.begin(); i != teams[index].playerNames.end(); i++){
            this->ponstageTemp[count].playerName = *i;
            this->ponstageTemp[count].onstage = players[findPlayer(players, *i, 1)].numberStage;
            count++;
        }
    }
    sort(this->ponstageTemp, this->ponstageTemp + count, comparePlayerOnStage);

    this->ponstageShow->setColumnCount(3);
    this->ponstageShow->setRowCount(count);
    this->ponstageShow->setColumnWidth(0, 50);
    this->ponstageShow->setColumnWidth(1, 240);
    this->ponstageShow->setColumnWidth(2, 220);
    this->ponstageShow->verticalHeader()->setVisible(false);
    this->ponstageShow->setHorizontalHeaderLabels(strs);

    for (int i = 0; i < count; i++){
        this->ponstageShow->setItem(i, 0, new QTableWidgetItem(QString::number(i + 1)));
        this->ponstageShow->setItem(i, 1, new QTableWidgetItem(this->ponstageTemp[i].playerName));
        this->ponstageShow->setItem(i, 2, new QTableWidgetItem(QString::number(this->ponstageTemp[i].onstage)));
        this->ponstageShow->item(i, 0)->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
        this->ponstageShow->item(i, 1)->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
        this->ponstageShow->item(i, 2)->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    }

    this->ponstageShow->setSelectionBehavior(QAbstractItemView::SelectRows);
    this->ponstageShow->setSelectionMode(QAbstractItemView::SingleSelection);
    this->ponstageShow->setEditTriggers(QAbstractItemView::NoEditTriggers);

    connect( this->ponstageShow, &QAbstractItemView::doubleClicked, this, [=](){
        int row = this->ponstageShow->currentItem()->row();
        this->playerNameSelect = ponstageTemp[row].playerName;
        emit this->playerDataWindowShowAndGetPlayer();;
    });
}

void Leaguedatawindow::setCurrentSeason(QString season){
    this->currentSeason = season;
}
