/*
 *	1483: [HNOI2009]�λò���
 *  
 *  ������
 *		����ʽ�ϲ�����:
 *		ʹ�ó��ӷ���ģ������Ȼ��ÿ�ν���ɫa�滻Ϊbʱ���Ѷ̵�����ϲ������������У�
 *		Ȼ���һ�α����������ʱ�������ڵ���ɫ��ͬ�Ļ���һ���ٴα�������ɫ���ڵ�
 *		�����ʱ�򣬽���ɫ�滻Ϊb��Ȼ���ٱ���һ�Σ���ɫ��ͬ�Ļ���һ���õ���tot����
 *		��ǰ����ɫ��
 *
 * */
#include <cstdio>
#include <cstring>
#include <iostream>

using namespace std;

const int X = 1e6+5;

#define debug puts("here");

int a[X],p[X],num[X];
int po[X],next[X],tol;
int n,m,tot;

int main(){
	freopen("sum.in","r",stdin);
	while(cin>>n>>m){
		int op,x,y;
		memset(po,0,sizeof(po));
		memset(num,0,sizeof(num));
		tol = 0;
		for(int i=1;i<X;i++)
			p[i] = i;
		
		for(int i=1;i<=n;i++){
			scanf("%d",&a[i]);
			num[ a[i] ] ++;
			
			next[++tol] = po[a[i]];
			po[a[i]] = tol;

			if(i==1 || a[i]!=a[i-1] )
				tot ++;
		}
		while(m--){
			scanf("%d",&op);
			if(op==1){
				scanf("%d%d",&x,&y);
				if(x==y)
					continue;
				if(num[ p[x] ]>num[ p[y] ])
					swap(p[x],p[y]);
				x = p[x];
				y = p[y];
				if(num[x]==0||num[y]==0)
					continue;
				
				for(int i=po[x];i;i=next[i]){
					if(a[i]!=a[i-1])
						tot --;
					if(i<n && a[i]!=a[i+1])
						tot --;
				}
				for(int i=po[x];i;i=next[i])
					a[i] = y;
				int pos = 0;
				for(int i=po[x];i;i=next[i]){
					if(a[i]!=a[i-1])
						tot ++;
					if(i<n && a[i]!=a[i+1])
						tot ++;
					pos = i;
				}
				
				int tmp = next[ po[y] ];
				next[ po[y] ] = po[x];
				next[pos] = tmp;
				
				num[y] += num[x];
				num[x] = 0;
				po[x] = 0;
			}
			else
				printf("%d\n",tot);
		}
	}
	return 0;
}
