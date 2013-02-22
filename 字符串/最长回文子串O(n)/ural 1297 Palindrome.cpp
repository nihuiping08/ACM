/*

题目：
    求最长回文子序列并输出该回文子串

分析：
    最长回文子序列模板+输出

*/
#include <iostream>
#include <cstring>
#include <cstdio>

using namespace std;

const int X = 2e3+5;

char s[X],in[X];
int rad[X],n,len;

void cal(){
    int id;
    int mx = 0;
    for(int i=1;i<len;i++)
    {
        if(mx>i)
            rad[i] = min(mx-i,rad[2*id-i]);
        else
            rad[i] = 1;
        for(;s[i-rad[i]]==s[i+rad[i]];rad[i]++)
            ;
        if(i+rad[i]>mx){
            mx = i+rad[i];
            id = i;
        }
    }
}

int main(){
    freopen("sum.in","r",stdin);
    //freopen("sum.out","w",stdout);
    while(scanf("%s",in)!=EOF){
        s[0] = '$';
        len = 1;
        //cout<<in<<endl;
        s[len++] = '#';
        for(int i=0;in[i];i++){
            s[len++] = in[i];
            s[len++] = '#';
        }
        s[len] = '\0';
        cal();
        int ans = 0;
        int cnt = 0,pos;
        for(int i=1;i<len;i++)
            if(rad[i]>ans){
                ans = rad[i];
                pos = i;
            }

        --ans;
        int x,y;
        x = pos-ans+1;
        y = pos+ans;
        for(int i=x;i<=y;i++)
            if(s[i]!='#'&&s[i]!='$')
                in[cnt++] = s[i];
        in[cnt] = '\0';
        puts(in);
    }
    return 0;
}
