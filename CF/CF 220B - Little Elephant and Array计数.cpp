/*

��Ŀ��
    ����n������Ȼ��ѯ������[l,r]����������x���ֹ��Ĵ�������Ϊx�����ĸ���

����:
    ������Ŀn�ķ�ΧΪ1e5���������ֻ��450�������ҷ������������ȰѲ���������
    ��ɾ�����õ��µ����У�Ȼ�������dp[i][j]��Ԥ�����λ��j�г��ֹ��˱��Ϊ
    i�����ĸ���

*/
#include <cstdio>
#include <cstring>
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

const int maxn = 500;
const int maxm = 100005;

int a[maxm],b[maxm],c[maxm][2],n,m;
int dp[maxn][maxm];
vector<int> v;

int main(){
    //freopen("sum.in","r",stdin);
    while(cin>>n>>m){
        for(int i=1;i<=n;i++){
            scanf("%d",&a[i]);
            b[i] = a[i];
        }

        sort(a+1,a+n+1);
        a[0] = -1;
        v.clear();
        int cnt = 0;

        memset(c,0,sizeof(c));
        for(int i=1;i<=n;i++){
            if(a[i]!=a[i-1])
                cnt++;
            c[cnt][0] = a[i];
            c[cnt][1]++;
        }
        for(int i=1;i<=cnt;i++)
            if(c[i][1]>=c[i][0])
                v.push_back(c[i][0]);

        int len = v.size();
        memset(dp,0,sizeof(dp));
        for(int i=0;i<len;i++){
            for(int j=1;j<=n;j++)
                if(v[i]==b[j])
                    dp[i][j] = dp[i][j-1]+1;
                else
                    dp[i][j] = dp[i][j-1];
        }
        int x,y;
        while(m--){
            scanf("%d%d",&x,&y);
            int ans = 0;
            for(int i=0;i<len;i++)
                ans += (dp[i][y]-dp[i][x-1])==v[i];
            printf("%d\n",ans);
        }
    }
    return 0;
}
