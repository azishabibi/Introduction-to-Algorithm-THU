#include "Point.h"

double dist(Point x1,Point x2){
    double d=sqrt((x1.x-x2.x)*(x1.x-x2.x)+(x1.y-x2.y)*(x1.y-x2.y));
    return d;
}
