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

vector< pair<int,int> > vec[3];
int n,v;
int len1,len2;

int ok(int x,int y){
    if(x<len1){
        if(v==1)
            return true;
        if(y<len2){
            if(vec[1][x].first >= vec[2][y].first)
                return true;
            else if(x+1<len1){
                if(vec[1][x].first+vec[1][x+1].first>vec[2][y].first)
                    return true;
                else
                    return false;
            }else
                return false;
        }else
            return true;
    }else{
        if(v>1) return false;
        else    return -1;
    }
    return -2;
}

int main(){

#ifndef ONLINE_JUDGE
	freopen("sum.in","r",stdin);
	//freopen("sum.out","w",stdout);
#endif

    while(~RD2(n,v)){
        int op,x,y;

        vec[0].clear();
        vec[1].clear();
        vec[2].clear();

        rep1(i,n){
            RD2(op,x);
            vec[op].pb( MP(x,i) );
        }

        sort( All(vec[1]) );
        reverse( All(vec[1]) );
        sort( All(vec[2]) );
        reverse( All(vec[2]) );

        int ans = 0;
        x = y = 0;

        len1 = vec[1].size();
        len2 = vec[2].size();

        while( v && (x<len1||y<len2) ){
            int id = ok(x,y);
            if(id==-1)
                break;
            else if(id==-2){
                debug;
                return 0;
            }else if( id==1 ){
                v --;
                ans += vec[1][x].first;
                vec[0].pb( MP(vec[1][x].second,0) );
                x ++;
            }else{
                v -= 2;
                ans += vec[2][y].first;
                vec[0].pb( MP(vec[2][y].second,0) );
                y ++;
            }
        }
        cout<<ans<<endl;
        foreach(i,vec[0])
            printf("%d ",vec[0][i].first);
        puts("");
    }

	return 0;
}
