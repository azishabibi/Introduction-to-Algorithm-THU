#include<iostream>
#include<windows.h>
#include<ctime>
using namespace std;
const long long inf = 1e9 + 7;
LARGE_INTEGER nFreq;
LARGE_INTEGER t1;
LARGE_INTEGER t2;
int main(){
    int n;
    cin>>n;
    unsigned long long int a1=1,a2=1,answer=0;
    //double t1=clock();
    double dt;
    QueryPerformanceFrequency(&nFreq);
    QueryPerformanceCounter(&t1);
    if (n==1||n==2) answer=1;
    for(int i=3;i<=n;i++){
        answer=(a1+a2)%inf;
        a2 = a1;
        a1=answer;
    }
    QueryPerformanceCounter(&t2);
    dt = (t2.QuadPart - t1.QuadPart) / (double)nFreq.QuadPart;
    cout << "iteration:" << answer << endl;
    cout << "Running time :" << dt * 1000000 << "μs" << endl;
    system("pause");
    return 0;
}