/*

��Ŀ��
    wwstdaadierfflitzzz
    stierlitz
    �����ڵ��ַ���һ���Ļ�����ɾ�����������ʣ�µ��ַ���

*/
#include <iostream>
#include <cstdio>
#include <cstring>

using namespace std;

const int X = 200005;

char s[X],q[X];

int main(){
    freopen("sum.in","r",stdin);
    while(gets(s)){
        int top = 0;
        int len = strlen(s);
        for(int i=0;i<len;i++){
            if(s[i]==' ')
                continue;
            if(top&&s[i]==s[top-1]){
                top--;
                continue;
            }
            s[top++] = s[i];
        }
        s[top] = '\0';
        puts(s);
    }
    return 0;
}
