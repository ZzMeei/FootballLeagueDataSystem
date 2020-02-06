#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "leaguedatawindow.h"
#include "adminverifywindow.h"
#include "datamanagewindow.h"
#include "teamdatawindow.h"
#include "playerdatawindow.h"
#include "schedulewindow.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    void getData(struct player players[], struct team teams[]);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    struct player players[1000];
    struct team teams[1000];
    QString seasonSelected;
};

#endif // MAINWINDOW_H
