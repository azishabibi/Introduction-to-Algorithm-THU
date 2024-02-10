#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#pragma once
#include <QMainWindow>
#include "Point.h"
#include <QPaintEvent>
#include <QMouseEvent>
#include <QtGui>
#include <QVector>
#include <QDebug>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT
private:
    Ui::MainWindow *ui;
    QImage image;
public:
    double choose(Point node[],int low,int high);

    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void Paint();
    void paintEvent(QPaintEvent* );
    void mousePressEvent(QMouseEvent* mouse);
    double choose_smart();
    double choose_brute();

    Point* point;
    int pointnum;
    Point ans1,ans2;

    QVector<double> _x,_y;

public slots:
    double choose_brute_1();
    void clear();
    void Randpoint();
};

double min(double x1, double x2);
void merge(Point sourceArr[], Point tempArr[], int startIndex, int midIndex, int endIndex,bool axis_x);
void mergesort(Point sourceArr[], Point tempArr[], int startIndex, int endIndex,bool axis_x);
#endif // MAINWINDOW_H
