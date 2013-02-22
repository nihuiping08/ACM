/*

��Ŀ��
    �׶�԰����N��С���ѣ�lxhgww��ʦ������Ҫ����ЩС�����Ƿ���
    �ǹ���Ҫ��ÿ��С���Ѷ�Ҫ�ֵ��ǹ�������С������Ҳ�м����ģ�
    ���ǻ����һЩҪ�󣬱���С����ϣ��С��ֵ����ǹ������Ķ࣬
    �����ڷ����ǹ���ʱ��lxhgww��Ҫ����С�����ǵ�K��Ҫ����
    ��԰���ǹ��������޵ģ�lxhgww��֪����������Ҫ׼�����ٸ���
    ��������ʹ��ÿ��С���Ѷ��ܹ��ֵ��ǹ�����������С��������
    �е�Ҫ��
    Input

    ����ĵ�һ������������N��K��
    ������K�У���ʾ��Щ����Ҫ����Ĺ�ϵ��ÿ��3�����֣�X��A��B��
    ���X=1�� ��ʾ��A��С���ѷֵ����ǹ�����͵�B��С���ѷֵ���
    �ǹ�һ���ࣻ
    ���X=2�� ��ʾ��A��С���ѷֵ����ǹ��������ڵ�B��С���ѷֵ�
    ���ǹ���
    ���X=3�� ��ʾ��A��С���ѷֵ����ǹ����벻���ڵ�B��С���ѷ�
    �����ǹ���
    ���X=4�� ��ʾ��A��С���ѷֵ����ǹ�������ڵ�B��С���ѷֵ�
    ���ǹ���
    ���X=5�� ��ʾ��A��С���ѷֵ����ǹ����벻���ڵ�B��С���ѷ�
    �����ǹ���

������
    ���Լ�������ǰ���ƽ���Ľ�ͼ�Ļ������и��߳��֣�������spfa
    ���ʱ��ת��Ϊ���·

*/
#include <iostream>
#include <cstdio>
#include <cstring>
#include <queue>

using namespace std;

const int X = 100005;

int po[X],tol;
int id[X],dis[X];
bool use[X];
int n,m;

struct node{
    int y,w,next;
}edge[X<<1];


long long spfa(){
    queue<int> q;
    for(int i=1;i<=n;i++){
        id[i] = dis[i] = 1;
        use[i] = true;
        q.push(i);
    }
    while(q.size()){
        int x = q.front();
        q.pop();
        use[x] = false;
        for(int i=po[x];i;i=edge[i].next){
            int y = edge[i].y;
            if(dis[x]+edge[i].w>dis[y]){
                dis[y] = dis[x]+edge[i].w;
                if(++id[y]>n)
                    return -1;
                if(!use[y]){
                    use[y] = true;
                    q.push(y);
                }
            }
        }
    }
    long long ans = 0;
    for(int i=1;i<=n;i++)
        ans += dis[i];
    return ans;
}

void add(int x,int y,int w){
    edge[++tol].y = y;
    edge[tol].w = w;
    edge[tol].next = po[x];
    po[x] = tol;
}

bool build(){
    memset(po,0,sizeof(po));
    tol = 0;
    int op,x,y;
    while(m--){
        scanf("%d%d%d",&op,&x,&y);
        if(op==1){
            if(x!=y){
                add(x,y,0);
                add(y,x,0);
            }
        }
        else if(op==2){
            if(x==y)
                return false;
            add(x,y,1);
        }
        else if(op==3){
            if(x!=y)
                add(y,x,0);
        }
        else if(op==4){
            if(x==y)
                return false;
            add(y,x,1);
        }
        else if(op==5){
            if(x!=y)
                add(x,y,0);
        }
    }
    return true;
}

int main(){
    freopen("sum.in","r",stdin);
    cin>>n>>m;
    if(build())
        cout<<spfa()<<endl;
    else
        puts("-1");
    return 0;
}
