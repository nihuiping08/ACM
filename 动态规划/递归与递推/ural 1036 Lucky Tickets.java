/*
 *��Ŀ�� 
 * 	�������ֳ���Ϊ2*n���������Ҹ�����������֮��Ϊs�����ܹ��ж��ٸ�������������������������ǰ׺0��
 *������
 * 	dp[i][j] = ��(dp[i-1][j-k])���������ù�������ʵ�ֽ�ά����
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
