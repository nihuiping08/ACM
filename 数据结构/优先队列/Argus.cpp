/*

题目：
    优先队列水题。。。

*/
#include <cstdio>
#include <cstring>
#include <string>
#include <queue>
#include <iostream>

using namespace std;

struct node{
    int id;
    int tot;
    int st;

    node(){}
    node(int _id,int _tot,int _st):id(_id),tot(_tot),st(_st){}

    friend bool operator < (node a,node b){
        return a.tot>b.tot||(a.tot==b.tot&&a.id>b.id);
    }
};

int main(){
    freopen("sum.in","r",stdin);
    priority_queue<node> q;
    int id,st;
    string s;
    while(true){
        cin>>s;
        if(s=="#")
            break;
        cin>>id>>st;
        q.push(node(id,st,st));
    }
    int k;
    cin>>k;
    while(k--){
        node pre = q.top();
        q.pop();
        cout<<pre.id<<endl;
        pre.tot += pre.st;
        q.push(pre);
    }
    return 0;
}
