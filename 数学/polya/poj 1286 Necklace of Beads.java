/*
 * polya计数原理，寻找循环节
 *
 * */
import java.math.*;
import java.util.*;

public class Main{
	
	public static int gcd(int x,int y){
		return x==0?y:gcd(y%x,x);
	}

	public static void main(String [] args){
		Scanner cin = new Scanner(System.in);
		
		BigInteger three = BigInteger.valueOf(3);

		while(cin.hasNext()){
			int n = cin.nextInt();
			if(n==0){
				System.out.println(0);
				continue;
			}
			if(n==-1)
				break;
			BigInteger ans = BigInteger.ZERO;
			
			BigInteger ret;
			
			for(int i=1;i<=n;i++){
				ret = three.pow( gcd(i,n) );
				ans = ans.add(ret);
			}
			
			if(n%2==1){
				ret = (three.pow((n+1)/2)).multiply(BigInteger.valueOf(n));
				ans = ans.add(ret);
			}
			else{
				BigInteger a = three.pow(n/2);
				BigInteger b = three.pow(n/2+1);
				ret = a.add(b);
				ret = ret.multiply(BigInteger.valueOf(n/2));
				ans = ans.add(ret);
			}
			System.out.println(ans.divide(BigInteger.valueOf(n*2)));
		}
	}
}
