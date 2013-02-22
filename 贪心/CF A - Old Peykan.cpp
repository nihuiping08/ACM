#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <set>
#include <string>
#include <map>
#include <queue>
#include <stack>
#include <vector>
#include <algorithm>

using namespace std;

typedef long long ll;

#define debug puts("here");

const int X = 1e3+10;

int d[X],s[X],n,k;

priority_queue<int> q;

int main(){
    //freopen("sum.in","r",stdin);
    while(cin>>n>>k){
        for(int i=1;i<=n;i++)
            scanf("%d",&d[i]);
        for(int i=1;i<=n;i++)
            scanf("%d",&s[i]);
        int sum = 0,ans = 0,tot = 0;
        while(q.size())
            q.pop();
        for(int i=1;i<=n;i++){
            q.push(s[i]);
            sum += s[i];
            tot += d[i];
            ans += d[i];
            while(sum<tot){
                sum += q.top();
                ans += k;
            }
        }
        cout<<ans<<endl;
    }
    return 0;
}

