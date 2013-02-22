/*

��Ŀ��
    ��ţ�Ǽƻ���ȥ��̲�������չ�ԡ��Ϊ�˱���Ƥ�����������ˣ�
    ����C(1 <= C <= 2500)ͷ��ţ�����ڳ���֮ǰ������Ĩ��ɹ˪��
    ��iͷ��ţ�ʺϵ���С���� ���SPFֵ�ֱ�ΪminSPF_i��maxSPF_i
    (1 <= minSPF_i <= 1,000; minSPF_i <= maxSPF_i <= 1,000)��
    ���ĳͷ��ţͿ�ķ�ɹ˪��SPFֵ��С����ô������Ȼ�� ������Ƥ
    �����ˣ������ɹ˪��SPFֵ�������ʹ�չ�ԡ����������˯��
    ��� ����û�в��Ϊ�ˣ���ţ��׼����һ�����ӷ�ɹ˪��һ��
    L(1 <= L <= 2500)ƿ����iƿ ��ɹ˪��SPFֵΪSPF_i
    (1 <= SPF_i <= 1,000)��ƿ�ӵĴ�СҲ��һ����ͬ����i ƿ��ɹ˪
    �ɹ�cover_iͷ��ţʹ�á���Ȼ��ÿͷ��ţֻ��Ϳĳһ��ƿ����ķ�
    ɹ˪ �������ܰ����ɸ�ƿ��Ļ�����á� �������һ�£����ʹ
    ����ţ��׼���ķ�ɹ˪������ж�����ţ���ڲ����� �˵�ǰ���£�
    ���ܵ��չ�ԡ��Ч����
    Input

    * ��1��: 2���ÿո������������C��L * ��2..C+1��: ��i+1�и�
    �����ʺϵ�iͷ��ţ��SPFֵ�ķ�Χ��minSPF_i�Լ� maxSPF_i * ��
    C+2..C+L+1��: ��i+C+1��Ϊ�˵�iƿ��ɹ˪�Ĳ�����SPF_i��
    cover_i������ �����ÿո������
    Output

    * ��1��: ���1����������ʾ����ж���ͷ��ţ�����ܵ��չ�ԡ

������
    ̰�ģ���max_spf�����������У�Ȼ��ÿ���ҵ���С��spf��������

*/
#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

const int X = 2505;

int m,n;

struct cow{
    int min,max;
    friend bool operator < (cow a,cow b){
        return a.max<b.max||(a.max==b.max&&a.min<b.min);
    }
}c[X];

struct spf{
    int num,sp;
    friend bool operator < (spf a,spf b){
        return a.sp<b.sp;
    }
}s[X];

int main(){
    freopen("sum.in","r",stdin);
    while(cin>>m>>n){
        for(int i=0;i<m;i++)
            scanf("%d%d",&c[i].min,&c[i].max);
        for(int i=0;i<n;i++)
            scanf("%d%d",&s[i].sp,&s[i].num);
        sort(c,c+m);
        sort(s,s+n);
        int ans = 0;
        for(int i=0;i<m;i++){
            int ok = 0;
            for(int j=0;j<n;j++){
                if(s[j].num&&s[j].sp>=c[i].min&&s[j].sp<=c[i].max){
                    ok = 1;
                    s[j].num --;
                    break;
                }
            }
            ans += ok;
        }
        cout<<ans<<endl;
    }
    return 0;
}
