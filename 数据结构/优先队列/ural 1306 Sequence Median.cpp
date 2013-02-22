/*

��Ŀ��
    ����λ��

������
    �������ȶ����������ȶ��б���n/2+1��Ԫ�أ����¼����Ԫ��С�ڶ�β������
    �ӽ���������ǰ�����е�Ԫ�ش���Ҫ�����Ԫ�ظ���ʱ���Ѷ�βԪ�س��ӣ����
    �ж�n�Ƿ�Ϊ��ż����

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
