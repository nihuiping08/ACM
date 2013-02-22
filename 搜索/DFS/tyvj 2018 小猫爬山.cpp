/*

��Ŀ��
    Freda��rainbowֻ�û�Ǯ��������������ɽ�������ϵ��³����
    ������ΪW����NֻСè�������ֱ���C1��C2����CN����Ȼ��ÿ����
    ���ϵ�Сè������֮�Ͳ��ܳ���W��ÿ����һ���³���Freda��
    rainbow��Ҫ��1��Ԫ������������֪����������Ҫ��������Ԫ��
    �ܰ���NֻСè��������ɽ��

������
    ö�ٴ𰸣�dfs+��֦

*/
#include <iostream>
#include <cstdio>
#include <cstring>

using namespace std;

const int X = 20;

int a[X],n,m;
bool use[X];
int sum[X];

bool dfs(int x,int ans){
    if(x>n)
        return true;
    for(int i=1;i<=ans&&i<=x;i++){
        if(sum[i]+a[x]<=m){
            sum[i] += a[x];
            if(dfs(x+1,ans))
                return true;
            sum[i] -= a[x];
        }
    }
    return 0;
}

int main(){
    freopen("sum.in","r",stdin);
    while(cin>>n>>m){
        for(int i=1;i<=n;i++)
            scanf("%d",&a[i]);
        memset(use,false,sizeof(use));
        memset(sum,0,sizeof(sum));
        for(int i=1;i<=n;i++)
            if(dfs(1,i)){
                cout<<i<<endl;
                break;
            }
    }
    return 0;
}
