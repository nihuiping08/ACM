/*

题目：
    给出一堆数的操作，问他属于那种数据结构

分析：
    直接枚举三种数据结构即可

*/
#include <iostream>
#include <cstring>
#include <cstdio>
#include <queue>
#include <stack>

using namespace std;

const int X = 1005;

#define debug puts("here");

int main(){
    freopen("sum.in","r",stdin);
    int n;
    while(cin>>n){
        stack<int> s;
        queue<int> q;
        priority_queue<int> pq;

        bool a1,a2,a3;
        a1 = a2 = a3 = true;
        int x,op;
        while(n--){
            scanf("%d%d",&op,&x);
            if(a1){
                if(op==1)
                    s.push(x);
                else if(s.size()){
                    if(s.top()!=x)
                        a1 = false;
                    else
                        s.pop();
                }
                else
                    a1 = a2 = a3 = false;
            }
            if(a2){
                if(op==1)
                    q.push(x);
                else if(q.size()){
                    if(q.front()!=x)
                        a2 = false;
                    else
                        q.pop();
                }
                else
                    a1 = a2 = a3 = false;
            }
            if(a3){
                if(op==1)
                    pq.push(x);
                else if(pq.size()){
                    if(pq.top()!=x)
                        a3 = false;
                    else
                        pq.pop();
                }
                else
                    a1 = a2 = a3 = false;
            }
        }

        int cnt = a1+a2+a3;
        if(cnt==1){
            if(a1)
                puts("stack");
            else if(a2)
                puts("queue");
            else
                puts("priority queue");
        }
        else if(cnt)
            puts("not sure");
        else
            puts("impossible");
    }
    return 0;
}
