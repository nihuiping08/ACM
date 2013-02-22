/*
 * 题目：
 * 		给出一个字符串矩阵，问如何涂色，使得在宽度为x到y（以列为一格）范围内为同种颜色，使得涂色的次数最小
 * 
 * 分析：
 * 		字符串处理DP，先预处理出每列中有多少个相同的颜色，然后进行状态转移
 * */
 
import java.util.*;

public class Main {
	
	public static void main(String [] auges){
		int maxm = 1010;
		
		int n,m,x,y;
		Scanner cin = new Scanner(System.in);
		n = cin.nextInt();
		m = cin.nextInt();
		x = cin.nextInt();
		y = cin.nextInt();

		char [][] s = new char [maxm][maxm];
		int [][] dp = new int[2][maxm]; 	//0 加 ， 1 减
		int [] sum = new int [maxm];
		int [] a = new int [maxm];

		

		Arrays.fill(sum, 0);
		Arrays.fill(a, 0);
		for(int i=0;i<=1;i++)
			for(int j=0;j<=m;j++)
				dp[i][j] = 1000000;
		
		for(int i=0;i<n;i++)
			s[i] = cin.next().toCharArray();

		for(int i=1;i<=m;i++){
			for(int j=1;j<=n;j++)
				if(s[j-1][i-1]=='#')
					a[i]++;
			sum[i] = sum[i-1]+a[i];
		}
		
		for(int i=x;i<=y;i++){
			dp[0][i] = sum[i];
			dp[1][i] = i*n-sum[i];
		}

		for(int i=1;i<=m;i++)
			for(int j=max(i-y,1);j<=i-x;j++){
				dp[0][i] = min(dp[0][i],dp[1][j]+sum[i]-sum[j]);
				dp[1][i] = min(dp[1][i],dp[0][j]+i*n-sum[i]-j*n+sum[j]);
			}
		
		System.out.println(min(dp[0][m],dp[1][m]));
	}
	

	public static int max(int a,int b){
		if(a>b)
			return a;
		return b;
	}
	
	public static int min(int a,int b){
		if(a<b)
			return a;
		return b;
	}
}
