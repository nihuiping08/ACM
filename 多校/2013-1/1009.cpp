#include <set>
#include <map>
#include <list>
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
#define rep1(i,n) for(int i=1;i<=n;i++)
#define REP(i,a,b) for(int i=a;i<=b;i++)
#define foreach(i,vec) for(unsigned i=0;i<vec.size();i++)
#define pb push_back
#define RD(n) scanf("%d",&n)
#define RD2(x,y) scanf("%d%d",&x,&y)
#define RD3(x,y,z) scanf("%d%d%d",&x,&y,&z)
#define RD4(x,y,z,w) scanf("%d%d%d%d",&x,&y,&z,&w)
#define All(vec) vec.begin(),vec.end()
#define MP make_pair
#define PII pair<int,int>
#define PQ priority_queue
#define cmax(x,y) x = max(x,y)
#define cmin(x,y) x = min(x,y)

/******** program ********************/

const int MAXN = 1e5+5;

char s[MAXN];
int len;
bool in;
int sum;

void add(){
    int op = 1;
    for(int i=len-1;i>=0;i--){
        int t = s[i]-'0'+op;
        if(t>9){
            op = 1;
            sum = sum-s[i]+'0'+t-10;
            s[i] = char(t-10+'0');
        }
        else{
            sum ++;
            op = false;
            s[i] = char(t+'0');
            break;
        }
    }
    sum += op;
    in = in||op;
}

int main(){

#ifndef ONLINE_JUDGE
	freopen("sum.in","r",stdin);
	//freopen("sum.out","w",stdout);
#endif

    int ncase;
    RD(ncase);
    getchar();
    while(ncase--){
        gets(s);
        len = strlen(s);

        sum = 0;
        rep(i,len)
            sum += s[i]-'0';
        in = 0;
        add();
        while(sum%10)
            add();
        if(in)
            cout<<1;
        puts(s);
    }

	return 0;
}
