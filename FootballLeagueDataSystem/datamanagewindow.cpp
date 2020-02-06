#include "datamanagewindow.h"
#include <QLabel>
#include <QDebug>
#include <QList>
#include <QTableWidgetItem>
#include <QHeaderView>
#include <QTabWidget>
#include <QFile>
#include <QTimer>
#include <QMessageBox>
#include <algorithm>

using namespace std;

datamanagewindow::datamanagewindow(QWidget *parent) : QMainWindow(parent)
{
    setFixedSize(800, 500);

    this->flag = false;

    QLabel *labelTitle = new QLabel("数据管理", this);
    labelTitle->move(330, 10);
    labelTitle->resize(200, 50);
    QFont ft;
    ft.setPointSize(20);
    labelTitle->setFont(ft);

    QPushButton *btnReturnMain = new QPushButton("返回主界面", this);
    btnReturnMain->move(650, 430);
    btnReturnMain->resize(150, 50);

    connect(btnReturnMain, &QPushButton::clicked, [=](){
        emit this->dataManageWindowBack();
    });

}

void datamanagewindow::getData(QList<QString> teamNames, struct player players[], struct team teams[], QList<struct matchKind> matchs[]){
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

void datamanagewindow::manageTableShow(){
    QList<QString>::iterator itor;

    if (! flag){
        int count;
        count = 0;
        for (itor = teamNames.begin(); itor != teamNames.end(); itor++){
            interfaceSelect->insertItem(count, *itor);
            count++;
        }
        interfaceSelect->move(50, 45);
        flag = true;
    }

    tableInit();

    this->playerAndTeamManageTableShow(findTeam(teams, interfaceSelect->currentText(), 1));

    connect( interfaceSelect, &QComboBox::currentTextChanged, this, [=](){
        this->playerAndTeamManageTableShow(findTeam(teams, interfaceSelect->currentText(), 1));
    });

}

//表格初始化
void datamanagewindow::tableInit(){
    manageAll->resize(478, 354);
    manageAll->move(150, 70);
    manageAll->addTab(teamDataManageShow, "球队信息");
    teamDataManageShow->setColumnCount(5);
    teamDataManageShow->setRowCount(10);
    teamDataManageShow->setColumnWidth(0, 150);
    teamDataManageShow->setColumnWidth(1, 80);
    teamDataManageShow->setColumnWidth(2, 80);
    teamDataManageShow->setColumnWidth(3, 80);
    teamDataManageShow->setColumnWidth(4, 80);
    teamDataManageShow->verticalHeader()->setVisible(false);

    manageAll->addTab(playerDataManageShow, "球员信息");
    playerDataManageShow->setColumnCount(5);
    playerDataManageShow->setRowCount(30);
    playerDataManageShow->setColumnWidth(0, 150);
    playerDataManageShow->setColumnWidth(1, 80);
    playerDataManageShow->setColumnWidth(2, 80);
    playerDataManageShow->setColumnWidth(3, 80);
    playerDataManageShow->setColumnWidth(4, 80);
    playerDataManageShow->verticalHeader()->setVisible(false);

    manageAll->addTab(scheduleDataManageShow, "球队赛程");
    scheduleDataManageShow->setColumnCount(6);
    scheduleDataManageShow->setRowCount(10);
    scheduleDataManageShow->setColumnWidth(0, 70);
    scheduleDataManageShow->setColumnWidth(1, 105);
    scheduleDataManageShow->setColumnWidth(2, 70);
    scheduleDataManageShow->setColumnWidth(3, 50);
    scheduleDataManageShow->setColumnWidth(4, 70);
    scheduleDataManageShow->setColumnWidth(5, 105);
    scheduleDataManageShow->verticalHeader()->setVisible(false);
}

//球员、球队信息、赛程信息修改界面
void datamanagewindow::playerAndTeamManageTableShow(int indexTeam){
    teamDataManageShow->clear();
    playerDataManageShow->clear();
    scheduleDataManageShow->clear();

    QStringList strsTeam = {"球队名", "积分", "进球", "失球", "排名"};
    teamDataManageShow->setHorizontalHeaderLabels(strsTeam);
    QStringList strsPlayer = {"球员名", "出场", "进球", "助攻", "扑救"};
    playerDataManageShow->setHorizontalHeaderLabels(strsPlayer);
    QStringList strsSchedule = {"轮次", "球队", "比分", " : ", "比分", "球队"};
    scheduleDataManageShow->setHorizontalHeaderLabels(strsSchedule);

    QList<QString>::iterator itor;
    teamDataManageShow->setItem(0, 0, new QTableWidgetItem(teams[indexTeam].name));
    teamDataManageShow->setItem(0, 1, new QTableWidgetItem(QString::number(teams[indexTeam].fraction)));
    teamDataManageShow->setItem(0, 2, new QTableWidgetItem(QString::number(teams[indexTeam].numberGoal)));
    teamDataManageShow->setItem(0, 3, new QTableWidgetItem(QString::number(teams[indexTeam].numberLose)));
    teamDataManageShow->setItem(0, 4, new QTableWidgetItem(QString::number(teams[indexTeam].ranking)));

    int count = 0;
    for (itor = teams[indexTeam].playerNames.begin(); itor != teams[indexTeam].playerNames.end(); itor++){
        playerDataManageShow->setItem(count, 0, new QTableWidgetItem(*itor));
        playerDataManageShow->setItem(count, 1, new QTableWidgetItem(QString::number(players[findPlayer(players, *itor, 1)].numberStage)));
        playerDataManageShow->setItem(count, 2, new QTableWidgetItem(QString::number(players[findPlayer(players, *itor, 1)].numberGoal)));
        playerDataManageShow->setItem(count, 3, new QTableWidgetItem(QString::number(players[findPlayer(players, *itor, 1)].numberAssist)));
        playerDataManageShow->setItem(count, 4, new QTableWidgetItem(QString::number(players[findPlayer(players, *itor, 1)].numberSave)));
        count++;
    }

    count = 0;
    for (int i = 0; i < 8; i++){
        for (QList<struct matchKind>::iterator itor = matchs[i].begin(); itor != matchs[i].end(); itor++){
            struct matchKind temp;
            temp = *itor;
            if ((temp.matchTeamA == indexTeam) || (temp.matchTeamB) == indexTeam){
                scheduleDataManageShow->setItem(count, 0, new QTableWidgetItem("第" + QString::number(i + 1) + "轮"));
                scheduleDataManageShow->setItem(count, 1, new QTableWidgetItem(teams[temp.matchTeamA].name));
                scheduleDataManageShow->setItem(count, 2, new QTableWidgetItem(QString::number(temp.fractionA)));
                scheduleDataManageShow->setItem(count, 3, new QTableWidgetItem(" : "));
                scheduleDataManageShow->setItem(count, 4, new QTableWidgetItem(QString::number(temp.fractionB)));
                scheduleDataManageShow->setItem(count, 5, new QTableWidgetItem(teams[temp.matchTeamB].name));
                count++;
            }
        }
    }

    playerAndTeamUpdateDataBTN(indexTeam);
}

//球员、球队信息、赛程信息保存按钮
void datamanagewindow::playerAndTeamUpdateDataBTN(int indexTeam){
    QPushButton *btnSave = new QPushButton("保存修改", this);
    btnSave->move(350, 430);
    btnSave->resize(100, 50);

    this->indexTeamBtn = indexTeam;
    connect(btnSave, &QPushButton::clicked, [=](){
        if (this->changable){
            QList<QString>::iterator itor;

            teams[indexTeamBtn].fraction = teamDataManageShow->item(0, 1)->text().toInt();
            teams[indexTeamBtn].numberGoal = teamDataManageShow->item(0, 2)->text().toInt();
            teams[indexTeamBtn].numberLose = teamDataManageShow->item(0, 3)->text().toInt();
            teams[indexTeamBtn].ranking = teamDataManageShow->item(0, 4)->text().toInt();

            int count = 0;
            for (itor = teamNames.begin(); itor != teamNames.end(); itor++){
                teamFractionTemp[count].teamName = *itor;
                teamFractionTemp[count].teamFraction = teams[findTeam(teams, *itor, 1)].fraction;
                teamFractionTemp[count].teamGoalDifference = teams[findTeam(teams, *itor, 1)].numberGoal - teams[findTeam(teams, *itor, 1)].numberLose;
                count++;
            }
            sort( teamFractionTemp, teamFractionTemp + 20, compareTeamFraction);
            for (int i = 0; i < 20; i++){
                teams[findTeam(teams, teamFractionTemp[i].teamName, 1)].ranking = i + 1;
            }

            count = 0;
            int index = 0;
            for (itor = teams[indexTeamBtn].playerNames.begin(); itor != teams[indexTeamBtn].playerNames.end(); itor++){
                index = findPlayer(players, *itor, 1);
                players[index].numberStage = playerDataManageShow->item(count, 1)->text().toInt();
                players[index].numberGoal = playerDataManageShow->item(count, 2)->text().toInt();
                players[index].numberAssist = playerDataManageShow->item(count, 3)->text().toInt();
                players[index].numberSave = playerDataManageShow->item(count, 4)->text().toInt();
                count++;
            }

            count = 0;
            for (int i = 0; i < 8; i++){
                for (QList<struct matchKind>::iterator itor = matchs[i].begin(); itor != matchs[i].end(); itor++){
                    if (((*itor).matchTeamA == indexTeamBtn) || ((*itor).matchTeamB) == indexTeamBtn){
                        (*itor).fractionA = scheduleDataManageShow->item(count, 2)->text().toInt();
                        (*itor).fractionB = scheduleDataManageShow->item(count, 4)->text().toInt();
                        count++;
                    }
                }
            }

            QFile fileUpdateDataTeam("/Users/yangqinjiang/Desktop/qt_project/data/19-20/TeamInformation.txt");
            if (fileUpdateDataTeam.open(QIODevice::WriteOnly | QIODevice::Text | QIODevice::Truncate)){
                QTextStream out(&fileUpdateDataTeam);
                for (itor = teamNames.begin(); itor != teamNames.end(); itor++){
                    index = findTeam(teams, *itor, 1);
                    out << *itor << endl;
                    out << teams[index].fraction << endl;
                    out << teams[index].ranking << endl;
                    out << teams[index].numberGoal << endl;
                    out << teams[index].numberLose << endl;
                    QList<QString>::iterator itorr;
                    for (itorr = teams[index].playerNames.begin(); itorr != teams[index].playerNames.end(); itorr++){
                        out << *itorr << endl;
                    }
                    out << "|||||" << endl;
                }
            }
            fileUpdateDataTeam.close();

            QFile fileUpdateDataPlayer("/Users/yangqinjiang/Desktop/qt_project/data/19-20/PlayersInformation.txt");
            if (fileUpdateDataPlayer.open(QIODevice::WriteOnly | QIODevice::Text | QIODevice::Truncate)){
                QTextStream out(&fileUpdateDataPlayer);
                for (itor = teamNames.begin(); itor != teamNames.end(); itor++){
                    index = findTeam(teams, *itor, 1);
                    QList<QString>::iterator itorr;
                    for (itorr = teams[index].playerNames.begin(); itorr != teams[index].playerNames.end(); itorr++){
                        int indexx = findPlayer(players, *itorr, 1);
                        out << players[indexx].name << endl;
                        out << players[indexx].nation << endl;
                        out << players[indexx].postion << endl;
                        out << players[indexx].team << endl;
                        out << players[indexx].age << endl;
                        out << players[indexx].id << endl;
                        out << players[indexx].numberStage << endl;
                        out << players[indexx].numberGoal << endl;
                        out << players[indexx].numberAssist << endl;
                        out << players[indexx].numberSave << endl;
                    }
                }
            }
            fileUpdateDataPlayer.close();

            QFile fileUpdateDataSchedule("/Users/yangqinjiang/Desktop/qt_project/data/19-20/ScheduleInformation.txt");
            if (fileUpdateDataSchedule.open(QIODevice::WriteOnly | QIODevice::Text | QIODevice::Truncate)){
                QTextStream out(&fileUpdateDataSchedule);
                for (int i = 0; i < 8; i++){
                    for (QList<struct matchKind>::iterator itor = matchs[i].begin(); itor != matchs[i].end(); itor++){
                        out << teams[(*itor).matchTeamA].name << endl;
                        out << teams[(*itor).matchTeamB].name << endl;
                        out << (*itor).fractionA << endl;
                        out << (*itor).fractionB << endl;
                    }
                }
            }
            fileUpdateDataSchedule.close();

            QTimer::singleShot(2000, this, [=](){
                QMessageBox *qmb = new QMessageBox();
                qmb->information(this, "成功", "修改成功！");
            });
        }else {
            QMessageBox *qmb = new QMessageBox();
            qmb->information(this, "失败", "过往赛季数据无法修改！");
        }
    });

}

void datamanagewindow::setIfChangable(int flag){
    if (flag == 0)
        this->changable = true;
    else if (flag == 1)
        this->changable = false;
}
