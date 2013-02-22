/*
 *题目： 
 * 	给出数字长度为2*n的数，并且该数所有数字之和为s，问总共有多少个这样的数满足条件（可以有前缀0）
 *分析：
 * 	dp[i][j] = ∑(dp[i-1][j-k])，可以利用滚动数组实现降维操作
 */
import java.util.*;
import java.math.*;
public class Main {
	public static void main(String [] args){
		Scanner cin = new Scanner(System.in);
		BigInteger [] dp = new BigInteger[505];
		
		int n,s;
		while(cin.hasNextInt()){
			n = cin.nextInt();
			s = cin.nextInt();
			if((s&1)==1){
				System.out.println(0);
				continue;
			}
			s >>= 1;
			for(int i=1;i<=500;i++)
				dp[i] = BigInteger.ZERO;
			dp[0] = BigInteger.ONE;
			for(int i=1;i<=n;i++)
				for(int j=9*i;j>=1;j--)
					for(int k=1;k<=9&&k<=j;k++)
						dp[j] = dp[j].add(dp[j-k]);
			System.out.println(dp[s].multiply(dp[s]));
		}
	}
}
