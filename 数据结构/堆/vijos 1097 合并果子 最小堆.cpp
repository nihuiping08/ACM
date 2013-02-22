/*

题目：
    合并果子

分析：
    最小堆实现，跟哈夫曼树的思想一样

*/
#include <iostream>
#include <cstdio>
#include <cstring>

using namespace std;

const int X = 40005;
#define debug puts("here");

int a[X],n,s;

void insert(int val){
    int i;
    for(i=++s;a[i>>1] > val;i=i>>1)
        a[i] = a[i>>1];
    a[i] = val;
}

void del(){
    int val = a[s];
    a[s--] = 0;
    int t = 1;
    int i = 0;
    for(i=1;i*2<=s;i=t){
        t = i<<1;
        if(t!=s&&a[t]>a[t|1])
            t = t|1;
        if(val>a[t])
            a[i] = a[t];
        else
            break;
    }
    a[i] = val;
    return;
}

int main(){
    freopen("sum.in","r",stdin);
    int val;
    while(cin>>n){
        s = 0;
        for(int i=1;i<=n;i++){
            scanf("%d",&val);
            insert(val);
        }
        int x,y;
        int ans = 0;
        for(int i=1;i<n;i++){
            x = a[1];
            del();
            y = a[1];
            del();
            //cout<<x<<" "<<y<<endl;
            ans += x+y;
            insert(x+y);
        }
        cout<<ans<<endl;
    }
    return 0;
}
