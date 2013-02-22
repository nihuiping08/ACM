/*
ST�㷨��Sparse Table��:����һ�ֶ�̬�滮�ķ�����
����СֵΪ����aΪ��Ѱ�ҵ�����.
��һ����ά����f(i,j)��¼����[i,i+2^j-1](����2^j��)�����е���Сֵ������f[i,0] = a[i];
���ԣ����������һ��(i,j)��f(i,j) = min{f(i,j-1),f(i+2^(j-1),j-1)}��ʹ�ö�̬�滮���������
����㷨�ĸ���֮���������������̬�滮�Ľ������������Ĳ�ѯ�����Ĳ�ѯЧ����O(1).
��������Ҫ������[m,n]��a����Сֵ���ҵ�һ����kʹ��2^k<n-m+1.
���������԰��������ֳ��������֣�[m,m+2^k-1]��[n-2^k+1,n].���Ƿ��֣��������������Ѿ���ʼ���õ�.
ǰ���������f(m,k)�������������f(n-2^k+1,k).
������ֻҪ���������������Сֵ���Ϳ���֪�������������Сֵ��


11.*һάRMQ ST�㷨
12.*����RMQ���� makermq(int n,int b[]) O(nlog(n))���㷨���Ӷ�
13.*dp[i][j] ��ʾ��i��i+2^j -1����С��һ��ֵ(��i��ʼ����2^j����)
14.*dp[i][j]=min{dp[i][j-1],dp[i+2^(j-1)][j-1]}
15.*��ѯRMQ rmq(int s,int v)
16.*��s-v �ֳ�����2^k������
17.*�� k=(int)log2(s-v+1)
18.*��ѯ���Ӧ��Ϊ min(dp[s][k],dp[v-2^k+1][k])
19.*/

#include <iostream>
#include <cstring>
#include <cstdio>
#include <cmath>
using namespace std;
#define X 500005
int dp[X][20],dex[X][20];
int b[X],n,m;
void make_rmq(){    //�������ֵ
    for(int i=0;i<n;i++)
        dp[i][0] = b[i];
    for(int j=1;(1<<j)<=n;j++)
        for(int i=0;i+(1<<j)-1<n;i++)
            dp[i][j] = max(dp[i][j-1],dp[i+(1<<(j-1))][j-1]);
}
int rmq(int s,int v){   //�������ֵ
    int k = (int)(log((v-s+1)*1.0)/log(2.0));
    return max(dp[s][k],dp[v-(1<<k)+1][k]);
}
void make_rmq_index(){  //�������ֵ���±�
    for(int i=0;i<n;i++)
        dex[i][0] = i;
    for(int j=1;(1<<j)<=n;j++)
        for(int i=0;i+(1<<j)-1<n;i++)
            dex[i][j] = b[dex[i][j-1]]>b[dex[i+(1<<(j-1))][j-1]]?dex[i][j-1]:dex[i+(1<<(j-1))][j-1];
}

int rmq_index(int s,int v){     //�������ֵ���±�
    int k = (int)(log((v-s+1)*1.0)/log(2.0));
    return b[dex[s][k]]>b[dex[v-(1<<k)+1][k]]?dex[s][k]:dex[v-(1<<k)+1][k];
}
int main(){
    freopen("sum.in","r",stdin);
    freopen("sum.out","w",stdout);
    int s,v;
    while(cin>>n>>m){
        for(int i=0;i<n;i++)
            scanf("%d",&b[i]);
        make_rmq();
        make_rmq_index();
        while(m--){
            scanf("%d%d",&s,&v);
            printf("%d\n",b[rmq_index(s-1,v-1)]);
        }
    }
    return 0;
}
