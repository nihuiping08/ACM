/*

��Ŀ��
    ������

������
    ���ݳ˷�ԭ��n��������Ϊ(p1+1)*(p2+1)*...
    ���Կ���ʹ�õݹ����ʽ�ҵ�������n�ķ�������������Ҫʹ����Ŀ
    ��࣬���Ա���ʹ������������С����Ŀ��ࣨ������һ��֦ʹ��
    �������죩��

*/
#include <iostream>
#include <cstdio>
#include <cstring>

using namespace std;

typedef long long ll;

#define debug puts("here");

ll n;
ll p[] = {1,2,3,5,7,11,13,17,19,23,29};

ll ans,maxsum;

void dfs(ll x,ll pos,ll sum,ll limit){
    if(pos>10)
        return;
    if(sum>maxsum){
        maxsum = sum;
        ans = x;
    }
    else if(sum==maxsum)
        ans = min(ans,x);
    ll temp = x;
    for(ll i=1;i<=limit;i++){
        if(temp*p[pos]>n)
            return;
        temp *= p[pos];
        dfs(temp,pos+1,sum*(i+1),i);
    }
}

int main(){
    freopen("sum.in","r",stdin);
    while(cin>>n){
        maxsum = 0;
        ans = 0;
        dfs(1,1,1,35);
        cout<<ans<<endl;
    }

    return 0;
}
