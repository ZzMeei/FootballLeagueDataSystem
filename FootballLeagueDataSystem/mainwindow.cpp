#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QPushButton>
#include <QLabel>
#include <QDebug>
#include <QTreeWidget>
#include <QTreeWidgetItem>
#include <QStringList>
#include <QMessageBox>
#include <QTimer>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    setFixedSize(800, 500);

    QFont ft;

    QPushButton *btnUser = new QPushButton("用户", this);
    btnUser->move(210, 180);
    btnUser->resize(200, 100);
    ft.setPointSize(20);
    btnUser->setFont(ft);

    QPushButton *btnAdmin = new QPushButton("管理员", this);
    btnAdmin->move(510, 180);
    btnAdmin->resize(200, 100);
    ft.setPointSize(20);
    btnAdmin->setFont(ft);

    QLabel *labelTitle = new QLabel("足球联赛数据系统", this);
    labelTitle->move(300, 50);
    labelTitle->resize(200, 80);
    ft.setPointSize(25);
    labelTitle->setFont(ft);

    Leaguedatawindow *leagueDataWindow = new Leaguedatawindow(this);
    adminverifywindow *adminVerifyWindow = new adminverifywindow(this);
    datamanagewindow *dataManageWindow = new datamanagewindow(this);
    teamdatawindow *teamDataWindow = new teamdatawindow(this);
    playerdatawindow *playerDataWindow = new playerdatawindow(this);
    scheduleWindow *ScheduleWindow = new scheduleWindow(this);

    QPushButton *btnClose = new QPushButton("退出程序", this);
    btnClose->move(700, 430);
    btnClose->resize(100, 50);
    connect( btnClose, &QPushButton::clicked, this, [=](){
        leagueDataWindow->close();
        adminVerifyWindow->close();
        dataManageWindow->close();
        teamDataWindow->close();
        playerDataWindow->close();
        ScheduleWindow->close();
        this->close();
    });

    //赛季选择
    QTableWidget *currentSeason = new QTableWidget(this);
    currentSeason->resize(172, 32);
    currentSeason->move(50,90);
    currentSeason->setColumnCount(2);
    currentSeason->setRowCount(1);
    currentSeason->setColumnWidth(0, 70);
    currentSeason->setColumnWidth(1, 100);
    currentSeason->verticalHeader()->setVisible(false);
    currentSeason->horizontalHeader()->setVisible(false);
    currentSeason->setEditTriggers(QAbstractItemView::NoEditTriggers);
    currentSeason->setItem(0, 0, new QTableWidgetItem("当前赛季"));
    currentSeason->setItem(0, 1, new QTableWidgetItem("19-20"));
    currentSeason->item(0, 0)->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    currentSeason->item(0, 1)->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    QTreeWidget *seasonSelect = new QTreeWidget(this);
    seasonSelect->move(50, 150);
    seasonSelect->resize(100,300);
    QStringList strs = {"赛季选择"};
    seasonSelect->setHeaderLabels(strs);
    QTreeWidgetItem *season1920 = new QTreeWidgetItem(seasonSelect);
    season1920->setText(0, "19-20");
    QTreeWidgetItem *season1819 = new QTreeWidgetItem(seasonSelect);
    season1819->setText(0, "18-19");
    QTreeWidgetItem *season1718 = new QTreeWidgetItem(seasonSelect);
    season1718->setText(0, "17-18");
    QTreeWidgetItem *season1617 = new QTreeWidgetItem(seasonSelect);
    season1617->setText(0, "16-17");

    seasonSelected = "19-20";
    playerDataWindow->getData(seasonSelected);
    playerDataWindow->setReReadFlag();
    dataManageWindow->setIfChangable(0);

    connect( seasonSelect, &QTreeWidget::itemActivated, this, [=](){
        QTimer::singleShot(500, this, [=](){
            seasonSelected = seasonSelect->currentItem()->text(0);
            if (seasonSelected == "19-20"){
                dataManageWindow->setIfChangable(0);
            }else{
                dataManageWindow->setIfChangable(1);
            }
            playerDataWindow->getData(seasonSelected);
            QMessageBox *qmb = new QMessageBox();
            qmb->information(this, "赛季选择", "切换到" + seasonSelect->currentItem()->text(0) + "赛季");
            currentSeason->setItem(0,1, new QTableWidgetItem(seasonSelected));
            currentSeason->item(0, 1)->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
        });
    });

    //赛季选择

    this->getData(playerDataWindow->getPlayers(), playerDataWindow->getTeams());

    //从主窗口进入联赛数据窗口
    connect( btnUser, &QPushButton::clicked, leagueDataWindow, [=](){
        leagueDataWindow->getData(playerDataWindow->getTeamNames(), playerDataWindow->getPlayers(), playerDataWindow->getTeams());
        leagueDataWindow->setCurrentSeason(playerDataWindow->getCurrentSeason());
        leagueDataWindow->showTable();
        leagueDataWindow->show();
        this->hide();
    });

    //从联赛数据窗口返回主窗口
    connect( leagueDataWindow, &Leaguedatawindow::leagueDataWindowBack, this, [=](){
        leagueDataWindow->hide();
        this->show();
    });

    //从主窗口进入验证窗口
    connect( btnAdmin, &QPushButton::clicked, adminVerifyWindow, [=](){
        adminVerifyWindow->show();
        this->hide();
    });

    //从验证窗口返回主窗口
    connect( adminVerifyWindow, &adminverifywindow::adminVerifWindowBack, this, [=](){
        adminVerifyWindow->hide();
        this->show();
    });

    //从验证窗口进入数据管理窗口
    connect( adminVerifyWindow, &adminverifywindow::adminVerifSucceed, this, [=](){
        dataManageWindow->getData(playerDataWindow->getTeamNames(), playerDataWindow->getPlayers(), playerDataWindow->getTeams(), playerDataWindow->getSchedule());
        dataManageWindow->manageTableShow();
        dataManageWindow->show();
        adminVerifyWindow->hide();
    });

    //从数据管理窗口返回主窗口
    connect( dataManageWindow, &datamanagewindow::dataManageWindowBack, this, [=](){
        playerDataWindow->getData(seasonSelected);
        dataManageWindow->hide();
        this->show();
    });

    //从球队数据窗口返回联赛数据窗口
    connect( teamDataWindow, &teamdatawindow::teamDataWindowBackToLeague, this, [=](){
        leagueDataWindow->show();
        teamDataWindow->hide();
    });

    //从球队数据窗口返回赛程窗口
    connect( teamDataWindow, &teamdatawindow::teamDataWindowBackToSchedule, this, [=](){
        ScheduleWindow->getData(playerDataWindow->getTeams(), playerDataWindow->getSchedule());
        ScheduleWindow->showSchedule();
        ScheduleWindow->show();
        teamDataWindow->hide();
    });

    //从球员数据窗口返回球队数据窗口
    connect( playerDataWindow, &playerdatawindow::playerDataWindowBack, this, [=](){
        teamDataWindow->getData(playerDataWindow->getPlayers(), playerDataWindow->getTeams(), playerDataWindow->getSchedule());
        teamDataWindow->setTeamNameNow(findTeam(teams, playerDataWindow->getTeamSelect(), 1));
        teamDataWindow->showAll();
        teamDataWindow->showAttributes();
        teamDataWindow->show();
        playerDataWindow->hide();
    });

    //从联赛数据窗口进入某个球队的数据窗口
    connect( leagueDataWindow, &Leaguedatawindow::teamDataWindowShowAndGetTeam, this, [=](){
        teamDataWindow->getData(playerDataWindow->getPlayers(), playerDataWindow->getTeams(), playerDataWindow->getSchedule());
        teamDataWindow->setTeamNameNow(findTeam(teams, leagueDataWindow->getTeamSelect(), 1));
        teamDataWindow->showAll();
        teamDataWindow->showAttributes();
        teamDataWindow->show();
        leagueDataWindow->hide();
    });

    //从球队窗口进入某个球员的数据窗口
    connect( teamDataWindow, &teamdatawindow::playerDataWindowShowAndGetPlayer, this, [=](){
        playerDataWindow->setPlayerNameNow(findPlayer(players, teamDataWindow->getPlayerSelect(), 1));
        playerDataWindow->showTable();
        playerDataWindow->show();
        teamDataWindow->hide();
    });

    //从联赛窗口进入赛程窗口
    connect( leagueDataWindow, &Leaguedatawindow::scheduleWindowShow, this, [=](){
        ScheduleWindow->getData(playerDataWindow->getTeams(), playerDataWindow->getSchedule());
        ScheduleWindow->showSchedule();
        ScheduleWindow->show();
        leagueDataWindow->hide();
    });

    //从赛程窗口返回联赛窗口
    connect( ScheduleWindow, &scheduleWindow::scheduleWindowBack, this, [=](){
        leagueDataWindow->show();
        ScheduleWindow->hide();
    });

    //从赛程窗口进入某个球队的数据窗口
    connect( ScheduleWindow, &scheduleWindow::teamDataWindowShowAndGetTeam, this, [=](){
        teamDataWindow->getData(playerDataWindow->getPlayers(), playerDataWindow->getTeams(), playerDataWindow->getSchedule());
        teamDataWindow->setTeamNameNow(findTeam(teams, ScheduleWindow->getTeamSelect(), 1));
        teamDataWindow->showAll();
        teamDataWindow->showAttributes();
        teamDataWindow->show();
        ScheduleWindow->hide();
    });

    //从联赛窗口进入某个球员的数据窗口
    connect( leagueDataWindow, &Leaguedatawindow::playerDataWindowShowAndGetPlayer, this, [=](){
        playerDataWindow->setPlayerNameNow(findPlayer(players, leagueDataWindow->getPlayerSelect(), 1));
        playerDataWindow->showTable();
        playerDataWindow->show();
        leagueDataWindow->hide();
    });

    //从球员窗口返回联赛窗口
    connect( playerDataWindow, &playerdatawindow::playerDataWindowBackToLeague, this, [=](){
        leagueDataWindow->show();
        playerDataWindow->hide();
    });
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::getData(struct player *players, struct team *teams){
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
