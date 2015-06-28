#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "des.h"
#include <QTimer>
#include <ctime>
#include <cstdlib>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent):
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    srand(time(NULL));
    for(int i=0; i<10 ; i++){
        for(int k=0; k<10; k++){
            arr[i][k]=new blank(i,k,this);
            connect(arr[i][k],SIGNAL(Click(int,int)),this,SLOT(button_click(int,int)));
            connect(arr[i][k],SIGNAL(moveover()),this,SLOT(fillzero()));
            //connect(t,SIGNAL(timeout()),this,SLOT(Time()));
            //t->start(1000); /*開始計時 一千毫秒發出信號*/
        }
    }
    clicked=false;
    Countscore=0;
    gamestart();
}

void MainWindow::gamestart(){
     clicked=false;
     qDebug() << "In gamestart function";
     for(int i=0; i<10; i++){
         for(int k=0; k<10; k++){
             arr[i][k]->setnum();/*產生亂數*/
             arr[i][k]->setButtonPic();
             if(k>=2&&arr[i][k]->num==arr[i][k-2]->num&&arr[i][k]->num==arr[i][k-1]->num)
                k--;
             if(i>=2&&arr[i][k]->num==arr[i-2][k]->num&&arr[i][k]->num==arr[i-1][k]->num)
                k--; /*有重複就往回重新產生*/
         }
     }
}

void MainWindow::setclickpic(blank *b){
  if(clicked==0){
    switch(b->num){
    case 1: b->button->setIcon(QIcon(QPixmap(":/pic/pics/1_.jpg")));
            b->button->setIconSize(b->button->size());break;
    case 11: b->button->setIcon(QIcon(QPixmap(":/pic/pics/11_.jpg")));
             b->button->setIconSize(b->button->size());break;
    case 12: b->button->setIcon(QIcon(QPixmap(":/pic/pics/12_.jpg")));
             b->button->setIconSize(b->button->size());break;
    case 13: b->button->setIcon(QIcon(QPixmap(":/pic/pics/13_.jpg")));
             b->button->setIconSize(b->button->size());break;
    case 2: b->button->setIcon(QIcon(QPixmap(":/pic/pics/2_.jpg")));
            b->button->setIconSize(b->button->size());break;
    case 21: b->button->setIcon(QIcon(QPixmap(":/pic/pics/21_.jpg")));
             b->button->setIconSize(b->button->size());break;
    case 22: b->button->setIcon(QIcon(QPixmap(":/pic/pics/22_.jpg")));
             b->button->setIconSize(b->button->size());break;
    case 23: b->button->setIcon(QIcon(QPixmap(":/pic/pics/23_.jpg")));
             b->button->setIconSize(b->button->size());break;
    case 3: b->button->setIcon(QIcon(QPixmap(":/pic/pics/3_.jpg")));
            b->button->setIconSize(b->button->size());break;
    case 31: b->button->setIcon(QIcon(QPixmap(":/pic/pics/31_.jpg")));
             b->button->setIconSize(b->button->size());break;
    case 32: b->button->setIcon(QIcon(QPixmap(":/pic/pics/32-.jpg")));
             b->button->setIconSize(b->button->size());break;
    case 33: b->button->setIcon(QIcon(QPixmap(":/pic/pics/33_.jpg")));
             b->button->setIconSize(b->button->size());break;
    case 4: b->button->setIcon(QIcon(QPixmap(":/pic/pics/4_.jpg")));
            b->button->setIconSize(b->button->size());break;
    case 41: b->button->setIcon(QIcon(QPixmap(":/pic/pics/41_.jpg")));
             b->button->setIconSize(b->button->size());break;
    case 42: b->button->setIcon(QIcon(QPixmap(":/pic/pics/42_.jpg")));
             b->button->setIconSize(b->button->size());break;
    case 43: b->button->setIcon(QIcon(QPixmap(":/pic/pics/43_.jpg")));
             b->button->setIconSize(b->button->size());break;
    case 5: b->button->setIcon(QIcon(QPixmap(":/pic/pics/5_.jpg")));
            b->button->setIconSize(b->button->size());break;
    }
  }
  else{
      b->setButtonPic();
  }
}

bool MainWindow::check(int r1, int c1, int r2, int c2){
    qDebug() << "setclickpic";
    star(r1,c1);
    star(r2,c2);
    block(r1,c1);
    block(r2,c2);
    hor(r1,c1);
    hor(r1,c1);
    ver(r1,c1);
    ver(r1,c1);
    threeR(r1,c1);
    threeR(r2,c2);
    threeC(r1,c1);
    threeC(r2,c2);
}

bool MainWindow::star(int r, int c){
     qDebug() << "In checkstar";
     int type=arr[r][c]->num;
     int count[5]={0};
     qDebug() << "A";
     if((type/10==0)&&(r>=2)&&(r<=7)&&((type==arr[r-2][c]->num)||(type==arr[r-2][c]->num/10))&&((type==arr[r-1][c]->num)||(type==arr[r-1][c]->num/10))&&((type==arr[r+1][c]->num)||(type==arr[r+1][c]->num/10))&&((type==arr[r+2][c]->num)||(type==arr[r+2][c]->num/10))){
         qDebug() << "In func B";
         arr[r][c]->num=5;
         Countscore=Countscore+100;
         if(arr[r-2][c]->num/10!=0)
            count[0]=arr[r-2][c]->num%10;
         if(arr[r-1][c]->num/10!=0)
            count[1]=arr[r-1][c]->num%10;
         count[2]=arr[r][c]->num;
         if(arr[r+1][c]->num/10!=0)
            count[3]=arr[r+1][c]->num%10;
         if(arr[r+2][c]->num/10!=0)
            count[4]=arr[r+2][c]->num%10;
         for(int i=0; i<5; i++){
             switch(count[i]){
              case 0: break;
              case 1: serial(1,r-2+i,c);arr[r-2+i][c]->num=0;break;
              case 2: serial(2,r-2+i,c);arr[r-2+i][c]->num=0;break;
              case 3: serial(3,r-2+i,c);arr[r-2+i][c]->num=0;break;
             }
         } /*連環引爆，爆炸後要歸零*/
         arr[r-2][c]->num=0;
         arr[r-1][c]->num=0;
         arr[r+2][c]->num=0;
         arr[r+1][c]->num=0;
         qDebug() << "End B";
         return true;
     }

     else if((type/10==0)&&(c>=2)&&(c<=7)&&((type==arr[r][c-2]->num)||(type==arr[r][c-2]->num/10))&&((type==arr[r][c-1]->num)||(type==arr[r][c-1]->num/10))&&((type==arr[r][c+1]->num)||(type==arr[r][c+1]->num/10))&&((type==arr[r][c+2]->num)||(type==arr[r][c+2]->num/10))){
         qDebug() << "In func C";
         arr[r][c]->num=5;
         Countscore=Countscore+100;
         if(arr[r][c-2]->num/10!=0)
            count[0]=arr[r][c-2]->num%10;
         if(arr[r][c-1]->num/10!=0)
            count[1]=arr[r][c-1]->num%10;
         count[2]=arr[r][c]->num;
         if(arr[r][c+1]->num/10!=0)
            count[3]=arr[r][c+1]->num%10;
         if(arr[r][c+2]->num/10!=0)
            count[4]=arr[r][c+2]->num%10;
         for(int i=0; i<5; i++){
             switch(count[i]){
              case 0: break;
              case 1: serial(1,r,c-2+i);arr[r][c-2+i]->num=0;break;
              case 2: serial(2,r,c-2+i);arr[r][c-2+i]->num=0;break;
              case 3: serial(3,r,c-2+i);arr[r][c-2+i]->num=0;break;
             }
         }
         arr[r][c-2]->num=0;
         arr[r][c-1]->num=0;
         arr[r][c+2]->num=0;
         arr[r][c+1]->num=0;
         qDebug() << "End C";
         return true;
     }

     else if((type/10!=0)&&(r>=2)&&(r<=7)&&((type/10==arr[r-2][c]->num)||(type/10==arr[r-2][c]->num/10))&&((type/10==arr[r-1][c]->num)||(type/10==arr[r-1][c]->num/10))&&((type/10==arr[r+1][c]->num)||(type/10==arr[r+1][c]->num/10))&&((type/10==arr[r+2][c]->num)||(type/10==arr[r+2][c]->num/10))){
         qDebug() << "In func D";
         Countscore=Countscore+100;
         if(arr[r-2][c]->num/10!=0)
            count[0]=arr[r-2][c]->num%10;
         if(arr[r-1][c]->num/10!=0)
            count[1]=arr[r-1][c]->num%10;
         count[2]=arr[r][c]->num%10;
         if(arr[r+1][c]->num/10!=0)
            count[3]=arr[r+1][c]->num%10;
         if(arr[r+2][c]->num/10!=0)
            count[4]=arr[r+2][c]->num%10;
         for(int i=0; i<5; i++){
             switch(count[i]){
              case 0: break;
              case 1: serial(1,r-2+i,c);arr[r-2+i][c]->num=0;break;
              case 2: serial(2,r-2+i,c);arr[r-2+i][c]->num=0;break;
              case 3: serial(3,r-2+i,c);arr[r-2+i][c]->num=0;break;
             }
         }
         arr[r][c]->num=0;
         arr[r-2][c]->num=0;
         arr[r-1][c]->num=0;
         arr[r+2][c]->num=0;
         arr[r+1][c]->num=0;
         qDebug() << " End D";
         return true;
       } /*進去的東西非普通糖果的情況*/

     else if((type/10!=0)&&(c>=2)&&(c<=7)&&((type/10==arr[r][c-2]->num)||(type/10==arr[r][c-2]->num/10))&&((type/10==arr[r][c-1]->num)||(type/10==arr[r][c-1]->num/10))&&((type/10==arr[r][c+1]->num)||(type/10==arr[r][c+1]->num/10))&&((type/10==arr[r][c+2]->num)||(type/10==arr[r][c+2]->num/10))){
         qDebug() << "In func E";
         Countscore=Countscore+100;
         if(arr[r][c-2]->num/10!=0)
            count[0]=arr[r][c-2]->num%10;
         if(arr[r][c-1]->num/10!=0)
            count[1]=arr[r][c-1]->num%10;
         count[2]=arr[r][c]->num%10;
         if(arr[r][c+1]->num/10!=0)
            count[3]=arr[r][c+1]->num%10;
         if(arr[r][c+2]->num/10!=0)
            count[4]=arr[r][c+2]->num%10;
         for(int i=0; i<5; i++){
             switch(count[i]){
              case 0: break;
              case 1: serial(1,r,c-2+i);arr[r][c-2+i]->num=0;break;
              case 2: serial(2,r,c-2+i);arr[r][c-2+i]->num=0;break;
              case 3: serial(3,r,c-2+i);arr[r][c-2+i]->num=0;break;
             }
         }
         arr[r][c]->num=0;
         arr[r][c-2]->num=0;
         arr[r][c-1]->num=0;
         arr[r][c+2]->num=0;
         arr[r][c+1]->num=0;
         qDebug() << "E";
         return true;
     } /*進去的東西非普通糖果的情況*/

    qDebug() << "F";
    return false;
}

bool MainWindow::hor(int r, int c){
    qDebug() << "In checkhor";
    int type=arr[r][c]->num; /*按鍵的糖果代表的數字*/
    int color=(arr[r][c]->num)/10; /*糖果顏色*/
    int count[4]={0};
    if((type/10==0)&&(c>=1)&&(c<=7)&&((type==arr[r][c-1]->num)||(type==arr[r][c-1]->num/10))&&((type==arr[r][c+1]->num)||(type==arr[r][c+1]->num/10))&&((type==arr[r][c+2]->num)||(type==arr[r][c+2]->num/10))){
        arr[r][c]->num=(color*10)+2; /*水平消除的炸彈是糖果種類*10+2*/
        Countscore=Countscore+60;
        if(arr[r][c-1]->num>10)
            count[0]=arr[r][c-1]->num%10;
        count[1]=arr[r][c]->num;
        if(arr[r][c+1]->num>10)
            count[2]=arr[r][c+1]->num%10;
        if(arr[r][c+2]->num>10)
            count[3]=arr[r][c+2]->num%10;
        for(int i=0; i<4; i++){
            switch(count[i]){
              case 0: break;
              case 1: serial(1,r,c-1+i); arr[r][c-1+i]->num=0; break;
              case 2: serial(2,r,c-1+i); arr[r][c-1+i]->num=0; break;
              case 3: serial(3,r,c-1+i); arr[r][c-1+i]->num=0; break;
            }
        } /*連環引爆*/
        arr[r][c-1]->num=0;
        arr[r][c+1]->num=0;
        arr[r][c+2]->num=0;
        return true;
    }  /*c-1 c+1 c+2*/

    else if((type/10==0)&&(c>=2)&&(c<=8)&&((type==arr[r][c-1]->num)||(type==arr[r][c-1]->num/10))&&((type==arr[r][c-2]->num)||(type==arr[r][c-2]->num/10))&&((type==arr[r][c+1]->num)||(type==arr[r][c+1]->num/10))){
        Countscore=Countscore+60;
        if(arr[r][c-1]->num>10)
            count[1]=arr[r][c-1]->num%10;
        if(arr[r][c-2]->num>10)
            count[0]=arr[r][c-2]->num%10;
        count[2]=arr[r][c]->num;
        if(arr[r][c+1]->num>10)
            count[3]=arr[r][c+1]->num%10;
        for(int i=0; i<4; i++){
            switch(count[i]){
              case 0: break;
              case 1: serial(1,r,c-2+i); arr[r][c-2+i]->num=0; break;
              case 2: serial(2,r,c-2+i); arr[r][c-2+i]->num=0; break;
              case 3: serial(3,r,c-2+i); arr[r][c-2+i]->num=0; break;
            }
        }
        arr[r][c]->num=0;
        arr[r][c-1]->num=0;
        arr[r][c-2]->num=0;
        arr[r][c+1]->num=0;
        return true;
    } /*c-1 c-2 c+1*/

    else if((type/10!=0)&&(c>=1)&&(c<=7)&&((type/10==arr[r][c-1]->num)||(type/10==arr[r][c-1]->num/10))&&((type/10==arr[r][c+1]->num)||(type/10==arr[r][c+1]->num/10))&&((type/10==arr[r][c+2]->num)||(type/10==arr[r][c+2]->num/10))){
        Countscore=Countscore+60;
        if(arr[r][c-1]->num>10)
            count[0]=arr[r][c-1]->num%10;
        count[1]=arr[r][c]->num%10;
        if(arr[r][c+1]->num>10)
            count[2]=arr[r][c+1]->num%10;
        if(arr[r][c+2]->num>10)
            count[3]=arr[r][c+2]->num%10;
         for(int i=0; i<4; i++){
                switch(count[i]){
                  case 0: break;
                  case 1: serial(1,r,c-1+i); arr[r][c-1+i]->num=0; break;
                  case 2: serial(2,r,c-1+i); arr[r][c-1+i]->num=0; break;
                  case 3: serial(3,r,c-1+i); arr[r][c-1+i]->num=0; break;
                }
         } /*連環引爆*/
         arr[r][c]->num=0;
         arr[r][c-1]->num=0;
         arr[r][c+2]->num=0;
         arr[r][c+1]->num=0;
         return true;
     }  /*c-1 c+1 c+2*/

    else if((type/10!=0)&&(c>=2)&&(c<=8)&&((type/10==arr[r][c-1]->num)||(type/10==arr[r][c-1]->num/10))&&((type/10==arr[r][c-2]->num)||(type/10==arr[r][c-2]->num/10))&&((type/10==arr[r][c+1]->num)||(type/10==arr[r][c+1]->num/10))){
        arr[r][c]->num=(color*10)+2;
        Countscore=Countscore+60;
         if(arr[r][c-1]->num>10)
             count[0]=arr[r][c-1]->num%10;
         if(arr[r][c-2]->num>10)
             count[1]=arr[r][c-2]->num%10;
         count[2]=arr[r][c]->num%10;
         if(arr[r][c+1]->num>10)
             count[3]=arr[r][c+1]->num%10;
         for(int i=0; i<4; i++){
                switch(count[i]){
                  case 0: break;
                  case 1: serial(1,r,c-2+i); arr[r][c-2+i]->num=0; break;
                  case 2: serial(2,r,c-2+i); arr[r][c-2+i]->num=0; break;
                  case 3: serial(3,r,c-2+i); arr[r][c-2+i]->num=0; break;
                }
            }
         arr[r][c-1]->num=0;
         arr[r][c-2]->num=0;
         arr[r][c+1]->num=0;
         return true;
    } /*c-1 c-2 c+1*/
    /*進去的東西非普通糖果的情況*/
   return false;
} /*產生水平消除的炸彈*/

bool MainWindow::ver(int r, int c){
    qDebug() << "In checkver";
    int type=arr[r][c]->num; /*按鍵的糖果代表的數字*/
    int color=(arr[r][c]->num)/10; /*糖果顏色*/
    int count[4]={0};
    if((type/10==0)&&(r>=1)&&(r<=7)&&((type==arr[r-1][c]->num)||(type==arr[r-1][c]->num/10))&&((type==arr[r+1][c]->num)||(type==arr[r+1][c]->num/10))&&((type==arr[r+2][c]->num)||(type==arr[r+2][c]->num/10))){
        arr[r][c]->num=(color*10)+1; /*垂直消除的炸彈是(糖果種類)*10+1*/
        Countscore=Countscore+60;
        if(arr[r-1][c]->num>10)
            count[0]=arr[r-1][c]->num%10;
        count[1]=arr[r][c]->num;
        if(arr[r+1][c]->num>10)
            count[2]=arr[r+1][c]->num%10;
        if(arr[r+2][c]->num>10)
            count[3]=arr[r+2][c]->num%10;
        for(int i=0; i<4; i++){
           switch(count[i]){
              case 0: arr[r-1+i][c]->num=0;break;
              case 1: serial(1,r-1+i,c); arr[r-1+i][c]->num=0; break;
              case 2: serial(2,r-1+i,c); arr[r-1+i][c]->num=0; break;
              case 3: serial(3,r-1+i,c); arr[r-1+i][c]->num=0; break;
           }
        } /*連環引爆*/
        arr[r-1][c]->num=0;
        arr[r+1][c]->num=0;
        arr[r+2][c]->num=0;

        return true;
    } /*r-1 r+1 r+2*/

    //qDebug() << "In checkverA";

    else if((type/10!=0)&&(r>=2)&&(r<=8)&&((type==arr[r-1][c]->num)||(type==arr[r-1][c]->num/10))&&((type==arr[r-2][c]->num)||(type==arr[r-2][c]->num/10))&&((type==arr[r+1][c]->num)||(type==arr[r+1][c]->num/10))){
        arr[r][c]->num=color+1; /*垂直消除的炸彈是糖果種類*10+1*/
        Countscore=Countscore+60;
        if(arr[r-1][c]->num>10)
            count[0]=arr[r-1][c]->num%10;
        if(arr[r-2][c]->num>10)
            count[1]=arr[r-2][c]->num%10;
        count[2]=arr[r][c]->num;
        if(arr[r+1][c]->num>10)
            count[3]=arr[r+1][c]->num%10; /*討論還會引爆別人的狀況*/
        for(int i=0; i<4; i++){
           switch(count[i]){
              case 0: arr[r-2+i][c]->num=0;break;
              case 1: serial(1,r-2+i,c); arr[r-2+i][c]->num=0; break;
              case 2: serial(2,r-2+i,c); arr[r-2+i][c]->num=0; break;
              case 3: serial(3,r-2+i,c); arr[r-2+i][c]->num=0; break;
           }
        } /*連環引爆*/
        arr[r-1][c]->num=0;
        arr[r-2][c]->num=0;
        arr[r+1][c]->num=0;
        return true;
    } /*r-1 r-2 r+1*/

    //qDebug() << "In checkverB";

    else if((type/10!=0)&&(r>=1)&&(r<=7)&&((type/10==arr[r-1][c]->num)||(type/10==arr[r-1][c]->num/10))&&((type/10==arr[r+1][c]->num)||(type/10==arr[r+1][c]->num/10))&&((type/10==arr[r+2][c]->num)||(type/10==arr[r+2][c]->num/10))){
        Countscore=Countscore+60;
        if(arr[r-1][c]->num>10)
            count[0]=arr[r-1][c]->num%10;
        count[1]=arr[r][c]->num%10;
        if(arr[r+1][c]->num>10)
            count[2]=arr[r+1][c]->num%10;
        if(arr[r+2][c]->num>10)
            count[3]=arr[r+2][c]->num%10;
        for(int i=0; i<4; i++){
               switch(count[i]){
                  case 0: arr[r-1+i][c]->num=0;break;
                  case 1: serial(1,r-1+i,c); arr[r-1+i][c]->num=0; break;
                  case 2: serial(2,r-1+i,c); arr[r-1+i][c]->num=0; break;
                  case 3: serial(3,r-1+i,c); arr[r-1+i][c]->num=0; break;
               }
        } /*連環引爆*/
        arr[r][c]->num=0;
        arr[r-1][c]->num=0;
        arr[r+1][c]->num=0;
        arr[r+2][c]->num=0;
        return true;
      } /*r-1 r+1 r+2*/

    else if((type/10!=0)&&(r>=2)&&(r<=8)&&((type/10==arr[r-1][c]->num)||(type/10==arr[r-1][c]->num/10))&&((type/10==arr[r-2][c]->num)||(type/10==arr[r-2][c]->num/10))&&((type/10==arr[r+1][c]->num)||(type/10==arr[r+1][c]->num/10))){
        Countscore=Countscore+60;
        if(arr[r-1][c]->num>10)
            count[0]=arr[r-1][c]->num%10;
        if(arr[r-2][c]->num>10)
            count[1]=arr[r-2][c]->num%10;
        count[2]=arr[r][c]->num%10;
        if(arr[r+1][c]->num>10)
            count[3]=arr[r+1][c]->num%10; /*討論還會引爆別人的狀況*/
        for(int i=0; i<4; i++){
               switch(count[i]){
                  case 0: arr[r-2+i][c]->num=0;break;
                  case 1: serial(1,r-2+i,c); arr[r-2+i][c]->num=0; break;
                  case 2: serial(2,r-2+i,c); arr[r-2+i][c]->num=0; break;
                  case 3: serial(3,r-2+i,c); arr[r-2+i][c]->num=0; break;
               }
        } /*連環引爆*/
        arr[r][c]->num=0;
        arr[r-1][c]->num=0;
        arr[r-2][c]->num=0;
        arr[r+1][c]->num=0;
        return true;
    } /*r-1 r-2 r+1*/
   /*進去的東西非普通糖果的情況*/
    //qDebug() << "In checkverC";
    return false;
} /*產生垂直消除的炸彈*/

bool MainWindow::block(int r, int c){
    qDebug() << "In checkblock";
    int type=arr[r][c]->num; /*按鍵的糖果代表的數字*/
    int color=(arr[r][c]->num)/10;
    int count[5]={0};
    if((type/10==0)&&(r>=2)&&(c<=7)&&((type==arr[r][c+1]->num)||(type==arr[r][c+1]->num/10))&&((type==arr[r][c+2]->num)||(type==arr[r][c+2]->num/10))&&((type==arr[r-1][c]->num)||(type==arr[r-1][c]->num/10))&&((type==arr[r-2][c]->num)||(type==arr[r-2][c]->num/10))){
        arr[r][c]->num=(color*10)+3; /*block的炸彈是(糖果種類)*10+3*/
        Countscore=Countscore+80;
        if((arr[r+1][c]->num==arr[r][c]->num)&&(r<=8)){
           arr[r+1][c]->num=0;
        }
        if((arr[r][c-1]->num==arr[r][c]->num)&&(c>=1)){
           arr[r][c-1]->num=0;
        } /*邊間要一起消除*/

        if(arr[r][c+1]->num>10)
            count[0]=arr[r][c+1]->num%10;
        if(arr[r][c+2]->num>10)
            count[1]=arr[r][c+2]->num%10;
        count[2]=arr[r][c]->num;
        if(arr[r-1][c]->num>10)
            count[3]=arr[r-1][c]->num%10;
        if(arr[r-2][c]->num>10)
            count[4]=arr[r-2][c]->num%10;

        switch (count[0]) {
        case 0: break;
        case 1: serial(1,r,c+1); arr[r][c+1]->num=0; break;
        case 2: serial(2,r,c+1); arr[r][c+1]->num=0; break;
        case 3: serial(3,r,c+1); arr[r][c+1]->num=0; break;
        }

        switch (count[1]) {
        case 0: break;
        case 1: serial(1,r,c+2); arr[r][c+2]->num=0; break;
        case 2: serial(2,r,c+2); arr[r][c+2]->num=0; break;
        case 3: serial(3,r,c+2); arr[r][c+2]->num=0; break;
        }

        switch (count[3]) {
        case 0: break;
        case 1: serial(1,r-1,c); arr[r-1][c]->num=0; break;
        case 2: serial(2,r-1,c); arr[r-1][c]->num=0; break;
        case 3: serial(3,r-1,c); arr[r-1][c]->num=0; break;
        }

        switch (count[4]) {
        case 0: break;
        case 1: serial(1,r-2,c); arr[r-2][c]->num=0; break;
        case 2: serial(2,r-2,c); arr[r-2][c]->num=0; break;
        case 3: serial(3,r-2,c); arr[r-2][c]->num=0; break;
        } /* 分開討論連續引爆*/
        arr[r-2][c]->num=0;
        arr[r-1][c]->num=0;
        arr[r][c+1]->num=0;
        arr[r][c+2]->num=0;
        return true;
    } /*c+1 c+2 r-1 r-2 */

    else if((type/10==0)&&(r<=7)&&(c>=2)&&((type==arr[r][c-1]->num)||(type==arr[r][c-1]->num/10))&&((type==arr[r][c-2]->num)||(type==arr[r][c-2]->num/10))&&((type==arr[r+1][c]->num)||(type==arr[r+1][c]->num/10))&&((type==arr[r+2][c]->num)||(type==arr[r+2][c]->num/10))){
        arr[r][c]->num=(color*10)+3;
        Countscore=Countscore+80;
        if((arr[r-1][c]->num==arr[r][c]->num)&&(r>=1)){
           arr[r-1][c]->num=0;
        }
        if((arr[r][c+1]->num==arr[r][c]->num)&&(c<=8)){
           arr[r][c+1]->num=0;
        } /*邊間*/

        if(arr[r][c-1]->num>10)
            count[0]=arr[r][c-1]->num%10;
        if(arr[r][c-2]->num>10)
            count[1]=arr[r][c-2]->num%10;
        count[2]=arr[r][c]->num;
        if(arr[r+1][c]->num>10)
            count[3]=arr[r+1][c]->num%10;
        if(arr[r+2][c]->num>10)
            count[4]=arr[r+2][c]->num%10;

        switch (count[0]) {
        case 0: arr[r][c-1]->num=0;break;
        case 1: serial(1,r,c-1); arr[r][c-1]->num=0; break;
        case 2: serial(2,r,c-1); arr[r][c-1]->num=0; break;
        case 3: serial(3,r,c-1); arr[r][c-1]->num=0; break;
        }

        switch (count[1]) {
        case 0: arr[r][c-2]->num=0;break;
        case 1: serial(1,r,c-2); arr[r][c-2]->num=0; break;
        case 2: serial(2,r,c-2); arr[r][c-2]->num=0; break;
        case 3: serial(3,r,c-2); arr[r][c-2]->num=0; break;
        }

        switch (count[3]) {
        case 0: arr[r+1][c]->num=0;break;
        case 1: serial(1,r+1,c); arr[r+1][c]->num=0; break;
        case 2: serial(2,r+1,c); arr[r+1][c]->num=0; break;
        case 3: serial(3,r+1,c); arr[r+1][c]->num=0; break;
        }

        switch (count[4]) {
        case 0: arr[r+2][c]->num=0;break;
        case 1: serial(1,r+2,c); arr[r+2][c]->num=0; break;
        case 2: serial(2,r+2,c); arr[r+2][c]->num=0; break;
        case 3: serial(3,r+2,c); arr[r+2][c]->num=0; break;
        }
        arr[r][c-2]->num=0;
        arr[r][c-1]->num=0;
        arr[r+1][c]->num=0;
        arr[r+2][c]->num=0;
        return true;
    } /*c-1 c-2 r+1 r+2 */

    else if((type/10==0)&&(r<=7)&&(c<=7)&&((type==arr[r][c+1]->num)||(type==arr[r][c+1]->num/10))&&((type==arr[r][c+2]->num)||(type==arr[r][c+2]->num/10))&&((type==arr[r+1][c]->num)||(type==arr[r+1][c]->num/10))&&((type==arr[r+2][c]->num)||(type==arr[r+2][c]->num/10))){
        arr[r][c]->num=(color*10)+3;
        Countscore=Countscore+80;
        if((arr[r-1][c]->num==arr[r][c]->num)&&(r>=1)){
           arr[r-1][c]->num=0;
        }
        if((arr[r][c-1]->num==arr[r][c]->num)&&(c>=1)){
           arr[r][c-1]->num=0;
        } /*邊間*/

        if(arr[r][c+1]->num>10)
            count[0]=arr[r][c+1]->num%10;
        if(arr[r][c+2]->num>10)
            count[1]=arr[r][c+2]->num%10;
        count[2]=arr[r][c]->num;
        if(arr[r+1][c]->num>10)
            count[3]=arr[r+1][c]->num%10;
        if(arr[r+2][c]->num>10)
            count[4]=arr[r+2][c]->num%10;

        switch (count[0]) {
        case 0: arr[r][c+1]->num=0;break;
        case 1: serial(1,r,c+1); arr[r][c+1]->num=0; break;
        case 2: serial(2,r,c+1); arr[r][c+1]->num=0; break;
        case 3: serial(3,r,c+1); arr[r][c+1]->num=0; break;
        }

        switch (count[1]) {
        case 0: arr[r][c+2]->num=0;break;
        case 1: serial(1,r,c+2); arr[r][c+2]->num=0; break;
        case 2: serial(2,r,c+2); arr[r][c+2]->num=0; break;
        case 3: serial(3,r,c+2); arr[r][c+2]->num=0; break;
        }

        switch (count[3]) {
        case 0: arr[r+1][c]->num=0;break;
        case 1: serial(1,r+1,c); arr[r+1][c]->num=0; break;
        case 2: serial(2,r+1,c); arr[r+1][c]->num=0; break;
        case 3: serial(3,r+1,c); arr[r+1][c]->num=0; break;
        }

        switch (count[4]) {
        case 0: arr[r+2][c]->num=0;break;
        case 1: serial(1,r+2,c); arr[r+2][c]->num=0; break;
        case 2: serial(2,r+2,c); arr[r+2][c]->num=0; break;
        case 3: serial(3,r+2,c); arr[r+2][c]->num=0; break;
        }
        arr[r][c+1]->num=0;
        arr[r][c+2]->num=0;
        arr[r+1][c]->num=0;
        arr[r+2][c]->num=0;
        return true;
    } /*c+1 c+2 r+1 r+2 */

    else if((type/10==0)&&(r>=2)&&(c>=2)&&((type==arr[r][c-1]->num)||(type==arr[r][c-1]->num/10))&&((type==arr[r][c-2]->num)||(type==arr[r][c-2]->num/10))&&((type==arr[r-1][c]->num)||(type==arr[r-1][c]->num/10))&&((type==arr[r-2][c]->num)||(type==arr[r-2][c]->num/10))){
        arr[r][c]->num=(color*10)+3;
        Countscore=Countscore+80;
        if((arr[r+1][c]->num==arr[r][c]->num)&&(r<=8)){
           arr[r+1][c]->num=0;
        }
        if((arr[r][c+1]->num==arr[r][c]->num)&&(c<=8)){
           arr[r][c+1]->num=0;
        } /*邊間*/

        if(arr[r][c-1]->num>10)
            count[0]=arr[r][c-1]->num%10;
        if(arr[r][c-2]->num>10)
            count[1]=arr[r][c-2]->num%10;
        count[2]=arr[r][c]->num;
        if(arr[r-1][c]->num>10)
            count[3]=arr[r-1][c]->num%10;
        if(arr[r-2][c]->num>10)
            count[4]=arr[r-2][c]->num%10;

        switch (count[0]) {
        case 0: arr[r][c-1]->num=0;break;
        case 1: serial(1,r,c-1); arr[r][c-1]->num=0; break;
        case 2: serial(2,r,c-1); arr[r][c-1]->num=0; break;
        case 3: serial(3,r,c-1); arr[r][c-1]->num=0; break;
        }

        switch (count[1]) {
        case 0: arr[r][c-2]->num=0;break;
        case 1: serial(1,r,c-2); arr[r][c-2]->num=0; break;
        case 2: serial(2,r,c-2); arr[r][c-2]->num=0; break;
        case 3: serial(3,r,c-2); arr[r][c-2]->num=0; break;
        }

        switch (count[3]) {
        case 0: arr[r-1][c]->num=0; break;
        case 1: serial(1,r-1,c); arr[r-1][c]->num=0; break;
        case 2: serial(2,r-1,c); arr[r-1][c]->num=0; break;
        case 3: serial(3,r-1,c); arr[r-1][c]->num=0; break;
        }

        switch (count[4]) {
        case 0: arr[r-2][c]->num=0; break;
        case 1: serial(1,r-2,c); arr[r-2][c]->num=0; break;
        case 2: serial(2,r-2,c); arr[r-2][c]->num=0; break;
        case 3: serial(3,r-2,c); arr[r-2][c]->num=0; break;
        }
        arr[r][c-2]->num=0;
        arr[r][c-1]->num=0;
        arr[r-1][c]->num=0;
        arr[r-2][c]->num=0;
        return true;
    } /*c-1 c-2 r-1 r-2 */
    /*L型*/

    else if((type/10==0)&&(r>=2)&&(c>=1)&&(c<=8)&&((type==arr[r][c-1]->num)||(type==arr[r][c-1]->num/10))&&((type==arr[r][c+1]->num)||(type==arr[r][c+1]->num/10))&&((type==arr[r-1][c]->num)||(type==arr[r-1][c]->num/10))&&((type==arr[r-2][c]->num)||(type==arr[r-2][c]->num/10))){
        arr[r][c]->num=(color*10)+3; /*block的炸彈是(糖果種類)*10+3*/
        Countscore=Countscore+80;
        if(arr[r][c+1]->num>10)
            count[0]=arr[r][c+1]->num%10;
        if(arr[r][c-1]->num>10)
            count[1]=arr[r][c-1]->num%10;
        count[2]=arr[r][c]->num;
        if(arr[r-1][c]->num>10)
            count[3]=arr[r-1][c]->num%10;
        if(arr[r-2][c]->num>10)
            count[4]=arr[r+2][c]->num%10;

        switch (count[0]) {
        case 0: arr[r][c+1]->num=0; break;
        case 1: serial(1,r,c+1); arr[r][c+1]->num=0; break;
        case 2: serial(2,r,c+1); arr[r][c+1]->num=0; break;
        case 3: serial(3,r,c+1); arr[r][c+1]->num=0; break;
        }

        switch (count[1]) {
        case 0: arr[r][c-1]->num=0; break;
        case 1: serial(1,r,c-1); arr[r][c-1]->num=0; break;
        case 2: serial(2,r,c-1); arr[r][c-1]->num=0; break;
        case 3: serial(3,r,c-1); arr[r][c-1]->num=0; break;
        }

        switch (count[3]) {
        case 0: arr[r-1][c]->num=0; break;
        case 1: serial(1,r-1,c); arr[r-1][c]->num=0; break;
        case 2: serial(2,r-1,c); arr[r-1][c]->num=0; break;
        case 3: serial(3,r-1,c); arr[r-1][c]->num=0; break;
        }

        switch (count[4]) {
        case 0: arr[r-2][c]->num=0; break;
        case 1: serial(1,r-2,c); arr[r-2][c]->num=0; break;
        case 2: serial(2,r-2,c); arr[r-2][c]->num=0; break;
        case 3: serial(3,r-2,c); arr[r-2][c]->num=0; break;
        }
        arr[r-2][c]->num=0;
        arr[r-1][c]->num=0;
        arr[r][c+1]->num=0;
        arr[r][c-1]->num=0;
        return true;
    } /*c+1 c-1 r-1 r-2 */

    else if((type/10==0)&&(r<=7)&&(c>=1)&&(c<=8)&&((type==arr[r][c-1]->num)||(type==arr[r][c-1]->num/10))&&((type==arr[r][c+1]->num)||(type==arr[r][c+1]->num/10))&&((type==arr[r+1][c]->num)||(type==arr[r+1][c]->num/10))&&((type==arr[r+2][c]->num)||(type==arr[r+2][c]->num/10))){
        arr[r][c]->num=(color*10)+3;
        Countscore=Countscore+80;
        if(arr[r][c+1]->num>10)
            count[0]=arr[r][c+1]->num%10;
        if(arr[r][c-1]->num>10)
            count[1]=arr[r][c-1]->num%10;
        count[2]=arr[r][c]->num;
        if(arr[r+1][c]->num>10)
            count[3]=arr[r+1][c]->num%10;
        if(arr[r+2][c]->num>10)
            count[4]=arr[r+2][c]->num%10;

        switch (count[0]) {
        case 0: arr[r][c+1]->num=0;break;
        case 1: serial(1,r,c+1); arr[r][c+1]->num=0; break;
        case 2: serial(2,r,c+1); arr[r][c+1]->num=0; break;
        case 3: serial(3,r,c+1); arr[r][c+1]->num=0; break;
        }

        switch (count[1]) {
        case 0: arr[r][c-1]->num=0;break;
        case 1: serial(1,r,c-1); arr[r][c-1]->num=0; break;
        case 2: serial(2,r,c-1); arr[r][c-1]->num=0; break;
        case 3: serial(3,r,c-1); arr[r][c-1]->num=0; break;
        }

        switch (count[3]) {
        case 0: arr[r+1][c]->num=0;break;
        case 1: serial(1,r+1,c); arr[r+1][c]->num=0; break;
        case 2: serial(2,r+1,c); arr[r+1][c]->num=0; break;
        case 3: serial(3,r+1,c); arr[r+1][c]->num=0; break;
        }

        switch (count[4]) {
        case 0: arr[r+2][c]->num=0;break;
        case 1: serial(1,r+2,c); arr[r+2][c]->num=0; break;
        case 2: serial(2,r+2,c); arr[r+2][c]->num=0; break;
        case 3: serial(3,r+2,c); arr[r+2][c]->num=0; break;
        }
        arr[r][c+1]->num=0;
        arr[r][c-1]->num=0;
        arr[r+1][c]->num=0;
        arr[r+2][c]->num=0;
        return true;
    } /*c+1 c-1 r+1 r+2 */

    else if((type/10==0)&&(r>=1)&&(c<=7)&&(r<=8)&&((type==arr[r][c+1]->num)||(type==arr[r][c+1]->num/10))&&((type==arr[r][c+2]->num)||(type==arr[r][c+2]->num/10))&&((type==arr[r+1][c]->num)||(type==arr[r+1][c]->num/10))&&((type==arr[r-1][c]->num)||(type==arr[r-1][c]->num/10))){
        arr[r][c]->num=(color*10)+3;
        Countscore=Countscore+80;
        if(arr[r][c+1]->num>10)
            count[0]=arr[r][c+1]->num%10;
        if(arr[r][c+2]->num>10)
            count[1]=arr[r][c+2]->num%10;
        count[2]=arr[r][c]->num;
        if(arr[r-1][c]->num>10)
            count[3]=arr[r-1][c]->num%10;
        if(arr[r+1][c]->num>10)
            count[4]=arr[r+1][c]->num%10;

        switch (count[0]) {
        case 0: arr[r][c+1]->num=0;break;
        case 1: serial(1,r,c+1); arr[r][c+1]->num=0; break;
        case 2: serial(2,r,c+1); arr[r][c+1]->num=0; break;
        case 3: serial(3,r,c+1); arr[r][c+1]->num=0; break;
        }

        switch (count[1]) {
        case 0: arr[r][c+2]->num=0;break;
        case 1: serial(1,r,c+2); arr[r][c+2]->num=0; break;
        case 2: serial(2,r,c+2); arr[r][c+2]->num=0; break;
        case 3: serial(3,r,c+2); arr[r][c+2]->num=0; break;
        }

        switch (count[3]) {
        case 0: arr[r-1][c]->num=0;break;
        case 1: serial(1,r-1,c); arr[r-1][c]->num=0; break;
        case 2: serial(2,r-1,c); arr[r-1][c]->num=0; break;
        case 3: serial(3,r-1,c); arr[r-1][c]->num=0; break;
        }

        switch (count[4]) {
        case 0: arr[r+1][c]->num=0;break;
        case 1: serial(1,r+1,c); arr[r+1][c]->num=0; break;
        case 2: serial(2,r+1,c); arr[r+1][c]->num=0; break;
        case 3: serial(3,r+1,c); arr[r+1][c]->num=0; break;
        }
        arr[r+1][c]->num=0;
        arr[r-1][c]->num=0;
        arr[r][c+1]->num=0;
        arr[r][c+2]->num=0;
        return true;
    } /*c+1 c+2 r-1 r+1 */

    else if((type/10==0)&&(r>=1)&&(c>=2)&&(r<=8)&&((type==arr[r][c-1]->num)||(type==arr[r][c-1]->num/10))&&((type==arr[r][c-2]->num)||(type==arr[r][c-2]->num/10))&&((type==arr[r+1][c]->num)||(type==arr[r+1][c]->num/10))&&((type==arr[r-1][c]->num)||(type==arr[r-1][c]->num/10))){
        arr[r][c]->num=(color*10)+3;
        Countscore=Countscore+80;
        if(arr[r][c-1]->num>10)
            count[0]=arr[r][c-1]->num%10;
        if(arr[r][c-2]->num>10)
            count[1]=arr[r][c-2]->num%10;
        count[2]=arr[r][c]->num;
        if(arr[r-1][c]->num>10)
            count[3]=arr[r-1][c]->num%10;
        if(arr[r+1][c]->num>10)
            count[4]=arr[r+1][c]->num%10;

        switch (count[0]) {
        case 0: arr[r][c-1]->num=0;break;
        case 1: serial(1,r,c-1); arr[r][c-1]->num=0; break;
        case 2: serial(2,r,c-1); arr[r][c-1]->num=0; break;
        case 3: serial(3,r,c-1); arr[r][c-1]->num=0; break;
        }

        switch (count[1]) {
        case 0: arr[r][c-2]->num=0;break;
        case 1: serial(1,r,c-2); arr[r][c-2]->num=0; break;
        case 2: serial(2,r,c-2); arr[r][c-2]->num=0; break;
        case 3: serial(3,r,c-2); arr[r][c-2]->num=0; break;
        }

        switch (count[3]) {
        case 0: arr[r-1][c]->num=0;break;
        case 1: serial(1,r-1,c); arr[r-1][c]->num=0; break;
        case 2: serial(2,r-1,c); arr[r-1][c]->num=0; break;
        case 3: serial(3,r-1,c); arr[r-1][c]->num=0; break;
        }

        switch (count[4]) {
        case 0: arr[r+1][c]->num=0; break;
        case 1: serial(1,r+1,c); arr[r+1][c]->num=0; break;
        case 2: serial(2,r+1,c); arr[r+1][c]->num=0; break;
        case 3: serial(3,r+1,c); arr[r+1][c]->num=0; break;
        }
        arr[r+1][c]->num=0;
        arr[r-1][c]->num=0;
        arr[r][c-1]->num=0;
        arr[r][c-2]->num=0;
        return true;
    } /*c-1 c-2 r-1 r+1 */
    /*T型*/

    else if((type/10!=0)&&(r>=2)&&(c<=7)&&((type/10==arr[r][c+1]->num)||(type/10==arr[r][c+1]->num/10))&&((type/10==arr[r][c+2]->num)||(type/10==arr[r][c+2]->num/10))&&((type/10==arr[r-1][c]->num)||(type/10==arr[r-1][c]->num/10))&&((type/10==arr[r-2][c]->num)||(type/10==arr[r-2][c]->num/10))){
            Countscore=Countscore+80;
            if((arr[r+1][c]->num==arr[r][c]->num)&&(r<=8)){
               arr[r+1][c]->num=0;
            }
            if((arr[r][c-1]->num==arr[r][c]->num)&&(c>=1)){
               arr[r][c-1]->num=0;
            } /*邊間要一起消除*/

            if(arr[r][c+1]->num>10)
                count[0]=arr[r][c+1]->num%10;
            if(arr[r][c+2]->num>10)
                count[1]=arr[r][c+2]->num%10;
            count[2]=arr[r][c]->num%10;
            if(arr[r-1][c]->num>10)
                count[3]=arr[r-1][c]->num%10;
            if(arr[r-2][c]->num>10)
                count[4]=arr[r-2][c]->num%10;

            switch (count[0]) {
            case 0: break;
            case 1: serial(1,r,c+1); arr[r][c+1]->num=0; break;
            case 2: serial(2,r,c+1); arr[r][c+1]->num=0; break;
            case 3: serial(3,r,c+1); arr[r][c+1]->num=0; break;
            }

            switch (count[1]) {
            case 0: break;
            case 1: serial(1,r,c+2); arr[r][c+2]->num=0; break;
            case 2: serial(2,r,c+2); arr[r][c+2]->num=0; break;
            case 3: serial(3,r,c+2); arr[r][c+2]->num=0; break;
            }

            switch (count[2]) {
            case 0: break;
            case 1: serial(1,r,c); arr[r][c]->num=0; break;
            case 2: serial(2,r,c); arr[r][c]->num=0; break;
            case 3: serial(3,r,c); arr[r][c]->num=0; break;
            }

            switch (count[3]) {
            case 0: break;
            case 1: serial(1,r-1,c); arr[r-1][c]->num=0; break;
            case 2: serial(2,r-1,c); arr[r-1][c]->num=0; break;
            case 3: serial(3,r-1,c); arr[r-1][c]->num=0; break;
            }

            switch (count[4]) {
            case 0: break;
            case 1: serial(1,r-2,c); arr[r-2][c]->num=0; break;
            case 2: serial(2,r-2,c); arr[r-2][c]->num=0; break;
            case 3: serial(3,r-2,c); arr[r-2][c]->num=0; break;
            } /* 分開討論連續引爆*/
            arr[r][c]->num=0;
            arr[r-2][c]->num=0;
            arr[r-1][c]->num=0;
            arr[r][c+1]->num=0;
            arr[r][c+2]->num=0;
            return true;
     } /*c+1 c+2 r-1 r-2 */

    else if((type/10!=0)&&(r<=7)&&(c>=2)&&((type/10==arr[r][c-1]->num)||(type/10==arr[r][c-1]->num/10))&&((type/10==arr[r][c-2]->num)||(type/10==arr[r][c-2]->num/10))&&((type/10==arr[r+1][c]->num)||(type/10==arr[r+1][c]->num/10))&&((type/10==arr[r+2][c]->num)||(type/10==arr[r+2][c]->num/10))){
            Countscore=Countscore+80;
            if((arr[r-1][c]->num==arr[r][c]->num)&&(r>=1)){
               arr[r-1][c]->num=0;
            }
            if((arr[r][c+1]->num==arr[r][c]->num)&&(c<=8)){
               arr[r][c+1]->num=0;
            } /*邊間*/

            if(arr[r][c-1]->num>10)
                count[0]=arr[r][c-1]->num%10;
            if(arr[r][c-2]->num>10)
                count[1]=arr[r][c-2]->num%10;
            count[2]=arr[r][c]->num%10;
            if(arr[r+1][c]->num>10)
                count[3]=arr[r+1][c]->num%10;
            if(arr[r+2][c]->num>10)
                count[4]=arr[r+2][c]->num%10;

            switch (count[0]) {
            case 0: arr[r][c-1]->num=0;break;
            case 1: serial(1,r,c-1); arr[r][c-1]->num=0; break;
            case 2: serial(2,r,c-1); arr[r][c-1]->num=0; break;
            case 3: serial(3,r,c-1); arr[r][c-1]->num=0; break;
            }

            switch (count[1]) {
            case 0: arr[r][c-2]->num=0;break;
            case 1: serial(1,r,c-2); arr[r][c-2]->num=0; break;
            case 2: serial(2,r,c-2); arr[r][c-2]->num=0; break;
            case 3: serial(3,r,c-2); arr[r][c-2]->num=0; break;
            }

            switch (count[2]) {
            case 0: break;
            case 1: serial(1,r,c); arr[r][c]->num=0; break;
            case 2: serial(2,r,c); arr[r][c]->num=0; break;
            case 3: serial(3,r,c); arr[r][c]->num=0; break;
            }

            switch (count[3]) {
            case 0: arr[r+1][c]->num=0;break;
            case 1: serial(1,r+1,c); arr[r+1][c]->num=0; break;
            case 2: serial(2,r+1,c); arr[r+1][c]->num=0; break;
            case 3: serial(3,r+1,c); arr[r+1][c]->num=0; break;
            }

            switch (count[4]) {
            case 0: arr[r+2][c]->num=0;break;
            case 1: serial(1,r+2,c); arr[r+2][c]->num=0; break;
            case 2: serial(2,r+2,c); arr[r+2][c]->num=0; break;
            case 3: serial(3,r+2,c); arr[r+2][c]->num=0; break;
            }
            arr[r][c]->num=0;
            arr[r][c-2]->num=0;
            arr[r][c-1]->num=0;
            arr[r+1][c]->num=0;
            arr[r+2][c]->num=0;
            return true;
     } /*c-1 c-2 r+1 r+2 */

    else if((type/10!=0)&&(r<=7)&&(c<=7)&&((type/10==arr[r][c+1]->num)||(type/10==arr[r][c+1]->num/10))&&((type/10==arr[r][c+2]->num)||(type/10==arr[r][c+2]->num/10))&&((type/10==arr[r+1][c]->num)||(type/10==arr[r+1][c]->num/10))&&((type/10==arr[r+2][c]->num)||(type/10==arr[r+2][c]->num/10))){
            Countscore=Countscore+80;
            if((arr[r-1][c]->num==arr[r][c]->num)&&(r>=1)){
               arr[r-1][c]->num=0;
            }
            if((arr[r][c-1]->num==arr[r][c]->num)&&(c>=1)){
               arr[r][c-1]->num=0;
            } /*邊間*/

            if(arr[r][c+1]->num>10)
                count[0]=arr[r][c+1]->num%10;
            if(arr[r][c+2]->num>10)
                count[1]=arr[r][c+2]->num%10;
            count[2]=arr[r][c]->num%10;
            if(arr[r+1][c]->num>10)
                count[3]=arr[r+1][c]->num%10;
            if(arr[r+2][c]->num>10)
                count[4]=arr[r+2][c]->num%10;

            switch (count[0]) {
            case 0: arr[r][c+1]->num=0;break;
            case 1: serial(1,r,c+1); arr[r][c+1]->num=0; break;
            case 2: serial(2,r,c+1); arr[r][c+1]->num=0; break;
            case 3: serial(3,r,c+1); arr[r][c+1]->num=0; break;
            }

            switch (count[1]) {
            case 0: arr[r][c+2]->num=0;break;
            case 1: serial(1,r,c+2); arr[r][c+2]->num=0; break;
            case 2: serial(2,r,c+2); arr[r][c+2]->num=0; break;
            case 3: serial(3,r,c+2); arr[r][c+2]->num=0; break;
            }

            switch (count[2]) {
            case 0: break;
            case 1: serial(1,r,c); arr[r][c]->num=0; break;
            case 2: serial(2,r,c); arr[r][c]->num=0; break;
            case 3: serial(3,r,c); arr[r][c]->num=0; break;
            }

            switch (count[3]) {
            case 0: arr[r+1][c]->num=0;break;
            case 1: serial(1,r+1,c); arr[r+1][c]->num=0; break;
            case 2: serial(2,r+1,c); arr[r+1][c]->num=0; break;
            case 3: serial(3,r+1,c); arr[r+1][c]->num=0; break;
            }

            switch (count[4]) {
            case 0: arr[r+2][c]->num=0;break;
            case 1: serial(1,r+2,c); arr[r+2][c]->num=0; break;
            case 2: serial(2,r+2,c); arr[r+2][c]->num=0; break;
            case 3: serial(3,r+2,c); arr[r+2][c]->num=0; break;
            }
            arr[r][c]->num=0;
            arr[r+1][c]->num=0;
            arr[r+2][c]->num=0;
            arr[r][c+1]->num=0;
            arr[r][c+2]->num=0;
            return true;
     } /*c+1 c+2 r+1 r+2 */

    else if((type/10!=0)&&(r>=2)&&(c>=2)&&((type/10==arr[r][c-1]->num)||(type/10==arr[r][c-1]->num/10))&&((type/10==arr[r][c-2]->num)||(type/10==arr[r][c-2]->num/10))&&((type/10==arr[r-1][c]->num)||(type/10==arr[r-1][c]->num/10))&&((type/10==arr[r-2][c]->num)||(type/10==arr[r-2][c]->num/10))){
            Countscore=Countscore+80;
            if((arr[r+1][c]->num==arr[r][c]->num)&&(r<=8)){
               arr[r+1][c]->num=0;
            }
            if((arr[r][c+1]->num==arr[r][c]->num)&&(c<=8)){
               arr[r][c+1]->num=0;
            } /*邊間*/

            if(arr[r][c-1]->num>10)
                count[0]=arr[r][c-1]->num%10;
            if(arr[r][c-2]->num>10)
                count[1]=arr[r][c-2]->num%10;
            count[2]=arr[r][c]->num%10;
            if(arr[r-1][c]->num>10)
                count[3]=arr[r-1][c]->num%10;
            if(arr[r-2][c]->num>10)
                count[4]=arr[r-2][c]->num%10;

            switch (count[0]) {
            case 0: arr[r][c-1]->num=0;break;
            case 1: serial(1,r,c-1); arr[r][c-1]->num=0; break;
            case 2: serial(2,r,c-1); arr[r][c-1]->num=0; break;
            case 3: serial(3,r,c-1); arr[r][c-1]->num=0; break;
            }

            switch (count[1]) {
            case 0: arr[r][c-2]->num=0;break;
            case 1: serial(1,r,c-2); arr[r][c-2]->num=0; break;
            case 2: serial(2,r,c-2); arr[r][c-2]->num=0; break;
            case 3: serial(3,r,c-2); arr[r][c-2]->num=0; break;
            }

            switch (count[2]) {
            case 0: break;
            case 1: serial(1,r,c); arr[r][c]->num=0; break;
            case 2: serial(2,r,c); arr[r][c]->num=0; break;
            case 3: serial(3,r,c); arr[r][c]->num=0; break;
            }

            switch (count[3]) {
            case 0: arr[r-1][c]->num=0; break;
            case 1: serial(1,r-1,c); arr[r-1][c]->num=0; break;
            case 2: serial(2,r-1,c); arr[r-1][c]->num=0; break;
            case 3: serial(3,r-1,c); arr[r-1][c]->num=0; break;
            }

            switch (count[4]) {
            case 0: arr[r-2][c]->num=0; break;
            case 1: serial(1,r-2,c); arr[r-2][c]->num=0; break;
            case 2: serial(2,r-2,c); arr[r-2][c]->num=0; break;
            case 3: serial(3,r-2,c); arr[r-2][c]->num=0; break;
            }
            arr[r][c]->num=0;
            arr[r-2][c]->num=0;
            arr[r-1][c]->num=0;
            arr[r][c-1]->num=0;
            arr[r][c-2]->num=0;
            return true;
     } /*c-1 c-2 r-1 r-2 */
        /*L型*/

    else if((type/10!=0)&&(r>=2)&&(c>=1)&&(c<=8)&&((type/10==arr[r][c-1]->num)||(type/10==arr[r][c-1]->num/10))&&((type/10==arr[r][c+1]->num)||(type/10==arr[r][c+1]->num/10))&&((type/10==arr[r-1][c]->num)||(type/10==arr[r-1][c]->num/10))&&((type/10==arr[r-2][c]->num)||(type/10==arr[r-2][c]->num/10))){
            Countscore=Countscore+80;
            if(arr[r][c+1]->num>10)
                count[0]=arr[r][c+1]->num%10;
            if(arr[r][c-1]->num>10)
                count[1]=arr[r][c-1]->num%10;
            count[2]=arr[r][c]->num%10;
            if(arr[r-1][c]->num>10)
                count[3]=arr[r-1][c]->num%10;
            if(arr[r-2][c]->num>10)
                count[4]=arr[r+2][c]->num%10;

            switch (count[0]) {
            case 0: arr[r][c+1]->num=0; break;
            case 1: serial(1,r,c+1); arr[r][c+1]->num=0; break;
            case 2: serial(2,r,c+1); arr[r][c+1]->num=0; break;
            case 3: serial(3,r,c+1); arr[r][c+1]->num=0; break;
            }

            switch (count[1]) {
            case 0: arr[r][c-1]->num=0; break;
            case 1: serial(1,r,c-1); arr[r][c-1]->num=0; break;
            case 2: serial(2,r,c-1); arr[r][c-1]->num=0; break;
            case 3: serial(3,r,c-1); arr[r][c-1]->num=0; break;
            }

            switch (count[2]) {
            case 0: break;
            case 1: serial(1,r,c); arr[r][c]->num=0; break;
            case 2: serial(2,r,c); arr[r][c]->num=0; break;
            case 3: serial(3,r,c); arr[r][c]->num=0; break;
            }

            switch (count[3]) {
            case 0: arr[r-1][c]->num=0; break;
            case 1: serial(1,r-1,c); arr[r-1][c]->num=0; break;
            case 2: serial(2,r-1,c); arr[r-1][c]->num=0; break;
            case 3: serial(3,r-1,c); arr[r-1][c]->num=0; break;
            }

            switch (count[4]) {
            case 0: arr[r-2][c]->num=0; break;
            case 1: serial(1,r-2,c); arr[r-2][c]->num=0; break;
            case 2: serial(2,r-2,c); arr[r-2][c]->num=0; break;
            case 3: serial(3,r-2,c); arr[r-2][c]->num=0; break;
            }
            arr[r][c]->num=0;
            arr[r-2][c]->num=0;
            arr[r-1][c]->num=0;
            arr[r][c+1]->num=0;
            arr[r][c-1]->num=0;
            return true;
     } /*c+1 c-1 r-1 r-2 */

    else if((type/10!=0)&&(r<=7)&&(c>=1)&&(c<=8)&&((type/10==arr[r][c-1]->num)||(type/10==arr[r][c-1]->num/10))&&((type/10==arr[r][c+1]->num)||(type/10==arr[r][c+1]->num/10))&&((type/10==arr[r+1][c]->num)||(type/10==arr[r+1][c]->num/10))&&((type/10==arr[r+2][c]->num)||(type/10==arr[r+2][c]->num/10))){
            Countscore=Countscore+80;
            if(arr[r][c+1]->num>10)
                count[0]=arr[r][c+1]->num%10;
            if(arr[r][c-1]->num>10)
                count[1]=arr[r][c-1]->num%10;
            count[2]=arr[r][c]->num%10;
            if(arr[r+1][c]->num>10)
                count[3]=arr[r+1][c]->num%10;
            if(arr[r+2][c]->num>10)
                count[4]=arr[r+2][c]->num%10;

            switch (count[0]) {
            case 0: arr[r][c+1]->num=0;break;
            case 1: serial(1,r,c+1); arr[r][c+1]->num=0; break;
            case 2: serial(2,r,c+1); arr[r][c+1]->num=0; break;
            case 3: serial(3,r,c+1); arr[r][c+1]->num=0; break;
            }

            switch (count[1]) {
            case 0: arr[r][c-1]->num=0;break;
            case 1: serial(1,r,c-1); arr[r][c-1]->num=0; break;
            case 2: serial(2,r,c-1); arr[r][c-1]->num=0; break;
            case 3: serial(3,r,c-1); arr[r][c-1]->num=0; break;
            }

            switch (count[2]) {
            case 0: break;
            case 1: serial(1,r,c); arr[r][c]->num=0; break;
            case 2: serial(2,r,c); arr[r][c]->num=0; break;
            case 3: serial(3,r,c); arr[r][c]->num=0; break;
            }

            switch (count[3]) {
            case 0: arr[r+1][c]->num=0;break;
            case 1: serial(1,r+1,c); arr[r+1][c]->num=0; break;
            case 2: serial(2,r+1,c); arr[r+1][c]->num=0; break;
            case 3: serial(3,r+1,c); arr[r+1][c]->num=0; break;
            }

            switch (count[4]) {
            case 0: arr[r+2][c]->num=0;break;
            case 1: serial(1,r+2,c); arr[r+2][c]->num=0; break;
            case 2: serial(2,r+2,c); arr[r+2][c]->num=0; break;
            case 3: serial(3,r+2,c); arr[r+2][c]->num=0; break;
            }
            arr[r][c]->num=0;
            arr[r+2][c]->num=0;
            arr[r+1][c]->num=0;
            arr[r][c+1]->num=0;
            arr[r][c-1]->num=0;
            return true;
     } /*c+1 c-1 r+1 r+2 */

    else if((type/10!=0)&&(r>=1)&&(c<=7)&&(r<=8)&&((type/10==arr[r][c+1]->num)||(type/10==arr[r][c+1]->num/10))&&((type/10==arr[r][c+2]->num)||(type/10==arr[r][c+2]->num/10))&&((type/10==arr[r+1][c]->num)||(type/10==arr[r+1][c]->num/10))&&((type/10==arr[r-1][c]->num)||(type/10==arr[r-1][c]->num/10))){
            Countscore=Countscore+80;
            if(arr[r][c+1]->num>10)
                count[0]=arr[r][c+1]->num%10;
            if(arr[r][c+2]->num>10)
                count[1]=arr[r][c+2]->num%10;
            count[2]=arr[r][c]->num%10;
            if(arr[r-1][c]->num>10)
                count[3]=arr[r-1][c]->num%10;
            if(arr[r+1][c]->num>10)
                count[4]=arr[r+1][c]->num%10;

            switch (count[0]) {
            case 0: arr[r][c+1]->num=0;break;
            case 1: serial(1,r,c+1); arr[r][c+1]->num=0; break;
            case 2: serial(2,r,c+1); arr[r][c+1]->num=0; break;
            case 3: serial(3,r,c+1); arr[r][c+1]->num=0; break;
            }

            switch (count[1]) {
            case 0: arr[r][c+2]->num=0;break;
            case 1: serial(1,r,c+2); arr[r][c+2]->num=0; break;
            case 2: serial(2,r,c+2); arr[r][c+2]->num=0; break;
            case 3: serial(3,r,c+2); arr[r][c+2]->num=0; break;
            }

            switch (count[2]) {
            case 0: break;
            case 1: serial(1,r,c); arr[r][c]->num=0; break;
            case 2: serial(2,r,c); arr[r][c]->num=0; break;
            case 3: serial(3,r,c); arr[r][c]->num=0; break;
            }

            switch (count[3]) {
            case 0: arr[r-1][c]->num=0;break;
            case 1: serial(1,r-1,c); arr[r-1][c]->num=0; break;
            case 2: serial(2,r-1,c); arr[r-1][c]->num=0; break;
            case 3: serial(3,r-1,c); arr[r-1][c]->num=0; break;
            }

            switch (count[4]) {
            case 0: arr[r+1][c]->num=0;break;
            case 1: serial(1,r+1,c); arr[r+1][c]->num=0; break;
            case 2: serial(2,r+1,c); arr[r+1][c]->num=0; break;
            case 3: serial(3,r+1,c); arr[r+1][c]->num=0; break;
            }
            arr[r][c]->num=0;
            arr[r+1][c]->num=0;
            arr[r-1][c]->num=0;
            arr[r][c+1]->num=0;
            arr[r][c+2]->num=0;
            return true;
     } /*c+1 c+2 r-1 r+1 */

    else if((type/10!=0)&&(r>=1)&&(c>=2)&&(r<=8)&&((type/10==arr[r][c-1]->num)||(type/10==arr[r][c-1]->num/10))&&((type/10==arr[r][c-2]->num)||(type/10==arr[r][c-2]->num/10))&&((type/10==arr[r+1][c]->num)||(type/10==arr[r+1][c]->num/10))&&((type/10==arr[r-1][c]->num)||(type/10==arr[r-1][c]->num/10))){
            Countscore=Countscore+80;
            if(arr[r][c-1]->num>10)
                count[0]=arr[r][c-1]->num%10;
            if(arr[r][c-2]->num>10)
                count[1]=arr[r][c-2]->num%10;
            count[2]=arr[r][c]->num%10;
            if(arr[r-1][c]->num>10)
                count[3]=arr[r-1][c]->num%10;
            if(arr[r+1][c]->num>10)
                count[4]=arr[r+1][c]->num%10;

            switch (count[0]) {
            case 0: arr[r][c-1]->num=0;break;
            case 1: serial(1,r,c-1); arr[r][c-1]->num=0; break;
            case 2: serial(2,r,c-1); arr[r][c-1]->num=0; break;
            case 3: serial(3,r,c-1); arr[r][c-1]->num=0; break;
            }

            switch (count[1]) {
            case 0: arr[r][c-2]->num=0;break;
            case 1: serial(1,r,c-2); arr[r][c-2]->num=0; break;
            case 2: serial(2,r,c-2); arr[r][c-2]->num=0; break;
            case 3: serial(3,r,c-2); arr[r][c-2]->num=0; break;
            }

            switch (count[2]) {
            case 0: break;
            case 1: serial(1,r,c); arr[r][c]->num=0; break;
            case 2: serial(2,r,c); arr[r][c]->num=0; break;
            case 3: serial(3,r,c); arr[r][c]->num=0; break;
            }

            switch (count[3]) {
            case 0: arr[r-1][c]->num=0;break;
            case 1: serial(1,r-1,c); arr[r-1][c]->num=0; break;
            case 2: serial(2,r-1,c); arr[r-1][c]->num=0; break;
            case 3: serial(3,r-1,c); arr[r-1][c]->num=0; break;
            }

            switch (count[4]) {
            case 0: arr[r+1][c]->num=0; break;
            case 1: serial(1,r+1,c); arr[r+1][c]->num=0; break;
            case 2: serial(2,r+1,c); arr[r+1][c]->num=0; break;
            case 3: serial(3,r+1,c); arr[r+1][c]->num=0; break;
            }
            arr[r+1][c]->num=0;
            arr[r-1][c]->num=0;
            arr[r][c-1]->num=0;
            arr[r][c-2]->num=0;
            return true;
     } /*c-1 c-2 r-1 r+1 */
        /*T型*/
    /*進入的不是普通糖果的狀況*/
    return false;
}

bool MainWindow::threeR(int r, int c){
    qDebug() << "In checkthreeR";
    int type=arr[r][c]->num; /*按鍵的糖果代表的數字*/
    int count[3]={0};
    if((type/10==0)&&(c<=7)&&((type==arr[r][c+1]->num)||(type==arr[r][c+1]->num/10))&&((type==arr[r][c+2]->num)||(type==arr[r][c+2]->num/10))){
        arr[r][c]->num=0;
        Countscore=Countscore+50;
        count[0]=arr[r][c]->num;
        if(arr[r][c+1]->num>10)
            count[1]=arr[r][c+1]->num%10;
        if(arr[r][c+2]->num>10)
            count[2]=arr[r][c+2]->num%10;
        for(int i=0; i<3; i++){
            switch(count[i]){
              case 0: arr[r][c+i]->num=0;break;
              case 1: serial(1,r,c+i); arr[r][c+i]->num=0; break;
              case 2: serial(2,r,c+i); arr[r][c+i]->num=0; break;
              case 3: serial(3,r,c+i); arr[r][c+i]->num=0; break;
            }
        } /*連環引爆*/
        arr[r][c+1]->num=0;
        arr[r][c+2]->num=0;
        return true;
    }  /*c c+1 c+2*/

    else if((type/10==0)&&(c>=1)&&(c<=8)&&((type==arr[r][c+1]->num)||(type==arr[r][c+1]->num/10))&&((type==arr[r][c-1]->num)||(type==arr[r][c-1]->num/10))){
        arr[r][c]->num=0;
        Countscore=Countscore+50;
        if(arr[r][c+1]->num>10)
            count[2]=arr[r][c+1]->num%10;
        count[1]=arr[r][c]->num;
        if(arr[r][c-1]->num>10)
            count[0]=arr[r][c-1]->num%10;
        for(int i=0; i<3; i++){
           switch(count[i]){
              case 0: arr[r][c-1+i]->num=0;break;
              case 1: serial(1,r,c-1+i); arr[r][c-1+i]->num=0; break;
              case 2: serial(2,r,c-1+i); arr[r][c-1+i]->num=0; break;
              case 3: serial(3,r,c-1+i); arr[r][c-1+i]->num=0; break;
           }
        } /*連環引爆*/
        arr[r][c+1]->num=0;
        arr[r][c-1]->num=0;
        return true;
    }  /*c-1 c c+1*/

    else if((type/10==0)&&(c>=2)&&((type==arr[r][c-2]->num)||(type==arr[r][c-2]->num/10))&&((type==arr[r][c-1]->num)||(type==arr[r][c-1]->num/10))){
        arr[r][c]->num=0;
        Countscore=Countscore+50;
        if(arr[r][c-2]->num>10)
            count[0]=arr[r][c-2]->num%10;
        if(arr[r][c-1]->num>10)
            count[1]=arr[r][c-1]->num%10;
        count[2]=arr[r][c]->num;
        for(int i=0; i<3; i++){
           switch(count[i]){
              case 0: arr[r][c-2+i]->num=0;break;
              case 1: serial(1,r,c-2+i); arr[r][c-2+i]->num=0; break;
              case 2: serial(2,r,c-2+i); arr[r][c-2+i]->num=0; break;
              case 3: serial(3,r,c-2+i); arr[r][c-2+i]->num=0; break;
           }
        } /*連環引爆*/
        arr[r][c-2]->num=0;
        arr[r][c-1]->num=0;
        return true;
    }  /*c-2 c-1 c*/

    else if((type/10!=0)&&(c<=7)&&((type/10==arr[r][c+1]->num)||(type/10==arr[r][c+1]->num/10))&&((type/10==arr[r][c+2]->num)||(type/10==arr[r][c+2]->num/10))){
            Countscore=Countscore+50;
            count[0]=arr[r][c]->num%10;
            if(arr[r][c+1]->num>10)
                count[1]=arr[r][c+1]->num%10;
            if(arr[r][c+2]->num>10)
                count[2]=arr[r][c+2]->num%10;
            for(int i=0; i<3; i++){
                switch(count[i]){
                  case 0: arr[r][c+i]->num=0;break;
                  case 1: serial(1,r,c+i); arr[r][c+i]->num=0; break;
                  case 2: serial(2,r,c+i); arr[r][c+i]->num=0; break;
                  case 3: serial(3,r,c+i); arr[r][c+i]->num=0; break;
                }
            } /*連環引爆*/
            arr[r][c+1]->num=0;
            arr[r][c+2]->num=0;
            return true;
     }  /*c c+1 c+2*/

     else if((type/10!=0)&&(c>=1)&&(c<=8)&&((type/10==arr[r][c+1]->num)||(type/10==arr[r][c+1]->num/10))&&((type/10==arr[r][c-1]->num)||(type/10==arr[r][c-1]->num/10))){
            Countscore=Countscore+50;
            if(arr[r][c+1]->num>10)
                count[2]=arr[r][c+1]->num%10;
            count[1]=arr[r][c]->num%10;
            if(arr[r][c-1]->num>10)
                count[0]=arr[r][c-1]->num%10;
            for(int i=0; i<3; i++){
               switch(count[i]){
                  case 0: arr[r][c-1+i]->num=0;break;
                  case 1: serial(1,r,c-1+i); arr[r][c-1+i]->num=0; break;
                  case 2: serial(2,r,c-1+i); arr[r][c-1+i]->num=0; break;
                  case 3: serial(3,r,c-1+i); arr[r][c-1+i]->num=0; break;
               }
            } /*連環引爆*/
            arr[r][c+1]->num=0;
            arr[r][c-1]->num=0;
            return true;
        }  /*c-1 c c+1*/

     else if((type/10!=0)&&(c>=2)&&((type/10==arr[r][c-2]->num)||(type/10==arr[r][c-2]->num/10))&&((type/10==arr[r][c-1]->num)||(type/10==arr[r][c-1]->num/10))){
            Countscore=Countscore+50;
            if(arr[r][c-2]->num>10)
                count[0]=arr[r][c-2]->num%10;
            if(arr[r][c-1]->num>10)
                count[1]=arr[r][c-1]->num%10;
            count[2]=arr[r][c]->num%10;
            for(int i=0; i<3; i++){
               switch(count[i]){
                  case 0: arr[r][c-2+i]->num=0;break;
                  case 1: serial(1,r,c-2+i); arr[r][c-2+i]->num=0; break;
                  case 2: serial(2,r,c-2+i); arr[r][c-2+i]->num=0; break;
                  case 3: serial(3,r,c-2+i); arr[r][c-2+i]->num=0; break;
               }
            } /*連環引爆*/
            arr[r][c-1]->num=0;
            arr[r][c-2]->num=0;
            return true;
        }  /*c-2 c-1 c*/


    return false;
}

bool MainWindow::threeC(int r, int c){
    qDebug() << "In checkthreeC";
    int type=arr[r][c]->num; /*按鍵的糖果代表的數字*/
    int count[3]={0};
    if((type/10==0)&&(r<=7)&&((type==arr[r+1][c]->num)||(type==arr[r+1][c]->num/10))&&((type==arr[r+2][c]->num)||(type==arr[r+2][c]->num/10))){
        arr[r][c]->num=0;
        Countscore=Countscore+50;
        count[0]=arr[r][c]->num;
        if(arr[r+1][c]->num>10)
            count[1]=arr[r+1][c]->num%10;
        if(arr[r+2][c]->num>10)
            count[2]=arr[r+2][c]->num%10;
        for(int i=0; i<3; i++){
           switch(count[i]){
              case 0: arr[r+i][c]->num=0;break;
              case 1: serial(1,r+i,c); arr[r+i][c]->num=0; break;
              case 2: serial(2,r+i,c); arr[r+i][c]->num=0; break;
              case 3: serial(3,r+i,c); arr[r+i][c]->num=0; break;
           }
        } /*連環引爆*/
        arr[r+1][c]->num=0;
        arr[r+2][c]->num=0;
        return true;
    }  /*r r+1 r+2*/

    else if((type/10==0)&&(r>=1)&&(r<=8)&&((type==arr[r+1][c]->num)||(type==arr[r+1][c]->num/10))&&((type==arr[r-1][c]->num)||(type==arr[r-1][c]->num/10))){
        arr[r][c]->num=0;
        Countscore=Countscore+50;
        if(arr[r+1][c]->num>10)
            count[2]=arr[r+1][c]->num%10;
        if(arr[r-1][c]->num>10)
            count[0]=arr[r-1][c]->num%10;
        count[1]=arr[r][c]->num;
        for(int i=0; i<3; i++){
           switch(count[i]){
              case 0: arr[r-1+i][c]->num=0;break;
              case 1: serial(1,r-1+i,c); arr[r-1+i][c]->num=0; break;
              case 2: serial(2,r-1+i,c); arr[r-1+i][c]->num=0; break;
              case 3: serial(3,r-1+i,c); arr[r-1+i][c]->num=0; break;
           }
        } /*連環引爆*/
        arr[r-1][c]->num=0;
        arr[r+1][c]->num=0;
        return true;
    }  /*r-1 r r+1*/

    else if((type/10==0)&&(r>=2)&&((type==arr[r-2][c]->num)||(type==arr[r-2][c]->num/10))&&((type==arr[r-1][c]->num)||(type==arr[r-1][c]->num/10))){
        arr[r][c]->num=0;
        Countscore=Countscore+50;
        if(arr[r-2][c]->num>10)
            count[0]=arr[r-2][c]->num%10;
        if(arr[r-1][c]->num>10)
            count[1]=arr[r-1][c]->num%10;
        for(int i=0; i<3; i++){
           switch(count[i]){
              case 0: break;
              case 1: serial(1,r-2+i,c); arr[r-2+i][c]->num=0; break;
              case 2: serial(2,r-2+i,c); arr[r-2+i][c]->num=0; break;
              case 3: serial(3,r-2+i,c); arr[r-2+i][c]->num=0; break;
           }
        }
        arr[r-1][c]->num=0;
        arr[r-2][c]->num=0;
        return true;
    }  /*r-2 r-1 r*/

    if((type/10!=0)&&(r<=7)&&((type/10==arr[r+1][c]->num)||(type/10==arr[r+1][c]->num/10))&&((type/10==arr[r+2][c]->num)||(type/10==arr[r+2][c]->num/10))){
            Countscore=Countscore+50;
            count[0]=arr[r][c]->num%10;
            if(arr[r+1][c]->num>10)
                count[1]=arr[r+1][c]->num%10;
            if(arr[r+2][c]->num>10)
                count[2]=arr[r+2][c]->num%10;
            for(int i=0; i<3; i++){
               switch(count[i]){
                  case 0: arr[r+i][c]->num=0;break;
                  case 1: serial(1,r+i,c); arr[r+i][c]->num=0; break;
                  case 2: serial(2,r+i,c); arr[r+i][c]->num=0; break;
                  case 3: serial(3,r+i,c); arr[r+i][c]->num=0; break;
               }
            } /*連環引爆*/
            arr[r+2][c]->num=0;
            arr[r+1][c]->num=0;
            return true;
    }  /*r r+1 r+2*/

    else if((type/10!=0)&&(r>=1)&&(r<=8)&&((type/10==arr[r+1][c]->num)||(type/10==arr[r+1][c]->num/10))&&((type/10==arr[r-1][c]->num)||(type/10==arr[r-1][c]->num/10))){
            Countscore=Countscore+50;
            if(arr[r+1][c]->num>10)
                count[2]=arr[r+1][c]->num%10;
            if(arr[r-1][c]->num>10)
                count[0]=arr[r-1][c]->num%10;
            count[1]=arr[r][c]->num%10;
            for(int i=0; i<3; i++){
               switch(count[i]){
                  case 0: arr[r-1+i][c]->num=0;break;
                  case 1: serial(1,r-1+i,c); arr[r-1+i][c]->num=0; break;
                  case 2: serial(2,r-1+i,c); arr[r-1+i][c]->num=0; break;
                  case 3: serial(3,r-1+i,c); arr[r-1+i][c]->num=0; break;
               }
            } /*連環引爆*/
            arr[r-1][c]->num=0;
            arr[r+1][c]->num=0;
            return true;
     }  /*r-1 r r+1*/


    else if((type/10!=0)&&(r>=2)&&((type/10==arr[r-2][c]->num)||(type/10==arr[r-2][c]->num/10))&&((type/10==arr[r-1][c]->num)||(type/10==arr[r-1][c]->num/10))){
            Countscore=Countscore+50;
            count[2]=arr[r][c]->num%10;
            if(arr[r-2][c]->num>10)
                count[0]=arr[r-2][c]->num%10;
            if(arr[r-1][c]->num>10)
                count[1]=arr[r-1][c]->num%10;
            for(int i=0; i<3; i++){
               switch(count[i]){
                  case 0: break;
                  case 1: serial(1,r-2+i,c); arr[r-2+i][c]->num=0; break;
                  case 2: serial(2,r-2+i,c); arr[r-2+i][c]->num=0; break;
                  case 3: serial(3,r-2+i,c); arr[r-2+i][c]->num=0; break;
               }
            }
            arr[r-1][c]->num=0;
            arr[r-2][c]->num=0;
            return true;
     }  /*r-2 r-1 r*/

    return false;
}

void MainWindow::serial(int bombtype, int rr, int cc){
    switch (bombtype) {
    case 1:
        for(int i=0; i<10; i++){
            arr[rr][i]=0;
        }
        Countscore=Countscore+20;
        break; /*連續引爆水平消除*/
    case 2:
        for(int i=0; i<10; i++){
            arr[i][cc]=0;
        }
        Countscore=Countscore+20;
        break; /*連續引爆垂直消除*/
    case 3:
        if(rr>=1&&cc>=1) arr[rr-1][cc-1]->num=0;
        if(rr>=1) arr[rr-1][cc]->num=0;
        if(rr>=1&&cc<=8) arr[rr-1][cc+1]->num=0;
        if(cc>=1) arr[rr][cc-1]->num=0;
        if(cc<=8) arr[rr][cc+1]->num=0;
        if(rr>=1&&cc>=1) arr[rr-1][cc-1]->num=0;
        if(rr<=8) arr[rr+1][cc]->num=0;
        if(rr<=8&&cc<=8) arr[rr+1][cc+1]->num=0;
        arr[rr][cc]=0;
        Countscore=Countscore+30;
        break; /*連續引爆炸彈*/
    }
} /*處理連帶消掉的炸彈*/

void MainWindow::button_click(int R, int C){
    qDebug() << arr[R][C]->num;
     if(clicked==false){
         setclickpic(arr[R][C]);
         clicked=true;
         recordR=R;
         recordC=C;
     } /*紀錄位置，如果兩次案的位置不相鄰就不會有動作*/
     else{
         if(recordR==R&&C-1==recordC){
             *arr[recordR][recordC]-arr[R][C];
             if(check(recordR,recordC,R,C)){
                 down();
                 fillzero();
             }
             else if(!check(recordR,recordC,R,C)){
                 setclickpic(arr[recordR][recordC]);
             }

         }//左
         else if(recordR==R&&C+1==recordC){
             *arr[R][C]-arr[recordR][recordC];
             if(check(recordR,recordC,R,C)){
                 down();
                 fillzero();
             }
             else if(!check(recordR,recordC,R,C)){
                 setclickpic(arr[recordR][recordC]);
             }
         }//右
         else if(recordR==R-1&&C==recordC){
             *arr[recordR][recordC]|arr[R][C];
             if(check(recordR,recordC,R,C)){
                 down();
                 fillzero();
             }
             if(!check(recordR,recordC,R,C)){
                 setclickpic(arr[recordR][recordC]);
             }
         }//上
         else if(recordR==R+1&&C==recordC){
             *arr[R][C]|arr[recordR][recordC];
             if(check(recordR,recordC,R,C)){
                 down();
                 fillzero();
             }
             if(!check(recordR,recordC,R,C)){
                 setclickpic(arr[recordR][recordC]);
             }
         }//下
         else{
             setclickpic(arr[recordR][recordC]);
         }
         clicked=false;
     }
}

void MainWindow::Time(){
    --counttime;
}

void MainWindow::newpic(){
     for(int i=0; i<10; i++){
         for(int k=0; k<10; k++){
             arr[i][k]->setButtonPic();
         }
     }
}

void MainWindow::down(){
    qDebug() << "In down";
    for (int i=9; i>=0; i--) {
        for (int k=9; k>=0; k--){
           if (arr[i][k]->num==0){
              for (int j=i; j>=0; j--){
                  if(arr[j][k]->num!=0){
                      arr[i][k]->num=arr[j][k]->num;
                      arr[j][k]->num=0;
                      break;
                  }
               }
            }
         }
    }
} /*把零都移到下面*/

bool MainWindow::possible(){
    qDebug() << "In possible";
    bool pass=false;
    for(int i=0; i<10; i++){
        for(int k=0; k<10; k++){
            pass=star(i,k);
            if(pass){
                return pass;
            }
        }
    }
    for(int i=0; i<10; i++){
        for(int k=0; k<10; k++){
            pass=block(i,k);
            if(pass){
                return pass;
            }
        }
    }

    for(int i=0; i<10; i++){
        for(int k=0; k<10; k++){
            pass=hor(i,k);
            if(pass){
                return pass;
            }
        }
    }

    for(int i=0; i<10; i++){
        for(int k=0; k<10; k++){
            pass=ver(i,k);
            if(pass){
                return pass;
            }
        }
    }

    for(int i=0; i<10; i++){
        for(int k=0; k<10; k++){
            pass=threeR(i,k);
            if(pass){
                return pass;
            }
        }
    }

    for(int i=0; i<10; i++){
        for(int k=0; k<10; k++){
            pass=threeC(i,k);
            if(pass){
                return pass;
            }
        }
    }
    return pass;
}

void MainWindow::fillzero(){
    qDebug() << "In fillzero";
    bool possibility;
    do{
        down();
        possibility=possible();
    } while(possibility==true);

    for(int i=0; i<10; i++){
       qDebug() << "In bornnum";
       str=QString::number(Countscore,10);
       ui->score->setText(str);
       for(int k=0; k<10; k++){
          if(arr[i][k]==0){
           arr[i][k]->setnum();/*產生亂數*/
           if((k>=2)&&(arr[i][k]->num==arr[i][k-2]->num)&&(arr[i][k]->num==arr[i][k-1]->num))
              k--;
           if((i>=2)&&(arr[i][k]->num==arr[i-2][k]->num)&&(arr[i][k]->num==arr[i-1][k]->num))
              k--; /*有重複就往回重新產生*/
          }
       }
     } /* 把位於上面的零隨機產生數字補上*/

    newpic();

} /*糖果掉落，設定新圖片*/

MainWindow::~MainWindow(){
    delete ui;
}
