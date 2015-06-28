#ifndef BLANK_H
#define BLANK_H
#include <QPushButton>
#include <QObject>
#include <QTimer>

class blank:public QObject{
 Q_OBJECT
public:
    blank(int R, int C,QWidget*parent);
    ~blank();
    const int row;
    const int col;
    int num;
    int shift;
    QPushButton*button;
    QTimer*time;
    void setnum();
    void setButtonPic();
    void operator -(blank*arr);
    void operator |(blank*arr);

public slots:
    void click();
    void moveleft();
    void moveright();
    void moveup();
    void movedown();

signals:
    void Click(int row,int col);
    void moveover();

};

#endif
