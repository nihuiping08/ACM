/*

��Ŀ��
    ���������ֲ�����id��ʾջ�ı�ţ�val��ʾֵ��POPÿ�ζ��ǵ���ջ���Ϊid
    ��ջ����������ÿ��POP����ʱ��Ԫ���Ƕ���
    PUSH id val
    POP id

������
    ����ò�ƺܼ򵥣����ǿ��ڴ棬����~~��������������ͼ�ĳ��ӷ����ˡ�����
    ��һ��ջ������60000�����ϵ�Ԫ�أ���������int�͵Ļ������ǻᳬ�ģ�����
    ��¼ǰ����ʱ�����unsigned short�ͣ��ѳ��ӷ��е�ֵ����60000���¼��
    pre�У������ǵĻ�������ֱ�Ӱ�valֵȡ�����ɣ���ѯ��ʱֱ�����жϼ���

*/
#include <cstdio>
#include <cstring>

using namespace std;

const int X = 100001;

unsigned int po[1001];
unsigned short pre[X];
int a[X];
char s[5];
int x,y,n;

int main(){
    freopen("sum.in","r",stdin);
    while(scanf("%d",&n)!=EOF){
        memset(po,0,sizeof(po));
        int tol = 1;
        while(n--){
            scanf("%s%d",s,&x);
            if(s[1]=='U'){
                scanf("%d",&y);
                if(po[x]<60000){
                    a[tol] = y;
                    pre[tol] = po[x];
                }
                else{
                    pre[tol] = po[x]-60000;
                    a[tol] = -y;
                }
                po[x] = tol++;
            }
            else{
                if(a[po[x]]<0){
                    printf("%d\n",-a[po[x]]);
                    po[x] = pre[po[x]]+60000;
                }
                else{
                    printf("%d\n",a[po[x]]);
                    po[x] = pre[po[x]];
                }
            }
        }
    }
    return 0;
}
