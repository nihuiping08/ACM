/*

��Ŀ��
    Farmer John ��̫��Ĺ���Ҫ��������������������Ϊ����ũ����Ч��ת��
    �����뿿���Ĺ���׬Ǯ��ÿ�����һ����λʱ�䡣 ���Ĺ����մ�0ʱ�̿�
    ʼ����1000000000����λʱ�䣨����������һʱ�̣���������ѡ����1~N
    ��N(1 <= N <= 100000)����е�����һ�������ɡ� ��Ϊ����ÿ����
    λʱ����ֻ����һ����������ÿ�������һ����ֹ���ڣ�������������ʱ
    ���������N����������Ȼ�����п��ܡ� ���ڵ�i����������һ����ֹʱ��
    D_i(1 <= D_i <= 1000000000)�������������������������ô�����Ի�
    ��P_i( 1<=P_i<=1000000000 ). �ڸ����Ĺ�������ͽ�ֹʱ���£�FJ�ܹ�
    ��õ��������Ϊ�����أ��𰸿��ܻᳬ��32λ���͡�

������
    ʹ��heap�������ȶ���ʵ�֣���������������Ȼ��ʹ�����ȶ��ж���С��
    �۸���ӣ��������ձ������������к�ֵ���Ǵ�

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
