#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <vector>
#include <map>
#include <stack>
#include <queue>

using namespace std;

#define debug puts("here")
#define rep(i,n) for (int i = 0; i < (n); ++i)
#define rep1(i,n) for (int i = 1; i <= (n); ++i)
#define REP(i,st,ed) for (int i = (st); i <= (ed); ++i)
#define RD(x) scanf("%d", &x)
#define RD2(x,y) scanf("%d%d", &x, &y)
#define RD3(x,y,z) scanf("%d%d%d", &x, &y, &z)
#define pb push_back
#define mp make_pair
typedef long long ll;

long long f[5500][13];

long long getnum(int a, int b) {
    if(!a||!b)return 1;
    long long ret = 0;
    int w = 0, len = 0, w2 = 0;
    while(a) {
        w += (a%10)*(1<<len);
        ++len;
        a /= 10;
    }
    int s[12];
    len = 0;
    while(b) {
        w2 += (b%10)*(1<<len);
        s[++len] = b%10;
        b/=10;
    }
    w2 -= s[1];
    for (int i = 0; i <= s[1]; ++i)
        if (w>=w2+i)
            ++ret;
    for (int l = len; l; --l) {
        for (int i = 0; i < s[l]; ++i)
            if (w-(1<<(l-1))*i>=0)
                ret += f[w-(1<<(l-1))*i][l-1];
            else break;
        if (w>=(1<<(l-1))*s[l]) w -= (1<<(l-1))*s[l];
        else break;
    }
    return ret;
}

int main() {
#ifndef ONLINE_JUDGE
    freopen("sum.in", "r", stdin);
    // freopen("cf.out", "w", stdout);
#endif
    int T;
    scanf("%d", &T);
    for (int i = 0; i <= 9; ++i) f[i][1] = i+1;
    for (int i = 10; i <= 5500; ++i) f[i][1] = 10;

    for (int l = 2; l <= 9; ++l)
        for (int i = 0; i <= 5500; ++i)
            for (int j = 0; j <= 9; ++j)
                if (i-(1<<(l-1))*j>=0)
                    f[i][l] += f[i-(1<<(l-1))*j][l-1];

    for (int ncase = 1; ncase <= T; ++ncase) {
        int a, b;
        scanf("%d%d", &a, &b);
        printf("Case #%d: %I64d\n",ncase,getnum(a,b));
    }
    return 0;
}
