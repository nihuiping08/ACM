/*

��Ŀ��
    ���������⣬����һЩ��ϵ��������ʱ�ܹ�ȷ����ϵ�����߳���ì�ܣ��������û��ȷ����ϵ����û��
    ��С��ϵȫ��ȷ������û��ì�ܲ�������

������
    ÿ����һ���ϵʱ����������ͼ����һ����������������ɹ���˵����ǰΪ���Ž⣬�Ժ���Բ����ٴ�
    ������������������г���ì�ܣ�֤����ǰΪ����ì�ܵ����Ž⣬ͬ���Ժ���Բ��ý�������

    ���������˼�룺
        ������ͼ�У�ÿ��Ѱ�����Ϊ0�Ķ��㣬���ö�����Ϊ0��˵��ͼ���л������ö���������һ��˵����ʱ
        ����ȷ�����������ȵ��ж��Ƿ���ì�ܣ����Ի������½������򡣶��ҵ������Ϊ0�Ķ��㴢�浽�����У�
        ���������ɹ��󣬸������Ԫ�ؼ�Ϊ������Ԫ�صĴ�С��ϵ��

*/
#include <iostream>
#include <cstdio>
#include <cstring>
using namespace std;

const int X = 105;
int ans[X],t[X],in[X],n,m;
bool map[X][X];

int topo(){     //����ì�ܣ�����0������ɹ�����1����ûȷ����ϵ������-1
    int cnt,temp,ret = 0;
    for(int i=0;i<n;i++)
        t[i] = in[i];   //������һ���������浱ǰ�������
    int flag = 1;
    for(int i=0;i<n;i++){
        cnt = 0;
        for(int j=0;j<n;j++)
            if(t[j]==0){    //�ҵ����Ϊ0�ĵ�
                cnt++;
                temp = j;
            }
        if(cnt==0)  //&&cnt!=n  //֤���л�
            return 0;
        if(cnt>1)   //˵������ȷ����ϵ�������жϵ�����û��ì��
            flag = -1;
        t[temp] = -1;
        ans[ret++] = temp;  //�����
        for(int j=0;j<n;j++)
            if(map[temp][j])
                t[j]--;
    }
    return flag;
}

int main(){
    freopen("sum.in","r",stdin);
    freopen("sum.out","w",stdout);
    char s[10];
    while(cin>>n>>m,n||m){
        bool flag = true;
        int temp,x,y;

        memset(map,false,sizeof(map));
        memset(in,0,sizeof(in));

        for(int i=1;i<=m;i++){
            scanf("%s",s);
            x = s[0]-'A';
            y = s[2]-'A';
            map[x][y] = true;
            in[y]++;
            if(flag)
                temp = topo();
            if(temp==1&&flag){
                flag = false;
                printf("Sorted sequence determined after %d relations: ",i);
                for(int i=0;i<n;i++)
                    printf("%c",(char)ans[i]+'A');
                printf(".\n");
            }
            if(temp==0&&flag){
                flag = false;
                printf("Inconsistency found after %d relations.\n",i);
            }
        }
        if(flag)
            printf("Sorted sequence cannot be determined.\n");
    }
    return 0;
}
