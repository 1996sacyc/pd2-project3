#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QMainWindow>
#include "blank.h"
#include <ctime>
#include <Qstring>
#include <QWidget>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    blank * arr[10][10];
    QTimer *t;
    QString str;
    int recordR;
    int recordC;
    int Countstar;
    int Countscore;
    void gamestart();
    void setclickpic(blank*b);
    void newpic();
    void serial(int bombtype,int rr,int cc);
    void down();
    bool clicked;
    int counttime=0;
    bool check(int r1,int c1,int r2,int c2);
    bool star(int r,int c);
    bool ver(int r, int c);
    bool hor(int r, int c);
    bool block(int r, int c);
    bool threeR(int r, int c);
    bool threeC(int r, int c);
    bool possible();
    ~MainWindow();

public slots:
    void button_click(int R,int C);
    void Time();
    void fillzero();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
