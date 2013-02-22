/*

	m�ﵽ10^9����Ȼ����ֱ���㡣
    ��Ϊk����������֮����ǹ̶��ģ������뵽�þ��󣬾�������ݿ��԰�ʱ�临�ӶȽ���O��logm����
	����ת��Ϊ��ι���ת�þ���
    ˵���ҵ�˼·���۲��������ֲ��������ֵڶ������ֲ����Ƚ����״����ص����ڵ�һ�ֲ����ϡ�
    ��һ���ܺõİ취�������һ��������ʹ��ʼ�����Ϊһ��n+1Ԫ�飬���Ϊ0��n��������3��èΪ����
    �����ʼ����A = [1 0 0 0]��0��Ԫ�ع̶�Ϊ1��1~n�ֱ�Ϊ��Ӧ��è��ӵ�еĻ�������
    ���ڵ�һ�ֲ���g i�������ڵ�λ���������ʹMat[0][i]��Ϊ1������g 1��
    1 1 0 0
    0 1 0 0
    0 0 1 0
    0 0 0 1����Ȼ[1 0 0 0]*Mat = [1 1 0 0]
    ���ڵڶ��ֲ���e i�������ڵ�λ�������ʹMat[i][i] = 0,����e 2��
    1 0 0 0
    0 1 0 0
    0 0 0 0
    0 0 0 1, ��Ȼ[1 2 3 4]*Mat = [1 2 0 4]
    ���ڵ����ֲ���s i j�������ڵ�λ���������ʹ��i�����j����������s 1 2��
    1 0 0 0
    0 0 0 1
    0 0 1 0
    0 1 0 0����Ȼ[1 2 0 4]*Mat = [1 4 0 2]
    ���ڣ�����ÿһ���������Ƕ����Եõ�һ��ת�þ��󣬰�k�������ľ���������ǿ��Եõ�һ����
	��ת�þ���T��
    A * T ��ʾ���Ǿ���һ��������������ǿ��Եõ�����m������ľ���Ϊ A * T ^ m,���վ����
	[0][1~n]��Ϊ�𰸡�

    �����������Ƚ�ֱ�ۣ�����ʵ�ֹ����鷳����ΪҪ����k����ͬ����

    ��û�б�ķ�������ֱ�ӹ���ת�þ���T�����ǿ϶��ġ�
    ���ǻ����Ե�λ����Ϊ������
    ���ڵ�һ�ֲ���g i������ʹMat[0][i] = Mat[0][i] + 1��
    ���ڵڶ��ֲ���e i������ʹ����ĵ�i�����㣻
    ���ڵ����ֲ���s i j������ʹ��i�����j�л�����
    ����ʵ�ֵĻ�������ʼ���ڴ���һ��������ȥ����k��������鷳��

    ���ˣ�����ת�þ���T������ˣ�������ֻ���þ����������� A * T ^ m���ɣ�����һ��ע��ĵط���
	������Ҫ�õ�long long��

*/
#include <iostream>
#include <cstdio>
#include <cstring>

using namespace std;

const int X = 105;

typedef long long ll;

class matrix{
    public:
        int n,m;
        ll a[X][X];

        matrix(){
            memset(a,0,sizeof(a));
        }
        matrix(int _n,int _m):n(_n),m(_m){
            memset(a,0,sizeof(a));
        }

        matrix operator * (matrix p){
            int q = p.m;
            matrix c(n,q);
            for(int i=0;i<n;i++)
                for(int k=0;k<q;k++)
                    if(a[i][k])
                        for(int j=0;j<m;j++)
                            c.a[i][j] += a[i][k]*p.a[k][j];
            return c;
        }

        void getE(){
            for(int i=0;i<n;i++)
                a[i][i] = 1;
        }

        matrix pow(int exp){
            matrix temp(n,n);
            temp.getE();
            matrix cur = *this;

            while(exp>0){
                if(exp&1)
                    temp = temp*cur;
                cur = cur*cur;
                exp = exp >> 1;
            }
            return temp;
        }

        void display(){
            for(int i=0;i<n;i++){
                for(int j=0;j<m;j++)
                    cout<<a[i][j]<<" ";
                cout<<endl;
            }
            cout<<endl;
        }

};

int main(){
    freopen("sum.in","r",stdin);
    int n,m,q,x,y;
    char op[2];
    while(cin>>n>>m>>q,n||m||q){
        matrix ans(n+1,n+1);
        matrix a(1,n+1);
        ans.getE();
        a.a[0][0] = 1;
        while(q--){
            scanf("%s%d",op,&x);
            if(op[0]=='g')
                ans.a[0][x] ++;
            else if(op[0]=='e'){
                for(int i=0;i<=n;i++)
                    ans.a[i][x] = 0;
            }
            else{
                scanf("%d",&y);
                for(int i=0;i<=n;i++)
                    swap(ans.a[i][x],ans.a[i][y]);
            }
        }
        //ans.display();
        ans = ans.pow(m);
        //ans.display();
        ans = a*ans;
        //ans.display();
        cout<<ans.a[0][1];
        for(int i=2;i<=n;i++)
            printf(" %I64d",ans.a[0][i]);
        puts("");
    }
    return 0;
}
