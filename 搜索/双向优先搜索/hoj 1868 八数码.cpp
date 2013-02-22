/*

��Ŀ��
    ����������

������
    �����������н�ĳ��������Ҫ��������ż��ͬ�������������˫������������������
    ˫������������������ͨ��BFS����������һ�������ķ��򣬴��յ㿪ʼ����������Ĺ��̣�
    ����������һ���ѵ���������һ�������ѹ���λ�õ�ʱ�򣬾�������ߵľ���֮�͡�
    �����¼״̬��ʱ�����뵽���ǿɲ�������map����¼������һ��9λ����int�ͣ�Ȼ��ÿ��
    ����λ�õ�ʱ���Ȱ���������λ������������£�Ȼ��������Ԥ�ȼ���õ�ƫ������ʵ��
    λ�õ�ת���������˴����Ĵ��롣

*/
#include <cstdio>
#include <cstring>
#include <map>

using namespace std;

const int X = 370005;
#define debug cout<<"here"<<endl;

int a[9],b[9];
int dir[10][5] =
{
    {1,3},{-1,1,3},{-1,3},{-3,1,3},{-3,-1,1,3},{-3,-1,3},{-3,1},{-3,-1,1},{-3,-1}
};

struct node
{
    int state;
    int step;
}qa[X],qb[X];

int heada,taila,headb,tailb;

int cal(int *a)
{
    int ans = 0;
    for(int i=0;i<9;i++)
        ans = ans*10+a[i];
    return ans;
}

int ask_id(int state)
{
    int i;
    for(i=0;i<9;i++)
    {
        if(state%10==0)
            break;
        state /= 10;
    }
    return 9-i;
}

int bfs()
{
    node na,nb,cur;

    na.state = cal(a);
    na.step = 0;
    nb.state = cal(b);
    nb.step = 0;

    int cx = na.state;
    int cy = nb.state;

    heada = headb = 0;
    taila = tailb = 0;

    qa[heada++] = na;
    qb[headb++] = nb;

    map<int,int> usea;
    map<int,int> useb;

    int id,temp,cnt,x,y,t;
    int c[9];

    while(taila<heada&&tailb<headb)
    {
        na = qa[(taila++)%X];

        nb = qb[(tailb++)%X];

        if(na.state==cy)
            return na.step;
        if(nb.state==cx)
            return nb.step;
        if(useb[na.state])
            return useb[na.state]+na.step-1;
        if(usea[nb.state])
            return usea[nb.state]+nb.step-1;

        id = ask_id(na.state);
        temp = na.state;

        for(cnt=8;cnt>=0;cnt--)
        {
            c[cnt] = temp%10;
            temp /= 10;
        }
        for(id=0;id<9;id++)
            if(c[id]==0)
                break;
        for(int i=0;i<4;i++)
        {
            x = id+dir[id][i];
            if(x==id)
                break;

            t = c[id];
            c[id] = c[x];
            c[x] = t;

            y = cal(c);
            if(useb[y])
                return na.step+1+useb[y];

            else if(!usea[y])
            {
                cur.state = y;
                cur.step = na.step+1;
                qa[(heada++)%X] = cur;
                usea[y] = cur.step;
            }
            t = c[id];
            c[id] = c[x];
            c[x] = t;
        }

        id = ask_id(nb.state);
        temp = nb.state;

        for(cnt=8;cnt>=0;cnt--)
        {
            c[cnt] = temp%10;
            temp /= 10;
        }

        for(id=0;id<9;id++)
            if(c[id]==0)
                break;
        for(int i=0;i<4;i++)
        {
            x = id+dir[id][i];
            if(x==id)
                break;

            t = c[id];
            c[id] = c[x];
            c[x] = t;

            y = cal(c);
            if(usea[y])
                return nb.step+1+usea[y];
            else if(!useb[y])
            {
                cur.state = y;
                cur.step = nb.step+1;
                qb[(headb++)%X] = cur;
                useb[y] = cur.step;
            }
            t = c[id];
            c[id] = c[x];
            c[x] = t;
        }
    }
    return -1;
}

int main()
{
    freopen("sum.in","r",stdin);

    int ncase;
    scanf("%d",&ncase);
    int x,y;
    while(ncase--)
    {
        for(int i=0;i<9;i++)
            scanf("%d",&a[i]);
        for(int j=0;j<9;j++)
            scanf("%d",&b[j]);
        x = y = 0;
        for(int i=0;i<9;i++)
            for(int j=i+1;j<9;j++)
            {
                if(a[i]&&a[j]&&a[i]>a[j])
                    x++;
                if(b[i]&&b[j]&&b[i]>b[j])
                    y++;
            }
        if(x>y)
            swap(x,y);
        if((y-x)%2)
            puts("-1");
        else
            printf("%d\n",bfs());
    }
    return 0;
}
