/*

题目：
    稳定婚姻问题，男士最优策略

分析：
    先把所有的男士都放进求婚者的队列中，然后男士轮流订婚，如果订婚不成功，再
    放进队列中进行下一轮的订婚。对于女士来说，只要一经订婚成功，她一直都处于
    已订婚的状态

*/
#include <cstdio>
#include <cstring>
#include <iostream>
#include <string>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

const int X = 100;

#define debug puts("here");

queue<int> q;

int pref[X][X],order[X][X];
int man[X],wife[X],n;
int top[X];

int ha[140],hb[140];

struct node{
    char a,b;
    friend bool operator < (node a,node b){
        return a.a<b.a;
    }
}p[X];

void engage(int x,int y){   //订婚
    int m = man[y];
    if(m){
        wife[m] = 0;
        q.push(m);
    }
    man[y] = x;
    wife[x] = y;
}

void solve(){
    while(q.size()){    //还有男士求婚
        int x = q.front();
        q.pop();
        int y = pref[x][ top[x]++ ];
        if(order[y][x]<order[y][man[y]])
            engage(x,y);
        else if(!man[y])
            engage(x,y);
        else
            q.push(x);
    }
    while(q.size())
        q.pop();
}

int main(){
    freopen("sum.in","r",stdin);
    int ncase;
    cin>>ncase;
    while(ncase--){
        cin>>n;
        string str;
        char mm[X],ww[X];

        int x,y;

        memset(ha,0,sizeof(ha));
        memset(hb,0,sizeof(hb));

        for(int i=1;i<=n;i++){
            cin>>str;
            ha[(int)str[0]] = i;
            mm[i] = str[0];
            q.push(i);
        }

        for(int i=1;i<=n;i++){
            cin>>str;
            hb[(int)str[0]] = i;
            ww[i] = str[0];
        }

        for(int i=1;i<=2*n;i++){
            cin>>str;
            if(ha[(int)str[0]]){
                x = ha[(int)str[0]];
                for(int j=2;j<=n+1;j++){
                    y = hb[(int)str[j]];
                    pref[x][j-1] = y;
                }
                wife[x] = 0;
                top[x] = 1;
            }
            else{
                x = hb[(int)str[0]];
                for(int j=2;j<=n+1;j++){
                    y = ha[(int)str[j]];
                    order[x][y] = j-1;
                }
                man[x] = 0;
            }
        }

        solve();

        for(int i=1;i<=n;i++){
            p[i].a = mm[i];
            p[i].b = ww[wife[i]];
        }
        sort(p+1,p+n+1);
        for(int i=1;i<=n;i++)
            cout<<p[i].a<<" "<<p[i].b<<endl;
        if(ncase)
            puts("");
    }

    return 0;
}
