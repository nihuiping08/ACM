/*

��Ŀ��
    ����n�����⳵����ÿ�����������ʼʱ�䡢��������Լ��յ����꣬�����ط���
    �����������پ��룬���ҳ��⳵���Խ���һ������֮�󣬿�������һ������ʼ֮ǰ
    ����Ļ������ԽӸ�������������Ҫ���Ŷ��������⳵

������
    ��ÿ�����񿴳�һ�����㣬Ȼ����ڿ��Խ�������a֮����Խ�����b�����ߣ�������
    ת��Ϊ��С·��ƥ�� = ������-���ƥ��

*/
#include <iostream>
#include <cstring>
#include <cstdio>
#include <cmath>

using namespace std;

const int X = 505;

#define debug puts("here");

struct node{
    int a,b,c,d,t;
    node(){}
    node(int _x,int _y,int _a,int _b,int _c,int _d){
        t = _x*60+_y;
        a = _a;
        b = _b;
        c = _c;
        d = _d;
    }
}p[X];

bool map[X][X],use[X];
int ym[X],n;

bool dfs(int x){
    for(int i=1;i<=n;i++){
        if(map[x][i]&&!use[i]){
            use[i] = true;
            if(ym[i]==-1||dfs(ym[i])){
                ym[i] = x;
                return true;
            }
        }
    }
    return false;
}

void hungry(){
    memset(ym,-1,sizeof(ym));
    int ret = 0;
    for(int i=1;i<=n;i++){
        memset(use,false,sizeof(use));
        if(dfs(i))
            ret ++;
    }
    cout<<n-ret<<endl;
}

int dis(int i,int j){
    int ret = fabs(p[i].c-p[i].a)+fabs(p[i].d-p[i].b);
    ret += fabs(p[i].c-p[j].a)+fabs(p[i].d-p[j].b);
    return ret;
}

bool check(int i,int j){
    if(p[i].t+dis(i,j)<p[j].t)
        return true;
    return false;
}

int main(){
    freopen("sum.in","r",stdin);
    int ncase;
    cin>>ncase;
    while(ncase--){
        cin>>n;
        int a,b,c,d,x,y;
        for(int i=1;i<=n;i++){
            scanf("%d:%d%d%d%d%d",&x,&y,&a,&b,&c,&d);
            p[i] = node(x,y,a,b,c,d);
        }
        memset(map,false,sizeof(map));
        for(int i=1;i<=n;i++)
            for(int j=i+1;j<=n;j++)
                if(check(i,j))
                    map[i][j] = true;
        hungry();
    }
    return 0;
}
