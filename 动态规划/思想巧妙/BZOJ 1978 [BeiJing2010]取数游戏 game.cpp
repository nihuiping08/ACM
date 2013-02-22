/*

��Ŀ��
    ����n����������ѡ��һ����ʹ��ai,aj��gcd>=m��j>i��ʹ��������
    ���

������
    DP����������ôת�Ʒ����أ�
    dp[i]��ʾ����i��β�ĳ��ȣ���������һ�������¼ÿ������������
    �ӣ�ʵ��ת�Ʒ��̣�dp[a[i]] = max(dp[a[i]]])+1

*/
#include <cstdio>
#include <cstring>
#include <iostream>

using namespace std;

const int maxm = 1e6+10;
const int maxn = 1005;
const int inf = ~0U>>1;

int n,m;
int dp[maxm],a[maxm];

int main(){
    freopen("sum.in","r",stdin);
    while(cin>>n>>m){
        memset(dp,0,sizeof(dp));

        for(int j=0;j<n;j++){
            int x,top = 0;
            int temp = 0;
            scanf("%d",&x);
            for(int i=1;i*i<=x;i++)
                if(x%i==0){
                    if(i>=m)
                        a[top++] = i;
                    if(x/i>=m)
                        a[top++] = x/i;
                }
            for(int i=0;i<top;i++)
                temp = max(temp,dp[a[i]]);
            temp ++;
            for(int i=0;i<top;i++)
                dp[a[i]] = temp;
        }
        int ans = 0;
        for(int i=0;i<maxm;i++)
            ans = max(ans,dp[i]);
        cout<<ans<<endl;
    }
    return 0;
}
