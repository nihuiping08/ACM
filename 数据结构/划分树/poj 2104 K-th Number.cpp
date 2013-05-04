/*

题目：
    有n个数字排成一列，有m个询问，格式为：left right k，即问在区间[left,right]
    第k大的数据为多少？

分析：
    建树的过程比较简单，对于区间[l,r]，首先通过对原数组的排序找到这个区间的中
    位数a[mid]，小于a[mid]的数划入它的左子树[l,mid-1]，大于它的划入右子树[mid,r]。
    同时，对于第i个数a[i]，记录在[l,i]区间内有多少数被划入左子树。最后，对它的左
    子树区间[l,mid-1]和右子树区间[mid,r]递归的继续建树就可以了。
    建树的时候要注意，对于被分到同一子树的元素，元素间的相对位置不能改变。

    查找的过程中主要问题就是确定将要查找的区间。
    查找深度为dep，在大区间[L ,R]中找小区间[l ,r]中的第k元素。
    我们的想法是，先判断[l ,r]中第k元素在[L ,R]的哪个子树中，然后找出对应的小区
    间和k，递归的进行查找，直到小区间的l==r为止。
    通过之前的记录可以知道，在区间[L,l-1]中有(toleft[dep][l-1]-toleft[dep][L-1])
    进入左子树，
    记它为x。

    同理区间[L,r]中有(toleft[dep][r]-toleft[dep][L-1])个数进去左子树，记它为y。
    所以，我们知道区间小区间[l,r]中有(y-x)个数进入左子树。那么如果(y-x)>=k，那么
    就在左子树中继续查找，否则就在右子树中继续查找。

    接着，解决查找的小区间的问题。
    如果接下来要查找的是左子树，那么小区间应该是[L+([L,l-1]区间进入左子树的个
    数),L+([L,r]区间内进入左子树的个数)-1]。即区间[L+x,L+y-1]。
    显然，这里k不用变。
    如果接下来要查找的是右子树，那么小区间应该是[mid+([L,l-1]区间中进入右子树
    的个数),mid+([L,r]区间进入右子树的个数)-1]。
    即区间[mid+(l-L-x),mid+(r-L-y)]。
    显然，这里k要减去区间里已经进入左子树的个数，即k变为k-(y-x)。

*/
#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

const int maxn = 30;
const int maxm = 100005;
#define debug puts("here");

int n,m,sorted[maxm];
int toleft[maxn][maxm];
int data[maxn][maxm];

void build(int l,int r,int depth){
    if(l==r)
        return;

    int mid = (l+r)>>1;
    int ls = mid-l+1;
    int lp = l;
    int rp = mid+1;

    for(int i=l;i<=r;i++)
        if(data[depth][i]<sorted[mid])
            ls--;

    int ok;
    for(int i=l;i<=r;i++){
        ok = 0;
        if(data[depth][i]<sorted[mid]||(data[depth][i]==sorted[mid]&&ls>0)){
            ok = 1;
            data[depth+1][lp++] = data[depth][i];
            if(data[depth][i]==sorted[mid])
                ls--;
        }
        else
            data[depth+1][rp++] = data[depth][i];
        toleft[depth][i] = toleft[depth][i-1]+ok;
    }
    build(l,mid,depth+1);
    build(mid+1,r,depth+1);
}

int ask(int left,int right,int k,int l,int r,int depth){
    if(left==right)
        return data[depth][left];
    int mid = (l+r)>>1;
    int x = toleft[depth][left-1]-toleft[depth][l-1];//位于left左边的放于左子树中的数字个数
    int y = toleft[depth][right]-toleft[depth][l-1];//到right为止位于左子树的个数
    int rx = left-l-x;  //left左边放在右子树中的数字个数
    int ry = right-l-y; //到right右边为止位于右子树的数字个数
    int cnt = y-x;      //[left,right]区间内放到左子树中的个数

    if(cnt>=k)
        return ask(l+x,l+y-1,k,l,mid,depth+1);
    else
        return ask(mid+rx+1,mid+ry+1,k-cnt,mid+1,r,depth+1);
}

int main(){
    freopen("sum.in","r",stdin);
    int l,r,k;
    while(scanf("%d%d",&n,&m)!=EOF){
        for(int i=1;i<=n;i++){
            scanf("%d",&data[0][i]);
            sorted[i] = data[0][i];
        }
        sort(sorted+1,sorted+n+1);
        build(1,n,0);
        while(m--){
            scanf("%d%d%d",&l,&r,&k);
            printf("%d\n",ask(l,r,k,1,n,0));
        }
    }
    return 0;
}
