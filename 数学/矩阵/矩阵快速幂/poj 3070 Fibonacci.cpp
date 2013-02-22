/*

题目：
    斐波那契数列的矩阵算法

分析：
    裸的矩阵快速幂

*/
#include <iostream>
#include <cstring>
#include <cstdio>

using namespace std;

const int X = 5;
const int mod = 10000;

int n;

class matrix{
    public:
        int a[X][X];
        int size;
        int mod;

        matrix(){
            memset(a,0,sizeof(a));
        }
        matrix(int _size,int _mod):size(_size),mod(_mod){
            memset(a,0,sizeof(a));
        }

        void setE(){
            for(int i=0;i<size;i++)
                a[i][i] = 1;
        }

        matrix operator * (matrix p){
            matrix c(size,mod);
            for(int i=0;i<size;i++)
                for(int j=0;j<size;j++)
                    for(int k=0;k<size;k++){
                        c.a[i][j] += a[i][k]*p.a[k][j];
                        c.a[i][j] %= mod;
                    }
            return c;
        }

        matrix pow(int exp){
            matrix cur = *this;
            matrix c(size,mod);
            c.setE();

            while(exp){
                if(exp&1)
                    c = c*cur;
                cur = cur*cur;
                exp = exp>>1;
            }
            return c;
        }

        void display(){
            for(int i=0;i<size;i++){
                for(int j=0;j<size;j++)
                    cout<<a[i][j]<<" ";
                cout<<endl;
            }
        }
};

int main(){
    freopen("sum.in","r",stdin);
    while(scanf("%d",&n),n!=-1){
        if(!n){
            puts("0");
            continue;
        }
        matrix ans(2,mod);
        ans.a[0][0] = ans.a[0][1] = ans.a[1][0] = 1;
        ans.a[1][1] = 0;

        ans = ans.pow(n-1);

        printf("%d\n",ans.a[0][0]);
    }
    return 0;
}
