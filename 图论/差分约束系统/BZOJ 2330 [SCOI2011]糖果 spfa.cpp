/*

题目：
    幼儿园里有N个小朋友，lxhgww老师现在想要给这些小朋友们分配
    糖果，要求每个小朋友都要分到糖果。但是小朋友们也有嫉妒心，
    总是会提出一些要求，比如小明不希望小红分到的糖果比他的多，
    于是在分配糖果的时候，lxhgww需要满足小朋友们的K个要求。幼
    儿园的糖果总是有限的，lxhgww想知道他至少需要准备多少个糖
    果，才能使得每个小朋友都能够分到糖果，并且满足小朋友们所
    有的要求。
    Input

    输入的第一行是两个整数N，K。
    接下来K行，表示这些点需要满足的关系，每行3个数字，X，A，B。
    如果X=1， 表示第A个小朋友分到的糖果必须和第B个小朋友分到的
    糖果一样多；
    如果X=2， 表示第A个小朋友分到的糖果必须少于第B个小朋友分到
    的糖果；
    如果X=3， 表示第A个小朋友分到的糖果必须不少于第B个小朋友分
    到的糖果；
    如果X=4， 表示第A个小朋友分到的糖果必须多于第B个小朋友分到
    的糖果；
    如果X=5， 表示第A个小朋友分到的糖果必须不多于第B个小朋友分
    到的糖果；

分析：
    差分约束，若是按照平常的建图的话，会有负边出现，所以用spfa
    求的时候转化为求最长路

*/
#include <iostream>
#include <cstdio>
#include <cstring>
#include <queue>

using namespace std;

const int X = 100005;

int po[X],tol;
int id[X],dis[X];
bool use[X];
int n,m;

struct node{
    int y,w,next;
}edge[X<<1];


long long spfa(){
    queue<int> q;
    for(int i=1;i<=n;i++){
        id[i] = dis[i] = 1;
        use[i] = true;
        q.push(i);
    }
    while(q.size()){
        int x = q.front();
        q.pop();
        use[x] = false;
        for(int i=po[x];i;i=edge[i].next){
            int y = edge[i].y;
            if(dis[x]+edge[i].w>dis[y]){
                dis[y] = dis[x]+edge[i].w;
                if(++id[y]>n)
                    return -1;
                if(!use[y]){
                    use[y] = true;
                    q.push(y);
                }
            }
        }
    }
    long long ans = 0;
    for(int i=1;i<=n;i++)
        ans += dis[i];
    return ans;
}

void add(int x,int y,int w){
    edge[++tol].y = y;
    edge[tol].w = w;
    edge[tol].next = po[x];
    po[x] = tol;
}

bool build(){
    memset(po,0,sizeof(po));
    tol = 0;
    int op,x,y;
    while(m--){
        scanf("%d%d%d",&op,&x,&y);
        if(op==1){
            if(x!=y){
                add(x,y,0);
                add(y,x,0);
            }
        }
        else if(op==2){
            if(x==y)
                return false;
            add(x,y,1);
        }
        else if(op==3){
            if(x!=y)
                add(y,x,0);
        }
        else if(op==4){
            if(x==y)
                return false;
            add(y,x,1);
        }
        else if(op==5){
            if(x!=y)
                add(x,y,0);
        }
    }
    return true;
}

int main(){
    freopen("sum.in","r",stdin);
    cin>>n>>m;
    if(build())
        cout<<spfa()<<endl;
    else
        puts("-1");
    return 0;
}
