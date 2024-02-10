#include<iostream>
#include<windows.h>
#include<cmath>
#include<ctime>
using namespace std;
const long long inf = 1e9 + 7;
LARGE_INTEGER nFreq;
LARGE_INTEGER t1;
LARGE_INTEGER t2;
double fib(int n){
    double v1,v2,num1,num2;
    num1=1;num2=1;
    double sqrt_5=sqrt(5);
    v1=(sqrt_5+1)/2;v2=-(sqrt_5-1)/2;
    while(n>0){
        if (n%2==1){
            num1*=v1;num2*=v2;
        }
        v1=v1*v1;v2=v2*v2;
        n>>=1;
    }
    return (num1-num2);
}

int main(){
    int n;
    cin>>n;
    double dt;
    QueryPerformanceFrequency(&nFreq);
    QueryPerformanceCounter(&t1);
    //double t1=clock();
    double f=fib(n);
    long long answer=(long long)(f/sqrt(5)+0.5)%inf;
    QueryPerformanceCounter(&t2);
    dt = (t2.QuadPart - t1.QuadPart) / (double)nFreq.QuadPart;
    cout << "formula:" << answer << endl;
    cout << "Running time :" << dt * 1000000 << "μs" << endl;
    system("pause");
    return 0;
}