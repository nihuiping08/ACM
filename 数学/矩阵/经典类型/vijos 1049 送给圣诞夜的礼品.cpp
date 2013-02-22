/*

题目：
    “列表共有m行，这m行都称作操作（不是序列），每一行有n个数字，这些数字互
    不相同而且每个数字都在1到n之间。一开始，礼品的序列就是现在礼品所处的位
    置，也就是说，一开始礼品的序列就是1、2、3、4……n；那么然后，我们看列表的
    第一行操作，设这一行操作的第i个数字为a[i]，那么就把原来序列中的第a[i]个
    礼物放到现在这个序列的第i的位置上，然后组成新的礼物序列。然后，看列表的
    第二行操作……、第三行操作……一直到最后一行操作，重复上面的操作。当最后一行
    的操作结束，组成了的序列又按照第一行来操作，然后第二行操作……第三行操作……
    一直循环下去，直到一共操作了k行为止。最后生成的这个序列就是我们最终礼品
    送给孩子们的序列了。

分析：
    矩阵快速幂以及矩阵乘法。具体看Matrix 67

*/
#include <set>
#include <map>
#include <cmath>
#include <queue>
#include <stack>
#include <string>
#include <vector>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>

using namespace std;

typedef long long ll;

#define debug puts("here")

const int MAXN = 102;
const int MAXM = 11;

int n,m;

class Matrix{
public:
    int a[MAXN][MAXN];

    Matrix(){
        memset(a,0,sizeof(a));
    }

    void setE(){
        memset(a,0,sizeof(a));
        for(int i=0;i<n;i++)
            a[i][i] = 1;
    }

    Matrix operator * (Matrix b){
        Matrix c = Matrix();
        for(int i=0;i<n;i++)
            for(int j=0;j<n;j++)
                for(int k=0;k<n;k++)
                    c.a[i][j] += a[i][k]*b.a[k][j];
        return c;
    }

    Matrix bin(int exp){
        Matrix ans;
        Matrix cur = *this;
        ans.setE();
        while(exp>0){
            if(exp&1)
                ans = ans*cur;
            cur = cur*cur;
            exp >>= 1;
        }
        return ans;
    }
    void di(){
        for(int i=0;i<n;i++){
            for(int j=0;j<n;j++)
                cout<<a[i][j]<<" ";
            cout<<endl;
        }
        cout<<endl;
    }
};

int main(){

#ifndef ONLINE_JUDGE
	freopen("sum.in","r",stdin);
#endif

    int k;
    while(cin>>n>>m>>k){
        int x;
        Matrix ans;
        ans.setE();
        Matrix ret[12];
        ret[0].setE();

        for(int i=0;i<m;i++){
            Matrix cur;
            for(int j=0;j<n;j++){
                scanf("%d",&x);
                cur.a[j][x-1] = 1;
            }
            ret[i+1] = cur*ret[i];
            //ret[i+1].di();
            ans = cur*ans;
        }

        ans = ans.bin(k/m);
        ans = ret[k%m]*ans;
        //ans.di();

        for(int i=0;i<n;i++)
            for(int j=0;j<n;j++){
                if(ans.a[i][j]){
                    if(i)
                        cout<<" ";
                    cout<<j+1;
                    break;
                }
            }
        cout<<endl;
    }
	return 0;
}
