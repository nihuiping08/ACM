/*

题目：
    给出n个人，每个人的衣服都有各自的size，有S M L X T五种，然后给出n个
    字符串比如ST表示该人从S到T的size大小都合适，然后下一行给出这五种衣服
    的数量，然后问能不能够满足所有的人的穿着

分析：
    对每件衣服编号，然后枚举每个人与相应的衣服编号段连上边，最后求二分匹
    配的最大匹配是不是等于n即可

*/
#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>

using namespace std;

const int X = 105;

char s[20];
char str[20][10];

int ym[X],n,m;
bool use[X];
bool map[X][X];

bool dfs(int u)
{
    int t;
    for(int v=1;v<=m;v++)
    {
        if(map[u][v]&&!use[v])
        {
            use[v] = true;
            t = ym[v];
            if(t==-1||dfs(t))
            {
                ym[v] = u;
                return true;
            }
        }
    }
    return false;
}

void hungry()
{
    memset(ym,-1,sizeof(ym));
    int ret = 0;
    for(int u=0;u<n;u++)
    {
        memset(use,false,sizeof(use));
        if(dfs(u))
            ret++;
    }
    if(ret==n)
        puts("T-shirts rock!");
    else
        puts("I'd rather not wear a shirt anyway...");
}

int main()
{
    freopen("sum.in","r",stdin);
    int ha[128];
    ha[(int)'S'] = 1;
    ha[(int)'M'] = 2;
    ha[(int)'L'] = 3;
    ha[(int)'X'] = 4;
    ha[(int)'T'] = 5;
    while(scanf("%s",s),strcmp(s,"ENDOFINPUT"))
    {
        int a[10];
        vector<int> b[10];
        scanf("%d",&n);
        for(int i=0;i<n;i++)
            scanf("%s",str[i]);
        m = 0;
        for(int i=1;i<=5;i++)
        {
            scanf("%d",&a[i]);
            for(int j=m+1;j<=m+a[i];j++)
                b[i].push_back(j);
            m += a[i];
        }
        memset(map,false,sizeof(map));
        int id;
        int sx,ex;
        for(int i=0;i<n;i++)
        {
            sx = 5,ex = 0;
            for(int j=0;str[i][j];j++)
            {
                id = ha[(int)str[i][j]];
                sx = min(sx,id);
                ex = max(ex,id);
            }
            for(int j=sx;j<=ex;j++)
            {
                int len = b[j].size();
                for(int k=0;k<len;k++)
                {
                    int y = b[j][k];
                    map[i][y] = true;
                }
            }
        }
        hungry();
        scanf("%s",s);
    }
    return 0;
}
