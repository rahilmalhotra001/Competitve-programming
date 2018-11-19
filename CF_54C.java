import java.util.*;
import java.io.*;
import java.math.*;
import java.text.*;
public class CF_54C
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

    static long digcache[][][];
    static String s;  
    public static long digdp(int pos,int check,int ones)
    {
        if(pos==65)
        {
            if(ones==1&&check==1)
            return 1;
            return 0;
        }
        if(digcache[pos][check][ones]!=-1)
        return digcache[pos][check][ones];
        if(check==1)
        {
            long ans=digdp(pos+1,check,ones);
            for(int i=1;i<=9;i++)
            {
                if(i==1)
                {
                    if(ones==0)
                    ans+=digdp(pos+1,check,1);
                    else
                    ans+=digdp(pos+1,check,ones);
                }
                else
                {
                    if(ones==1)
                    ans+=digdp(pos+1,check,ones);
                    else
                    ans+=digdp(pos+1,check,2);
                }
            }
            return digcache[pos][check][ones]=ans;
        }
        else
        {
            long ans=0;
            for(int i=0;i<=s.charAt(pos)-48;i++)
            {
                if(i==s.charAt(pos)-48)
                {
                    if(i==0)
                    ans+=digdp(pos+1,check,ones);
                    else
                    {
                        if(i==1)
                        {
                            if(ones==0)
                            ans+=digdp(pos+1,check,1);
                            else
                            ans+=digdp(pos+1,check,ones);
                        }
                        else
                        {
                            if(ones==1)
                            ans+=digdp(pos+1,check,ones);
                            else
                            ans+=digdp(pos+1,check,2);
                        }
                    }
                }
                else
                {
                    if(i==0)
                    ans+=digdp(pos+1,1,ones);
                    else
                    {
                        if(i==1)
                        {
                            if(ones==0)
                            ans+=digdp(pos+1,1,1);
                            else
                            ans+=digdp(pos+1,1,ones);
                        }
                        else
                        {
                            if(ones==1)
                            ans+=digdp(pos+1,1,ones);
                            else
                            ans+=digdp(pos+1,1,2);
                        }
                    }
                }
            }
            return digcache[pos][check][ones]=ans;
        }
    }
    public static long f(long r)
    {
        StringBuilder s1=new StringBuilder(Long.toString(r));
        s1=s1.reverse();
        while(s1.length()!=65)
        s1=s1.append("0");
        s1=s1.reverse();
        s=s1.toString();
        digcache=new long[66][2][3];
        for(int i=0;i<66;i++)for(int j=0;j<2;j++)Arrays.fill(digcache[i][j],-1l);
        return digdp(0,0,0);
    }
    static int n,k;
    static long arr[][];
    static double cache[][];
    public static double dp(int i,int taken)
    {
        if(i==n)
        {
            if(taken*100>=n*k)
            return 1.0;
            return 0.0;
        }
        if(cache[i][taken]!=-1)
        return cache[i][taken];
        double ans=arr[i][0]*1.0/arr[i][1]*dp(i+1,taken+1)+((arr[i][1]-arr[i][0])*1.0/arr[i][1])*dp(i+1,taken);
        return cache[i][taken]=ans;
    }
    public static void main(String args[])throws IOException
    {
        PrintWriter out=new PrintWriter(System.out);
        Reader sc=new Reader();
        n=sc.i();
        arr=new long[n][2];
        for(int i=0;i<n;i++)
        {
            long a=sc.l();
            long b=sc.l();
            arr[i][1]=b-a+1;
            arr[i][0]=f(b+1)-f(a);
        }
        k=sc.i();
        cache=new double[n+1][n+1];
        for(int i=0;i<=n;i++)Arrays.fill(cache[i],-1);
        out.println(dp(0,0));
        out.flush();
    }
}