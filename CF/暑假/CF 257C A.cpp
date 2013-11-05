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
const double PI = acos(-1.0);

vector<double> vec;

int main(){

#ifndef ONLINE_JUDGE
	freopen("sum.in","r",stdin);
	//freopen("sum.out","w",stdout);
#endif

    int n;
    while(cin>>n){
        vec.clear();
        int x,y;
        rep1(i,n){
            RD2(x,y);
            double t = atan2(y,x)/PI*180;
            vec.push_back( t );
            vec.push_back( t+360 );
            //cout<<x<<" "<<y<<" "<<t<<endl;
        }

        if(n==1){
            puts("0.0000000000");
            continue;
        }
        sort( All(vec) );
        vec.pb( vec[0] );

        double ans = 0;

        rep1(i,n)
            cmax( ans,fabs(vec[i]-vec[i-1]) );
        printf("%.12lf\n",360-ans);
    }

	return 0;
}