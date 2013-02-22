/*

题目：
    约瑟夫环问题，问最后只剩下的元素

*/
#include <cstdio>
#include <cstring>
#include <iostream>

using namespace std;

const int X = 100005;
#define debug puts("here");

int tol,root;

struct node{
    int l,r,val,s;
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

int del(int &t,int val){
    if(!t)  return 0;
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

int find_k_min(int &t,int k){
    if(k<=sbt[sbt[t].l].s)
        return find_k_min(sbt[t].l,k);
    else if(k>sbt[sbt[t].l].s+1)
        return find_k_min(sbt[t].r,k-sbt[sbt[t].l].s-1);
    return sbt[t].val;
}

int find_k_max(int &t,int k){
    if(k<sbt[sbt[t].r].s)
        return find_k_max(sbt[t].r,k);
    else if(k>sbt[sbt[t].r].s+1)
        return find_k_max(sbt[t].l,k-sbt[sbt[t].r].s-1);
    return sbt[t].val;
}

int get_pre(int &t,int val){
    if(!t)  return 0;
    if(val<sbt[t].val)
        return get_pre(sbt[t].l,val);
    else
        return max(sbt[t].val,get_pre(sbt[t].r,val));
}

int get_next(int &t,int val){
    if(!t)  return 0;
    if(val>sbt[t].val)
        return get_next(sbt[t].r,val);
    else
        return min(sbt[t].val,get_next(sbt[t].l,val));
}

int get_rank(int &t,int val){
    if(val<sbt[t].val)
        return get_rank(sbt[t].l,val);
    else if(val>sbt[t].val)
        return get_rank(sbt[t].r,val)+sbt[sbt[t].l].s+1;
    else
        return sbt[sbt[t].l].s+1;
}

int main(){
    freopen("sum.in","r",stdin);
    int n,k,s;
    while(cin>>n>>k>>s,n||k||s){
        if(n==1){
            puts("1");
            continue;
        }
        root = tol = 0;
        for(int i=1;i<=n;i++)
            insert(root,i);
        int pos = s+n-k;
        while(n){
            int temp = (pos+k-1)%n+1;
            pos = temp-1;
            temp = find_k_min(root,temp);
            del(root,temp);
            if(n==2){
                printf("%d\n",find_k_min(root,1));
                break;
            }
            n--;
        }
    }
    return 0;
}
