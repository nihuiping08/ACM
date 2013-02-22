/*

题目：
    给出n个点，问这n个点能够组成多少个包含原点的三角形

分析：
    对于输入的点进行极角排序，然后枚举每一个点，以他与原点所在的直线将平面划分
    为两个半平面，统计在一个半平面上有多少个点(m个)，然后不能组成符合条件的三角
    形的个数为m*(m-1)/2，然后求和，再用c(n,3)减即可

*/
#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

const int X = 200005;

typedef long long ll;

struct node{
    int x,y,s;
    node(){}
    node(int _x,int _y,int _s):x(_x),y(_y),s(_s){}
    inline friend bool operator < (node a,node b){
        if(a.s==b.s)
            return (ll)a.x*b.y>(ll)a.y*b.x;
        return a.s<b.s;
    }
}p[X];

inline ll cross(int x1,int y1,int x2,int y2){
    return (ll)x1*y2-(ll)x2*y1;
}

int main(){
    freopen("sum.in","r",stdin);
    int n;
    while(scanf("%d",&n)==1){
        int x,y,s;
        for(int i=0;i<n;i++){
            scanf("%d%d",&x,&y);
            if(x>=0&&y>=0)
                s = 0;
            else if(x<=0&&y>=0)
                s = 1;
            else if(x<=0&&y<=0)
                s = 2;
            else
                s = 3;
            p[i] = node(x,y,s);
        }
        if(n<3){
            puts("0");
            continue;
        }
        sort(p,p+n);
        for(int i=0;i<n;i++)
            p[i+n] = p[i];

        ll ans = 0;
        int j = 0;
        for(int i=0;i<n;i++){
            while(j<i+n&&cross(p[i].x,p[i].y,p[j].x,p[j].y)>=0)
                j = j+1;
            if(j-i>2)
                ans +=(ll)(j-i-1)*(j-i-2)/2;
        }
        ans = (ll)n*(n-1)*(n-2)/6-ans;
        printf("%lld\n",ans);
    }
    return 0;
}
