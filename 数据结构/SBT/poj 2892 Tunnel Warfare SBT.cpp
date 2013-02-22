/*

题目：
    现有n座城堡在一直线上，除了两端之外，其余的都各自与相邻的城堡有道路，
    现在有三种操作，摧毁城堡，修复城堡，询问城堡x与他相连的城堡数目（包括
    自己）。

分析:
    SBT，每当摧毁城堡的时候插入一个节点，当询问的时候，查找比栈顶元素小的
    以及大的位置，两者相减再减一。

*/
#include <cstdio>
#include <cstring>
#include <iostream>

using namespace std;

const int X = 200005;
#define debug puts("here");

int n,m;
int s[X],top;
int use[X];
int root,tol;

struct node{
    int l,r,val,s;
    void init(){
        l = r = 0;
        s = 1;
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
        else
            return;
    }
    else{
        if(sbt[sbt[sbt[t].r].r].s>sbt[sbt[t].l].s)
            left_rotate(t);
        else if(sbt[sbt[sbt[t].r].l].s>sbt[sbt[t].l].s){
            right_rotate(sbt[t].r);
            left_rotate(t);
        }
        else
            return;
    }
    maintain(sbt[t].l,0);
    maintain(sbt[t].r,1);
    maintain(t,0);
    maintain(t,1);
}

void insert(int &t,int val){
    if(!t){
        t = ++tol;
        sbt[t].init();
        sbt[t].val = val;
    }
    else{
        sbt[t].s++;
        if(val<sbt[t].val)
            insert(sbt[t].l,val);
        else
            insert(sbt[t].r,val);
        maintain(t,val>=sbt[t].val);
    }
}

int del(int &t,int val){
    if(!t)
        return 0;
    sbt[t].s--;
    if(val==sbt[t].val||(val<sbt[t].val&&!sbt[t].l)||(val>sbt[t].val&&!sbt[t].r)){
        if(sbt[t].l&&sbt[t].r){
            int pos = del(sbt[t].l,val+1);
            sbt[t].val = sbt[pos].val;
            return pos;
        }
        else{
            int pos = t;
            t = sbt[t].l+sbt[t].r;
            return pos;
        }
    }
    else
        return del(val<sbt[t].val?sbt[t].l:sbt[t].r,val);
}

int less_than(int t,int val){
    if(!t)
        return 0;
    if(val<sbt[t].val)
        return less_than(sbt[t].l,val);
    else
        return max(sbt[t].val,less_than(sbt[t].r,val));
}

int greater_than(int t,int val){
    if(!t)
        return n+1;
    if(val>sbt[t].val)
        return greater_than(sbt[t].r,val);
    else
        return min(sbt[t].val,greater_than(sbt[t].l,val));
}

int main(){
    freopen("sum.in","r",stdin);
    char str[5];
    int x;
    while(cin>>n>>m){
        for(int i=0;i<=X;i++)
            sbt[i].init();
        memset(use,0,sizeof(use));
        top = 0;
        root = 0;
        tol = 0;
        while(m--){
            scanf("%s",str);
            if(str[0]=='D'){
                scanf("%d",&x);
                use[x]++;
                s[++top] = x;
                insert(root,x);
            }
            else if(str[0]=='R'){
                if(top>0){
                    del(root,s[top]);
                    use[s[top--]]--;
                }
            }
            else{
                scanf("%d",&x);
                if(use[x])
                    puts("0");
                else{
                    int r = greater_than(root,x);
                    int l = less_than(root,x);
                    //cout<<r<<" "<<l<<" ";
                    printf("%d\n",r-l-1);
                }
            }
        }
    }
    return 0;
}
