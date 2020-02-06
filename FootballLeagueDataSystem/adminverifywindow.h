#ifndef ADMINVERIFYWINDOW_H
#define ADMINVERIFYWINDOW_H

#include <QMainWindow>

class adminverifywindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit adminverifywindow(QWidget *parent = nullptr);

signals:
    void adminVerifWindowBack();
    void adminVerifSucceed();

public slots:
};

#endif // ADMINVERIFYWINDOW_H
