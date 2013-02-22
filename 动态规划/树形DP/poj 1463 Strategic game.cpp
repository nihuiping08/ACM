/*

��С�߼��������⡣�����ĸ�ڵ㲻����ʿ�����أ����ӱ���ȫ�ð���ʿ�����ء�
����ĸ�ڵ㰲�ŵĻ������ӽڵ���԰��ţ����Բ����ţ�����״̬ת�Ʒ���Ϊ
dp[i][0] += dp[j][1]
dp[i][1] += min(dp[j][0],dp[j][1]); //j��i�Ķ���

*/
#include <cstdio>
#include <iostream>
#include <cstring>
#include <vector>
using namespace std;
#define MAXN 1505
int n,dp[MAXN][2];
vector<int> a[MAXN];
void dfs(int u,int pre){
    int size = a[u].size(),v;
    for(int i=0;i<size;i++){
        v = a[u][i];
        if(v!=pre){
            dfs(v,u);
            dp[u][0] += dp[v][1];
            dp[u][1] += min(dp[v][0],dp[v][1]);
        }
    }
    a[u].clear();
}
int main(){
    freopen("sum.in","r",stdin);
    freopen("sum.out","w",stdout);
    int x,y,z;
    while(cin>>n){
        for(int i=0;i<n;i++){
            scanf("%d:(%d)",&x,&z);
            while(z--){
                scanf("%d",&y);
                a[x].push_back(y);
                a[y].push_back(x);
            }
            dp[x][0] = 0;
            dp[x][1] = 1;
        }
        dfs(0,0);
        printf("%d\n",min(dp[0][0],dp[0][1]));
    }
    return 0;
}
