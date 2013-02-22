/*

��Ŀ��
    ���б���m�У���m�ж������������������У���ÿһ����n�����֣���Щ���ֻ�
    ����ͬ����ÿ�����ֶ���1��n֮�䡣һ��ʼ����Ʒ�����о���������Ʒ������λ
    �ã�Ҳ����˵��һ��ʼ��Ʒ�����о���1��2��3��4����n����ôȻ�����ǿ��б��
    ��һ�в���������һ�в����ĵ�i������Ϊa[i]����ô�Ͱ�ԭ�������еĵ�a[i]��
    ����ŵ�����������еĵ�i��λ���ϣ�Ȼ������µ��������С�Ȼ�󣬿��б��
    �ڶ��в��������������в�������һֱ�����һ�в������ظ�����Ĳ����������һ��
    �Ĳ�������������˵������ְ��յ�һ����������Ȼ��ڶ��в������������в�������
    һֱѭ����ȥ��ֱ��һ��������k��Ϊֹ��������ɵ�������о�������������Ʒ
    �͸������ǵ������ˡ�

������
    ����������Լ�����˷������忴Matrix 67

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

#define debug puts("here")

const int MAXN = 102;
const int MAXM = 11;

int n,m;

class Matrix{
public:
    int a[MAXN][MAXN];

    Matrix(){
        memset(a,0,sizeof(a));
    }

    void setE(){
        memset(a,0,sizeof(a));
        for(int i=0;i<n;i++)
            a[i][i] = 1;
    }

    Matrix operator * (Matrix b){
        Matrix c = Matrix();
        for(int i=0;i<n;i++)
            for(int j=0;j<n;j++)
                for(int k=0;k<n;k++)
                    c.a[i][j] += a[i][k]*b.a[k][j];
        return c;
    }

    Matrix bin(int exp){
        Matrix ans;
        Matrix cur = *this;
        ans.setE();
        while(exp>0){
            if(exp&1)
                ans = ans*cur;
            cur = cur*cur;
            exp >>= 1;
        }
        return ans;
    }
    void di(){
        for(int i=0;i<n;i++){
            for(int j=0;j<n;j++)
                cout<<a[i][j]<<" ";
            cout<<endl;
        }
        cout<<endl;
    }
};

int main(){

#ifndef ONLINE_JUDGE
	freopen("sum.in","r",stdin);
#endif

    int k;
    while(cin>>n>>m>>k){
        int x;
        Matrix ans;
        ans.setE();
        Matrix ret[12];
        ret[0].setE();

        for(int i=0;i<m;i++){
            Matrix cur;
            for(int j=0;j<n;j++){
                scanf("%d",&x);
                cur.a[j][x-1] = 1;
            }
            ret[i+1] = cur*ret[i];
            //ret[i+1].di();
            ans = cur*ans;
        }

        ans = ans.bin(k/m);
        ans = ret[k%m]*ans;
        //ans.di();

        for(int i=0;i<n;i++)
            for(int j=0;j<n;j++){
                if(ans.a[i][j]){
                    if(i)
                        cout<<" ";
                    cout<<j+1;
                    break;
                }
            }
        cout<<endl;
    }
	return 0;
}
