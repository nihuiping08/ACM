/*

��Ŀ��
    ������Ӵ������и������ַ����������ķ�ת�Ĵ��г���

������
    ����ö�����п��ܵĳ��ȣ�Ȼ����KMP�㷨�жϸ�ö�ٵ��Ӵ��Ƿ������и������ַ���
    �������ķ�ת���г��֡�

*/
#include <iostream>
#include <cstdio>
#include <cstring>

using namespace std;

const int X = 205;

char in[X][X],p[X];

int fail[X],len[X],n,lens;
int mid;    //mid ��ʾö�ٵĳ���
int ma,pos; //ma��ʾ���д��г�����С�ģ�pos��ʾ����̴���λ��

void shift()    //ģʽ�������Լ�����ģʽƥ�䣬���failָ��
{
    fail[0] = -1;
    int j = -1;
    for(int i=1;i<mid;i++)
    {
        while(j!=-1&&p[i]!=p[j+1])
            j = fail[j];
        if(p[i]==p[j+1])
            j++;
        fail[i] = j;
    }
}

bool kmp(char *s) //ģʽ�����ı�������ģʽƥ�䣬�ж��Ƿ����ı����г���ģʽ��
{
    int j = -1;
    for(int i=0;i<lens;i++)
    {
        while(j!=-1&&s[i]!=p[j+1])
            j = fail[j];
        if(s[i]==p[j+1])
            j++;
        if(j+1==mid)
            return true;
    }
    return false;
}

void solve()        //����ö�ٺ���
{
    int right = ma,left = 0;
    int temp;
    while(left<=right)
    {
        bool ok = true;
        mid = (left+right+1)>>1;
        temp = len[pos]-mid;
        for(int i=0;i<=temp;i++)
        {
            int cnt = 0;
            for(int j=i;j<mid+i;j++)    //�Ӹ�λ��ʼö�����иó��ȵ��Ӵ�
                p[cnt++] = in[pos][j];
            p[mid] = '\0';  //����

            shift();    //����failָ��

            ok = true;
            for(int j=0;j<n;j+=2)
            {
                if(j==pos)
                    continue;
                lens = len[j];
                if(kmp(in[j])||kmp(in[j+1]))//�����ǰ�Ĵ��򷴴��г�����ö�ٵĴ�
                    continue;
                ok = false;
                break;
            }
            if(ok)  //������ж����Ͽ�ֱ������
                break;
        }
        if(ok)
            left = mid+1;
        else
            right = mid-1;
    }
    cout<<right<<endl;
}

int main()
{
    freopen("sum.in","r",stdin);
    freopen("sum.out","w",stdout);
    int ncase,cnt;
    cin>>ncase;
    while(ncase--)
    {
        ma = 1000;
        scanf("%d ",&n);
        n = n<<1;
        for(int i=0;i<n;i+=2)
        {
            cnt = 0;
            gets(in[i]);
            len[i] = len[i+1] = strlen(in[i]);
            if(len[i]<ma)
            {
                ma = len[i];
                pos = i;
            }
            for(int j=len[i]-1;j>=0;j--)    //�󷴴�
                in[i+1][cnt++] = in[i][j];
            in[i+1][cnt] = '\0';
        }
        solve();
    }
    return 0;
}
