//Author - Rahil Malhotra
#include <bits/stdc++.h>
using namespace std;
 
#define IOS ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
#define endl '\n'
#define int long long
#define double long double
 
int n,m;
set<int>v[100005];
int lvl[100005],par[22][100005];
bool vis[100005];
int tim[2][100005];
int ct=0;
int subtree[100005],partree[100005];
int ans[100005];
int dfs(int i,int p,int l)
{
    par[0][i]=p;
    lvl[i]=l;
    tim[0][i]=++ct;
    for(auto j:v[i])
        if(j!=p)
            dfs(j,i,l+1);
    tim[1][i]=ct;
}
void compute()
{
    for(int i=1;i<22;i++)
        for(int j=1;j<=n;j++)
            if(par[i-1][j])
                par[i][j]=par[i-1][par[i-1][j]];
}
int LCA(int a,int b)
{
    if(lvl[a]<lvl[b])
        swap(a,b);
    int diff=lvl[a]-lvl[b];
    for(int i=21;i>=0;i--)
        if((1<<i)&diff)
            a=par[i][a];
    if(a==b)
        return a;
    for(int i=21;i>=0;i--)
        if(par[i][a] && par[i][a]!=par[i][b])
            a=par[i][a],b=par[i][b];
    return par[0][a];
}
int path(int a,int h)
{
    for(int i=21;i>=0;i--)if((1<<i)&h)a=par[i][a];
    return a;
}
 
int DFSsubtree(int i,int p)
{
    int sum=0;
    for(auto j:v[i])
        if(j!=p)
            sum+=DFSsubtree(j,i);
    sum++;
    subtree[i]=sum;
    return sum;
}
 
int centroid(int i,int p,int sz)
{
    for(auto j:v[i])
        if(j!=p && subtree[j]>sz/2)
            return centroid(j,i,sz);
    return i;
}
void decompose(int i,int p)
{
    DFSsubtree(i,p);
    int cent = centroid(i,p,subtree[i]);
    partree[cent]=p;
    for(auto j:v[cent])
    {
        v[j].erase(cent);
        decompose(j,cent);
    }
}
 
void update(int i,int node)
{
    if(i==0)
        return;
    int lca=LCA(i,node);
    int dist=lvl[i]+lvl[node]-2*lvl[lca];
    ans[i]=min(ans[i],dist);
    update(partree[i],node);
}
int query(int i,int node)
{
    if(i==0)
        return 1e18;
    int lca=LCA(i,node);
    int dist=lvl[i]+lvl[node]-2*lvl[lca];
    return min(dist+ans[i],query(partree[i],node));
}
int32_t main()
{
    IOS;
    cin>>n>>m;
    for(int i=0;i<n-1;i++)
    {
        int a,b;
        cin>>a>>b;
        v[a].insert(b);
        v[b].insert(a);
    }
    dfs(1,0,1);
    compute();
    decompose(1,0);
    for(int i=0;i<n+2;i++)
        ans[i]=1e18;
    update(1,1);
    while(m--)
    {
        int t,v;
        cin>>t>>v;
        if(t==1)
            update(v,v);
        else
            cout<<query(v,v)<<endl;
    }
}