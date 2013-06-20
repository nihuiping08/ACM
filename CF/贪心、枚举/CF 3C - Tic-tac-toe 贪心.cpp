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

/******** program ********************/

string s[3];

int cnt(char op){
    int ans = 0;
    rep(i,3)
        rep(j,3)
            ans += s[i][j]==op;
    return ans;
}

bool win(char op){
    rep(i,3){
        bool ok = true;
        rep(j,3)
            ok = ok&&(s[i][j]==op);
        if(ok)  return true;
        ok = true;
        rep(j,3)
            ok = ok&&(s[j][i]==op);
        if(ok)  return true;
    }
    if(s[0][0]==op&&s[1][1]==op&&s[2][2]==op)
        return true;
    if(s[0][2]==op&&s[1][1]==op&&s[2][0]==op)
        return true;
    return false;
}

int main(){

#ifndef ONLINE_JUDGE
	freopen("sum.in","r",stdin);
	//freopen("sum.out","w",stdout);
#endif

    rep(i,3)
        cin>>s[i];

    int x = cnt('X');
    int o = cnt('0');

    bool wx = win('X');
    bool wo = win('0');

    //cout<<wx<<" "<<x<<" "<<o<<endl;

    if( x<o || x>o+1 || (wx&&wo) || (x>o&&wo) || (wx && x==o) )
        puts("illegal");
    else if(wx)
        puts("the first player won");
    else if(wo)
        puts("the second player won");
    else if(x+o==9)
        puts("draw");
    else if(x>o)
        puts("second");
    else
        puts("first");

	return 0;
}
