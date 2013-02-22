/*

	m达到10^9，显然不能直接算。
    因为k个操作给出之后就是固定的，所以想到用矩阵，矩阵快速幂可以把时间复杂度降到O（logm）。
	问题转化为如何构造转置矩阵？
    说下我的思路，观察以上三种操作，发现第二，三种操作比较容易处理，重点落在第一种操作上。
    有一个很好的办法就是添加一个辅助，使初始矩阵变为一个n+1元组，编号为0到n，下面以3个猫为例：
    定义初始矩阵A = [1 0 0 0]，0号元素固定为1，1~n分别为对应的猫所拥有的花生数。
    对于第一种操作g i，我们在单位矩阵基础上使Mat[0][i]变为1，例如g 1：
    1 1 0 0
    0 1 0 0
    0 0 1 0
    0 0 0 1，显然[1 0 0 0]*Mat = [1 1 0 0]
    对于第二种操作e i，我们在单位矩阵基础使Mat[i][i] = 0,例如e 2：
    1 0 0 0
    0 1 0 0
    0 0 0 0
    0 0 0 1, 显然[1 2 3 4]*Mat = [1 2 0 4]
    对于第三种操作s i j，我们在单位矩阵基础上使第i列与第j互换，例如s 1 2：
    1 0 0 0
    0 0 0 1
    0 0 1 0
    0 1 0 0，显然[1 2 0 4]*Mat = [1 4 0 2]
    现在，对于每一个操作我们都可以得到一个转置矩阵，把k个操作的矩阵相乘我们可以得到一个新
	的转置矩阵T。
    A * T 表示我们经过一组操作，类似我们可以得到经过m组操作的矩阵为 A * T ^ m,最终矩阵的
	[0][1~n]即为答案。

    上述的做法比较直观，但是实现过于麻烦，因为要构造k个不同矩阵。

    有没有别的方法可以直接构造转置矩阵T？答案是肯定的。
    我们还是以单位矩阵为基础：
    对于第一种操作g i，我们使Mat[0][i] = Mat[0][i] + 1；
    对于第二种操作e i，我们使矩阵的第i列清零；
    对于第三种操作s i j，我们使第i列与第j列互换。
    这样实现的话，我们始终在处理一个矩阵，免去构造k个矩阵的麻烦。

    至此，构造转置矩阵T就完成了，接下来只需用矩阵快速幂求出 A * T ^ m即可，还有一个注意的地方，
	该题需要用到long long。

*/
#include <iostream>
#include <cstdio>
#include <cstring>

using namespace std;

const int X = 105;

typedef long long ll;

class matrix{
    public:
        int n,m;
        ll a[X][X];

        matrix(){
            memset(a,0,sizeof(a));
        }
        matrix(int _n,int _m):n(_n),m(_m){
            memset(a,0,sizeof(a));
        }

        matrix operator * (matrix p){
            int q = p.m;
            matrix c(n,q);
            for(int i=0;i<n;i++)
                for(int k=0;k<q;k++)
                    if(a[i][k])
                        for(int j=0;j<m;j++)
                            c.a[i][j] += a[i][k]*p.a[k][j];
            return c;
        }

        void getE(){
            for(int i=0;i<n;i++)
                a[i][i] = 1;
        }

        matrix pow(int exp){
            matrix temp(n,n);
            temp.getE();
            matrix cur = *this;

            while(exp>0){
                if(exp&1)
                    temp = temp*cur;
                cur = cur*cur;
                exp = exp >> 1;
            }
            return temp;
        }

        void display(){
            for(int i=0;i<n;i++){
                for(int j=0;j<m;j++)
                    cout<<a[i][j]<<" ";
                cout<<endl;
            }
            cout<<endl;
        }

};

int main(){
    freopen("sum.in","r",stdin);
    int n,m,q,x,y;
    char op[2];
    while(cin>>n>>m>>q,n||m||q){
        matrix ans(n+1,n+1);
        matrix a(1,n+1);
        ans.getE();
        a.a[0][0] = 1;
        while(q--){
            scanf("%s%d",op,&x);
            if(op[0]=='g')
                ans.a[0][x] ++;
            else if(op[0]=='e'){
                for(int i=0;i<=n;i++)
                    ans.a[i][x] = 0;
            }
            else{
                scanf("%d",&y);
                for(int i=0;i<=n;i++)
                    swap(ans.a[i][x],ans.a[i][y]);
            }
        }
        //ans.display();
        ans = ans.pow(m);
        //ans.display();
        ans = a*ans;
        //ans.display();
        cout<<ans.a[0][1];
        for(int i=2;i<=n;i++)
            printf(" %I64d",ans.a[0][i]);
        puts("");
    }
    return 0;
}
