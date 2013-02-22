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
    avl[t].h = max(avl[avl[t].l].h,avl[avl[t].r].h)+(t>0);
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

void maintain(int &t){
    int lh,rh;
    if(avl[avl[t].l].h>avl[avl[t].r].h+1){
        lh = avl[avl[avl[t].l].l].h;
        rh = avl[avl[avl[t].l].r].h;
        if(lh>=rh)
            right_rotate(t);
        else{
            left_rotate(avl[t].l);
            right_rotate(t);
        }
    }
    if(avl[avl[t].r].h>avl[avl[t].l].h){
        lh = avl[avl[avl[t].r].l].h;
        rh = avl[avl[avl[t].r].r].h;
        if(rh>=lh)
            left_rotate(t);
        else{
            right_rotate(avl[t].r);
            left_rotate(t);
        }
    }
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
    maintain(t);
    update(t);
}

void del(int &t,int val){
    if(!t)  return;
    if(avl[t].val==val){
        if(avl[t].l&&avl[t].r){
            int k = avl[t].r;
            while(avl[k].l)
                k = avl[k].l;
            avl[t].val = avl[k].val;
            avl[t].id = avl[k].id;
            del(avl[t].r,avl[k].val);
            maintain(t);
        }
        else if(avl[t].l){
            avl[t].val = avl[avl[t].l].val;
            avl[t].id = avl[avl[t].l].id;
            avl[t].l = 0;
        }
        else if(avl[t].r){
            avl[t].val = avl[avl[t].r].val;
            avl[t].id = avl[avl[t].r].id;
            avl[t].r = 0;
        }
        else
            t = 0;
        update(t);
        return;
    }
    else if(val<avl[t].val)
        del(avl[t].l,val);
    else
        del(avl[t].r,val);
    maintain(t);
    update(t);
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
    freopen("sum.in","r",stdin);
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
