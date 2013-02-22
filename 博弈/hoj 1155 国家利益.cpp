/*

²©ŞÄÂÛÌâ

*/
#include <iostream>
#include <cstdio>
using namespace std;
int main()
{
    freopen("sum.in","r",stdin);
    freopen("sum.out","w",stdout);
    int n,m;
    while(cin>>n>>m){
        int t = (n-1)>>1;
        int ans = max(m-t,0);
        cout<<ans<<endl;
    }
    return 0;
}
