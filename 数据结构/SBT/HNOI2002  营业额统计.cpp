/*

题目：
    最小波动值= min { | 该天以前某一天的营业额-该天的营业额 | }

分析：
    求前驱以及后继与当前的数相减的绝对值的最小值。

*/
#include <cstdio>
#include <cstring>
#include <iostream>
#include <cstdlib>

using namespace std;

const int X = 1111111;

int root,tol,n;
bool use[X] = {0};

struct node{
    int val,l,r,s;
    void init(int _val){
        l = r = 0;
        s = 1;
        val = _val;
    }
}sbt[X];

void left_rotate(int &t){
    int k = sbt[t].r;
    sbt[t].r = sbt[k].l;
    sbt[k].l = t;
    sbt[k].s = sbt[t].s;
    sbt[t].s = sbt[sbt[t].l].s+sbt[sbt[t].r].s+1;
    t = k;
}

void right_rotate(int &t){
    int k = sbt[t].l;
    sbt[t].l = sbt[k].r;
    sbt[k].r = t;
    sbt[k].s = sbt[t].s;
    sbt[t].s = sbt[sbt[t].l].s+sbt[sbt[t].r].s+1;
    t = k;
}

void maintain(int &t,bool ok){
    if(!ok){
        if(sbt[sbt[sbt[t].l].l].s>sbt[sbt[t].r].s)
            right_rotate(t);
        else if(sbt[sbt[sbt[t].l].r].s>sbt[sbt[t].r].s){
            left_rotate(sbt[t].l);
            right_rotate(t);
        }
        else return;
    }
    else{
        if(sbt[sbt[sbt[t].r].r].s>sbt[sbt[t].l].s)
            left_rotate(t);
        else if(sbt[sbt[sbt[t].r].l].s>sbt[sbt[t].l].s){
            right_rotate(sbt[t].r);
            left_rotate(t);
        }
        else return;
    }
    maintain(sbt[t].l,0);
    maintain(sbt[t].r,1);
    maintain(t,0);
    maintain(t,1);
}

void insert(int &t,int val){
    if(!t){
        t = ++tol;
        sbt[t].init(val);
        return;
    }
    sbt[t].s++;
    if(val<sbt[t].val)
        insert(sbt[t].l,val);
    else
        insert(sbt[t].r,val);
    maintain(t,val>=sbt[t].val);
}

int get_pre(int t,int val){
    if(!t)
        return val;
    if(val<=sbt[t].val)
        return get_pre(sbt[t].l,val);
    else{
        int temp = get_pre(sbt[t].r,val);
        return temp==val?sbt[t].val:temp;
    }
}

int get_succ(int t,int val){
    if(!t)
        return val;
    if(val>=sbt[t].val)
        return get_succ(sbt[t].r,val);
    else{
        int temp = get_succ(sbt[t].l,val);
        return temp==val?sbt[t].val:temp;
    }
}

int main(){
    freopen("sum.in","r",stdin);
    //freopen("sum.out","w",stdout);
    root = tol = 0;
    int ans = 0,x;
    cin>>n>>x;
    int qq = 1000000;
    ans = x;
    insert(root,x);
    use[x+qq] = true;
    int xx,yy;
    for(int i=1;i<n;i++){
        if(scanf("%d",&x)==EOF)
            x = 0;
        if(use[qq+x])
            continue;
        use[qq+x] = true;
        if(!(xx = x-get_pre(root,x)))
            xx = X;
        if(!(yy = get_succ(root,x)-x))
            yy = X;

        ans += min(xx,yy);
        insert(root,x);
    }
    cout<<ans<<endl;
    return 0;
}
