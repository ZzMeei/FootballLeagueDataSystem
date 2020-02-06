#ifndef PLAYERDATAWINDOW_H
#define PLAYERDATAWINDOW_H

#include <QMainWindow>
#include <QTableWidget>

struct player{
    QString name; //姓名
    QString nation; //国籍
    QString postion; //场上位置
    QString team; //所属球队
    int age; //年龄
    int id; //场上号码
    int numberStage; //出场数
    int numberGoal; //进球数
    int numberAssist; //助攻数
    int numberSave; //扑救数
};

struct team{
    QString name; //球队名
    int fraction; //积分
    int ranking; //排名
    int numberGoal; //进球数
    int numberLose; //失球数
    QList<QString> playerNames;
};

struct matchKind{
    int matchTeamA, matchTeamB;
    int fractionA, fractionB;
};

struct teamAndRanking{
    QString teamName;
    int teamRanking;
};

struct teamAndFraction{
    QString teamName;
    int teamFraction;
    int teamGoalDifference;
};

struct teamAndLose{
    QString teamName;
    int lose;
};

struct teamAndGoal{
    QString teamName;
    int goal;
};

struct playerAndGoal{
    QString playerName;
    int goal;
};

struct playerAndAssist{
    QString playerName;
    int assist;
};

struct playerAndSave{
    QString playerName;
    int save;
};

struct playerAndOnStage{
    QString playerName;
    int onstage;
};

class playerdatawindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit playerdatawindow(QWidget *parent = nullptr);
    QList<QString> getTeamNames();
    struct player* getPlayers();
    struct team* getTeams();
    void setPlayerNameNow(int index);
    void showTable();
    QList<struct matchKind>* getSchedule();
    QString getTeamSelect();
    QTableWidget *playerInformationShow = new QTableWidget(this);
    void getData(QString seasonSelected);
    QString getCurrentSeason();
    void setReReadFlag();

signals:
    void playerDataWindowBack();
    void playerDataWindowBackToLeague();

public slots:

private:
    QString currentSeason;
    QList<QString> teamNames;
    struct player players[1000];
    struct team teams[1000];
    int indexPlayer;
    QList<struct matchKind> matchs[38];
    int reReadFlagPlayer;
    int reReadFlagTeam;
};

unsigned int BKDRHash(QString str);

bool compareTeamRanking(struct teamAndRanking a, struct teamAndRanking b);
bool compareTeamFraction(struct teamAndFraction a, struct teamAndFraction b);
bool compareTeamLose(struct teamAndLose a, struct teamAndLose b);
bool compareTeamGoal(struct teamAndGoal a, struct teamAndGoal b);
bool comparePlayerGoal(struct playerAndGoal a, struct playerAndGoal b);
bool comparePlayerAssist(struct playerAndAssist a, struct playerAndAssist b);
bool comparePlayerSave(struct playerAndSave a, struct playerAndSave b);
bool comparePlayerOnStage(struct playerAndOnStage a, struct playerAndOnStage b);
int findPlayer(struct player players[], QString playerName, int flag);
int findTeam(struct team teams[], QString teamName, int flag);

#endif // PLAYERDATAWINDOW_H
