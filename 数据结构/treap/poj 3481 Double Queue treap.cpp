#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstdlib>

using namespace std;

const int maxn = 1e6+5;
#define debug puts("here");
const int inf = 1e9;

struct node{
    int val,id;
    int fix;
    node *l,*r;
    node(){
        l = r = 0;
        val = id = inf;
    }
    node(int _val,int _id):val(_val),id(_id){
        fix = rand();
        l = r = 0;
    }
};

void left_rotate(node *&t){
    node *p = t->r;
    t->r = p->l;
    p->l = t;
    t = p;
}

void right_rotate(node *&t){
    node *p = t->l;
    t->l = p->r;
    p->r = t;
    t = p;
}

void insert(node *&t,int val,int id){
    if(!t){
        t = new node(val,id);
        return;
    }
    else if(val <= t->val){
        insert(t->l,val,id);
        if(t->l->fix < t->fix)
            right_rotate(t);
    }
    else{
        insert(t->r,val,id);
        if(t->r->fix < t->fix)
            left_rotate(t);
    }
}

void del(node *&t,int val){
    if(val==t->val){
        if(!t->l||!t->r){
            node *p = t;
            if(!t->l)
                t = t->r;
            else
                t = t->l;
            delete p;
        }
        else{
            if(t->l->fix > t->r->fix){
                right_rotate(t);
                del(t->r,val);
            }
            else{
                left_rotate(t);
                del(t->l,val);
            }
        }
    }
    else if(val<t->val)
        del(t->l,val);
    else
        del(t->r,val);
}

int ans;

int get_max(node *t){
    while(t->r)
        t = t->r;
    ans = t->id;
    return t->val;
}

int get_min(node *t){
    while(t->l)
        t = t->l;
    ans = t->id;
    return t->val;
}

int main(){
    freopen("sum.in","r",stdin);
    int op,val,id;
    while(cin>>op){
        node *treap = NULL;
        int n = 0;
        while(op){
            ans = 0;
            //cout<<"size = "<<n<<endl;
            if(op==1){
                n++;
                //debug;
                scanf("%d%d",&id,&val);
                scanf("%d",&op);
                insert(treap,val,id);
            }
            else if(op==2){
                scanf("%d",&op);
                if(!n){
                    puts("0");
                    continue;
                }
                n--;
                val = get_max(treap);
                del(treap,val);
                printf("%d\n",ans);
            }
            else{
                scanf("%d",&op);
                if(!n){
                    puts("0");
                    continue;
                }
                n--;
                val = get_min(treap);
                del(treap,val);
                printf("%d\n",ans);
            }
        }
    }
    return 0;
}
