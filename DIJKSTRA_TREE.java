import java.util.*;
import java.io.*;
import java.math.*;
import java.text.*;
public class DIJKSTRA_TREE
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

    static class pair 
    {
       int x;
       long w;
       int index;
       public pair (int k,long p,int c) 
       {
           x=k;
           w=p;
           index = c;
       }
       @Override
       public boolean equals(Object o) {
            if (this == o) return true;
            if (o == null || getClass() != o.getClass()) return false;
            pair pair = (pair) o;
            return x == pair.x && w==pair.w && index==pair.index;
        }
    
       @Override
       public int hashCode() {
            return Objects.hash(x,w,index);
       }
    }
    static class PC implements Comparator<pair>
    {
        public int compare(pair first, pair second) 
        {
            if(first.w<second.w)return -1;
            else if(first.w>second.w)return 1;
            return 0;
        }
    }
    static LinkedList<pair> adj[];
    static int n,m,k;
    public static void main(String[] args)throws IOException
    {
        PrintWriter out= new PrintWriter(System.out);
        Reader sc=new Reader();
        n=sc.i();m=sc.i();k=sc.i();
        adj=new LinkedList[n];
        for(int i=0;i<n;i++)
            adj[i]=new LinkedList<>();
        for(int i=0;i<m;i++)
        {
            int a=sc.i(),b=sc.i();
            long c=sc.l();
            a--;b--;
            adj[a].add(new pair(b,c,i+1));
            adj[b].add(new pair(a,c,i+1));
        }
        PriorityQueue<pair> pq = new PriorityQueue<pair>(new PC());
        long mindis[]=new long[n];
        Arrays.fill(mindis,(long)Math.pow(10,18));
        mindis[0]=0;
        pq.add(new pair(0,0,-1));
        
        //ArrayList has the indexes of all the edges part of the dijkstra tree.
        ArrayList<Integer> al=new ArrayList<>();
        while(pq.size()!=0)
        {
            pair p=pq.remove();
            if(p.index!=-1&&mindis[p.x]==p.w)
            al.add(p.index);
            for(pair a:adj[p.x])
            {
                if(a.w+p.w<mindis[a.x])
                {
                    mindis[a.x]=a.w+p.w;
                    pq.add(new pair(a.x,a.w+p.w,a.index));
                }
            }
        }
        for(int i=0;i<al.size();i++)
        out.print(al.get(i)+" ");
        out.flush();
    }
}