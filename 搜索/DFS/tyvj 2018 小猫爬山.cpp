/*

题目：
    Freda和rainbow只好花钱让它们坐索道下山。索道上的缆车最大
    承重量为W，而N只小猫的重量分别是C1、C2……CN。当然，每辆缆
    车上的小猫的重量之和不能超过W。每租用一辆缆车，Freda和
    rainbow就要付1美元，所以他们想知道，最少需要付多少美元才
    能把这N只小猫都运送下山？

分析：
    枚举答案，dfs+剪枝

*/
#include <iostream>
#include <cstdio>
#include <cstring>

using namespace std;

const int X = 20;

int a[X],n,m;
bool use[X];
int sum[X];

bool dfs(int x,int ans){
    if(x>n)
        return true;
    for(int i=1;i<=ans&&i<=x;i++){
        if(sum[i]+a[x]<=m){
            sum[i] += a[x];
            if(dfs(x+1,ans))
                return true;
            sum[i] -= a[x];
        }
    }
    return 0;
}

int main(){
    freopen("sum.in","r",stdin);
    while(cin>>n>>m){
        for(int i=1;i<=n;i++)
            scanf("%d",&a[i]);
        memset(use,false,sizeof(use));
        memset(sum,0,sizeof(sum));
        for(int i=1;i<=n;i++)
            if(dfs(1,i)){
                cout<<i<<endl;
                break;
            }
    }
    return 0;
}
