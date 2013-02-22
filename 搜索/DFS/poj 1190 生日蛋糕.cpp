#include <iostream>
#include <cstring>
#include <cstdio>

using namespace std;

const int X = 22;
const int INF = 1000000000;
#define debug cout<<"here"<<endl;


int min_v[X],min_s[X];
int total_v,total_level;
int ans;

void init()
{
    min_s[0] = min_v[0] = 0;
    for(int i=1;i<X;i++)
    {
        min_v[i] = min_v[i-1]+i*i*i;
        min_s[i] = min_s[i-1]+i*i;
    }
}

void dfs(int depth,int pre_r,int pre_h,int pre_s,int pre_v)
{
    int temp;
    if(pre_s>=ans)
        return;
    if(pre_v>total_v)
        return;
    if(depth==0)
    {
        if(pre_v==total_v&&ans>pre_s)
            ans = pre_s;
        return;
    }
    if(pre_v+min_v[depth-1]>total_v||pre_s+min_s[depth-1]>=ans)
        return;
    if(pre_s+2*(total_v-pre_v)/pre_r>=ans)
        return;
    for(int i=pre_r-1;i>=depth;i--)
    {
        if(depth==total_level)
            pre_s = i*i;
        temp = (total_v-pre_v-min_v[depth-1])/(i*i);
        temp = min(temp,pre_h-1);
        for(int j=temp;j>=depth;j--)
            dfs(depth-1,i,j,pre_s+2*i*j,pre_v+i*i*j);
    }
}

int main()
{
    freopen("sum.in","r",stdin);
    freopen("sum.out","w",stdout);
    init();
    cin>>total_v>>total_level;
    ans = INF;
    dfs(total_level,total_v+1,total_v+1,0,0);
    ans==INF?printf("0\n"):printf("%d\n",ans);
    return 0;
}
