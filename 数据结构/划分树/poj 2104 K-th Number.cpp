/*

��Ŀ��
    ��n�������ų�һ�У���m��ѯ�ʣ���ʽΪ��left right k������������[left,right]
    ��k�������Ϊ���٣�

������
    �����Ĺ��̱Ƚϼ򵥣���������[l,r]������ͨ����ԭ����������ҵ�����������
    λ��a[mid]��С��a[mid]������������������[l,mid-1]���������Ļ���������[mid,r]��
    ͬʱ�����ڵ�i����a[i]����¼��[l,i]�������ж���������������������󣬶�������
    ��������[l,mid-1]������������[mid,r]�ݹ�ļ��������Ϳ����ˡ�
    ������ʱ��Ҫע�⣬���ڱ��ֵ�ͬһ������Ԫ�أ�Ԫ�ؼ�����λ�ò��ܸı䡣

    ���ҵĹ�������Ҫ�������ȷ����Ҫ���ҵ����䡣
    �������Ϊdep���ڴ�����[L ,R]����С����[l ,r]�еĵ�kԪ�ء�
    ���ǵ��뷨�ǣ����ж�[l ,r]�е�kԪ����[L ,R]���ĸ������У�Ȼ���ҳ���Ӧ��С��
    ���k���ݹ�Ľ��в��ң�ֱ��С�����l==rΪֹ��
    ͨ��֮ǰ�ļ�¼����֪����������[L,l-1]����(toleft[dep][l-1]-toleft[dep][L-1])
    ������������
    ����Ϊx��

    ͬ������[L,r]����(toleft[dep][r]-toleft[dep][L-1])������ȥ������������Ϊy��
    ���ԣ�����֪������С����[l,r]����(y-x)������������������ô���(y-x)>=k����ô
    �����������м������ң���������������м������ҡ�

    ���ţ�������ҵ�С��������⡣
    ���������Ҫ���ҵ�������������ôС����Ӧ����[L+([L,l-1]��������������ĸ�
    ��),L+([L,r]�����ڽ����������ĸ���)-1]��������[L+x,L+y-1]��
    ��Ȼ������k���ñ䡣
    ���������Ҫ���ҵ�������������ôС����Ӧ����[mid+([L,l-1]�����н���������
    �ĸ���),mid+([L,r]��������������ĸ���)-1]��
    ������[mid+(l-L-x),mid+(r-L-y)]��
    ��Ȼ������kҪ��ȥ�������Ѿ������������ĸ�������k��Ϊk-(y-x)��

*/
#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

const int maxn = 30;
const int maxm = 100005;
#define debug puts("here");

int n,m,sorted[maxm];
int toleft[maxn][maxm];
int data[maxn][maxm];

void build(int l,int r,int depth){
    if(l==r)
        return;

    int mid = (l+r)>>1;
    int ls = mid-l+1;
    int lp = l;
    int rp = mid+1;

    for(int i=l;i<=r;i++)
        if(data[depth][i]<sorted[mid])
            ls--;

    int ok;
    for(int i=l;i<=r;i++){
        ok = 0;
        if(data[depth][i]<sorted[mid]||(data[depth][i]==sorted[mid]&&ls>0)){
            ok = 1;
            data[depth+1][lp++] = data[depth][i];
            if(data[depth][i]==sorted[mid])
                ls--;
        }
        else
            data[depth+1][rp++] = data[depth][i];
        toleft[depth][i] = toleft[depth][i-1]+ok;
    }
    build(l,mid,depth+1);
    build(mid+1,r,depth+1);
}

int ask(int left,int right,int k,int l,int r,int depth){
    if(left==right)
        return data[depth][left];
    int mid = (l+r)>>1;
    int x = toleft[depth][left-1]-toleft[depth][l-1];//λ��left��ߵķ����������е����ָ���
    int y = toleft[depth][right]-toleft[depth][l-1];//��rightΪֹλ���������ĸ���
    int rx = left-l-x;  //left��߷����������е����ָ���
    int ry = right-l-y; //��right�ұ�Ϊֹλ�������������ָ���
    int cnt = y-x;      //[left,right]�����ڷŵ��������еĸ���

    if(cnt>=k)
        return ask(l+x,l+y-1,k,l,mid,depth+1);
    else
        return ask(mid+rx+1,mid+ry+1,k-cnt,mid+1,r,depth+1);
}

int main(){
    freopen("sum.in","r",stdin);
    int l,r,k;
    while(scanf("%d%d",&n,&m)!=EOF){
        for(int i=1;i<=n;i++){
            scanf("%d",&data[0][i]);
            sorted[i] = data[0][i];
        }
        sort(sorted+1,sorted+n+1);
        build(1,n,0);
        while(m--){
            scanf("%d%d%d",&l,&r,&k);
            printf("%d\n",ask(l,r,k,1,n,0));
        }
    }
    return 0;
}
