/*

��Ŀ��
    f(1) = 1, f(2) = 1, f(n) = (A * f(n - 1) + B * f(n - 2)) mod 7.
    ����A,B��f(n)ģ7

������
    ���ǿ��Թ���һ������
    [ a b ]  *  [ fn-1 ]  =  [ fn   ]
    [ 1 0 ]     [ fn-2 ]     [ fn-1 ]

    �������Ҫ����ߵľ����(n-2)���ݺ����õ���������ĺ�ֵ����
    fn�������õ��˾���Ŀ����ݿ�����~~

*/
#include <iostream>
#include <cstdio>
#include <cstring>

using namespace std;

const int X = 3;

class matrix{
    public:
        int a[X][X];

        matrix(){
            memset(a,0,sizeof(a));
        }

        matrix(int _size,int _mod):size(_size),mod(_mod){
            memset(a,0,sizeof(a));
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

        void setE(){
            for(int i=0;i<size;i++)
                a[i][i] = 1;
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

    private:
        int size;
        int mod;
};

int main(){
    freopen("sum.in","r",stdin);
    int a,b,n;
    while(cin>>a>>b>>n,a||b||n){
        if(n==1){
            cout<<1<<endl;
            continue;
        }
        else if(n==2){
            cout<<1<<endl;
            continue;
        }
        matrix ans(2,7);
        ans.a[0][0] = a;
        ans.a[0][1] = b;
        ans.a[1][0] = 1;
        ans.a[1][1] = 0;

        ans = ans.pow(n-2);

        cout<<(ans.a[0][0]+ans.a[0][1])%7<<endl;
    }
    return 0;
}
