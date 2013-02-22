/*

��Ŀ��
    ϲ�����������JS ͬѧ������������˶Լ��ܷ�����˼����һ�죬��ͻȻ�����
    һ������Ϊ���ռ��ļ��ܰ취������Ҫ���ܵ���Ϣ�ų�һȦ����Ȼ�������кܶ���
    ��ͬ�Ķ�����������ͼ�����Զ�����
    JSOI07 SOI07J OI07JS I07JSO 07JSOI 7JSOI0 �����ǰ����ַ����Ĵ�С����
    07JSOI 7JSOI0 I07JSO JSOI07 OI07JS SOI07J �������һ���ַ���I0O7SJ

������
    ���ǿ��԰������ַ����ĺ������ͬ��һ��������ַ�����Ȼ������DA�㷨���SA
    ���飬sa[i]��ʾ��i�ֵ���ĺ�׺��λ�ã�Ȼ����2*n���ȵ�sa�����У����
    sa[i]>=n��ʾ��iС�ĺ�׺��λ���ں������ϵ��ַ����У��������ǿ��԰����е�
    sa[i]<n�ĵ�n���ַ����������

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
        /// ��������ĵڶ����ؼ�������
        rep(i,m)    wc[i] = 0;
        rep(i,n)    wc[ x[y[i]] ]++;
        REP(i,1,m)  wc[i] += wc[i-1];
        for(int i=n-1;i>=0;i--) sa[ --wc[x[y[i]]] ] = y[i];
        /// ����sa��y��������µ�x����
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
