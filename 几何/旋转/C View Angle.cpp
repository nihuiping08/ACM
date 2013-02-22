/*

题目：
    给出n个点，问从原点出发的角度最少多大能够把所有的点看完。

分析：
    极角序。每个点可能顺时针或者逆时针跟另一个点组成的角最小，所以我们添加的
    时候多加上绕了一圈之后的该点。

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

#define debug puts("here");

vector<double> vec;

int main(){

#ifndef ONLINE_JUDGE
	freopen("sum.in","r",stdin);
#endif

    int n;
    while(cin>>n){
        double x,y;
        vec.clear();
        for(int i=0;i<n;i++){
            scanf("%lf%lf",&x,&y);
            vec.push_back(atan2(y,x));
            vec.push_back(atan2(y,x)+2*M_PI);
        }
        sort(vec.begin(),vec.end());
        double ans = 0;
        n = vec.size();
        for(int i=1;i<n;i++)
            ans = max(ans,vec[i]-vec[i-1]);
        ans = 360-ans/M_PI*180;
        printf("%.6lf\n",ans);
    }

	return 0;
}
