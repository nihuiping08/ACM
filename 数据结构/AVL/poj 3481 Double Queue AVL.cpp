#include <cstdio>
#include <cstring>
#include <iostream>

using namespace std;

const int X = 1e6+10;

int tol,root;

struct node{
    int l,r,h,val,id;
    void init(int _val,int _id){
        val = _val;
        id = _id;
        l = r = 0;
        h = 1;
    }
}avl[X];

void update(int t){
    avl[t].h = max(avl[avl[t].l].h,avl[avl[t].r].h)+(t>1);
}

void left_rotate(int &t){
    int k = avl[t].r;
    avl[t].r = avl[k].l;
    avl[k].l = t;
    update(t);
    update(k);
    t = k;
}

void right_rotate(int &t){
    int k = avl[t].l;
    avl[t].l = avl[k].r;
    avl[k].r = t;
    update(t);
    update(k);
    t = k;
}

void maintain(int &t,bool ok){
    if(!ok){
        if(avl[avl[avl[t].l].l].h>avl[avl[t].r].h+1)
            right_rotate(t);
        else if(avl[avl[avl[t].l].r].h>avl[avl[t].r].h+1){
            left_rotate(avl[t].l);
            right_rotate(t);
        }
        else    return;
    }
    else{
        if(avl[avl[avl[t].r].r].h>avl[avl[t].l].h+1)
            left_rotate(t);
        else if(avl[avl[avl[t].r].l].h>avl[avl[t].l].h+1){
            right_rotate(avl[t].r);
            left_rotate(t);
        }
        else    return;
    }
    maintain(avl[t].l,0);
    maintain(avl[t].r,1);
    maintain(t,0);
    maintain(t,1);
}

void insert(int &t,int val,int id){
    if(!t){
        t = ++tol;
        avl[t].init(val,id);
        return;
    }
    if(val<avl[t].val)
        insert(avl[t].l,val,id);
    else
        insert(avl[t].r,val,id);
    maintain(t,val>=avl[t].val);
    update(t);
}

int del(int &t,int val){
    if(!t)  return 0;
    if(val==avl[t].val||(val<avl[t].val&&!avl[t].l)||(val>avl[t].val&&!avl[t].r)){
        if(avl[t].l&&avl[t].r){
            int pos = del(avl[t].l,val+1);
            avl[t].id = avl[pos].id;
            avl[t].val = avl[pos].val;
            maintain(t,val>=avl[t].val);
            update(t);
            return pos;
        }
        else{
            int pos = t;
            t = avl[t].l+avl[t].r;
            maintain(t,val>=avl[t].val);
            update(t);
            return pos;
        }
    }
    else{
        int pos = del(val<avl[t].val?avl[t].l:avl[t].r,val);
        maintain(t,val>=avl[t].val);
        update(t);
        return pos;
    }
}

int ans;

int get_min(int t){
    while(avl[t].l)
        t = avl[t].l;
    ans = avl[t].id;
    return avl[t].val;
}

int get_max(int t){
    while(avl[t].r)
        t = avl[t].r;
    ans = avl[t].id;
    return avl[t].val;
}

int main(){
    int op,val,id;
    while(scanf("%d",&op),op){
        if(op==1){
            scanf("%d%d",&id,&val);
            insert(root,val,id);
        }
        else if(op==2){
            val = get_max(root);
            del(root,val);
            printf("%d\n",ans);
        }
        else{
            val = get_min(root);
            del(root,val);
            printf("%d\n",ans);
        }
    }
    return 0;
}
