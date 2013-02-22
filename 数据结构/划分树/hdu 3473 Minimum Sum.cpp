/*

��Ŀ��
    ��������[l,r]���ҳ�һ��xʹ�á�|x-xi|��С

����:
    Ҫʹ�ú�ֵ��С��x��Ϊ�������λ����Ȼ�����û�������˼�룬����һ��
    lsum[depth][i]���飬��ʾ��depth���1��iλ��Ϊֹ�����ֵ���������Ԫ��
    ������Ȼ����ѯ�ʵ�ʱ�򣬼�¼��������Ԫ�غ�suml�Լ�������Ԫ�ظ�����
    ��λ��ave���������������Ԫ�غ�sumr�Լ���������Ԫ�ظ���rnum�����ֱ
    �Ӽ��㼴�ɡ�
    ans = sumr-rnum*ave+lnum*ave-suml

*/
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>

using namespace std;

const int maxn = 30;
const int maxm = 100005;
#define debug puts("here");

int data[maxn][maxm],toleft[maxn][maxm],n,m;
int sorted[maxm];
__int64 sum[maxm];
__int64 lsum[maxn][maxm];

void build(int l,int r,int depth)
{
    if(l==r)
        return;
    int mid = (r+l)>>1;
    int ls = mid-l+1;
    int lp = l,rp = mid+1;

    for(int i=l;i<=r;i++)
        if(data[depth][i]<sorted[mid])
            ls--;

    for(int i=l;i<=r;i++)
    {
        int ok = 0;
        lsum[depth][i] = lsum[depth][i-1];
        if(data[depth][i]<sorted[mid]||(data[depth][i]==sorted[mid]&&ls>0))
        {
            ok = 1;
            data[depth+1][lp++] = data[depth][i];
            if(data[depth][i]==sorted[mid])
                ls--;
            lsum[depth][i] += data[depth][i];
        }
        else
            data[depth+1][rp++] = data[depth][i];
        toleft[depth][i] = toleft[depth][i-1]+ok;
    }
    build(l,mid,depth+1);
    build(mid+1,r,depth+1);
}

__int64 suml,sumr,ans;
int lnum,rnum;

int query(int left,int right,int k,int l,int r,int depth)
{
    if(left==right)
        return data[depth][left];
    int mid = (r+l)>>1;
    int x = toleft[depth][left-1]-toleft[depth][l-1];
    int y = toleft[depth][right]-toleft[depth][l-1];
    int rx = left-l-x;
    int ry = right-l-y;
    int cnt = y-x;
    if(cnt>=k)
        return query(l+x,l+y-1,k,l,mid,depth+1);
    else
    {
        lnum += cnt;
        suml += lsum[depth][right]-lsum[depth][left-1];
        return query(mid+rx+1,mid+ry+1,k-cnt,mid+1,r,depth+1);
    }
}

int main()
{
    freopen("sum.in","r",stdin);
    int ncase,x,y,mid,cnt = 0;
    cin>>ncase;
    sum[0] = 0;
    while(ncase--)
    {
        printf("Case #%d:\n",++cnt);
        cin>>n;
        for(int i=1;i<=n;i++)
        {
            scanf("%d",&data[0][i]);
            sorted[i] = data[0][i];
            sum[i] = sum[i-1]+data[0][i];
        }
        sort(sorted+1,sorted+1+n);
        build(1,n,0);
        cin>>m;
        while(m--)
        {
            scanf("%d%d",&x,&y);
            x++;
            y++;
            mid = (y-x+2)>>1;
            suml = 0;
            lnum = 0;
            int ave = query(x,y,mid,1,n,0);
            rnum = y-x+1-lnum;
            sumr = sum[y]-sum[x-1]-suml;
            ans =  sumr+(__int64)lnum*ave-suml-(__int64)rnum*ave;

            printf("%I64d\n",ans);
        }
        puts("");
    }
    return 0;
}
