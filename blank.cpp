#include "blank.h"
#include <ctime>
#include <cstdlib>

blank::blank(int R,int C,QWidget*parent):row(R),col(C),QObject(parent){
   button=new QPushButton(parent);
   button->setGeometry(col*70,row*70,70,70);
   connect(button,SIGNAL(clicked()),this,SLOT(click())); /*連結*/
   shift=1;
   time=new QTimer();
}

void blank::click(){
    emit Click(row,col);
} /*接收訊號,按鍵位置*/

void blank::moveright(){
     button->setGeometry(col*70+shift*10,row*70,70,70);
     shift++;
     if(shift==8){
         shift=1;
         disconnect(time,SIGNAL(timeout()),this,SLOT(moveright()));
         button->setGeometry(col*70,row*70,70,70);
         setButtonPic();
         emit moveover();
     }
}

void blank::moveleft(){
    button->setGeometry(col*70-shift*10,row*70,70,70);
    shift++;
    if(shift==8){
        shift=1;
        disconnect(time,SIGNAL(timeout()),this,SLOT(moveleft()));
        button->setGeometry(col*70,row*70,70,70);
        setButtonPic();
    }
}

void blank::moveup(){
    button->setGeometry(col*70,row*70-shift*10,70,70);
    shift++;
    if(shift==8){
        shift=1;
        disconnect(time,SIGNAL(timeout()),this,SLOT(moveup()));
        button->setGeometry(col*70,row*70,70,70);
        setButtonPic();
        emit moveover();
    }
}

void blank::movedown(){
    button->setGeometry(col*70,row*70+shift*10,70,70);
    shift++;
    if(shift==8){
        shift=1;
        disconnect(time,SIGNAL(timeout()),this,SLOT(movedown()));
        button->setGeometry(col*70,row*70,70,70);
        setButtonPic();
    }
}

void blank::setnum(){
    num=rand()%4+1; /*產生糖果*/
}

void blank::setButtonPic(){
    switch(num){
    case 1: button->setIcon(QIcon(QPixmap(":/pic/pics/1.jpg")));
            button->setIconSize(button->size());break;
    case 11: button->setIcon(QIcon(QPixmap(":/pic/pics/11.jpg")));
             button->setIconSize(button->size());break;
    case 12: button->setIcon(QIcon(QPixmap(":/pic/pics/12.jpg")));
             button->setIconSize(button->size());break;
    case 13: button->setIcon(QIcon(QPixmap(":/pic/pics/13.jpg")));
             button->setIconSize(button->size());break;
    case 2: button->setIcon(QIcon(QPixmap(":/pic/pics/2.jpg")));
            button->setIconSize(button->size());break;
    case 21: button->setIcon(QIcon(QPixmap(":/pic/pics/21.jpg")));
             button->setIconSize(button->size());break;
    case 22: button->setIcon(QIcon(QPixmap(":/pic/pics/22.jpg")));
             button->setIconSize(button->size());break;
    case 23: button->setIcon(QIcon(QPixmap(":/pic/pics/23.jpg")));
             button->setIconSize(button->size());break;
    case 3: button->setIcon(QIcon(QPixmap(":/pic/pics/3.jpg")));
            button->setIconSize(button->size());break;
    case 31: button->setIcon(QIcon(QPixmap(":/pic/pics/31.jpg")));
             button->setIconSize(button->size());break;
    case 32: button->setIcon(QIcon(QPixmap(":/pic/pics/32.jpg")));
             button->setIconSize(button->size());break;
    case 33: button->setIcon(QIcon(QPixmap(":/pic/pics/33.jpg")));
             button->setIconSize(button->size());break;
    case 4: button->setIcon(QIcon(QPixmap(":/pic/pics/4.jpg")));
            button->setIconSize(button->size());break;
    case 41: button->setIcon(QIcon(QPixmap(":/pic/pics/41.jpg")));
             button->setIconSize(button->size());break;
    case 42: button->setIcon(QIcon(QPixmap(":/pic/pics/42.jpg")));
             button->setIconSize(button->size());break;
    case 43: button->setIcon(QIcon(QPixmap(":/pic/pics/43.jpg")));
             button->setIconSize(button->size());break;
    case 5: button->setIcon(QIcon(QPixmap(":/pic/pics/5.jpg")));
            button->setIconSize(button->size());break;
    default: button->setIcon(QIcon(QPixmap(" ")));break;
    }
} /*set pictures*/

void blank::operator -(blank*arr){
    int tmpnum=arr->num;
    arr->num=num;
    num=tmpnum;
    connect(time,SIGNAL(timeout()),this,SLOT(moveright()));
    connect(arr->time,SIGNAL(timeout()),arr,SLOT(moveleft()));
    time->start(100);
    arr->time->start(100); /*50毫秒後移動*/
}

void blank::operator |(blank*arr){
    int tmpnum=arr->num;
    arr->num=num;
    num=tmpnum;
    connect(time,SIGNAL(timeout()),this,SLOT(movedown()));
    connect(arr->time,SIGNAL(timeout()),arr,SLOT(moveup()));
    time->start(100);
    arr->time->start(100); /*50毫秒後移動*/
}

blank::~blank(){

}
