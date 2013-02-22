/*

ural 1521
http://ac.jobdu.com/problem.php?pid=1188
��Ŀ1188��Լɪ��
��Ŀ������
N����Χ��һȦ˳���ţ���1�ſ�ʼ��1��2��3......˳��������p���˳�Ȧ�⣬��������ٴ�1��2��3��ʼ��������p�������˳�Ȧ�⣬�Դ����ơ�
�밴�˳�˳�����ÿ���˳��˵�ԭ��š�

���룺
����һ������N(1<=N<=3000)��һ������p��

�����
�������ݿ����ж��飬����ÿһ�����ݣ�
���˳�˳�����ÿ���˳��˵�ԭ��š�

�������룺
7 3
���������
3 6 2 7 5 1 4

*/

/*

������
    �Ȱ������˲��뵽SBT�У�Ȼ���ȥ��ʱ�򣬰�����SBT��ɾ�������ҵ�Ҫɾ����
    Ԫ��Ϊpos = (pre+k-1)%n+1��nÿ��ȥһ���˼�һ����pre��0��ʼ�����Ѿ�����
    ���ӣ�����Ϊ��һ���˳��ӵ�λ�ü�һ��Ȼ������ҵ���posС����

*/

#include <iostream>
#include <cstdio>
#include <cstring>

using namespace std;

const int X = 100005;

int root,tol,n,m;

struct node{
    int val,l,r,s;
    void init(int _val){
        l = r = 0;
        s = 1;
        val = _val;
    }
}sbt[X];

void left_rotate(int &t){
    int k = sbt[t].r;
    sbt[t].r = sbt[k].l;
    sbt[k].l = t;
    sbt[k].s = sbt[t].s;
    sbt[t].s = sbt[sbt[t].l].s+sbt[sbt[t].r].s+1;
    t = k;
}

void right_rotate(int &t){
    int k = sbt[t].l;
    sbt[t].l = sbt[k].r;
    sbt[k].r = t;
    sbt[k].s = sbt[t].s;
    sbt[t].s = sbt[sbt[t].l].s+sbt[sbt[t].r].s+1;
    t = k;
}

void maintain(int &t,bool ok){
    if(!ok){
        if(sbt[sbt[sbt[t].l].l].s>sbt[sbt[t].r].s)
            right_rotate(t);
        else if(sbt[sbt[sbt[t].l].r].s>sbt[sbt[t].r].s){
            left_rotate(sbt[t].l);
            right_rotate(t);
        }
        else return;
    }
    else{
        if(sbt[sbt[sbt[t].r].r].s>sbt[sbt[t].l].s)
            left_rotate(t);
        else if(sbt[sbt[sbt[t].r].l].s>sbt[sbt[t].l].s){
            right_rotate(sbt[t].r);
            left_rotate(t);
        }
        else return;
    }
    maintain(sbt[t].l,0);
    maintain(sbt[t].r,1);
    maintain(t,0);
    maintain(t,1);
}

void insert(int &t,int val){
    if(!t){
        t = ++tol;
        sbt[t].init(val);
        return;
    }
    sbt[t].s++;
    if(val<sbt[t].val)
        insert(sbt[t].l,val);
    else
        insert(sbt[t].r,val);
    maintain(t,val>=sbt[t].val);
}

int del(int &t,int val){
    if(!t)  return 0;
    sbt[t].s--;
    if(val==sbt[t].val||(val<sbt[t].val&&!sbt[t].l)||(val>sbt[t].val&&!sbt[t].r)){
        if(sbt[t].l&&sbt[t].r){
            int pos = del(sbt[t].l,val+1);
            sbt[t].val = sbt[pos].val;
            return pos;
        }
        else{
            int pos = t;
            t = sbt[t].l+sbt[t].r;
            return pos;
        }
    }
    else
        return del(val<sbt[t].val?sbt[t].l:sbt[t].r,val);
}

int find_k_min(int &t,int k){   //�ҵ���kС
    if(k<=sbt[sbt[t].l].s)
        return find_k_min(sbt[t].l,k);
    else if(k>sbt[sbt[t].l].s+1)
        return find_k_min(sbt[t].r,k-sbt[sbt[t].l].s-1);
    else
        return sbt[t].val;
}

int main()
{
    freopen("sum.in","r",stdin);
    freopen("sum.out","w",stdout);
    while(cin>>n>>m){
        int pos = 0,temp,val;
        root = tol = 0;
        for(int i=1;i<=n;i++)
            insert(root,i);
        while(n){
            temp = (pos+m-1)%n+1;
            pos = temp-1;
            val = find_k_min(root,temp);
            del(root,val);
            printf("%d",val);
            if(n>1)
                putchar(' ');
            n--;
        }
        puts("");
    }
    return 0;
}
