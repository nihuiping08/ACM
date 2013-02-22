/*
 * ��Ŀ��
 *		����n*n�ķ��������t����ɫ������ת�������ķ��䡢�ضԽ��߷���������Ϳɫ��
 *		�ʲ��ȼ��������
 *	������
 *		������ת�������������
 *		0�ȣ�ѭ��Ⱥ��n*n��
 *		90�ȡ�270�ȣ�ѭ��Ⱥ��(n*n-n)/2+n��
 *		180�ȣ�ѭ��Ⱥ��(n*n+1)/2��
 *		
 *		���ڷ��䣺
 *		1.�ضԽ��ߣ������֣�����(n*n-n)/2+n
 *		2.�����ģ������֣���nΪ������ʱ��(n*n-n)/2+n;��nΪż����ʱ��(n*n)/2
 *
 *		���Դ� = {  t^(n*n) + t^(n*n+n) + t^(n*n+1)/2 + t^(n*n+n) } + 
 *					t^(n*n+n) // ����
 *					t^(n*n) // ż��
 *
 * */
import java.math.*;
import java.util.*;

public class Main{
	
	public static BigInteger pw(int q,int cnt){
		BigInteger t = BigInteger.valueOf(q);
		BigInteger ans = BigInteger.ONE;
		for(int i=0;i<cnt;i++)
			ans = ans.multiply(t);
		return ans;
	}

	public static void main(String [] args){
		Scanner cin = new Scanner(System.in);
		BigInteger two = BigInteger.valueOf(2);
		while(cin.hasNext()){
			int n = cin.nextInt();
			int t = cin.nextInt();
			BigInteger ans = BigInteger.ZERO;
			ans = ans.add( pw( t , n*n ) ); // 0
			ans = ans.add( pw( t , (n*n+3)/4) ); // 90
			ans = ans.add( pw( t , (n*n+1)/2 ) ); // 180
			ans = ans.add( pw( t , (n*n+3)/4 ) ); // 270
			ans = ans.add( pw( t , (n*n-n)/2+n ).multiply(two) ); // �Խ���
			if(n%2==1)  // �Գ�
				ans = ans.add( pw( t , (n*n-n)/2+n ).multiply(two) );
			else
				ans = ans.add( pw( t , (n*n)/2 ).multiply(two) );
			System.out.println(ans.divide(BigInteger.valueOf(8)));
		}
	}
}
