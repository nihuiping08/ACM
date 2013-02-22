/*

分析：
    SBT功能的应用：删除、前驱、后继
    这题就是简单的元素插入删除操作，注意一下绝对值相同的时候取较小的即可，
    还有就是每次收养所里要么都是人，要么都是宠物。
    当树种相同的时候，直接插入SBT中，当树种不一样的时候，从SBT中找到满足条
    件的前驱或者后继，更新答案后在SBT中删除该值即可

*/
#include <iostream>
#include <cstdio>
#include <cstring>

using namespace std;

const int X = 1000005;
const long long mod = 1000000;
#define debug puts("here");

int root,tol;

struct node{
    int l,r,s,val;
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
        else if(sbt[sbt[sbt[t].l].r].s>sbt[sbt[t].l].s){
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
    return del(val<sbt[t].val?sbt[t].l:sbt[t].r,val);
}

int get_pre(int t,int val){
    if(!t)  return val;
    if(val<=sbt[t].val)
        return get_pre(sbt[t].l,val);
    else{
        int temp = get_pre(sbt[t].r,val);
        return temp==val?sbt[t].val:temp;
    }
}

int get_succ(int t,int val){
    if(!t)  return val;
    if(val>=sbt[t].val)
        return get_succ(sbt[t].r,val);
    else{
        int temp = get_succ(sbt[t].l,val);
        return val==temp?sbt[t].val:temp;
    }
}

int main(){
    freopen("sum.in","r",stdin);
    int n,x,y,pre,succ,op,val;
    while(cin>>n){
        long long ans = 0;
        root = tol = 0;
        int sum  = 0,kind = 0;
        for(int i=0;i<n;i++){
            scanf("%d%d",&op,&val);
            if(!sum||kind==op){
                kind = op;
                insert(root,val);
                sum++;
            }
            else{
                pre = get_pre(root,val);
                succ = get_succ(root,val);
                x = val-pre;
                y = succ-val;
                sum--;
                if(!x){
                    ans = (ans+y)%mod;
                    del(root,succ);
                    continue;
                }
                if(!y){
                    ans = (ans+x)%mod;
                    del(root,pre);
                    continue;
                }
                if(x<=y){
                    ans = (ans+x)%mod;
                    del(root,pre);
                }
                else{
                    ans = (ans+y)%mod;
                    del(root,succ);
                }
            }
        }
        cout<<ans<<endl;
    }
    return 0;
}
