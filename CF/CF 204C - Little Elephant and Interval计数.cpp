#include <cstdio>
#include <cstring>
#include <iostream>

using namespace std;

typedef long long ll;

ll a[20],dp[20],top;
ll ten[20];

ll qq(int l,int r){
    ll ans = 0;
    for(int i=r-1;i>=l;i--)
        ans = ans*10+a[i];
    return ans;
}

ll cal(ll n){
    if(n<10)
        return n;
    top = 0;
    ll temp = n;
    while(temp){
        a[top++] = temp%10;
        temp /= 10;
    }

    ll ans = 0;
    for(int i=1;i<top;i++)
        ans += ten[max(i-2,0)]*9;
    ans += (a[top-1]-1)*ten[top-2];

    temp = qq(1,top-1);

    //cout<<n<<" "<<temp<<endl;

    ans += temp+1;
    if(a[top-1]>a[0])
        ans--;

    return ans;
}

int main(){
    //freopen("sum.in","r",stdin);
    ll l,r;
    ten[0] = 1;
    for(int i=1;i<18;i++)
        ten[i] = ten[i-1]*10;
    while(cin>>l>>r)
        cout<<cal(r)-cal(l-1)<<endl;
    return 0;
}
