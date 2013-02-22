/*

题目：
    求中位数

分析：
    利用优先队列做，优先队列保存n/2+1个元素，若新加入的元素小于队尾，把他
    加进来，当当前队列中的元素大于要保存的元素个数时，把队尾元素出队，最后
    判断n是否为奇偶即可

*/
#include <cstdio>
#include <queue>
#include <cstring>
#include <iostream>

using namespace std;

//#define debug puts("here");
priority_queue<unsigned int> q;

int main(){
    freopen("sum.in","r",stdin);
    unsigned int val;
    int n;
    while(cin>>n){
        while(q.size())
            q.pop();
        unsigned int mid = (n+2)>>1;
        for(int i=0;i<n;i++){
            scanf("%d",&val);
            q.push(val);
            if(q.size()>mid)
                q.pop();
        }
        mid = (n+1)>>1;
        if(n&1){
            if(!(n&1))
                q.pop();
            cout<<q.top()<<endl;
        }
        else{
            long long ans = q.top();
            q.pop();

            ans += q.top();
            cout<<(ans>>1);
            if(ans&1)
                cout<<".5";
            cout<<endl;
        }
    }

    return 0;
}
