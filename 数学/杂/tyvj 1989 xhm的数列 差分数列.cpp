/*

题目：
    给定N个整数A[1..N]
    现在有两种操作：
    操作1：选择一个连续子序列[l, r]，把他们的数值全部增加T
    操作2：询问数列中某个元素A[i]的值是多少。
    为了降低难度，我们先执行Q1次操作1，再执行Q2次操作2。

分析：
    解法1：线段数OR树状数组 朴素操作即可
    重点讲解法2:
    用差分数列做
    我们数列有 a_1 a_2 a_3...a_n;
    我们令 d_1=a_1
    d_n=a_n-a_(n-1) (n>2)
    这样我们就可以通过累加 前N项 数列D 得知数列A的值了
    我们可以证明
    如果对于区间[l,r] 增加 t 只需对 d_l + t 和 d_(r+1)-t
    这样就可以了。。。时间 复杂度为O（N）
    区间加减操作结束用 再累加。。得出数列A的值

*/
#include <iostream>
#include <cstdio>
#include <cstring>

using namespace std;

typedef __int64 ll;

const int X = 100005;

int n,m,q;
ll a[X],d[X],sum[X];

int main(){
    freopen("sum.in","r",stdin);
    int l,r;
    ll add;
    while(cin>>n>>m>>q){
        a[0] = 0;
        for(int i=1;i<=n;i++){
            scanf("%I64d",&a[i]);
            d[i] = a[i]-a[i-1];
        }
        while(m--){
            scanf("%d%d%I64d",&l,&r,&add);
            d[l] += add;
            d[r+1] -= add;
        }
        sum[0] = 0;
        for(int i=1;i<=n;i++)
            sum[i] = sum[i-1]+d[i];
        while(q--){
            scanf("%d",&l);
            printf("%I64d\n",sum[l]);
        }
    }
    return 0;
}
