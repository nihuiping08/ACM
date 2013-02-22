/*

题目：
    第一行有两个非负整数n和min。n表示下面有多少条命令，min表示工资下界。
    接下来的n行，每行表示一条命令。命令可以是以下四种之一：
    I命令(I k): 新建一个工资档案，初始工资为k。如果某员工的初始工资低
    于工资下界，他将立刻离开公司。
    A命令(A k): 把每位员工的工资加上k
    S命令(S k): 把每位员工的工资扣除k
    F命令(F k): 查询第k多的工资
    一旦某位员工发现自己的工资已经低于了合同规定的工资下界，他就会立刻
    气愤地离开公司，并且再也不会回来了。问现在工资第k多的员工拿多少工资

分析：
    像线段树的lazy标记一样，设置标记delay表示当前为止已经增加了的工资，
    若重新来了一名新员工的话，得要把他的工资减掉delay，表示他现在的工资
    （因为在delete操作中是SBT中的val值加上delay）。其他的基本如同SBT求
    第K大了。

*/
#include <iostream>
#include <cstdio>
#include <cstring>

using namespace std;

const int X = 100005;

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

void Delete(int &t,int delay,int min_val){
    if(!t)
        return;
    if(sbt[t].val+delay<min_val){
        t = sbt[t].r;
        Delete(t,delay,min_val);
    }
    else{
        Delete(sbt[t].l,delay,min_val);
        sbt[t].s = sbt[sbt[t].l].s+sbt[sbt[t].r].s+1;
    }
}

int find_k(int &t,int k){
    if(k<=sbt[sbt[t].l].s)
        return find_k(sbt[t].l,k);
    else if(k>sbt[sbt[t].l].s+1)
        return find_k(sbt[t].r,k-sbt[sbt[t].l].s-1);
    else
        return sbt[t].val;
}

int find_k_max(int &t,int k){
    if(k<=sbt[sbt[t].r].s)
        return find_k_max(sbt[t].r,k);
    else if(k>sbt[sbt[t].r].s+1)
        return find_k_max(sbt[t].l,k-sbt[sbt[t].r].s-1);
    else
        return sbt[t].val;
}

int get_rank(int &t,int val){
    if(val<sbt[t].val)
        return get_rank(sbt[t].l,val);
    else if(val>sbt[t].val)
        return get_rank(sbt[t].r,val)+sbt[sbt[t].l].s+1;
    else
        return sbt[sbt[t].l].s+1;
}

void inorder(int &t){
    if(!t)
        return;
    inorder(sbt[t].l);
    printf("%d\n",sbt[t].val);
    inorder(sbt[t].r);
}

int get_min(int &t){
    while(sbt[t].l)
        t = sbt[t].l;
    return t;
}

int get_max(int &t){
    while(sbt[t].r)
        t = sbt[t].r;
    return t;
}

int main(){
    freopen("sum.in","r",stdin);
    int x;
    int n,min_val,delay;
    char str[5];
    int ncase;
    cin>>ncase;
    while(ncase--){
        cin>>n>>min_val;
        root = delay = tol = 0;
        while(n--){
            scanf("%s%d",str,&x);
            if(str[0]=='I'){
                if(x<min_val)
                    continue;
                insert(root,x-delay);
            }
            else if(str[0]=='A')
                delay += x;
            else if(str[0]=='S'){
                delay -= x;
                Delete(root,delay,min_val);
            }
            else
                printf("%d\n",sbt[root].s>=x?find_k_max(root,x)+delay:-1);
        }
        printf("%d\n",tol-sbt[root].s);
    }
    return 0;
}
