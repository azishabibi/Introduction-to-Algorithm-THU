#include <iostream>
#include <windows.h>
#include <cmath>
#include <ctime>
using namespace std;
const long long inf = 1e9 + 7;
LARGE_INTEGER nFreq;
LARGE_INTEGER t1;
LARGE_INTEGER t2;
class mat{
    private:
        long long num[2][2];
    public:
        mat(){};
        void init(){
            num[0][0] = num[1][0] = num[0][1]=1;
            num[1][1]=0;
        }
        void init_(){
            num[0][0] = 1;
            num[1][0] = num[0][1] = 0;
            num[1][1] = 1;
        }
        long long ans(){
            return num[1][0];
        }
        friend mat operator*(const mat&A,const mat&B){
            mat C;
            C.num[0][0] = (A.num[0][0] * B.num[0][0] + A.num[0][1] * B.num[1][0])%inf;
            C.num[0][1] = (A.num[0][0] * B.num[0][1] + A.num[0][1] * B.num[1][1]) % inf;
            C.num[1][0] = (A.num[1][0] * B.num[0][0] + A.num[1][1] * B.num[1][0]) % inf;
            C.num[1][1] = (A.num[1][0] * B.num[0][1] + A.num[1][1] * B.num[1][1]) % inf;
            return C;
        }
};
long long pow(mat &A,unsigned long long int n){
    mat C;
    C.init();
    while(n>0){
        if(n%2==1){
            A=A*C;
        }
        C=C*C;
        n>>=1;
    }
    return A.ans();
}
int main(){
    unsigned long long int n;
    cin>>n;
    //n=1.6*1e19;
    mat ori;
    ori.init_();
    double dt;
    QueryPerformanceFrequency(&nFreq);
    QueryPerformanceCounter(&t1);
    long long answer=pow(ori,n);
    QueryPerformanceCounter(&t2);
    dt = (t2.QuadPart - t1.QuadPart) / (double)nFreq.QuadPart;
    cout << "matrix:" << answer << endl;
    cout << "Running time :" << dt * 1000000 << "μs" << endl;
    system("pause");
    return 0;
}