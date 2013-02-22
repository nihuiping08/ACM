#include <iostream>
#include <cstdio>
#include <cstring>

using namespace std;

const int X = 101;
const int inf = 1e9;
#define debug puts("here");

int mnum,hnum;
int map[X][X],r,c;
int match[X],lx[X],ly[X];
bool visx[X],visy[X];
char s[X];

struct node
{
    int x,y;
}man[X],home[X];

bool dfs(int x)
{
    visx[x] = true;
    for(int i=1;i<=hnum;i++)
    {
        if(!visy[i]&&lx[x]+ly[i]==map[x][i])
        {
            visy[i] = true;
            if(match[i]==0||dfs(match[i]))
            {
                match[i] = x;
                return true;
            }
        }
    }
    return false;
}

void KM()
{
    memset(match,0,sizeof(match));
    for(int i=1;i<=mnum;i++)
    {
        while(true)
        {
            memset(visx,false,sizeof(visx));
            memset(visy,false,sizeof(visy));
            if(dfs(i))
                break;
            int MIN = inf;
            for(int j=1;j<=mnum;j++)
                if(visx[j])
                    for(int qq=1;qq<=hnum;qq++)
                        if(!visy[qq])
                            MIN = min(MIN,map[j][qq]-lx[j]-ly[qq]);
            for(int j=1;j<=mnum;j++)
                if(visx[j])
                    lx[j] += MIN;
            for(int j=1;j<=hnum;j++)
                if(visy[j])
                    ly[j] -= MIN;
        }
    }
    int sum = 0;
    for(int i=1;i<=hnum;i++)
        sum += map[match[i]][i];
    printf("%d\n",sum);
}

void init()
{
    memset(map,0,sizeof(map));
    int x,y;
    for(int i=1;i<=mnum;i++)
        for(int j=1;j<=hnum;j++)
        {
            x = man[i].x-home[j].x;
            y = man[i].y-home[j].y;
            map[i][j] = max(x,-x)+max(y,-y);
        }
    memset(lx,127,sizeof(lx));
    memset(ly,0,sizeof(ly));
    for(int i=1;i<=mnum;i++)
        for(int j=1;j<=hnum;j++)
            lx[i] = min(lx[i],map[i][j]);
}

int main()
{
    freopen("sum.in","r",stdin);
    while(cin>>r>>c,r||c)
    {
        getchar();
        mnum = hnum = 0;
        for(int i=0;i<r;i++)
        {
            gets(s);
            for(int j=0;s[j];j++)
            {
                if(s[j]=='m')
                {
                    man[++mnum].x = i;
                    man[mnum].y = j;
                }
                else if(s[j]=='H')
                {
                    home[++hnum].x = i;
                    home[hnum].y = j;
                }
            }
        }
        init();
        KM();
    }
    return 0;
}
