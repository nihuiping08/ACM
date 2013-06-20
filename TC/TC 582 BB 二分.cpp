/*

题目：
	有n种人，每种人的能力为g[i]
	有m种敌人，每种敌人有num[i]个，并且它的能力为b[i]
	当g[i]>=b[j]时，i可以打败j
	问：每种人中需要最多的最小人数需要多少个。

分析：
	二分上限然后判断合法。
	
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
#define rep1(i,n) for(int i=1;i<=n;i++)
#define REP(i,a,b) for(int i=a;i<=b;i++)
#define foreach(i,vec) for(unsigned i=0;i<vec.size();i++)
#define pb push_back
#define RD(n) scanf("%d",&n)
#define RD2(x,y) scanf("%d%d",&x,&y)
#define RD3(x,y,z) scanf("%d%d%d",&x,&y,&z)
#define All(vec) vec.begin(),vec.end()
#define MP make_pair

/******** program ********************/

class  SpaceWarDiv2{
public:

    vector<int> a;
    vector< pair<int,int> > vec;

    bool ok(int mid){
        vector<int> b,c;
        foreach(i,vec){
            b.pb(vec[i].first);
            c.pb(vec[i].second);
        }

        int res = mid;
        int x = 0;
        int len = b.size();

        foreach(i,a){
            if(x>=len)
                return true;
            if( a[i]>=b[x] ){
                if( res>=c[x] ){
                    res -= c[x];
                    i --;
                    c[x] = 0;
                    x ++;
                }else{
                    c[x] -= res;
                    res = mid;
                }
            }else
                res = mid;
        }


        return x>=len;
    }

    int minimalFatigue(vector <int> g, vector <int> e, vector <int> cc){
        int ans = 0;

        foreach(i,e){
            vec.pb( MP( e[i],cc[i] ) );
            ans += cc[i];
        }

        a = g;
        sort( All(a) );
        sort( All(vec) );

        int l = 0 , r = ans;
        ans = -1;
        while(l<=r){
            int mid = (l+r)/2;
            if( ok(mid) ){
                ans = mid;
                r = mid-1;
            }else
                l = mid+1;
        }
        return ans;
    }


};
