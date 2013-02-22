/*

��Ŀ��
    ����n���������ĸ߶Ⱦ�Ϊh����ÿ�����Ϲ���һЩƻ����һֻè
    ���Դ�һ����������һ�������������������������Ǹ߶���
    ��d����è�ܴ�����һ��������������è�ܹ��õ������ƻ����Ŀ

������
    DP������ѭ����DPת�Ʒ��̱ȽϺ��룬
    dp[i][j] = max( max(dp[k][j-d])),dp[i][j-1])+map[i][j]
    �������ݱȽϴ�����ѭ���ᳬʱ�����Ե�Ҫѹ��������ѭ��
    �ö��������best��¼ÿ��߶ȵ����Ž⣬��һάdp��¼��ǰ
    λ�õ����Ž⣬��ת�Ʒ��̿���дΪ
    dp[i] = max(dp[i],max(best[j-d])) + map[i][j]
    best[j] = max(dp[i])

*/
#include <cstdio>
#include <cstring>
#include <iostream>

using namespace std;

const int X = 2005;

int map[X][X];
int dp[X],best[X],n,h,d;

int main(){
    freopen("sum.in","r",stdin);
    int x,y;
    while(cin>>n>>h>>d){
        memset(dp,0,sizeof(dp));
        memset(best,0,sizeof(best));
        memset(map,0,sizeof(map));
        for(int i=1;i<=n;i++){
            scanf("%d",&y);
            while(y--){
                scanf("%d",&x);
                map[i][x] ++;
            }
        }
        for(int j=1;j<=h;j++){
            for(int i=1;i<=n;i++){
                if(j>=d)
                    dp[i] = max(dp[i],best[j-d])+map[i][j];
                else
                    dp[i] = dp[i]+map[i][j];
                best[j] = max(best[j],dp[i]);
            }
        }
        cout<<best[h]<<endl;
    }
    return 0;
}
