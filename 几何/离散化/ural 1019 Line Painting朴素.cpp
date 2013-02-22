/*

��Ŀ��
    ������Ϳɫ������[l,r] b��ʾ������Ⱦ�ɺ�ɫ��w��ʾ��ɫ����ʼ��ʱ��������
    ��ɫ�ģ�����İ�ɫ�������ʼ��ֹλ��

������
    ��ɢ��������ÿ��λ�õ�����λ�ã�����ʼ��Ϊ-1��Ⱦɫ�����У�������(l,r]
    ����Ⱦɫ���ɣ�����ͳ��һ����������ɢ�������������ʾ������伴��

*/
#include <map>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>

using namespace std;

const int X = 50005;
#define debug puts("here");

int n,m;
int a[X],b[X];
int c[X],use[X];
map<int,int> ma,mh,mb;
int qq[X];

int main(){
    freopen("sum.in","r",stdin);
    int x,y;
    char s[5];
    while(cin>>m){
        n = 0;
        memset(c,1,sizeof(c));
        for(int i=1;i<=m;i++){
            scanf("%d%d%s",&a[i],&b[i],s);
            if(s[0]=='b')
                c[i] = 0;
            else
                c[i] = 1;
            qq[++n] = a[i]-1;
            qq[++n] = a[i];
            qq[++n] = a[i]+1;
            qq[++n] = b[i]-1;
            qq[++n] = b[i];
            qq[++n] = b[i]+1;
        }
        sort(qq+1,qq+n+1);
        int cnt = 0;
        ma.clear();
        mb.clear();
        mh.clear();
        for(int i=1;i<=n;i++){
            x = qq[i];
            if(ma[x])
                continue;
            ma[x] = ++cnt;
            mh[cnt] = x;
        }

        memset(use,-1,sizeof(use));
        for(int i=1;i<=m;i++){
            x = ma[a[i]];
            y = ma[b[i]];
            for(int j=x+1;j<=y;j++)
                use[j] = c[i];
        }
        int ansx = 0,ansy = 0;
        int ans = 0;
        x = 0;
        n = cnt;
        for(int i=1;i<=n;i++){
            if(use[i]){
                y = mh[i];
            }
            else{
                if(ans<y-x){
                    ansx = x;
                    ansy = y;
                    ans = y-x;
                }
                x = mh[i];
            }
        }
        y = 1e9;
        x = n;
        while(x&&use[x])
            x--;
        x = mh[x];
        if(ans<y-x){
            ans = y;
            ansx = x;
            ansy = y;
        }
        cout<<ansx<<" "<<ansy<<endl;
    }
    return 0;
}
