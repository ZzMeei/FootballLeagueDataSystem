#include "playerdatawindow.h"
#include <QLabel>
#include <QPushButton>
#include <QString>
#include <QList>
#include <QDebug>
#include <QFile>
#include <stdlib.h>
#include <stdio.h>
#include <QTableWidgetItem>
#include <QHeaderView>

playerdatawindow::playerdatawindow(QWidget *parent) : QMainWindow(parent)
{
    setFixedSize(800, 500);

    QLabel *labelTitle = new QLabel("球员数据", this);
    labelTitle->move(330, 10);
    labelTitle->resize(200, 50);
    QFont ft;
    ft.setPointSize(20);
    labelTitle->setFont(ft);

    QPushButton *btnReturnTeam = new QPushButton("返回球队数据界面", this);
    btnReturnTeam->move(650, 370);
    btnReturnTeam->resize(150, 50);

    connect(btnReturnTeam, &QPushButton::clicked, [=](){
        emit this->playerDataWindowBack();
    });

    QPushButton *btnReturnLeague = new QPushButton("返回联赛数据界面", this);
    btnReturnLeague->move(650, 430);
    btnReturnLeague->resize(150, 50);

    connect(btnReturnLeague, &QPushButton::clicked, [=](){
        emit this->playerDataWindowBackToLeague();
    });

    reReadFlagPlayer = 0;
    reReadFlagTeam = 0;
}

// BKDR Hash Function
unsigned int BKDRHash(QString str)
{
    unsigned int seed = 131; // 31 131 1313 13131 131313 etc..
    unsigned int hash = 0;
    int len = str.length() - 1;
    int index = 0;
    while (index <= len)
    {
        char c = str[index].toLatin1();
        hash = hash * seed + (unsigned int)c;
        index++;
    }

    return ((hash & 0x7FFFFFFF) % 1000);
}

//线性探测法解决冲突问题
int findTeam(struct team teams[], QString teamName, int flag){ //flag = 0 插入 flag = 1 查询
    int index;
    index = BKDRHash(teamName);
    if (flag == 0){
        while (! teams[index].name.isEmpty()){
            index++;
            if (index >= 1000){
                index = 0;
            }
        }
    }
    if (flag == 1){
        while (teams[index].name != teamName){
            index++;
            if (index >= 1000){
                index = 0;
            }
        }
    }
    return index;
}

//线性探测法解决冲突问题
int findPlayer(struct player players[], QString playerName, int flag){
    int index;
    index = BKDRHash(playerName);
    if (flag == 0){
        while (! players[index].name.isEmpty()){
            index++;
            if (index >= 1000){
                index = 0;
            }
        }
    }
    if (flag == 1){
        while (players[index].name != playerName){
            index++;
            if (index >= 1000){
                index = 0;
            }
        }
    }
    return index;
}

bool compareTeamRanking(struct teamAndRanking a, struct teamAndRanking b){
    return a.teamRanking < b.teamRanking;
}

bool compareTeamFraction(struct teamAndFraction a, struct teamAndFraction b){
    if (a.teamFraction > b.teamFraction)
        return true;
    else {
        return a.teamGoalDifference > b.teamGoalDifference;
    }
}

bool compareTeamLose(struct teamAndLose a, struct teamAndLose b){
    return a.lose > b.lose;
}

bool compareTeamGoal(struct teamAndGoal a, struct teamAndGoal b){
    return a.goal > b.goal;
}

bool comparePlayerGoal(struct playerAndGoal a, struct playerAndGoal b){
    return a.goal > b.goal;
}

bool comparePlayerAssist(struct playerAndAssist a, struct playerAndAssist b){
    return a.assist > b.assist;
}

bool comparePlayerSave(struct playerAndSave a, struct playerAndSave b){
    return a.save > b.save;
}

bool comparePlayerOnStage(struct playerAndOnStage a, struct playerAndOnStage b){
    return a.onstage > b.onstage;
}

QList<QString> playerdatawindow::getTeamNames(){
    return teamNames;
}

struct player* playerdatawindow::getPlayers(){
    return &players[0];
}

struct team* playerdatawindow::getTeams(){
    return &teams[0];
}

QList<struct matchKind>* playerdatawindow::getSchedule(){
    return &matchs[0];
}

void playerdatawindow::setPlayerNameNow(int index){
    this->indexPlayer = index;
}

void playerdatawindow::showTable(){
    playerInformationShow->setColumnCount(2);
    playerInformationShow->setColumnWidth(0, 90);
    playerInformationShow->setColumnWidth(1, 200);
    playerInformationShow->resize(293, 272);
    playerInformationShow->move(230, 100);
    playerInformationShow->setEditTriggers(QAbstractItemView::NoEditTriggers);
    playerInformationShow->verticalHeader()->setVisible(false);
    playerInformationShow->horizontalHeader()->setVisible(false);
    if (this->players[this->indexPlayer].postion == "Goalkeeper"){
        playerInformationShow->resize(293, 302);
        playerInformationShow->setRowCount(10);
        playerInformationShow->setItem(9, 0, new QTableWidgetItem("扑救"));
        playerInformationShow->setItem(9, 1, new QTableWidgetItem(QString::number(this->players[this->indexPlayer].numberSave)));
        playerInformationShow->item(9, 0)->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
        playerInformationShow->item(9, 1)->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    }else{
        playerInformationShow->setRowCount(9);
    }
    playerInformationShow->setItem(0, 0, new QTableWidgetItem("姓名"));
    playerInformationShow->setItem(1, 0, new QTableWidgetItem("国籍"));
    playerInformationShow->setItem(2, 0, new QTableWidgetItem("场上位置"));
    playerInformationShow->setItem(3, 0, new QTableWidgetItem("球队"));
    playerInformationShow->setItem(4, 0, new QTableWidgetItem("年龄"));
    playerInformationShow->setItem(5, 0, new QTableWidgetItem("号码"));
    playerInformationShow->setItem(6, 0, new QTableWidgetItem("出场"));
    playerInformationShow->setItem(7, 0, new QTableWidgetItem("进球"));
    playerInformationShow->setItem(8, 0, new QTableWidgetItem("助攻"));
    playerInformationShow->setItem(0, 1, new QTableWidgetItem(this->players[this->indexPlayer].name));
    playerInformationShow->setItem(1, 1, new QTableWidgetItem(this->players[this->indexPlayer].nation));
    playerInformationShow->setItem(2, 1, new QTableWidgetItem(this->players[this->indexPlayer].postion));
    playerInformationShow->setItem(3, 1, new QTableWidgetItem(this->players[this->indexPlayer].team));
    playerInformationShow->setItem(4, 1, new QTableWidgetItem(QString::number(this->players[this->indexPlayer].age)));
    playerInformationShow->setItem(5, 1, new QTableWidgetItem(QString::number(this->players[this->indexPlayer].id)));
    playerInformationShow->setItem(6, 1, new QTableWidgetItem(QString::number(this->players[this->indexPlayer].numberStage)));
    playerInformationShow->setItem(7, 1, new QTableWidgetItem(QString::number(this->players[this->indexPlayer].numberGoal)));
    playerInformationShow->setItem(8, 1, new QTableWidgetItem(QString::number(this->players[this->indexPlayer].numberAssist)));
    for (int i = 0; i <= 8; i++)
        for (int j = 0; j <=1; j++)
            playerInformationShow->item(i, j)->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
}

QString playerdatawindow::getTeamSelect(){
    return this->players[this->indexPlayer].team;
}

void playerdatawindow::getData(QString seasonSelected){
    //------------------------------------数据部分 开始-------------------------------------------------
    //读入球员数据
    QFile filePlayersInformation("/Users/yangqinjiang/Desktop/qt_project/data/" + seasonSelected + "/PlayersInformation.txt");
    if (filePlayersInformation.open(QIODevice::ReadOnly | QIODevice::Text)){
        QByteArray bytesIn;
        int flag = 0;
        int index = 0;
        while (!filePlayersInformation.atEnd()){
            bytesIn = filePlayersInformation.readLine();
            if (flag == 0){
                QString str;
                str.prepend(bytesIn);
                str = str.mid(0, str.length() - 1);
                index = findPlayer(players, str, reReadFlagPlayer);
                players[index].name = str;
                flag = 1;
            }
            else if (flag == 1){
                QString str;
                str.prepend(bytesIn);
                str = str.mid(0, str.length() - 1);
                players[index].nation = str;
                flag = 2;
            }
            else if (flag == 2){
                QString str;
                str.prepend(bytesIn);
                str = str.mid(0, str.length() - 1);
                players[index].postion = str;
                flag = 3;
            }
            else if (flag == 3){
                QString str;
                str.prepend(bytesIn);
                str = str.mid(0, str.length() - 1);
                players[index].team = str;
                flag = 4;
            }
            else if (flag == 4){
                QString str;
                str.prepend(bytesIn);
                players[index].age = str.toInt();
                flag = 5;
            }
            else if (flag == 5){
                QString str;
                str.prepend(bytesIn);
                players[index].id = str.toInt();
                flag = 6;
            }
            else if (flag == 6){
                QString str;
                str.prepend(bytesIn);
                players[index].numberStage = str.toInt();
                flag = 7;
            }
            else if (flag == 7){
                QString str;
                str.prepend(bytesIn);
                players[index].numberGoal = str.toInt();
                flag = 8;
            }
            else if (flag == 8){
                QString str;
                str.prepend(bytesIn);
                players[index].numberAssist = str.toInt();
                flag = 9;
            }
            else if (flag == 9){
                QString str;
                str.prepend(bytesIn);
                players[index].numberSave = str.toInt();
                flag = 0;
            }
        }
        filePlayersInformation.close();
    }

    //读入球队数据
    QFile fileTeamsInformation("/Users/yangqinjiang/Desktop/qt_project/data/" + seasonSelected + "/TeamInformation.txt");
    if (fileTeamsInformation.open(QIODevice::ReadOnly | QIODevice::Text)){
        QByteArray bytesIn;
        int flag = 0;
        int index = 0;
        while (!fileTeamsInformation.atEnd()){
            bytesIn = fileTeamsInformation.readLine();
            if (flag == 0){
                QString str;
                str.prepend(bytesIn);
                str = str.mid(0, str.length() - 1);
                index = findTeam(teams, str, reReadFlagTeam);
                teams[index].name = str;
                teams[index].playerNames.clear();
                flag = 1;
            }
            else if (flag == 1){
                QString str;
                str.prepend(bytesIn);
                teams[index].fraction = str.toInt();
                flag = 2;
            }
            else if (flag == 2){
                QString str;
                str.prepend(bytesIn);
                teams[index].ranking = str.toInt();
                flag = 3;
            }
            else if (flag == 3){
                QString str;
                str.prepend(bytesIn);
                teams[index].numberGoal = str.toInt();
                flag = 4;
            }
            else if (flag == 4){
                QString str;
                str.prepend(bytesIn);
                teams[index].numberLose = str.toInt();
                flag = 5;
            }
            else if (flag == 5){
                QString str;
                str.prepend(bytesIn);
                str = str.mid(0, str.length() - 1);
                if (str != "|||||"){
                    teams[index].playerNames.push_back(str);
                }else{
                    flag = 0;
                }
            }
        }
        fileTeamsInformation.close();
    }

    //读入球队名称列表
    QFile fileLeagueInformation("/Users/yangqinjiang/Desktop/qt_project/data/" + seasonSelected + "/LeagueInformation.txt");
    if (fileLeagueInformation.open(QIODevice::ReadOnly | QIODevice::Text)){
        QByteArray bytesIn;
        teamNames.clear();
        bytesIn = fileLeagueInformation.readLine();
        QString strTemp;
        strTemp.prepend(bytesIn);
        strTemp = strTemp.mid(0, strTemp.length() - 1);
        currentSeason = strTemp;
        while (!fileLeagueInformation.atEnd()){
            bytesIn = fileLeagueInformation.readLine();
            QString str;
            str.prepend(bytesIn);
            str = str.mid(0, str.length() - 1);
            teamNames.push_back(str);
        }
        fileLeagueInformation.close();
    }

    //读入赛程
    QFile fileScheduleInformation("/Users/yangqinjiang/Desktop/qt_project/data/" + seasonSelected + "/ScheduleInformation.txt");
    if (fileScheduleInformation.open(QIODevice::ReadOnly | QIODevice::Text)){
        QByteArray bytesIn;
        int flag = 0;
        int count1 = 0;
        int count2 = 0;
        struct matchKind temp;
        matchs[count2].clear();
        while (!fileScheduleInformation.atEnd()){
            bytesIn = fileScheduleInformation.readLine();
            if (count1 == 10){
                count2++;
                count1 = 0;
                matchs[count2].clear();
            }
            if (flag == 0){
                QString str;
                str.prepend(bytesIn);
                str = str.mid(0, str.length() - 1);
                temp.matchTeamA = findTeam(teams, str, 1);
                flag = 1;
            }
            else if (flag == 1){
                QString str;
                str.prepend(bytesIn);
                str = str.mid(0, str.length() - 1);
                temp.matchTeamB = findTeam(teams, str, 1);
                flag = 2;
            }
            else if (flag == 2){
                QString str;
                str.prepend(bytesIn);
                temp.fractionA = str.toInt();
                flag = 3;
            }
            else if (flag == 3){
                QString str;
                str.prepend(bytesIn);
                temp.fractionB = str.toInt();
                matchs[count2].push_back(temp);
                flag = 0;
                count1++;
            }

        }
        fileScheduleInformation.close();
    }

    //---------------------------------------数据部分 结束-------------------------------------------------
}

QString playerdatawindow::getCurrentSeason(){
    return currentSeason;
}

void playerdatawindow::setReReadFlag(){
    this->reReadFlagTeam = 1;
    this->reReadFlagPlayer = 1;
}
