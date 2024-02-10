#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "Point.h"
#include <QString>
#include <ctime>
#include <iostream>
#include <cmath>
#include <string>
using namespace std;

double min(double a,double b){
    if(a<b) return a;
    else return b;
}

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    point=new Point[1000100];
    pointnum=0;

    image=QImage(1000,1000,QImage::Format_RGB32);
    QColor blank=qRgb(255,255,255);
    image.fill(blank);
    Paint();

    connect(ui->Clear,SIGNAL(clicked()),this,SLOT(clear()));
    connect(ui->Clear,SIGNAL(clicked()),this,SLOT(hideWord()));
    connect(ui->Run,SIGNAL(clicked()),this,SLOT(hideWord()));
    connect(ui->Run,SIGNAL(clicked()),this,SLOT(Randpoint()));
    connect(ui->RunMouse,SIGNAL(clicked()),this,SLOT(choose_brute_1()));
    connect(ui->RunMouse,SIGNAL(clicked()),this,SLOT(hideWord()));

}

MainWindow::~MainWindow()
{
    delete[] point;
    delete ui;
}
void MainWindow::clear(){
    _x.clear();
    _y.clear();
    ans1={0,0};
    ans2={100000,100000};
    pointnum=0;
    delete[] point;
    point=new Point[1000100];
    repaint();
}

void MainWindow::Paint(){
    QPainter painter(&image);
    painter.setRenderHint(QPainter::Antialiasing, true);

    painter.drawRect(0,0,1000,1000);
    painter.drawLine(0,990,1000,990);
    painter.drawLine(10,0,10,1000);
    return;
}
void MainWindow::paintEvent(QPaintEvent*){
    QPainter painter(this);
    QPen pen;
    QPen pen_2;
    QPen pen_3;
    Point near_point={0,0};

    pen.setColor(Qt::red);
    pen.setWidth(3);
    painter.setPen(pen);
    pen_2.setColor(Qt::darkGreen);
    pen_2.setWidth(3);
    pen_3.setColor(Qt::black);
    pen_3.setWidth(3);
    painter.drawImage(10,10,image);

    for(int i=0;i<pointnum;i++){
        if((_x[i]==ans1.x&&_y[i]==ans1.y)||(_x[i]==ans2.x&&_y[i]==ans2.y)){
            if(near_point.x==0) near_point.x=_x[i],near_point.y=_y[i];
            else{
                painter.setPen(pen_3);
                painter.drawLine(near_point.x+1,near_point.y+1,_x[i]+1,_y[i]+1);
                painter.setPen(pen_2);//最近点显示
                painter.drawPoint(_x[i]+1,_y[i]+1);
                painter.drawPoint(near_point.x+1,near_point.y+1);
            }
            painter.setPen(pen);
            continue;
        }
        painter.drawPoint(_x[i]+1,_y[i]+1);
    }
    return;
}

void MainWindow::mousePressEvent(QMouseEvent *mouse){
    if(mouse->pos().x()<=1000&&mouse->pos().y()<=1000){
        _y.push_back(mouse->pos().y());
        _x.push_back(mouse->pos().x());
        point[pointnum].y=mouse->pos().y();
        point[pointnum].x=mouse->pos().x();
        pointnum++;
        repaint();
        return;
    }
}
void merge(Point sourceArr[], Point tempArr[], int startIndex, int midIndex, int endIndex,bool axis_x){

    int i = startIndex, j=midIndex+1, k = startIndex;
    if (axis_x==true){//true按照x排序
    while(i!=midIndex+1 && j!=endIndex+1) {
        if(sourceArr[i].x > sourceArr[j].x)
            tempArr[k++] = sourceArr[j++];
        else
            tempArr[k++] = sourceArr[i++];
    }
    while(i != midIndex+1)
        tempArr[k++] = sourceArr[i++];
    while(j != endIndex+1)
        tempArr[k++] = sourceArr[j++];
    for(i=startIndex; i<=endIndex; i++)
        sourceArr[i] = tempArr[i];}
    else {//false 按照y排序
        while(i!=midIndex+1 && j!=endIndex+1) {
            if(sourceArr[i].y > sourceArr[j].y)
                tempArr[k++] = sourceArr[j++];
            else
                tempArr[k++] = sourceArr[i++];
        }
        while(i != midIndex+1)
            tempArr[k++] = sourceArr[i++];
        while(j != endIndex+1)
            tempArr[k++] = sourceArr[j++];
        for(i=startIndex; i<=endIndex; i++)
            sourceArr[i] = tempArr[i];
    }

}
void mergesort(Point sourceArr[], Point tempArr[], int startIndex, int endIndex,bool axis_x){
    int midIndex;
        if(startIndex < endIndex) {
            midIndex = startIndex + (endIndex-startIndex) / 2;
            mergesort(sourceArr, tempArr, startIndex, midIndex,axis_x);
            mergesort(sourceArr, tempArr, midIndex+1, endIndex,axis_x);
            merge(sourceArr, tempArr, startIndex, midIndex, endIndex,axis_x);
        }

}
void MainWindow::Randpoint(){

    QString s=ui->Sizein->text();
    int inNum=s.toInt();
    if (inNum<2)inNum+=2;
    srand(time(NULL));
    clear();

    clock_t start,end;
    Point inNode;
    QString p="";

    for(int i=0;i<inNum;i++){
        inNode.x=double((rand()<<16|rand())%10000000)/100.0;
        inNode.y=double((rand()<<16|rand())%10000000)/100.0;
        point[pointnum++]=inNode;
    }
    for(int i=0;i<inNum;i++){
        _y.push_back(point[i].y/100);
        _x.push_back(point[i].x/100);

    }
    repaint();
    double minDistance;

    start=clock();
    minDistance=choose_smart();
    end=clock();
    p+="Runtime of O(nlogn) is "+QString::number(end-start)+"ms. \nMin distance is "+QString::number(minDistance)+".\n Locations: ("+
            QString::number(ans1.x)+","+QString::number(ans1.y)+"),("+QString::number(ans2.x)+","+QString::number(ans2.y)+").\n";
    if(inNum<=10000){
        start=clock();
        minDistance=choose_brute();
        end=clock();

        p+="Runtime of O(n^2) is "+QString::number(end-start)+"ms. \n Min distance is "+QString::number(minDistance)+".\n Locations: ("+
                QString::number(ans1.x)+","+QString::number(ans1.y)+"),("+QString::number(ans2.x)+","+QString::number(ans2.y)+").\n";
    }
    ui->Out->setText(p);
    ans1.x=ans1.x/100;
    ans2.x=ans2.x/100;
    ans1.y=ans1.y/100;
    ans2.y=ans2.y/100;
    repaint();
    return;
}


double MainWindow::choose(Point node[],int low,int high){
    int l=high-low;
    if(l==2){
        if(dist(node[low+1],node[low])<dist(ans2,ans1)){
            ans2=node[low+1];
            ans1=node[low];
        }
        return dist(node[low+1],node[low]);
    }
    else if(l==3){
        if(dist(node[low+2],node[low])>=dist(node[low+1],node[low])
                &&dist(node[low+2],node[low+1])>=dist(node[low+1],node[low])){
            if(dist(node[low+1],node[low])<dist(ans2,ans1)){
                ans2=node[low+1];ans1=node[low];
            }
            return dist(node[low+1],node[low]);
        }
        else if(dist(node[low+1],node[low])>=dist(node[low+1],node[low+2])
                &&dist(node[low+2],node[low])>=dist(node[low+1],node[low+2])){
            if(dist(node[low+1],node[low+2])<dist(ans2,ans1)){
                ans2=node[low+1];ans1=node[low+2];
            }
            return dist(node[low+1],node[low+2]);
        }
        else{
            if(dist(node[low+2],node[low])<dist(ans2,ans1)){                
                ans2=node[low+2];ans1=node[low];
            }
            return dist(node[low+2],node[low]);
        }
    }

    int mid=(low+high)/2;
    double R=choose(node,mid,high);
    double L=choose(node,low,mid);
    double Min=min(L,R);

    Point* p=new Point[l+6];
    Point* p_=new Point[l+6];
    int size_p=0;
    for(int i=low;i<high;i++)
    {
        if((node[mid].x-node[i].x)<Min&&(node[mid].x-node[i].x)>-Min){
            p[size_p]=node[i];
            size_p++;
        }
    }
    mergesort(p,p_,0,size_p-1,false);

    for(int i=0;i<size_p;i++){
        for(int j=i+1;j<size_p;j++){
            if(p[j].y-p[i].y>=Min)break;
            double t=dist(p[i],p[j]);
            if(p[i].x==p[j].x&&p[i].y==p[j].y) continue;
            if(t<Min){
                Min=t;
                if(dist(ans2,ans1)>Min){
                    ans2=p[j];ans1=p[i];
                }
            }
        }
    }
    delete[] p;
    delete[] p_;
    return Min;
}

double MainWindow::choose_smart(){
    ans1={0,0};
    ans2={100000,100000};
    Point *point_;
    point_ =new Point[1000010];
    mergesort(point,point_,0,pointnum-1,true);
    return choose(point,0,pointnum);
}

double MainWindow::choose_brute(){
    ans1={0,0};
    ans2={100000,100000};
    double Min=2000000;
    for(int i=0;i<pointnum-1;i++){
        for(int j=i+1;j<pointnum;j++){
            if(point[i].y==point[j].y&&point[i].x==point[j].x) continue;
            if(dist(point[j],point[i])<Min){
                Min=dist(point[i],point[j]);
                ans2=point[j];ans1=point[i];
            }
        }
    }
    return Min;
}


double MainWindow::choose_brute_1(){
    double Min=2000000;
    ans1={0,0};
    ans2={100000,100000};
    QString s=ui->Sizein->text();
    for(int i=0;i<pointnum-1;i++){
        for(int j=i+1;j<pointnum;j++){
            if(point[i].y==point[j].y&&point[i].x==point[j].x) continue;
            if(dist(point[i],point[j])<Min){
                Min=dist(point[i],point[j]);
                ans2=point[j];ans1=point[i];
            }
        }
    }
    s="Min distance is "+QString::number(Min)+". \nLocations: ("+
            QString::number(ans1.x)+","+QString::number(ans1.y)+"),("+QString::number(ans2.x)+","+QString::number(ans2.y)+").";
    ui->Out->setText(s);
    repaint();
    return Min;
}


