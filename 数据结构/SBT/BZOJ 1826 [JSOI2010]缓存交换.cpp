/*
 *	分析：
 *		贪心+堆或者平衡树（以下统一称为树）。越在后面，切换他是最好的。。。
 *		
 *		1.当已经在树上的时候，换掉之前已在树上的该主存块，换成当前主存块的下一个出现的位置。
 *		2.当前可用的cache足够的时候，直接插入到树中。
 *		3.每次需要切换cache的时候，都切掉距离当前位置最远的那个主存块，然后将当前的cache的
 *			下一次出现的位置更新到树上。
 *
 *		先离散化，然后使用池子法从后往前扫，这样就可以统计每个主存块下一次出现的位置，插入
 *		的时候，直接插入的是当前主存块的下一个他出现的位置
 *
 * */
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
#include <map>

using namespace std;

const int X = 100005;

#define debug puts("here");

int tot;

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
        t = ++tot;
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

int find_max(int t){
	while(sbt[t].r)
		t = sbt[t].r;
	return sbt[t].val;
}

int find(int t,int val){
	if(!t)
		return 0;
	if(sbt[t].val==val)
		return true;
	if(sbt[t].val>val)
		return find(sbt[t].l,val);
	return find(sbt[t].r,val);
}

int a[X],n;
map<int,int> ma;
int po[X],tol,Next[X];

int main(){
	int n,m;
	int inf = 100000000;
	while(cin>>n>>m){
		tot = 0;
		ma.clear();

		int cnt = 0;
		int x,y;
		int root = 0;
		tol = n;

		for(int i=1;i<=n;i++){
			scanf("%d",&a[i]);
			if(ma[a[i]]==0)	//使用map离散化
				ma[a[i]] = ++cnt;
			po[i] = ++tol;
		}

		for(int i=n;i;i--){
			x = ma[a[i]];
			Next[i] = po[x];	//池子法，从后往前扫
			po[x] = i;
		}

		cnt = 0;
		int ans = 0;
		for(int i=1;i<=n;i++){
			if(find(root,i)){	//已存在树中，直接删除后更新
				del(root,i);
				insert(root,Next[i]);
			}
			else{
				ans ++;
				if(cnt==m)		//cache数不够了，需要删除
					del(root,find_max(root));
				else			//够用的话，但是需要插入，cache已使用的数目加一
					cnt ++;
				insert(root,Next[i]);//插入当前主存块的下一个位置
			}
		}
			
		cout<<ans<<endl;
	}
	return 0;
}
