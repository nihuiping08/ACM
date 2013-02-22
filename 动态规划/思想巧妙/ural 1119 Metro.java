/*
 * ��Ŀ��
 * 		����һ��n*m�ľ��Σ��ʴӣ�0,0���ߵ���n,m����ֻ������������ߣ����õ�Ϊ������k����֮һ����������������µ����
 * 		��С�ľ���
 * 
 * ����:
 * 		��ʹ�ö�ά��DP�Ļ����ȽϺ��룬dp[i][j] = min(dp[i][j-1],dp[i-1][j])+1�����õ�������㣬��Ӷ�һ���ж�
 * 		dp[i][j] = min(dp[i][j],dp[i-1][j-1]+sqrt(2))
 * 		
 * 		��������Ŀ���ڴ����ƣ����Ե�Ҫ�ù����������ʽ����ռ䣬������a[i]��¼��һ��i�е�״̬��������b[i]��ʾ��ǰλ�õ�״
 * 		̬����״̬ת�Ʒ��̿����Ƴ�������
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

