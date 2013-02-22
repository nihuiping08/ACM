/*
 * 题目：
 * 		给出一个n*m的矩形，问从（0,0）走到（n,m），只能往左或者上走，若该点为给出的k个点之一，则可以由他的左下到达，问
 * 		最小的距离
 * 
 * 分析:
 * 		若使用二维的DP的话，比较好想，dp[i][j] = min(dp[i][j-1],dp[i-1][j])+1，若该点是特殊点，则加多一个判断
 * 		dp[i][j] = min(dp[i][j],dp[i-1][j-1]+sqrt(2))
 * 		
 * 		但由于题目的内存限制，所以得要用滚动数组的形式化简空间，用数组a[i]记录上一行i列的状态，用数组b[i]表示当前位置的状
 * 		态，这状态转移方程可以推出。。。
 * 
 * */
import java.util.*;

public class Main {
	
	public static void main(String [] args){
		Scanner cin = new Scanner(System.in);
		double con=1.4142135623730950488016887242097;
		
		while(cin.hasNext()){
			int n = cin.nextInt();
			int m = cin.nextInt();
			int k = cin.nextInt();
			
			node [] p = new node[k+1];
			
			double [] a = new double [m+1];
			double [] b = new double [m+1];
			
			int x,y;
			
			for(int i=0;i<k;i++){
				x = cin.nextInt();
				y = cin.nextInt();
				p[i] = new node(x,y);
			}
			
			for(int i=1;i<=m;i++)
				a[i] = i;
			
			for(int i=1;i<=n;i++){
				b[0] = i;
				for(int j=1;j<=m;j++){
					boolean ok = false;
					for(int qq=0;qq<k;qq++)
						if(p[qq].x==i&&p[qq].y==j){
							ok = true;
							break;
						}
					b[j] = min(b[j-1]+1,a[j]+1);
					if(ok)
						b[j] = min(b[j],a[j-1]+con);
				}
				for(int j=0;j<=m;j++)
					a[j] = b[j];
			}
			
			System.out.printf("%.0f\n",b[m]*100);
		}
	}
	public static double min(double x,double y){
		return x<y?x:y;
	}
	
	public static class node{
		node(){}
		node(int _x,int _y){
			x = _x;
			y = _y;
		}
		
		public int x;
		public int y;
	}
}

