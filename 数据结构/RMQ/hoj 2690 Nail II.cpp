/*
ST算法（Sparse Table）:它是一种动态规划的方法。
以最小值为例。a为所寻找的数组.
用一个二维数组f(i,j)记录区间[i,i+2^j-1](持续2^j个)区间中的最小值。其中f[i,0] = a[i];
所以，对于任意的一组(i,j)，f(i,j) = min{f(i,j-1),f(i+2^(j-1),j-1)}来使用动态规划计算出来。
这个算法的高明之处不是在于这个动态规划的建立，而是它的查询：它的查询效率是O(1).
假设我们要求区间[m,n]中a的最小值，找到一个数k使得2^k<n-m+1.
这样，可以把这个区间分成两个部分：[m,m+2^k-1]和[n-2^k+1,n].我们发现，这两个区间是已经初始化好的.
前面的区间是f(m,k)，后面的区间是f(n-2^k+1,k).
这样，只要看这两个区间的最小值，就可以知道整个区间的最小值！


11.*一维RMQ ST算法
12.*构造RMQ数组 makermq(int n,int b[]) O(nlog(n))的算法复杂度
13.*dp[i][j] 表示从i到i+2^j -1中最小的一个值(从i开始持续2^j个数)
14.*dp[i][j]=min{dp[i][j-1],dp[i+2^(j-1)][j-1]}
15.*查询RMQ rmq(int s,int v)
16.*将s-v 分成两个2^k的区间
17.*即 k=(int)log2(s-v+1)
18.*查询结果应该为 min(dp[s][k],dp[v-2^k+1][k])
19.*/

#include <iostream>
#include <cstring>
#include <cstdio>
#include <cmath>
using namespace std;
#define X 500005
int dp[X][20],dex[X][20];
int b[X],n,m;
void make_rmq(){    //计算最大值
    for(int i=0;i<n;i++)
        dp[i][0] = b[i];
    for(int j=1;(1<<j)<=n;j++)
        for(int i=0;i+(1<<j)-1<n;i++)
            dp[i][j] = max(dp[i][j-1],dp[i+(1<<(j-1))][j-1]);
}
int rmq(int s,int v){   //返回最大值
    int k = (int)(log((v-s+1)*1.0)/log(2.0));
    return max(dp[s][k],dp[v-(1<<k)+1][k]);
}
void make_rmq_index(){  //计算最大值的下标
    for(int i=0;i<n;i++)
        dex[i][0] = i;
    for(int j=1;(1<<j)<=n;j++)
        for(int i=0;i+(1<<j)-1<n;i++)
            dex[i][j] = b[dex[i][j-1]]>b[dex[i+(1<<(j-1))][j-1]]?dex[i][j-1]:dex[i+(1<<(j-1))][j-1];
}

int rmq_index(int s,int v){     //返回最大值的下标
    int k = (int)(log((v-s+1)*1.0)/log(2.0));
    return b[dex[s][k]]>b[dex[v-(1<<k)+1][k]]?dex[s][k]:dex[v-(1<<k)+1][k];
}
int main(){
    freopen("sum.in","r",stdin);
    freopen("sum.out","w",stdout);
    int s,v;
    while(cin>>n>>m){
        for(int i=0;i<n;i++)
            scanf("%d",&b[i]);
        make_rmq();
        make_rmq_index();
        while(m--){
            scanf("%d%d",&s,&v);
            printf("%d\n",b[rmq_index(s-1,v-1)]);
        }
    }
    return 0;
}
