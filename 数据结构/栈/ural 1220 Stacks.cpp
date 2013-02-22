/*

题目：
    有以下两种操作，id表示栈的编号，val表示值，POP每次都是弹出栈编号为id
    的栈顶，现在问每次POP操作时的元素是多少
    PUSH id val
    POP id

分析：
    这题貌似很简单，但是卡内存，郁闷~~后来利用类似于图的池子法过了。另外
    有一个栈超过了60000个以上的元素，若还是用int型的话，还是会超的，所以
    记录前驱的时候得用unsigned short型，把池子法中的值减掉60000后记录在
    pre中，另外标记的话，可以直接把val值取反即可，在询问时直接先判断即可

*/
#include <cstdio>
#include <cstring>

using namespace std;

const int X = 100001;

unsigned int po[1001];
unsigned short pre[X];
int a[X];
char s[5];
int x,y,n;

int main(){
    freopen("sum.in","r",stdin);
    while(scanf("%d",&n)!=EOF){
        memset(po,0,sizeof(po));
        int tol = 1;
        while(n--){
            scanf("%s%d",s,&x);
            if(s[1]=='U'){
                scanf("%d",&y);
                if(po[x]<60000){
                    a[tol] = y;
                    pre[tol] = po[x];
                }
                else{
                    pre[tol] = po[x]-60000;
                    a[tol] = -y;
                }
                po[x] = tol++;
            }
            else{
                if(a[po[x]]<0){
                    printf("%d\n",-a[po[x]]);
                    po[x] = pre[po[x]]+60000;
                }
                else{
                    printf("%d\n",a[po[x]]);
                    po[x] = pre[po[x]];
                }
            }
        }
    }
    return 0;
}
