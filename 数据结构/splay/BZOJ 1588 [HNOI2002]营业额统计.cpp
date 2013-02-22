/*

���������Լ��ĵ�һ��splay�⣬ֻ����������һ��ģ��ġ�����

��Ŀ���ӣ�http://www.lydsy.com/JudgeOnline/problem.php?id=1588

������
    ���������ǰ���ͺ�̡���ת��SBT��AVL��BST��treapһ�������Ҳ���Ҫά������ƽ�⣬
    Ĭ��Ϊ90%��ѯ�ʷ�����10%���������棬���������ڲ����ʱ��ͰѲ���ĵ����ݾ���
    splay������ת�ýڵ���������������ѯ��x��ǰ����ʱ�����ǿ����ȵõ�x��Ȼ���ٰ�x
    ����splay������ת�����������ҵ�����ǰ�������ͬ�������Ĳ����Ժ����ܽ�һ�¡���

*/
#include <set>
#include <map>
#include <cmath>
#include <queue>
#include <stack>
#include <string>
#include <vector>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>

using namespace std;

typedef long long ll;
typedef unsigned long long ull;

#define debug puts("here")
#define rep(i,n) for(int i=0;i<n;i++)
#define foreach(i,vec) for(unsigned i=0;i<vec.size();i++)
#define pb push_back

#define INF 1e9

namespace Splay{

#define X 1111111

#define px pre[x]
#define py pre[y]

#define lx ch[x][0]
#define ly ch[y][0]
#define lz ch[z][0]

#define rx ch[x][1]
#define ry ch[y][1]

    int root,tot;
    int ch[X][2],pre[X],val[X];

    inline void init(){ // ��ʼ��
        root = tot = 0;
        memset(ch,0,sizeof(ch));
        memset(pre,0,sizeof(pre));
        memset(val,0,sizeof(val));
    }

    inline void dfs(int x){ // debugʹ��
        if(x){
            dfs(lx);
            printf("self = %d , left = %d , right = %d , father = %d\n",x,lx,rx,px);
            dfs(rx);
        }
    }

    inline void new_node(int &x,int father,int v){ // �����½ڵ�
        x = ++tot;
        pre[x] = father;
        val[x] = v;
        ch[x][0] = ch[x][1] = 0;
    }

    inline void setc(int y,int d,int x){ // ��ת���̵�����������
        ch[y][d] = x;
        pre[x] = y;
    }

    inline int sgn(int x){ // 0��ʾ����1��ʾ����
        return ch[px][1]==x;
    }

    inline void _rot(int x,int d){
        int y = px;
        int z = py;

        setc(y,!d,ch[x][d]);//����SBT��Ҫ������һ����֧�ȸ����ڵ�

        if(z)   //������ڵ㲻�Ǹ���㣬��Ҫ�͸��ڵ�ĸ��ڵ���������
            setc(z,sgn(y),x);
        pre[x] = z;

        setc(x,d,y);
    }

    inline void rot(int x){_rot(x,!sgn(x));}
    inline void zag(int x){_rot(x,0);} // ����
    inline void zig(int x){_rot(x,1);} // ����

    // Splay����������Ϊr����������Ϊgoal
    inline int splay(int x,int goal=0){
        while(px!=goal){
            int y = px;
            int z = py;
            if(z==goal){
                rot(x);
                break;
            }
            if(lz==y){
                if(ly==x)
                    zig(y),zig(x);
                else
                    zag(x),zig(x);
            }
            else{
                if(ry==x)
                    zag(y),zag(x);
                else
                    zig(x),zag(x);
            }
        }
        if(goal==0)
            root = x;
        return x;
    }

    inline int insert(int v){ // ����
        int x = root;
        while(ch[x][ val[x]<v ]){
            if(val[x]==v){
                splay(x); // �Ѵ��ڣ�������Ժ��Ե���������Ҫ��ת�ýڵ���Ϊ��
                return 0;
            }
            x = ch[x][ val[x]<v ];
        }
        new_node(ch[x][ val[x]<v ],x,v);
        splay(ch[x][ val[x]<v ]); // �²���ڵ�splay������
        return 1;
    }

    inline int get_pre(int x){ // �õ�ǰ��
        int tmp = x;
        x = lx;
        if(x==0)
            return INF;
        while(rx)
            x = rx;
        return val[tmp]-val[x];
    }

    inline int get_next(int x){ // �õ����
        int tmp = x;
        x = rx;
        if(x==0)
            return INF;
        while(lx)
            x = lx;
        return val[x]-val[tmp];
    }

#undef X

#undef px
#undef py

#undef lx
#undef ly
#undef lz

#undef rx
#undef ry

}using namespace Splay;

int main(){

#ifndef ONLINE_JUDGE
	freopen("sum.in","r",stdin);
#endif

    int ans = 0,n,x;
    cin >> n;

    init();
    rep(i,n){
        if(scanf("%d",&x)==EOF)
            x = 0;
        if(i==0){
            ans += x;
            new_node(root,0,x);
            continue;
        }
        if(insert(x)==0)
            continue;
        // ǰ������ʱ��x�Ѿ�splay�����������Կ���ֱ����ֵ
        ans += min(get_pre(root),get_next(root));
    }
    cout<<ans<<endl;

	return 0;
}
