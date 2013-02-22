/*

题目：
    每两点平行于x轴或y轴就不用修建微子发射器，就是说他们是可以相互通信的，
    现在给出n个点的坐标，问你最少需要修建多少个微子发射器

分析：
    用x[a],y[b]数组来记录坐标(a,b)所在的位置号码，若输入的坐标中的a或b已经
    出现过了，就用并查集的方式使得该位置的号码与x[a]、y[b]的父亲连接

*/
#include <cstdio>
#include <iostream>
#include <cstring>

using namespace std;

const int X = 200005;

int aa,bb,n;
int x[X],y[X],f[X];
bool use[X];

int find_set(int x)
{
    if(x!=f[x])
        f[x] = find_set(f[x]);
    return f[x];
}

int main()
{
    freopen("sum.in","r",stdin);
    scanf("%d%d%d",&aa,&bb,&n);
    int a,b;
    memset(x,0,sizeof(x));
    memset(y,0,sizeof(y));

    for(int i=1;i<=n;i++)
        f[i] = i;

    int pa,pb;
    for(int i=1;i<=n;i++)
    {
        scanf("%d%d",&a,&b);
        if(x[a])
        {
            pa = find_set(x[a]);
            pb = find_set(i);
            if(pa!=pb)
                f[pb] = pa;
        }
        else
            x[a] = i;
        if(y[b])
        {
            pa = find_set(y[b]);
            pb = find_set(i);
            if(pa!=pb)
                f[pb] = pa;
        }
        else
            y[b] = i;
    }
    memset(use,false,sizeof(use));
    int ans = 0;
    for(int i=1;i<=n;i++)
    {
        pa = find_set(i);
        if(!use[pa])
        {
            use[pa] = true;
            ans++;
        }
    }
    cout<<ans-1<<endl;
    return 0;
}
