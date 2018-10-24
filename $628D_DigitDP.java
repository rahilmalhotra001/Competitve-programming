import java.util.*;
import java.io.*;
import java.math.*;
public class $628D_DigitDP
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

    static int m,d;
    static String a,b;
    static long cache[][][];
    public static long dp(int pos,int rem,int less)
    {
        if(pos==b.length())
        {
            if(rem==0)
            return 1;
            return 0;
        }
        if(cache[pos][rem][less]!=-1)
        return cache[pos][rem][less];
        if(less==0)
        {
            long ans=0;
            if(pos%2==1)
            {
                if(d>b.charAt(pos)-48)return cache[pos][rem][less]=0;
                else if(d==b.charAt(pos)-48) return cache[pos][rem][less]=dp(pos+1,(rem*10+d)%m,0);
                else return cache[pos][rem][less]=dp(pos+1,(rem*10+d)%m,1);
            }
            for(int i=0;i<=b.charAt(pos)-48;i++)
            {
                if(pos%2==0&&i==d)continue;
                if(i!=b.charAt(pos)-48||pos==b.length()-1)
                ans+=dp(pos+1,(rem*10+i)%m,1);
                else
                ans+=dp(pos+1,(rem*10+i)%m,0);
                ans%=1000000007;
            }
            return cache[pos][rem][less]=ans;
        }
        else
        {
            long ans=0;
            if(pos%2==1)
            return cache[pos][rem][less]=dp(pos+1,(rem*10+d)%m,1);
            for(int i=0;i<=9;i++)
            {
                if(pos%2==0&&i==d)continue;
                ans+=dp(pos+1,(rem*10+i)%m,1);
                ans%=1000000007;
            }
            return cache[pos][rem][less]=ans;
        }
    }
    public static long dp1(int pos,int rem,int less)
    {
        if(pos==a.length())
        {
            if(less==1&&rem==0)
            return 1;
            return 0;
        }
        if(cache[pos][rem][less]!=-1)
        return cache[pos][rem][less];
        if(less==0)
        {
            long ans=0;
            if(pos%2==1)
            {
                if(d>a.charAt(pos)-48)return cache[pos][rem][less]=0;
                else if(d==a.charAt(pos)-48) return cache[pos][rem][less]=dp1(pos+1,(rem*10+d)%m,0);
                else return cache[pos][rem][less]=dp1(pos+1,(rem*10+d)%m,1);
            }
            for(int i=0;i<=a.charAt(pos)-48;i++)
            {
                if(pos==a.length()-1&&i==a.charAt(pos)-48)continue;//(only <a numbers not <=a)
                if(pos%2==0&&i==d)continue;
                if(i!=a.charAt(pos)-48)
                ans+=dp1(pos+1,(rem*10+i)%m,1);
                else 
                ans+=dp1(pos+1,(rem*10+i)%m,0);
                ans%=1000000007;
            }
            return cache[pos][rem][less]=ans;
        }
        else
        {
            long ans=0;
            if(pos%2==1)
            return cache[pos][rem][less]=dp1(pos+1,(rem*10+d)%m,1);
            for(int i=0;i<=9;i++)
            {
                if(pos%2==0&&i==d)continue;
                ans+=dp1(pos+1,(rem*10+i)%m,1);
                ans%=1000000007;
            }
            return cache[pos][rem][less]=ans;
        }
    }
    public static void main(String[] args)throws IOException
    {
        PrintWriter out= new PrintWriter(System.out);
        Reader sc=new Reader();
        m=sc.i();d=sc.i();
        a=sc.s();
        b=sc.s();
        cache=new long[b.length()][m+1][2];
        for(int i=0;i<b.length();i++)for(int j=0;j<=m;j++)Arrays.fill(cache[i][j],-1);
        long ans1=dp(0,0,0);
        for(int i=0;i<b.length();i++)for(int j=0;j<=m;j++)Arrays.fill(cache[i][j],-1);
        long ans2=dp1(0,0,0);
        out.println((ans1-ans2+1000000007)%1000000007);
        out.flush();
    }
}