/*

题目：
    Your are to output a sequence of values displayed by the device.
    The first number of the sequence is the maximal element of the
    first M input numbers, the second number is the maximal element
    of the 2nd, …, M+1-st input numbers and so on.

分析：
    使用单调递减队列保存当前信息即可

*/
#include <iostream>
#include <cstdio>
#include <cstring>

using namespace std;

const int X = 25005;

struct node{
    int id,val;
}q[X];

int main(){
    freopen("sum.in","r",stdin);
    int x,n;
    while(cin>>n){
        int h = 0,t = 0;
        int id = 0;
        while(scanf("%d",&x),x!=-1){
            id++;
            while(h<t&&q[h].id+n<=id)
                h++;
            while(h<t&&q[t-1].val<=x)
                t--;
            q[t].val = x;
            q[t].id = id;
            t++;
            if(id>=n)
                printf("%d\n",q[h].val);
        }
    }
    return 0;
}
