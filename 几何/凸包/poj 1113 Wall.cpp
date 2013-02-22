/*

第一个凸包题。

graham的思想其实挺简单的，就是先对所有的点进行极角排序，排序过程中，若果极角相同的话，
就按坐标来排，然后得到排完序后的所有点的坐标，然后开始逆时针找到极角增大的点，判断他是否
在前一根线短（假设已在临时凸包上的线段）的左侧，不是的话就把上一个点出栈，直到没有向右转
的点为止，然后把新增的点加入到栈中，从而得到凸包，算法的时间复杂度为O(nlogn)。

题目：
    贪心的国王想用最少的石头包围皇宫，并且需要留出离皇宫一定的距离，问最长能用多长的线把它
    连起来。

分析：
    在求到的凸包中加上一个完整的圆的周长即可

*/
/*
    我们可以先将问题做一个转化：先求出城堡各点的凸包，然后求距凸包的距离为L的闭合图形的周长。

    至于为什么先转化成凸包，我们不妨用反证法，如果围墙向凸包内部的方向延伸的话必然还要延伸
    出来，这样就会更费料。

    围墙的形状不难想象，一部分是和边平行且等于各边的边长的，还有一部分就是墙角位置的弧形，
    而且这个弧形的圆心角正是两条边的方向向量的夹角。

    在计算周长的时候，一部分就是凸包的周长，另一部分就是这些弧的长度之和。我们当然可以求出
    每个角上的弧，然后累加到一起，但这样会涉及很多的三角函数和开方函数的运算，就会有更多精
    度上的损失，其实细想一下会发现把这些弧拼起来就是一个完整的圆，因此算完凸包的周长之后再
    加上一个半径为L的圆的周长即可。

*/
/*

好像这个是水平序排的。。。

*/
#include <iostream>
#include <cmath>
#include <cstdio>
#include <algorithm>
using namespace std;
#define PI 3.14159265
#define X 1005
struct point{
    int x,y;
    friend bool operator <(point a,point b){
        return a.y<b.y||(a.y==b.y&&a.x<b.x);
    }

}p[X],res[X];

int n,m,P;

int det(int x1,int y1,int x2,int y2)    //叉积
{
        return x1*y2-x2*y1;
}

bool del(int top,int i) //向右转的话，返回true，否则返回false
{
    if(det(res[top].x-res[top-1].x,res[top].y-res[top-1].y,p[i].x-res[top].x,p[i].y-res[top].y)<0)
        return true;
    return false;
}
int graham()       //求凸包
{
    int top = 1;
    res[0] = p[0],res[1] = p[1];
    for(int i=2;i<n;i++){
        while(top&&del(top,i))  //若向右转，出栈
            top--;
        res[++top] = p[i];      //把新增的点入栈
    }
    int mint = top;
    res[++top] = p[n-2];
    for(int i=n-3;i>=0;i--){
        while(top!=mint&&del(top,i))
            --top;
        res[++top] = p[i];
    }
    return top;
}

void cal()
{
    double ans = 0;
    res[P+1] = res[1];
    for(int i=0;i<P;i++)
        ans += sqrt(1.0*(res[i].x-res[i+1].x)*(res[i].x-res[i+1].x)+(res[i].y-res[i+1].y)*(res[i].y-res[i+1].y));
    printf("%d\n",(int)(ans+PI*2*m+0.5));
}
int main()
{
    freopen("sum.in","r",stdin);
    freopen("sum.out","w",stdout);
    while(cin>>n>>m){
        for(int i=0;i<n;i++)
            scanf("%d%d",&p[i].x,&p[i].y);
        sort(p,p+n);
        P = graham();
        cal();
    }
    return 0;
}
