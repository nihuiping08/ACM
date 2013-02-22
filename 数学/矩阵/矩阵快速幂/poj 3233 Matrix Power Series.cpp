/*

题目:
    求出 S = A + A^2 + A^3 + … + A^k.

分析：
    解法一
    Let B=   A I
             0 I

    B^(k+1) =    A^k   I+A+...+A^k
                 0          I

    解法二
    设f[n]=A^1+A^2+....A^n;
    当n是偶数,f[n]=f[n/2]+f[n/2]*A^(n/2);
    但n是奇数,f[n]=f[n-1]+A^(n);

*/
#include <iostream>
#include <cstdio>
#include <cstring>

using namespace std;

const int X = 31<<2;

int n,m,k;

class matrix{
    public:
        int size;
        int mod;
        int a[X][X];

        matrix(){
            memset(a,0,sizeof(a));
        }

        matrix(int _size,int _mod):size(_size),mod(_mod){
            memset(a,0,sizeof(a));
        }

        void setE(){
            for(int i=0;i<2*size;i++)
                a[i][i] = 1;
        }

        void print(){
            for(int i=0;i<size;i++){
                printf("%d",a[i][size]);
                for(int j=1;j<size;j++)
                    printf(" %d",a[i][j+size]);
                puts("");
            }
        }

        matrix operator * (matrix p){
            matrix c(size,mod);
            for(int i=0;i<2*size;i++)
                for(int j=0;j<2*size;j++)
                    for(int k=0;k<2*size;k++){
                        c.a[i][j] += a[i][k]*p.a[k][j];
                        c.a[i][j] %= mod;
                    }
            return c;
        }

        void operator -- (){
            for(int i=0;i<size;i++)
                a[i][i+size] = (--a[i][i+size]+mod)%mod;
        }

        matrix pow(int exp){
            matrix temp(size,mod);
            temp.setE();
            matrix cur = *this;
            while(exp){
                if(exp&1)
                    temp = temp*cur;
                cur = cur*cur;
                exp = exp>>1;
            }
            return temp;
        }

        void display(){
            for(int i=0;i<2*size;i++){
                for(int j=0;j<2*size;j++)
                    cout<<a[i][j]<<" ";
                cout<<endl;
            }
        }
};

int main(){
    freopen("sum.in","r",stdin);
    while(cin>>n>>k>>m){
        matrix ans(n,m);
        for(int i=0;i<n;i++)
            for(int j=0;j<n;j++)
                scanf("%d",&ans.a[i][j]);
        for(int i=n;i<2*n;i++)
            ans.a[i-n][i] = ans.a[i][i] = 1;

        ans = ans.pow(k+1);
        --ans;
        ans.print();
    }
    return 0;
}
