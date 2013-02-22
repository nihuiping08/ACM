import java.util.*;

public class Main {
	public static void main(String [] args){
		Scanner cin = new Scanner(System.in);
		int maxm = 1000005;
		
		int [] id = new int [maxm];
		int [] pval = new int [maxm];
		
		int [] a = new int[maxm];
		int val;
		
		while(cin.hasNext()){
			int n = cin.nextInt();
			int m = cin.nextInt();
			
			int head = 0,tail = 0;
			boolean ok = false;
			
			for(int i=0;i<n;i++){
				val = cin.nextInt();
				a[i] = val;
				
				while(head<tail){
					if(id[head]+m-1<i)
						head++;
					else
						break;
				}
				while(head<tail){
					if(pval[tail-1]>=val)
						tail--;
					else
						break;
				}
				id[tail] = i;
				pval[tail++] = val;
				if(i>=m-1){
					if(ok)
						System.out.print(" ");
					else
						ok = true;
					System.out.print(pval[head]);
				}
			}
			
			System.out.println();
			
			head = tail = 0;
			ok = false;
			for(int i=0;i<n;i++){
				val = a[i];
				while(head<tail){
					if(id[head]+m-1<i)
						head++;
					else
						break;
				}
				while(head<tail){
					if(pval[tail-1]<=val)
						tail--;
					else
						break;
				}
				id[tail] = i;
				pval[tail++] = val;
				if(i>=m-1){
					if(ok)
						System.out.print(" ");
					else
						ok = true;
					System.out.print(pval[head]);
				}
			}
			System.out.println();
		}
	}
	
}
