/*

题目：
    Farmer John 有太多的工作要做啊！！！！！！！！为了让农场高效运转，
    他必须靠他的工作赚钱，每项工作花一个单位时间。 他的工作日从0时刻开
    始，有1000000000个单位时间（！）。在任一时刻，他都可以选择编号1~N
    的N(1 <= N <= 100000)项工作中的任意一项工作来完成。 因为他在每个单
    位时间里只能做一个工作，而每项工作又有一个截止日期，所以他很难有时
    间完成所有N个工作，虽然还是有可能。 对于第i个工作，有一个截止时间
    D_i(1 <= D_i <= 1000000000)，如果他可以完成这个工作，那么他可以获
    利P_i( 1<=P_i<=1000000000 ). 在给定的工作利润和截止时间下，FJ能够
    获得的利润最大为多少呢？答案可能会超过32位整型。

分析：
    使用heap或者优先队列实现，相对输入进行排序，然后使用优先队列对最小的
    价格出队，这样最终保留下来的所有和值就是答案

*/
#include <iostream>
#include <cstdio>
#include <cstring>
#include <queue>
#include <algorithm>
#include <map>

using namespace std;

const int X = 100005;

typedef long long ll;

#define inf (~02u>>1)

struct node{
    ll d,val;

    node(){}
    node(ll _d,ll _val):d(_d),val(_val){}

    friend bool operator < (node a,node b){
        return a.val>b.val;
    }
};

struct qq{
    ll d,val;

    qq(){}
    qq(ll _d,ll _val):d(_d),val(_val){}

    friend bool operator < (qq a,qq b){
        return a.d<b.d||(a.d==b.d&&a.val<b.val);
    }
}p[X];

priority_queue<node> q;

int main(){
    freopen("sum.in","r",stdin);
    ll n;
    while(cin>>n){
        while(q.size())
            q.pop();

        ll x,y;
        for(ll i=0;i<n;i++){
            cin>>x>>y;
            p[i].d = x;
            p[i].val = y;
        }
        sort(p,p+n);

        ll ans = 0;

        for(ll i=0;i<n;i++){
            ll d = p[i].d;
            ll val = p[i].val;
            while((int)q.size()>=d)
                q.pop();
            q.push(node(d,val));
        }
        while(q.size()){
            node pre = q.top();
            q.pop();
            ans += pre.val;
        }

        cout<<ans<<endl;
    }
    return 0;
}
