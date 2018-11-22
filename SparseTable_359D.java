import java.util.*;
import java.io.*;
import java.math.*;
import java.text.*;
public class SparseTable_359D
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

    public static int GCD(int a, int b) 
    {
       if (b==0) 
       return a;
       return GCD(b,a%b);
    }       
    static int n,arr[],tablemin[][],tablegcd[][];
    public static boolean check(int cons)
    {
        int p=(int)(Math.log(cons)/Math.log(2));
        for(int i=0;i<n-cons+1;i++)
        {
            int a=Math.min(tablemin[i][p],tablemin[i+cons-1-(1<<p)+1][p]);
            int b=GCD(tablegcd[i][p],tablegcd[i+cons-1-(1<<p)+1][p]);
            if(a==b)return true;
        }
        return false;
    }
    static PrintWriter out;
    public static void print(int cons)
    {
        ArrayList<Integer> al=new ArrayList<>();
        int p=(int)(Math.log(cons)/Math.log(2));
        for(int i=0;i<n-cons+1;i++)
        {
            int a=Math.min(tablemin[i][p],tablemin[i+cons-1-(1<<p)+1][p]);
            int b=GCD(tablegcd[i][p],tablegcd[i+cons-1-(1<<p)+1][p]);
            if(a==b)
            al.add(i+1);
        }
        out.println(al.size()+" "+(cons-1));
        for(int i:al)out.print(i+" ");
    }
    public static void main(String[] args)throws IOException
    {
        out= new PrintWriter(System.out);
        Reader sc=new Reader();
        n=sc.i();
        arr=sc.arr(n);
        tablemin=new int[n][(int)(Math.log(n)/Math.log(2))+10];
        tablegcd=new int[n][(int)(Math.log(n)/Math.log(2))+10];
        for(int i=0;i<n;i++)
            tablemin[i][0]=arr[i];
        for (int j=1;(1<<j)<=n;j++) 
            for (int i=0;(i+(1<<j)-1)<n;i++)
                tablemin[i][j]=Math.min(tablemin[i][j-1],tablemin[i+(1<<(j - 1))][j-1]); 
                
        for(int i=0;i<n;i++)
            tablegcd[i][0]=arr[i];        
        for (int j=1;(1<<j)<=n;j++) 
            for (int i=0;(i+(1<<j)-1)<n;i++)
                tablegcd[i][j] = GCD(tablegcd[i][j-1],tablegcd[i+(1<<(j-1))][j-1]); 
        
        int low=0;
        int high=n;
        while(low<high)
        {
            int mid=(low+high+1)/2;
            if(!check(mid))
            high=mid-1;
            else
            low=mid;
        }
        print(low);
        out.flush();
    }
}