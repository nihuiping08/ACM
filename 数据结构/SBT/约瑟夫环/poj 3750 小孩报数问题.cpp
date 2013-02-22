/*

题目:
    约瑟夫环

*/
#include <iostream>
#include <cstdio>
#include <cstring>

using namespace std;

const int X = 100;

char str[X][20];
int n;
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
        else if(sbt[sbt[sbt[t].r].l].s>sbt[sbt[t].r].s){
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
        return;
    }
    sbt[t].s++;
    if(val<sbt[t].val)
        insert(sbt[t].l,val);
    else
        insert(sbt[t].r,val);
    maintain(t,val>=sbt[t].val);
}

int del(int &t,int val){
    if(!t)
        return 0;
    sbt[t].s--;
    if(sbt[t].val==val||(val<sbt[t].val&&!sbt[t].l)||(val>sbt[t].val&&!sbt[t].r)){
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

int find_k_min(int &t,int k){   //找到第k小
    if(k<=sbt[sbt[t].l].s)
        return find_k_min(sbt[t].l,k);
    else if(k>sbt[sbt[t].l].s+1)
        return find_k_min(sbt[t].r,k-sbt[sbt[t].l].s-1);
    else
        return sbt[t].val;
}

int main(){
    freopen("sum.in","r",stdin);
    int x,y;
    while(cin>>n){
        tol = root = 0;
        for(int i=1;i<=n;i++){
            scanf("%s",str[i]);
            insert(root,i);
        }
        scanf("%d,%d",&x,&y);
        x--;
        while(n){
            int temp = (x+y-1)%n+1;
            x = temp-1;
            temp = find_k_min(root,temp);
            printf("%s\n",str[temp]);
            del(root,temp);
            n--;
        }
    }
    return 0;
}
