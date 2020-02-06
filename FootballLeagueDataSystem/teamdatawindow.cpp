#include "teamdatawindow.h"
#include <QLabel>
#include <QPushButton>
#include <QDebug>
#include <QList>
#include <QTableWidgetItem>
#include <QHeaderView>
#include <algorithm>

using namespace std;

teamdatawindow::teamdatawindow(QWidget *parent) : QMainWindow(parent)
{
    setFixedSize(800, 500);

    QLabel *labelTitle = new QLabel("球队数据", this);
    labelTitle->move(330, 10);
    labelTitle->resize(200, 50);
    QFont ft;
    ft.setPointSize(20);
    labelTitle->setFont(ft);

    QPushButton *btnReturnLeague = new QPushButton("返回联赛数据界面", this);
    btnReturnLeague->move(650, 430);
    btnReturnLeague->resize(150, 50);

    connect(btnReturnLeague, &QPushButton::clicked, [=](){
        emit this->teamDataWindowBackToLeague();
    });

    QPushButton *btnReturnSchedule = new QPushButton("返回赛程界面", this);
    btnReturnSchedule->move(650, 370);
    btnReturnSchedule->resize(150, 50);

    connect(btnReturnSchedule, &QPushButton::clicked, [=](){
        emit this->teamDataWindowBackToSchedule();
    });

    this->flag = false;
}

void teamdatawindow::setTeamNameNow(int index){
    this->indexTeam = index;
//    qDebug() << teamNameNow << endl;
}

QString teamdatawindow::getPlayerSelect(){
    return this->playerSelect;
}

void teamdatawindow::getData(struct player *players, struct team *teams, QList<struct matchKind> matchs[]){
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
    for (int i = 0; i < 38; i++){
        QList<struct matchKind>::iterator itor;
        this->matchs[i].clear();
        for (itor = matchs[i].begin(); itor != matchs[i].end(); itor++){
            struct matchKind temp;
            temp.fractionA = (*itor).fractionA;
            temp.fractionB = (*itor).fractionB;
            temp.matchTeamA = (*itor).matchTeamA;
            temp.matchTeamB = (*itor).matchTeamB;
            this->matchs[i].push_back(temp);
        }
    }
}

void teamdatawindow::showAll(){
    if (! flag){
        interfaceSelect->move(50, 50);
        interfaceSelect->insertItem(0, "球员");
        interfaceSelect->insertItem(1, "队内排行榜");
        interfaceSelect->insertItem(2, "本队赛程");
        flag = true;
    }

    this->rankingTableInit();
    this->teamScheduleInit();
    this->clearAllTableWidget();
    this->hideAllTabWidget();
    if (interfaceSelect->currentText() == "球员"){
         this->showTable();
    }else if(interfaceSelect->currentText() == "队内排行榜"){
        this->showRankingAll();
    }else if(interfaceSelect->currentText() == "本队赛程"){
        this->teamScheduleShow();
    }

    connect( interfaceSelect, &QComboBox::currentTextChanged, this, [=](){
        if (interfaceSelect->currentText() == "球员"){
            this->hideAllTabWidget();
            this->showTable();
        }else if(interfaceSelect->currentText() == "队内排行榜"){
            this->hideAllTabWidget();
            this->showRankingAll();
        }else if(interfaceSelect->currentText() == "本队赛程"){
            this->hideAllTabWidget();
            this->teamScheduleShow();
        }
    });

}

void teamdatawindow::showTable(){
    playerAll->resize(378, 384);
    playerAll->move(270, 70);
    playerAll->show();

    QList<QString>::iterator itor;
    int playerNumber;
    int count;

    //前锋数据表
    count = 0;
    playerAll->addTab(playerShowForWard, "前锋");
    QStringList strsForWard = {"号码", "球员", "出场", "进球", "助攻"};
    playerNumber = 0;
    for (itor = this->teams[this->indexTeam].playerNames.begin(); itor != this->teams[this->indexTeam].playerNames.end(); itor++){
        if (players[findPlayer(players, *itor, 1)].postion == "Forward"){
            playerNumber++;
        }
    }
    playerShowForWard->setColumnCount(5);
    if (playerNumber <= 11){
        playerShowForWard->setRowCount(11);
    }else{
        playerShowForWard->setRowCount(playerNumber);
    }
    playerShowForWard->setColumnWidth(0, 50);
    playerShowForWard->setColumnWidth(1, 140);
    playerShowForWard->setColumnWidth(2, 60);
    playerShowForWard->setColumnWidth(3, 60);
    playerShowForWard->setColumnWidth(4, 60);
    playerShowForWard->verticalHeader()->setVisible(false);
    playerShowForWard->setHorizontalHeaderLabels(strsForWard);
    for (itor = this->teams[this->indexTeam].playerNames.begin(); itor != this->teams[this->indexTeam].playerNames.end(); itor++){
        if (players[findPlayer(players, *itor, 1)].postion == "Forward"){
            playerShowForWard->setItem(count, 0, new QTableWidgetItem(QString::number(players[findPlayer(players, *itor, 1)].id)));
            playerShowForWard->setItem(count, 1, new QTableWidgetItem(*itor));
            playerShowForWard->setItem(count, 2, new QTableWidgetItem(QString::number(players[findPlayer(players, *itor, 1)].numberStage)));
            playerShowForWard->setItem(count, 3, new QTableWidgetItem(QString::number(players[findPlayer(players, *itor, 1)].numberGoal)));
            playerShowForWard->setItem(count, 4, new QTableWidgetItem(QString::number(players[findPlayer(players, *itor, 1)].numberAssist)));
            playerShowForWard->item(count, 0)->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
            playerShowForWard->item(count, 1)->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
            playerShowForWard->item(count, 2)->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
            playerShowForWard->item(count, 3)->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
            playerShowForWard->item(count, 4)->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
            count++;
        }
    }
    playerShowForWard->setSelectionBehavior(QAbstractItemView::SelectRows);
    playerShowForWard->setSelectionMode(QAbstractItemView::SingleSelection);
    playerShowForWard->setEditTriggers(QAbstractItemView::NoEditTriggers);

    connect( playerShowForWard, &QAbstractItemView::doubleClicked, this, [=](){
        int row = playerShowForWard->currentItem()->row();
        this->playerSelect = playerShowForWard->item(row, 1)->text();
        emit this->playerDataWindowShowAndGetPlayer();
    });

    //中场数据表
    count = 0;
    playerAll->addTab(playerShowMidfield, "中场");
    QStringList strsMidfield = {"号码", "球员", "出场", "进球", "助攻"};
    playerNumber = 0;
    for (itor = this->teams[this->indexTeam].playerNames.begin(); itor != this->teams[this->indexTeam].playerNames.end(); itor++){
        if (players[findPlayer(players, *itor, 1)].postion == "Midfield"){
            playerNumber++;
        }
    }
    playerShowMidfield->setColumnCount(5);
    if (playerNumber <= 11){
        playerShowMidfield->setRowCount(11);
    }else{
        playerShowMidfield->setRowCount(playerNumber);
    }
    playerShowMidfield->setColumnWidth(0, 50);
    playerShowMidfield->setColumnWidth(1, 140);
    playerShowMidfield->setColumnWidth(2, 60);
    playerShowMidfield->setColumnWidth(3, 60);
    playerShowMidfield->setColumnWidth(4, 60);
    playerShowMidfield->verticalHeader()->setVisible(false);
    playerShowMidfield->setHorizontalHeaderLabels(strsMidfield);
    for (itor = this->teams[this->indexTeam].playerNames.begin(); itor != this->teams[this->indexTeam].playerNames.end(); itor++){
        if (players[findPlayer(players, *itor, 1)].postion == "Midfield"){
            playerShowMidfield->setItem(count, 0, new QTableWidgetItem(QString::number(players[findPlayer(players, *itor, 1)].id)));
            playerShowMidfield->setItem(count, 1, new QTableWidgetItem(*itor));
            playerShowMidfield->setItem(count, 2, new QTableWidgetItem(QString::number(players[findPlayer(players, *itor, 1)].numberStage)));
            playerShowMidfield->setItem(count, 3, new QTableWidgetItem(QString::number(players[findPlayer(players, *itor, 1)].numberGoal)));
            playerShowMidfield->setItem(count, 4, new QTableWidgetItem(QString::number(players[findPlayer(players, *itor, 1)].numberAssist)));
            playerShowMidfield->item(count, 0)->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
            playerShowMidfield->item(count, 1)->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
            playerShowMidfield->item(count, 2)->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
            playerShowMidfield->item(count, 3)->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
            playerShowMidfield->item(count, 4)->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
            count++;
        }
    }
    playerShowMidfield->setSelectionBehavior(QAbstractItemView::SelectRows);
    playerShowMidfield->setSelectionMode(QAbstractItemView::SingleSelection);
    playerShowMidfield->setEditTriggers(QAbstractItemView::NoEditTriggers);

    connect( playerShowMidfield, &QAbstractItemView::doubleClicked, this, [=](){
        int row = playerShowMidfield->currentItem()->row();
        this->playerSelect = playerShowMidfield->item(row, 1)->text();
        emit this->playerDataWindowShowAndGetPlayer();
    });

    //后卫数据表
    count = 0;
    playerAll->addTab(playerShowDefender, "后卫");
    QStringList strsDefender = {"号码", "球员", "出场", "进球", "助攻"};
    playerNumber = 0;
    for (itor = this->teams[this->indexTeam].playerNames.begin(); itor != this->teams[this->indexTeam].playerNames.end(); itor++){
        if (players[findPlayer(players, *itor, 1)].postion == "Defender"){
            playerNumber++;
        }
    }
    playerShowDefender->setColumnCount(5);
    if (playerNumber <= 11){
        playerShowDefender->setRowCount(11);
    }else{
        playerShowDefender->setRowCount(playerNumber);
    }
    playerShowDefender->setColumnWidth(0, 50);
    playerShowDefender->setColumnWidth(1, 140);
    playerShowDefender->setColumnWidth(2, 60);
    playerShowDefender->setColumnWidth(3, 60);
    playerShowDefender->setColumnWidth(4, 60);
    playerShowDefender->verticalHeader()->setVisible(false);
    playerShowDefender->setHorizontalHeaderLabels(strsDefender);
    for (itor = this->teams[this->indexTeam].playerNames.begin(); itor != this->teams[this->indexTeam].playerNames.end(); itor++){
        if (players[findPlayer(players, *itor, 1)].postion == "Defender"){
            playerShowDefender->setItem(count, 0, new QTableWidgetItem(QString::number(players[findPlayer(players, *itor, 1)].id)));
            playerShowDefender->setItem(count, 1, new QTableWidgetItem(*itor));
            playerShowDefender->setItem(count, 2, new QTableWidgetItem(QString::number(players[findPlayer(players, *itor, 1)].numberStage)));
            playerShowDefender->setItem(count, 3, new QTableWidgetItem(QString::number(players[findPlayer(players, *itor, 1)].numberGoal)));
            playerShowDefender->setItem(count, 4, new QTableWidgetItem(QString::number(players[findPlayer(players, *itor, 1)].numberAssist)));
            playerShowDefender->item(count, 0)->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
            playerShowDefender->item(count, 1)->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
            playerShowDefender->item(count, 2)->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
            playerShowDefender->item(count, 3)->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
            playerShowDefender->item(count, 4)->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
            count++;
        }
    }
    playerShowDefender->setSelectionBehavior(QAbstractItemView::SelectRows);
    playerShowDefender->setSelectionMode(QAbstractItemView::SingleSelection);
    playerShowDefender->setEditTriggers(QAbstractItemView::NoEditTriggers);

    connect( playerShowDefender, &QAbstractItemView::doubleClicked, this, [=](){
        int row = playerShowDefender->currentItem()->row();
        this->playerSelect = playerShowDefender->item(row, 1)->text();
        emit this->playerDataWindowShowAndGetPlayer();
    });

    //后卫数据表
    count = 0;
    playerAll->addTab(playerShowGoalkeeper, "门将");
    QStringList strsGoalkeeper = {"号码", "球员", "出场", "扑救", "进球", "助攻"};
    playerNumber = 0;
    for (itor = this->teams[this->indexTeam].playerNames.begin(); itor != this->teams[this->indexTeam].playerNames.end(); itor++){
        if (players[findPlayer(players, *itor, 1)].postion == "Goalkeeper"){
            playerNumber++;
        }
    }
    playerShowGoalkeeper->setColumnCount(6);
    if (playerNumber <= 11){
        playerShowGoalkeeper->setRowCount(11);
    }else{
        playerShowGoalkeeper->setRowCount(playerNumber);
    }
    playerShowGoalkeeper->setColumnWidth(0, 50);
    playerShowGoalkeeper->setColumnWidth(1, 100);
    playerShowGoalkeeper->setColumnWidth(2, 55);
    playerShowGoalkeeper->setColumnWidth(3, 55);
    playerShowGoalkeeper->setColumnWidth(4, 55);
    playerShowGoalkeeper->setColumnWidth(5, 55);
    playerShowGoalkeeper->verticalHeader()->setVisible(false);
    playerShowGoalkeeper->setHorizontalHeaderLabels(strsGoalkeeper);
    for (itor = this->teams[this->indexTeam].playerNames.begin(); itor != this->teams[this->indexTeam].playerNames.end(); itor++){
        if (players[findPlayer(players, *itor, 1)].postion == "Goalkeeper"){
            playerShowGoalkeeper->setItem(count, 0, new QTableWidgetItem(QString::number(players[findPlayer(players, *itor, 1)].id)));
            playerShowGoalkeeper->setItem(count, 1, new QTableWidgetItem(*itor));
            playerShowGoalkeeper->setItem(count, 2, new QTableWidgetItem(QString::number(players[findPlayer(players, *itor, 1)].numberStage)));
            playerShowGoalkeeper->setItem(count, 3, new QTableWidgetItem(QString::number(players[findPlayer(players, *itor, 1)].numberSave)));
            playerShowGoalkeeper->setItem(count, 4, new QTableWidgetItem(QString::number(players[findPlayer(players, *itor, 1)].numberGoal)));
            playerShowGoalkeeper->setItem(count, 5, new QTableWidgetItem(QString::number(players[findPlayer(players, *itor, 1)].numberAssist)));
            playerShowGoalkeeper->item(count, 0)->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
            playerShowGoalkeeper->item(count, 1)->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
            playerShowGoalkeeper->item(count, 2)->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
            playerShowGoalkeeper->item(count, 3)->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
            playerShowGoalkeeper->item(count, 4)->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
            playerShowGoalkeeper->item(count, 5)->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
            count++;
        }
    }
    playerShowGoalkeeper->setSelectionBehavior(QAbstractItemView::SelectRows);
    playerShowGoalkeeper->setSelectionMode(QAbstractItemView::SingleSelection);
    playerShowGoalkeeper->setEditTriggers(QAbstractItemView::NoEditTriggers);

    connect( playerShowGoalkeeper, &QAbstractItemView::doubleClicked, this, [=](){
        int row = playerShowGoalkeeper->currentItem()->row();
        this->playerSelect = playerShowGoalkeeper->item(row, 1)->text();
        emit this->playerDataWindowShowAndGetPlayer();
    });
}

void teamdatawindow::showAttributes(){
    QList<QString>::iterator itor;
    attributesTable->setColumnCount(2);
    attributesTable->setRowCount(9);
    attributesTable->setColumnWidth(0, 80);
    attributesTable->setColumnWidth(1, 145);
    attributesTable->resize(227, 272);
    attributesTable->move(30, 95);
    attributesTable->verticalHeader()->setVisible(false);
    attributesTable->horizontalHeader()->setVisible(false);
    attributesTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
    attributesTable->setItem(0, 0, new QTableWidgetItem("球队名"));
    attributesTable->setItem(0, 1, new QTableWidgetItem(this->teams[this->indexTeam].name));
    attributesTable->setItem(1, 0, new QTableWidgetItem("积分"));
    attributesTable->setItem(1, 1, new QTableWidgetItem(QString::number(this->teams[this->indexTeam].fraction)));
    attributesTable->setItem(2, 0, new QTableWidgetItem("排名"));
    attributesTable->setItem(2, 1, new QTableWidgetItem(QString::number(this->teams[this->indexTeam].ranking)));
    attributesTable->setItem(3, 0, new QTableWidgetItem("进球"));
    attributesTable->setItem(3, 1, new QTableWidgetItem(QString::number(this->teams[this->indexTeam].numberGoal)));
    attributesTable->setItem(4, 0, new QTableWidgetItem("失球"));
    attributesTable->setItem(4, 1, new QTableWidgetItem(QString::number(this->teams[this->indexTeam].numberLose)));
    attributesTable->setItem(5, 0, new QTableWidgetItem("最多进球"));
    QString nameMostGoal;
    int goal = -1;
    for (itor = teams[indexTeam].playerNames.begin(); itor != teams[indexTeam].playerNames.end(); itor++){
        if (players[findPlayer(players, *itor, 1)].numberGoal > goal){
            nameMostGoal = *itor;
            goal = players[findPlayer(players, *itor, 1)].numberGoal;
        }
    }
    attributesTable->setItem(5, 1, new QTableWidgetItem(nameMostGoal));
    attributesTable->setItem(6, 0, new QTableWidgetItem("最多助攻"));
    QString nameMostAssist;
    int assist = -1;
    for (itor = teams[indexTeam].playerNames.begin(); itor != teams[indexTeam].playerNames.end(); itor++){
        if (players[findPlayer(players, *itor, 1)].numberAssist > assist){
            nameMostAssist = *itor;
            assist = players[findPlayer(players, *itor, 1)].numberAssist;
        }
    }
    attributesTable->setItem(6, 1, new QTableWidgetItem(nameMostAssist));
    attributesTable->setItem(7, 0, new QTableWidgetItem("最多扑救"));
    QString nameMostSave;
    int save = -1;
    for (itor = teams[indexTeam].playerNames.begin(); itor != teams[indexTeam].playerNames.end(); itor++){
        if (players[findPlayer(players, *itor, 1)].numberSave > save){
            nameMostSave = *itor;
            save = players[findPlayer(players, *itor, 1)].numberSave;
        }
    }
    attributesTable->setItem(7, 1, new QTableWidgetItem(nameMostSave));
    attributesTable->setItem(8, 0, new QTableWidgetItem("最多出场"));
    QString nameMostOnstage;
    int onstage = -1;
    for (itor = teams[indexTeam].playerNames.begin(); itor != teams[indexTeam].playerNames.end(); itor++){
        if (players[findPlayer(players, *itor, 1)].numberStage > onstage){
            nameMostOnstage = *itor;
            onstage = players[findPlayer(players, *itor, 1)].numberStage;
        }
    }
    attributesTable->setItem(8, 1, new QTableWidgetItem(nameMostOnstage));

    for (int i = 0; i <= 8; i++)
        for (int j = 0; j <= 1; j++)
            attributesTable->item(i, j)->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
}

void teamdatawindow::rankingTableInit(){
    rankingAll->resize(378, 384);
    rankingAll->move(270, 70);

    rankingAll->addTab(playerGoalRanking, "进球");
    playerGoalRanking->setColumnCount(3);
    playerGoalRanking->setColumnWidth(0, 50);
    playerGoalRanking->setColumnWidth(1, 160);
    playerGoalRanking->setColumnWidth(2, 160);
    playerGoalRanking->verticalHeader()->setVisible(false);
    QStringList strsGoal = {"排名", "球员", "进球"};
    playerGoalRanking->setHorizontalHeaderLabels(strsGoal);

    rankingAll->addTab(playerAssistRanking, "助攻");
    playerAssistRanking->setColumnCount(3);
    playerAssistRanking->setColumnWidth(0, 50);
    playerAssistRanking->setColumnWidth(1, 160);
    playerAssistRanking->setColumnWidth(2, 160);
    playerAssistRanking->verticalHeader()->setVisible(false);
    QStringList strsAssist = {"排名", "球员", "助攻"};
    playerAssistRanking->setHorizontalHeaderLabels(strsAssist);

    rankingAll->addTab(playerSaveRanking, "扑救");
    playerSaveRanking->setColumnCount(3);
    playerSaveRanking->setColumnWidth(0, 50);
    playerSaveRanking->setColumnWidth(1, 160);
    playerSaveRanking->setColumnWidth(2, 160);
    playerSaveRanking->verticalHeader()->setVisible(false);
    QStringList strsSave = {"排名", "球员", "扑救"};
    playerSaveRanking->setHorizontalHeaderLabels(strsSave);

    rankingAll->addTab(playerOnstageRanking, "出场");
    playerOnstageRanking->setColumnCount(3);
    playerOnstageRanking->setColumnWidth(0, 50);
    playerOnstageRanking->setColumnWidth(1, 160);
    playerOnstageRanking->setColumnWidth(2, 160);
    playerOnstageRanking->verticalHeader()->setVisible(false);
    QStringList strsOnstage = {"排名", "球员", "出场"};
    playerOnstageRanking->setHorizontalHeaderLabels(strsOnstage);
}

void teamdatawindow::showRankingAll(){
    int count;
    rankingAll->show();
    //球员进球榜
    count = 0;
    for (QList<QString>::iterator i = teams[indexTeam].playerNames.begin(); i != teams[indexTeam].playerNames.end(); i++){
        this->pgoalTemp[count].playerName = *i;
        this->pgoalTemp[count].goal = players[findPlayer(players, *i, 1)].numberGoal;
        count++;
    }
    sort(this->pgoalTemp, this->pgoalTemp + count, comparePlayerGoal);
    if (count <= 11){
        playerGoalRanking->setRowCount(11);
    }else{
        playerGoalRanking->setRowCount(count);
    }
    for (int i = 0; i < count; i++){
        playerGoalRanking->setItem(i, 0, new QTableWidgetItem(QString::number(i + 1)));
        playerGoalRanking->setItem(i, 1, new QTableWidgetItem(pgoalTemp[i].playerName));
        playerGoalRanking->setItem(i, 2, new QTableWidgetItem(QString::number(pgoalTemp[i].goal)));
        for (int j = 0; j < 3; j++){
            playerGoalRanking->item(i, j)->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
        }
    }
    playerGoalRanking->setSelectionBehavior(QAbstractItemView::SelectRows);
    playerGoalRanking->setSelectionMode(QAbstractItemView::SingleSelection);
    playerGoalRanking->setEditTriggers(QAbstractItemView::NoEditTriggers);
    connect( playerGoalRanking, &QAbstractItemView::doubleClicked, this, [=](){
        int row = playerGoalRanking->currentItem()->row();
        playerSelect = pgoalTemp[row].playerName;
        emit this->playerDataWindowShowAndGetPlayer();
    });

    //球员助攻榜
    count = 0;
    for (QList<QString>::iterator i = teams[indexTeam].playerNames.begin(); i != teams[indexTeam].playerNames.end(); i++){
        this->passistTemp[count].playerName = *i;
        this->passistTemp[count].assist = players[findPlayer(players, *i, 1)].numberAssist;
        count++;
    }
    sort(this->passistTemp, this->passistTemp + count, comparePlayerAssist);
    if (count <= 11){
        playerAssistRanking->setRowCount(11);
    }else{
        playerAssistRanking->setRowCount(count);
    }
    for (int i = 0; i < count; i++){
        playerAssistRanking->setItem(i, 0, new QTableWidgetItem(QString::number(i + 1)));
        playerAssistRanking->setItem(i, 1, new QTableWidgetItem(passistTemp[i].playerName));
        playerAssistRanking->setItem(i, 2, new QTableWidgetItem(QString::number(passistTemp[i].assist)));
        for (int j = 0; j < 3; j++){
            playerAssistRanking->item(i, j)->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
        }
    }
    playerAssistRanking->setSelectionBehavior(QAbstractItemView::SelectRows);
    playerAssistRanking->setSelectionMode(QAbstractItemView::SingleSelection);
    playerAssistRanking->setEditTriggers(QAbstractItemView::NoEditTriggers);
    connect( playerAssistRanking, &QAbstractItemView::doubleClicked, this, [=](){
        int row = playerAssistRanking->currentItem()->row();
        playerSelect = passistTemp[row].playerName;
        emit this->playerDataWindowShowAndGetPlayer();
    });

    //球员扑救榜
    count = 0;
    for (QList<QString>::iterator i = teams[indexTeam].playerNames.begin(); i != teams[indexTeam].playerNames.end(); i++){
        this->psaveTemp[count].playerName = *i;
        this->psaveTemp[count].save = players[findPlayer(players, *i, 1)].numberSave;
        count++;
    }
    sort(this->psaveTemp, this->psaveTemp + count, comparePlayerSave);
    if (count <= 11){
        playerSaveRanking->setRowCount(11);
    }else{
        playerSaveRanking->setRowCount(count);
    }
    for (int i = 0; i < count; i++){
        playerSaveRanking->setItem(i, 0, new QTableWidgetItem(QString::number(i + 1)));
        playerSaveRanking->setItem(i, 1, new QTableWidgetItem(psaveTemp[i].playerName));
        playerSaveRanking->setItem(i, 2, new QTableWidgetItem(QString::number(psaveTemp[i].save)));
        for (int j = 0; j < 3; j++){
            playerSaveRanking->item(i, j)->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
        }
    }
    playerSaveRanking->setSelectionBehavior(QAbstractItemView::SelectRows);
    playerSaveRanking->setSelectionMode(QAbstractItemView::SingleSelection);
    playerSaveRanking->setEditTriggers(QAbstractItemView::NoEditTriggers);
    connect( playerSaveRanking, &QAbstractItemView::doubleClicked, this, [=](){
        int row = playerSaveRanking->currentItem()->row();
        playerSelect = psaveTemp[row].playerName;
        emit this->playerDataWindowShowAndGetPlayer();
    });

    //球员出场榜
    count = 0;
    for (QList<QString>::iterator i = teams[indexTeam].playerNames.begin(); i != teams[indexTeam].playerNames.end(); i++){
        this->ponstageTemp[count].playerName = *i;
        this->ponstageTemp[count].onstage = players[findPlayer(players, *i, 1)].numberStage;
        count++;
    }
    sort(this->ponstageTemp, this->ponstageTemp + count, comparePlayerOnStage);
    if (count <= 11){
        playerOnstageRanking->setRowCount(11);
    }else{
        playerOnstageRanking->setRowCount(count);
    }
    for (int i = 0; i < count; i++){
        playerOnstageRanking->setItem(i, 0, new QTableWidgetItem(QString::number(i + 1)));
        playerOnstageRanking->setItem(i, 1, new QTableWidgetItem(ponstageTemp[i].playerName));
        playerOnstageRanking->setItem(i, 2, new QTableWidgetItem(QString::number(ponstageTemp[i].onstage)));
        for (int j = 0; j < 3; j++){
            playerOnstageRanking->item(i, j)->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
        }
    }
    playerOnstageRanking->setSelectionBehavior(QAbstractItemView::SelectRows);
    playerOnstageRanking->setSelectionMode(QAbstractItemView::SingleSelection);
    playerOnstageRanking->setEditTriggers(QAbstractItemView::NoEditTriggers);
    connect( playerOnstageRanking, &QAbstractItemView::doubleClicked, this, [=](){
        int row = playerOnstageRanking->currentItem()->row();
        playerSelect = ponstageTemp[row].playerName;
        emit this->playerDataWindowShowAndGetPlayer();
    });
}

void teamdatawindow::teamScheduleShow(){
    scheduleAll->show();
    int count = 0;
    for (int i = 0; i < 8; i++){
        for (QList<struct matchKind>::iterator itor = matchs[i].begin(); itor != matchs[i].end(); itor++){
            struct matchKind temp;
            temp = *itor;
            if ((temp.matchTeamA == indexTeam) || (temp.matchTeamB) == indexTeam){
                teamSchedule->setItem(count, 0, new QTableWidgetItem("第" + QString::number(i + 1) + "轮"));
                teamSchedule->setItem(count, 1, new QTableWidgetItem(teams[temp.matchTeamA].name));
                teamSchedule->setItem(count, 2, new QTableWidgetItem(QString::number(temp.fractionA)));
                teamSchedule->setItem(count, 3, new QTableWidgetItem(" : "));
                teamSchedule->setItem(count, 4, new QTableWidgetItem(QString::number(temp.fractionB)));
                teamSchedule->setItem(count, 5, new QTableWidgetItem(teams[temp.matchTeamB].name));
                for (int j = 0; j <= 5; j++)
                    teamSchedule->item(count, j)->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
                count++;
            }
        }
    }
    teamSchedule->setEditTriggers(QAbstractItemView::NoEditTriggers);
}

void teamdatawindow::teamScheduleInit(){
    scheduleAll->resize(378, 384);
    scheduleAll->move(270, 70);

    scheduleAll->addTab(teamSchedule, "赛程");
    teamSchedule->setColumnCount(6);
    teamSchedule->setRowCount(11);
    teamSchedule->setColumnWidth(0, 70);
    teamSchedule->setColumnWidth(1, 85);
    teamSchedule->setColumnWidth(2, 50);
    teamSchedule->setColumnWidth(3, 30);
    teamSchedule->setColumnWidth(4, 50);
    teamSchedule->setColumnWidth(5, 85);
    teamSchedule->verticalHeader()->setVisible(false);
    QStringList strsSchedule = {"轮次", "球队", "比分", " : ", "比分", "球队"};
    teamSchedule->setHorizontalHeaderLabels(strsSchedule);
}

void teamdatawindow::clearAllTableWidget(){
    playerShowForWard->clear();
    playerShowMidfield->clear();
    playerShowDefender->clear();
    playerShowGoalkeeper->clear();
    playerGoalRanking->clear();
    playerAssistRanking->clear();
    playerSaveRanking->clear();
    playerOnstageRanking->clear();
    teamSchedule->clear();
}

void teamdatawindow::hideAllTabWidget(){
    playerAll->hide();
    rankingAll->hide();
    scheduleAll->hide();
}
