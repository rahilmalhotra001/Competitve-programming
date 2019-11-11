//Author - Rahil Malhotra
#include <bits/stdc++.h>
using namespace std;
 
#define IOS ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
#define endl '\n'
//#define int long long
#define double long double
 
int k,n;
vector<int>v[1000005];
int lvl[1000005],par[1000005][22];
bool vis[1000005];
int tim[1000005][2];
int ct=0;
int tree[6500005];
int lazy[6500005];
void propogate(int i,int l,int r)
{
    tree[i]=max(lazy[i],tree[i]);
    if(l!=r)
        lazy[i*2]=max(lazy[i*2],lazy[i]),lazy[i*2+1]=max(lazy[i*2+1],lazy[i]);
    lazy[i]=0;
}
void update(int i,int l,int r,int l1,int r1,int val)
{
    if(lazy[i])
        propogate(i,l,r);
    if(l1>r1 || l>r1 || l1>r)
        return;
    if(l1<=l && r<=r1)
    {
        tree[i]=max(val,tree[i]);
        if(l!=r)
            lazy[i*2]=max(lazy[i*2],val),lazy[i*2+1]=max(lazy[i*2+1],val);
        return;
    }
    int mid=(l+r)/2;
    update(i*2,l,mid,l1,r1,val);
    update(i*2+1,mid+1,r,l1,r1,val);
    tree[i]=max(tree[i*2],tree[i*2+1]);
}
int query(int i,int l,int r,int l1,int r1)
{
    if(l1>r1 || l>r1 || l1>r)
        return 0;
    if(lazy[i])
        propogate(i,l,r);
    if(l1<=l && r<=r1)
        return tree[i];
    int mid=(l+r)/2;
    return max(query(i*2,l,mid,l1,r1),query(i*2+1,mid+1,r,l1,r1));
}
int dfs(int i,int p,int l)
{
    vis[i]=1;
    par[i][0]=p;
    lvl[i]=l;
    tim[i][0]=++ct;
    for(auto j:v[i])
        if(!vis[j])
            dfs(j,i,l+1);
    tim[i][1]=++ct;
}
int LCA(int a,int b)
{
    if(lvl[a]<lvl[b])
        swap(a,b);
    int diff=lvl[a]-lvl[b];
    for(int i=21;i>=0;i--)
        if((1<<i)&diff)
            a=par[a][i];
    if(a==b)
        return a;
    for(int i=21;i>=0;i--)
        if(par[a][i] && par[a][i]!=par[b][i])
            a=par[a][i],b=par[b][i];
    return par[a][0];
}
int path(int a,int h)
{
    for(int i=21;i>=0;i--)
        if((1<<i)&h)
            a=par[a][i];
    return a;
}
int dist(int a,int b)
{
    if(a==b)
        return 0;
    int get=query(1,1,ct,tim[a][0],tim[a][0]);
    //cout<<a<<" "<<b<<" "<<lvl[a]<<" "<<get<<" "<<lvl[b]<<endl;
    return max(0,lvl[a]-max(get,lvl[b]));
}
void mark(int a,int b)
{
    update(1,1,ct,tim[a][0]+1,tim[a][1]-1,lvl[a]);
    if(vis[a]||a==b)
        return;
    vis[a]=1;
    mark(par[a][0],b);
}
int32_t main()
{
    IOS;
    cin>>n>>k;
    for(int i=0;i<n-1;i++)
    {
        int a,b;
        cin>>a>>b;
        v[a].push_back(b);
        v[b].push_back(a);
    }
    dfs(1,0,1);
    memset(vis,0,sizeof(vis));
    for(int i=1;i<22;i++)
        for(int j=1;j<=n;j++)
            if(par[j][i-1])
                par[j][i]=par[par[j][i-1]][i-1];
    vis[n]=1;
    int maxpar=n;
    update(1,1,ct,tim[n][0]+1,tim[n][1]-1,lvl[n]);
    int left=n-k-1;
    for(auto i=n-1;i>=1;i--)
    {
        if(vis[i])
            continue;
        if(left==0)
            break;
        int lca=LCA(i,maxpar);
        int dis=dist(i,lca);
        dis+=max(0,dist(maxpar,lca)-1);
        if(!vis[lca])
            dis++;
        if(dis>left)
            continue;
        //cout<<i<<":-"<<dis<<" "<<left<<" "<<lca<<" "<<vis[lca]<<endl;
        left-=dis;
        mark(i,lca);
        if(maxpar!=lca)
            mark(par[maxpar][0],lca);
        vis[lca]=1;
        maxpar=lca;
    }
    //cout<<left<<endl;
    for(int i=1;i<=n;i++)
        if(!vis[i])
            cout<<i<<" ";
}
