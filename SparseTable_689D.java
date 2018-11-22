import java.util.*;
import java.io.*;
import java.math.*;
import java.text.*;
public class SparseTable_689D
{
    static class Reader 
    { 
        private InputStream mIs;private byte[] buf = new byte[1024];private int curChar,numChars;public Reader() { this(System.in); }public Reader(InputStream is) { mIs = is;} 
        public int read() {if (numChars == -1) throw new InputMismatchException();if (curChar >= numChars) {curChar = 0;try { numChars = mIs.read(buf);} catch (IOException e) { throw new InputMismatchException();}if (numChars <= 0) return -1; }return buf[curChar++];} 
        public String nextLine(){int c = read();while (isSpaceChar(c)) c = read();StringBuilder res = new StringBuilder();do {res.appendCodePoint(c);c = read();}while (!isEndOfLine(c));return res.toString() ;} 
        public String s(){int c = read();while (isSpaceChar(c)) c = read();StringBuilder res = new StringBuilder();do {res.appendCodePoint(c);c = read();}while (!isSpaceChar(c));return res.toString();} 
        public long l(){int c = read();while (isSpaceChar(c)) c = read();int sgn = 1;if (c == '-') { sgn = -1 ; c = read() ; }long res = 0; do{ if (c < '0' || c > '9') throw new InputMismatchException();res *= 10 ; res += c - '0' ; c = read();}while(!isSpaceChar(c));return res * sgn;} 
        public int i(){int c = read() ;while (isSpaceChar(c)) c = read();int sgn = 1;if (c == '-') { sgn = -1 ; c = read() ; }int res = 0;do{if (c < '0' || c > '9') throw new InputMismatchException();res *= 10 ; res += c - '0' ; c = read() ;}while(!isSpaceChar(c));return res * sgn;} 
        public double d() throws IOException {return Double.parseDouble(s()) ;}
        public boolean isSpaceChar(int c) { return c == ' ' || c == '\n' || c == '\r' || c == '\t' || c == -1; } 
        public boolean isEndOfLine(int c) { return c == '\n' || c == '\r' || c == -1; } 
        public int[] arr(int n){int[] ret = new int[n];for (int i = 0; i < n; i++) {ret[i] = i();}return ret;}
    }
    
    
 
           //       |----|       /\      |    |   -----   |
           //       |   /       /  \     |    |     |     |
           //       |--/       /----\    |----|     |     |
           //       |   \     /      \   |    |     |     |
           //       |    \   /        \  |    |   -----   -------
    
    static int n,tablemin[][],tablemax[][];
    public static int maxA(int start,int end)
    {
        int p=(int)(Math.log(end-start+1)/Math.log(2));
        return Math.max(tablemax[start][p],tablemax[end-(1<<p)+1][p]);
    }
    public static int minB(int start,int end)
    {
        int p=(int)(Math.log(end-start+1)/Math.log(2));
        return Math.min(tablemin[start][p],tablemin[end-(1<<p)+1][p]);
    }
    public static void main(String args[])throws IOException
    {
        PrintWriter out=new PrintWriter(System.out);
        Reader sc=new Reader();
        int n=sc.i();
        int arr[]=sc.arr(n);
        int brr[]=sc.arr(n);
        
        tablemin=new int[n][(int)(Math.log(n)/Math.log(2))+10];
        tablemax=new int[n][(int)(Math.log(n)/Math.log(2))+10];
        for(int i=0;i<n;i++)
        {
            tablemax[i][0]=arr[i];
            tablemin[i][0]=brr[i];
        }
        for (int j=1;(1<<j)<=n;j++) 
            for (int i=0;(i+(1<<j)-1)<n;i++)
            {
                tablemin[i][j]=Math.min(tablemin[i][j-1],tablemin[i+(1<<(j - 1))][j-1]);
                tablemax[i][j]=Math.max(tablemax[i][j-1],tablemax[i+(1<<(j - 1))][j-1]);
            }
        long ans=0;
        for(int i=0;i<n;i++)
        {
            int low1=i;
            int high1=n-1;
            while(low1<high1)
            {
                int mid=(low1+high1)/2;
                if(maxA(i,mid)<minB(i,mid))
                low1=mid+1;
                else
                high1=mid;
            }
            int low2=i;
            int high2=n-1;
            while(low2<high2)
            {
                int mid=(low2+high2+1)/2;
                if(maxA(i,mid)>minB(i,mid))
                high2=mid-1;
                else
                low2=mid;
            }
            if(low1<=low2&&maxA(i,low1)==minB(i,low1)&&maxA(i,low2)==minB(i,low2))
            ans+=(long)(low2-low1+1);
        }
        out.println(ans);
        out.flush();
    }
}