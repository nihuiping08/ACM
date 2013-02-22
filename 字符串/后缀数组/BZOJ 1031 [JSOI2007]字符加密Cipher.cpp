/*

题目：
    喜欢钻研问题的JS 同学，最近又迷上了对加密方法的思考。一天，他突然想出了
    一种他认为是终极的加密办法：把需要加密的信息排成一圈，显然，它们有很多种
    不同的读法。例如下图，可以读作：
    JSOI07 SOI07J OI07JS I07JSO 07JSOI 7JSOI0 把它们按照字符串的大小排序：
    07JSOI 7JSOI0 I07JSO JSOI07 OI07JS SOI07J 读出最后一列字符：I0O7SJ

分析：
    我们可以把输入字符串的后面接上同样一个输入的字符串，然后利用DA算法求出SA
    数组，sa[i]表示第i字典序的后缀的位置，然后在2*n长度的sa数组中，如果
    sa[i]>=n表示第i小的后缀的位置在后面多接上的字符串中，所以我们可以把所有的
    sa[i]<n的第n个字符输出就行了

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

int sa[MAXN],wa[MAXN],wb[MAXN],wc[MAXN];
int height[MAXN],Rank[MAXN];
int n,m;
char s[MAXN];

void DA(){
    int *x = wa , *y = wb;
    rep(i,m)    wc[i] = 0;
    rep(i,n)    wc[ x[i] = s[i] ] ++;
    REP(i,1,m)  wc[i] += wc[i-1];
    for(int i=n-1;i>=0;i--) sa[ --wc[x[i]] ] = i;

    for(int k=1;k<=n;k<<=1){
        int cnt = 0;
        REP(i,n-k,n)    y[cnt++] = i;
        rep(i,n)    if(sa[i]>=k)    y[cnt++] = sa[i]-k;
        /// 基数排序的第二个关键字排序
        rep(i,m)    wc[i] = 0;
        rep(i,n)    wc[ x[y[i]] ]++;
        REP(i,1,m)  wc[i] += wc[i-1];
        for(int i=n-1;i>=0;i--) sa[ --wc[x[y[i]]] ] = y[i];
        /// 根据sa和y数组计算新的x数组
        swap(x,y);
        cnt = 1;
        x[sa[0]] = 0;
        REP(i,1,n){
            int tmp = y[sa[i-1]]==y[sa[i]] && y[sa[i-1]+k]==y[sa[i]+k];
            x[sa[i]] = tmp?cnt-1:cnt++;
        }

        if(cnt>=n)  break;
        m = cnt;
    }
}

int main(){

#ifndef ONLINE_JUDGE
	freopen("sum.in","r",stdin);
#endif

    m = 256;
    gets(s);
    n = strlen(s);
    rep(i,n) s[i+n] = s[i];
    n = 2*n-1;
    s[n++] = 0;
    DA();
    m = n>>1;
    rep(i,n)
        if(sa[i]<m)
            putchar(s[sa[i]+m-1]);
    puts("");

	return 0;
}
