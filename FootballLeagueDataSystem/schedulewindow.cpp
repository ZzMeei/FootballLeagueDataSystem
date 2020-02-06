#include "schedulewindow.h"

#include <QLabel>
#include <QPushButton>
#include <QList>
#include <QTableWidgetItem>
#include <QDebug>
#include <QHeaderView>

scheduleWindow::scheduleWindow(QWidget *parent) : QMainWindow(parent)
{
    setFixedSize(800, 500);

    QLabel *labelTitle = new QLabel("赛程", this);
    labelTitle->move(330, 0);
    labelTitle->resize(200, 80);
    QFont ft;
    ft.setPointSize(20);
    labelTitle->setFont(ft);

    QPushButton *btnReturn = new QPushButton("返回联赛界面", this);
    btnReturn->move(650, 430);
    btnReturn->resize(150, 50);

    connect( btnReturn, &QPushButton::clicked, [=](){
        emit this->scheduleWindowBack();
    });
}

void scheduleWindow::getData(struct team teams[], QList<struct matchKind> matchs[]){
    for (int i = 0; i < 1000; i++){
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

void scheduleWindow::showSchedule(){
    scheduleAll->resize(498, 354);
    scheduleAll->move(130, 80);
    scheduleAll->setUsesScrollButtons(true);

    this->addScheduleTurn(this->scheduleShow1, 0);
    this->addScheduleTurn(this->scheduleShow2, 1);
    this->addScheduleTurn(this->scheduleShow3, 2);
    this->addScheduleTurn(this->scheduleShow4, 3);
    this->addScheduleTurn(this->scheduleShow5, 4);
    this->addScheduleTurn(this->scheduleShow6, 5);
    this->addScheduleTurn(this->scheduleShow7, 6);
    this->addScheduleTurn(this->scheduleShow8, 7);
}

QString scheduleWindow::getTeamSelect(){
    return this->nameSelect;
}

void scheduleWindow::addScheduleTurn(QTableWidget *scheduleShow, int i){
    QList<struct matchKind>::iterator itor;
    scheduleAll->addTab(scheduleShow, "第" + QString::number(i + 1) + "轮");
    scheduleShow->setColumnCount(5);
    scheduleShow->setRowCount(10);
    scheduleShow->setColumnWidth(0, 150);
    scheduleShow->setColumnWidth(1, 70);
    scheduleShow->setColumnWidth(2, 50);
    scheduleShow->setColumnWidth(3, 70);
    scheduleShow->setColumnWidth(4, 150);
    scheduleShow->verticalHeader()->setVisible(false);
    QStringList strsSchedule = {"球队", "比分", " : ", "比分", "球队"};
    scheduleShow->setHorizontalHeaderLabels(strsSchedule);
    int count = 0;
    for (itor = this->matchs[i].begin(); itor != this->matchs[i].end(); itor++){
        struct matchKind temp;
        temp = *itor;
        scheduleShow->setItem(count, 0, new QTableWidgetItem(this->teams[temp.matchTeamA].name));
        scheduleShow->setItem(count, 1, new QTableWidgetItem(QString::number(temp.fractionA)));
        scheduleShow->setItem(count, 2, new QTableWidgetItem(" : "));
        scheduleShow->setItem(count, 3, new QTableWidgetItem(QString::number(temp.fractionB)));
        scheduleShow->setItem(count, 4, new QTableWidgetItem(this->teams[temp.matchTeamB].name));
        scheduleShow->item(count, 0)->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
        scheduleShow->item(count, 1)->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
        scheduleShow->item(count, 2)->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
        scheduleShow->item(count, 3)->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
        scheduleShow->item(count, 4)->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
        count++;
    }

    scheduleShow->setSelectionBehavior(QAbstractItemView::SelectItems);
    scheduleShow->setSelectionMode(QAbstractItemView::SingleSelection);
    scheduleShow->setEditTriggers(QAbstractItemView::NoEditTriggers);
    connect( scheduleShow, &QAbstractItemView::doubleClicked, this, [=](){
        int colum = scheduleShow->currentItem()->column();
        if ((colum == 0) || (colum == 4)){
            this->nameSelect = scheduleShow->currentItem()->text();
            emit this->teamDataWindowShowAndGetTeam();
        }
    });
}
