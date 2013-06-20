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
#define PII pair<int,int>

/******** program ********************/

string out[] = {
"zero",
"one",
"two",
"three",
"four",
"five",
"six",
"seven",
"eight",
"nine"
};

int main(){

#ifndef ONLINE_JUDGE
	freopen("sum.in","r",stdin);
	//freopen("sum.out","w",stdout);
#endif

    string s;
    cin>>s;
    int ans = 0;
    foreach(i,s)
        ans += s[i]-'0';
    if(ans==0){
        puts( "zero" );
        return 0;
    }
    vector<int> vec;
    while(ans){
        vec.pb(ans%10);
        ans /= 10;
    }
    for(int i=vec.size()-1;i>=0;i--){
        cout<< out[ vec[i] ];
        if(i)
            cout<<" ";
    }
    puts("");

	return 0;
}
