/*

题目:
    三种操作:
    0	The system needs to stop serving
    1 K P	Add client K to the waiting list with priority P
    2	Serve the client with the highest priority and drop him or her from the waiting list
    3	Serve the client with the lowest priority and drop him or her from the waiting list
    问出队序列

分析：
    2号操作的时候，直接搜索右子树的最右儿子的val域
    3号操作的时候，直接搜索左子树的最左儿子的val域

*/
#include <iostream>
#include <cstdio>
#include <cstring>

using namespace std;

const int X = 1e6+5;

int root,tol;

struct node{
    int l,r,s,id,val;
    void init(int _val,int _id){
        l = r = 0;
        s = 1;
        val = _val;
        id = _id;
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

void insert(int &t,int val,int id){
    if(!t){
        t = ++tol;
        sbt[t].init(val,id);
        return;
    }
    sbt[t].s++;
    if(val<sbt[t].val)
        insert(sbt[t].l,val,id);
    else
        insert(sbt[t].r,val,id);
    maintain(t,val>=sbt[t].val);
}

int del(int &t,int val){
    if(!t)  return 0;
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

int _val;

int get_min(int t){
    while(sbt[t].l)
        t = sbt[t].l;
    _val = sbt[t].val;
    return sbt[t].id;
}

int get_max(int t){
    while(sbt[t].r)
        t = sbt[t].r;
    _val = sbt[t].val;
    return sbt[t].id;
}

int main(){
    freopen("aum.in","r",stdin);
    int op,val,id,temp;
    root = tol = 0;
    while(scanf("%d",&op),op){
        if(op==1){
            scanf("%d%d",&id,&val);
            insert(root,val,id);
        }
        else if(op==2){
            temp = get_max(root);
            printf("%d\n",temp);
            del(root,_val);
        }
        else{
            temp = get_min(root);
            printf("%d\n",temp);
            del(root,_val);
        }
    }
    return 0;
}
