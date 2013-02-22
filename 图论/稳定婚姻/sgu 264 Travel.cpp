/*

裸的稳定婚姻模型，由于婚姻匹配问题必定存在解的问题，所以这题不存在no的情况

*/
#include <iostream>
#include <cstdio>
#include <cstring>
#include <map>

using namespace std;

const int X = 12;
const int maxm = 802;

map<string,int> ma;
int q[maxm*1000],head,tail;
int pref[maxm][maxm],order[maxm][maxm],wife[maxm],man[maxm];
char a[maxm][X],b[maxm][X];
int top[maxm],n;
            //男     女
void engage(int x,int y){
    int m = man[y];
    if(m){
        wife[m] = 0;
        q[tail++] = m;
    }
    man[y] = x;
    wife[x] = y;
}

void solve(){
    while(head<tail){
        int x = q[head++];
        int y = pref[x][ ++top[x] ];
        if(!man[y])
            engage(x,y);
        else if(order[y][x]<order[y][man[y]])
            engage(x,y);
        else
            q[tail++] = x;
    }
}

int main(){
    freopen("sum.in","r",stdin);
    while(cin>>n){
        char s[X];
        head = tail = 0;
        int x,y;
        ma.clear();
        int cnt = 0;
        for(int i=1;i<=n;i++){
            scanf("%s",s);
            strcpy(a[i],s);
            ma[s] = i;
            for(int j=1;j<=n;j++){
                scanf("%s",s);
                y = ma[s];
                if(!y){
                    y = ma[s] = ++cnt;
                    strcpy(b[cnt],s);
                }
                pref[i][j] = y;
            }
            top[i] = 0;
            q[tail++] = i;
            wife[i] = 0;
        }
        for(int i=1;i<=n;i++){
            scanf("%s",s);
            x = ma[s];
            for(int j=1;j<=n;j++){
                scanf("%s",s);
                y = ma[s];
                order[x][y] = j;
            }
            man[i] = 0;
        }
        solve();
        puts("YES");
        for(int i=1;i<=n;i++)
            printf("%s %s\n",a[i],b[wife[i]]);
    }
    return 0;
}
