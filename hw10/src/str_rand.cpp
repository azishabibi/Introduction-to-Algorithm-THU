#include<iostream>
#include<ctime>
#include<cstdio>
using namespace std;
char ch[68] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z', 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z',',','.',':','?',':',':','0','1','2','3','4','5','6','7','8','9'};

int main(){
    int n,m;
    cout<<"type the lenth of text and pattern"<<endl;
    cin>>n>>m;
    freopen("input.txt","w",stdout);
    srand((unsigned int)time(NULL));
    char temp;
    for (int i=0;i<n;i++){
        temp=ch[rand()%68];
        cout<<temp;
    }
    cout<<endl;
    //freopen("pattern.txt","w",stdout);
    for (int j=0;j<m;j++){
        temp = ch[rand() % 68];
        cout << temp;
    }
    cout<<endl;
}