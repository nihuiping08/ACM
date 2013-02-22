/*

题目：
    给出一个数n，从不大于n的数中随机选择一个素数，若该数是n的因子p的时候，可
    以转化为n/p的形式，否则n不变，现在给出n，问他能够转化为1的期望次数

分析：
    这题可以看做一个随机状态转换机，每个不大于n的素数都是一个等概率事件，根据
    全期望公式，不难发现递推关系如下：
    dp[x] = 1+dp[x]*( (sum[x]-p[x])/sum[x] )+∑ (dp[x/y] / sum[x] ),y为x的素数
    因子。
    1表示为已经转移了一次，若随机选出的不是x的素因子，则x不变化，所以有
    dp[x]*( (sum[x]-p[x])/sum[x] )，若y为x的素因子，转化为∑ (dp[x/y] / sum[x] )

    算法的实现：利用记忆化搜索即可实现该算法。先利用略为修改过的筛法，把不大于
    x的素数的个数统计出来，以及把x的素数因子存在二维数组里（注意到
    2*3*5*7*11*13*17*19>1000000），所以第二维可以开到9就行了。另外对于每次求过
    了的dp[x]，不用再次求出（对于所有的测试数据都一样~~）

*/
#include <iostream>
#include <cstring>
#include <cstdio>
#include <cmath>
#include <vector>

using namespace std;

const int X = 1000002;

int use[X];
int sum[X];
int p[X];
int div[X][9],top[X];
int n;
double dp[X];

void init(){
    memset(use,0,sizeof(use));
    memset(top,0,sizeof(top));
    for(int i=2;i<X;i++){
        if(use[i])
            sum[i] = sum[i-1];
        else{
            top[i] = 1;
            div[i][0] = i;
            sum[i] = sum[i-1]+1;
            for(int j=i+i;j<X;j+=i){
                use[j] = true;
                div[j][top[j]++] = i;
            }
        }
    }
}

double f(int x){
    if(use[x])
        return dp[x];
    use[x] = true;
    if(x==1)
        return dp[x] = 0;
    double ans = sum[x];
    for(int i=0;i<top[x];i++)
        ans += f(x/div[x][i]);
    return dp[x] = ans/top[x];
}

int main(){
    freopen("sum.in","r",stdin);
    init();
    int ncase,cnt = 0;
    cin>>ncase;
    memset(use,false,sizeof(use));
    while(ncase--){
        cin>>n;
        printf("Case %d: %.10lf\n",++cnt,f(n));
    }
    return 0;
}
