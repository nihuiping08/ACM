class Matrix{
    public:
        int n,m;
        int a[MAXN][MAXN];

        Matrix(){
            memset(a,0,sizeof(a));
        }
        Matrix(int _n,int _m):n(_n),m(_m){
            memset(a,0,sizeof(a));
        }

        Matrix operator * (Matrix p){
            int q = p.m;
            Matrix c(n,q);
            for(int i=0;i<n;i++)
                for(int k=0;k<q;k++)
                    if(a[i][k])
                        for(int j=0;j<m;j++)
                            c.a[i][j] = (c.a[i][j]+a[i][k]*p.a[k][j])%MOD;
            return c;
        }

        void setE(){
            for(int i=0;i<n;i++)
                a[i][i] = 1;
        }

        Matrix bin(int exp){
            Matrix temp(n,n);
            temp.setE();
            Matrix cur = *this;

            while(exp>0){
                if(exp&1)
                    temp = temp*cur;
                cur = cur*cur;
                exp = exp >> 1;
            }
            return temp;
        }

        void Debug(){
            for(int i=0;i<n;i++){
                for(int j=0;j<m;j++)
                    cout<<a[i][j]<<" ";
                cout<<endl;
            }
            cout<<endl;
        }
};