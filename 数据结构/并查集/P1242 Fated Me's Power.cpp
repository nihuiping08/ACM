/*

题目：
    YO-GI-OH中有这么一张魔法卡——力量。它会根据某种方法给予被装备者强大的力量。
    这张卡上写着，dota中所有有拓扑关系（若x与y有拓扑关系，并且y与z有拓扑关系，
    则x与z也有拓扑关系）的生物会组成一个佣兵团（很可惜他们的名字都是数字…）。
    其中LYD(鉴于LYD出题经常拿我(比如GF和猫咪的玩具那题)开涮，今天我也得反过来
    T_T)所在的佣兵团中的成员根据名字分为2个党派：质数党和非质数党（应wwwwodddd
    要求添加了这么有数论气息的名词..）。质数党中的每个生物可以和非质数党中的任
    意生物用硅酸钠粘到一起而成为一个称为互补金属合金氧化物半导体（BIOS）的东西。
    而互补金属合金氧化物半导体（BIOS）的数量就是这张魔法卡能提供的力量。

分析：
    题目好像有点说得不太明白，A了之后才发现是这样做的：
    先对n对拓扑关系用并查集的方式连接。对给出的LYD的名字找到他的父母节点名字，
    再枚举所有的节点寻找他们各自的父母节点名字，若跟LYD的相同，则分素数和非素数
    两类统计，最后输出较小的即可

*/
#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>

using namespace std;

const int X = 4005;

int f[X],n,m,pos;
bool use[X];

int find_set(int x)
{
    if(x!=f[x])
        f[x] = find_set(f[x]);
    return f[x];
}

void init()
{
    memset(use,false,sizeof(use));
    use[1] = true;
    for(int i=2;i<X;i++)
        if(!use[i])
            for(int j=i+i;j<X;j+=i)
                use[j] = true;
}

int main()
{
    freopen("sum.in","r",stdin);
    init();
    scanf("%d%d",&n,&m);
    int x,y;
    for(int i=1;i<=n;i++)
        f[i] = i;
    for(int i=1;i<=m;i++)
    {
        scanf("%d%d",&x,&y);
        x = find_set(x);
        y = find_set(y);
        if(x!=y)
            f[y] = x;
    }
    scanf("%d",&pos);
    int ans = 0;
    x = find_set(pos);
    pos = 0;
    for(int i=1;i<=n;i++)
    {
        y = find_set(i);
        if(x==y)
        {
            if(use[i])
                ans++;
            else
                pos++;
        }
    }
    cout<<min(pos,ans)<<endl;
    return 0;
}
