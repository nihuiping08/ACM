/*

题目：
    从1到n有n个数，在i点有数a[i]，现在从x点开始，在x上能够往后跳到x+a[i]
    的位置上，现在问从i出发，经过多少次使得它跳到n后面

分析：
    我们可以分块数组来做。
    sz[x]表示在x之后并且跟x同一个块中的元素个数。
    po[x]表示从x位置上，能够往后一直跳，直到跳到另一个块为止。
    fa[x]表示x所在的固定块的编号。

    1.首先，我们先固定fa数组。
    2.然后我们从后往前，确定每个位置的po值以及sz值
    3.询问的时候，我们从x顺着po[x]往后找，直到过了n为止
    4.修改的时候，我们需要把弹力系数a[x]修改，然后沿着x往前面修改po,sz
    值，直到块的编号不同就及时跳出。

    为什么第四步的时候需要修改po,sz？我们知道po[x]值是指从x往后跳，直到
    块的编号不同就跳出。所以我们修改了a[x]之后，由于po[x]的值不同了，所
    以前面相同的块中的元素同样需要做相应修改。

    最后，由于询问、修改的操作都是sqrt(n)级别的。所以总的时间复杂度为
    m*sqrt(n)

*/
#include <set>
#include <map>
#include <cmath>
#include <queue>
#include <stack>
#include <string>
#include <vector>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>

using namespace std;

typedef long long ll;
typedef unsigned long long ull;

#define debug puts("here")
#define rep(i,n) for(int i=0;i<n;i++)
#define REP(i,a,b) for(int i=a;i<b;i++)
#define foreach(i,vec) for(unsigned i=0;i<vec.size();i++)
#define pb push_back
#define RD(n) scanf("%d",&n)

const int MAXN = 2e5+5;

int po[MAXN],fa[MAXN],sz[MAXN];
int a[MAXN];
int n,m;

void make(int i){
    int j = min(i+a[i],n);
    if(fa[i]==fa[j]){
        sz[i] = sz[j]+1;
        po[i] = po[j];
    }
    else{
        po[i] = j;
        sz[i] = 1;
    }
}

int ask(int i){
    int ans = 0;
    for(int j=i;j<n;j=po[j])
        ans += sz[j];
    return ans;
}

void change(int x,int y){
    a[x] = y;
    for(int i=x;i>=0;i--)
        if(fa[i]==fa[x])
            make(i);
        else
            break;
}

int main(){

#ifndef ONLINE_JUDGE
	freopen("sum.in","r",stdin);
	//freopen("sum.out","w",stdout);
#endif

    RD(n);
    int len = (int)sqrt(n*1.0);
    rep(i,n){
        RD(a[i]);
        fa[i] = i/len+1;
    }
    for(int i=n-1;i>=0;i--)
        make(i);

    int x,y,op;
    RD(m);
    while(m--){
        scanf("%d%d",&op,&x);
        if(op==1)
            printf("%d\n",ask(x));
        else{
            RD(y);
            change(x,y);
        }
    }

	return 0;
}
