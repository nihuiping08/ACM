/*

剪枝好题

*/
#include <cstdio>
#include <algorithm>
#include <cstring>

using namespace std;

int len[22],n,ave,sum;
bool use[22];

bool dfs(int rest,int cur,int p)    //rest：还剩余的边数，cur:当前边已经匹配的长度，p：枚举位置
{               //  p，剪枝
    int temp;
    if(rest==1)
        return true;
    for(int i=p;i<n;i++)
    {
        if(use[i])
            continue;
        use[i] = true;
        temp = cur+len[i];
        if(temp==ave)   //刚好使得当前的边匹配
        {
            if(dfs(rest-1,0,1)) //当前匹配的话，应该冲=从1开始，因为若0都不匹配，剩下的肯定不匹配
                return true;
        }
        else if(temp<ave)
        {
            if(dfs(rest,temp,i+1))
                return true;
        }
        if(!i)
            return false;
        use[i] = false;
        while(len[i]==len[i+1]) //剪枝
            i++;
    }
    return false;
}
bool cmp(int a,int b)
{
    return a>b;
}
int main()
{
    freopen("sum.in","r",stdin);
    freopen("sum.out","w",stdout);
    int t;
    scanf("%d",&t);
    while(t--)
    {
        memset(use,false,sizeof(use));
        sum = 0;
        scanf("%d",&n);
        for(int i=0;i<n;i++)
        {
            scanf("%d",&len[i]);
            sum += len[i];
        }
        if(sum%4)   //剪枝
        {
            printf("no\n");
            continue;
        }
        ave = sum/4;
        sort(len,len+n,cmp);
        if(ave<len[0])   //剪枝
        {
            printf("no\n");
            continue;
        }
        if(dfs(4,0,0))
            printf("yes\n");
        else
            printf("no\n");
    }
    return 0;
}
