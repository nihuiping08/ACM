/*

��Ŀ��
    Given two strings a and b we define a*b to be their concatenation. For example,
    if a = "abc" and b = "def" then a*b = "abcdef". If we think of concatenation as
    multiplication, exponentiation by a non-negative integer is defined in the normal
    way: a^0 = "" (the empty string) and a^(n+1) = a*(a^n).

������
    a  b  c  d  a b c d a b c d��next�ֱ�Ϊ
    -1 -1 -1 -1 0 1 2 3 4 5 6 7
    ���Ƿ��֣�next[i]ָ����ǵڼ����ַ�������i�ַ���ǰ׺ӵ��next[i]�ַ�������ǰ׺�����⣬
    ��next[len-1]��ʱ����len-next[len-1]-1�󣬵õ�����a����Ŀ�е�Ҫ�󴮣��ĳ��ȣ���len
    ���������Ǵ���

*/
#include <iostream>
#include <cstdio>
#include <cstring>

using namespace std;

const int X = 1000005;

char s[X];
int next[X];

int main()
{
    freopen("sum.in","r",stdin);
    while(gets(s),s[0]!='.')
    {
        //memset(next,-1,sizeof(next));
        int j = -1;
        next[0] = -1;
        for(int i=1;s[i];i++)
        {
            while(j!=-1&&s[i]!=s[j+1])
                j = next[j];
            if(s[i]==s[j+1])
                j++;
            next[i] = j;
        }
        /*for(int i=0;s[i];i++)
            cout<<next[i]<<"  ";
        puts("");*/
        int len = strlen(s);
        int ans = len/(len-next[len-1]-1);
        printf("%d\n",ans);
    }
    return 0;
}
