import java.util.*;
import java.math.*;

public class Main {
	public static void main(String [] args){
		int n;
		Scanner cin = new Scanner(System.in);
		while(cin.hasNext()){
			n = cin.nextInt();
			BigInteger [] dp = new BigInteger[n+10];
			BigInteger x2 = BigInteger.valueOf(2);
			BigInteger x3 = BigInteger.valueOf(3);

			dp[1] = BigInteger.ONE;
			dp[2] = x2.add(x3);
			for(int i=3;i<=n;i++)
				dp[i] = ((dp[i-1].multiply(x3)).subtract(dp[i-2])).add(x2);
			System.out.println(dp[n]);
		}
	}
}
