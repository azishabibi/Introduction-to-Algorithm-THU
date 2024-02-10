#include <iostream>
#include <windows.h>
#include <cmath>
#include <ctime>
using namespace std;
const long long inf = 1e9 + 7;
LARGE_INTEGER nFreq;
LARGE_INTEGER t1;
LARGE_INTEGER t2;
unsigned long long int fib(int n){
    if (n==1||n==2) return 1;
    else return (fib(n-1)+fib(n-2))%inf;
}
int main(){
    int n;
    cin>>n;
    //double t1=clock();
    QueryPerformanceFrequency(&nFreq);
    QueryPerformanceCounter(&t1);
    unsigned long long int answer=fib(n)%inf;
    double dt;
    //double t2=clock();
    QueryPerformanceCounter(&t2);
    dt = (t2.QuadPart - t1.QuadPart) / (double)nFreq.QuadPart;
    cout << "recursion:" << answer << endl;
    cout << "Running time :" << dt * 1000000 << "μs" << endl;
    system("pause");
    return 0;
}