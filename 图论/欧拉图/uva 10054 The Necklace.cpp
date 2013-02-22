/*

��Ŀ��
	uva 10054 The Necklace
	��������������ɣ�ÿ�����ֶ�����ɫ������ͬ��ɫ���������ӿ��Դ�����һ���������ܲ��ܰ����е�����
	������һ�����ܹ������������ķ�ʽ

����:
    ��ŷ����·����ÿ����ɫ����ͼ�ϵ�һ�����㣬Ȼ�����ÿ�����ӹ���һ������ߣ����ж��Ƿ��������ȵĶ��㣬
	���еĻ���ŷ����·�����ڣ�����DFSһ�μ��ɡ�����ע��ͼ�п��ܴ��ڶ�����ͬ�ıߣ���û�����������ÿ��
	DFS��ʱ��ѱ�ɾ��һ������

*/
#include <iostream>
#include <cstdio>
#include <cstring>

using namespace std;

const int X = 60;
const int n = 50;

int map[X][X];
int id[X];
int m;

void dfs(int x){
    for(int y=1;y<=n;y++){
        if(map[x][y]>0){
            map[x][y] --;
            map[y][x] --;
            dfs(y);
            cout<<y<<" "<<x<<endl;
        }
    }
}

int main(){
    freopen("sum.in","r",stdin);
    int ncase,x,y,cnt = 0;
    cin>>ncase;
    while(ncase--){
        if(cnt)
            puts("");
        printf("Case #%d\n",++cnt);
        memset(map,0,sizeof(map));
        memset(id,0,sizeof(id));
        scanf("%d",&m);
        while(m--){
            scanf("%d%d",&x,&y);
            map[x][y] ++;
            map[y][x] ++;

            id[x] ++;
            id[y] ++;
        }
        bool ok = true;
        for(int i=1;i<=n;i++){
            if(id[i]&1){
                ok = false;
                puts("some beads may be lost");
                break;
            }
        }
        if(!ok)
            continue;
        dfs(x);
    }
    return 0;
}
