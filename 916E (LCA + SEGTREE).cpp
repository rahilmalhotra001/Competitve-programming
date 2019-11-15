//Author - Rahil Malhotra
#include <bits/stdc++.h>
using namespace std;
 
#define IOS ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
#define endl '\n'
#define int long long
#define double long double
 
int n,q;
vector<int>v[100005];
int lvl[100005],par[100005][22];
bool vis[100005];
int tim[100005][2],anti[100005];
int ct=0;
int arr[100005];
int tree[1000005],lazy[1000005];
void propogate(int i,int l,int r)
{
    tree[i]+=(r-l+1)*lazy[i];
    if(l!=r)
        lazy[i*2]+=lazy[i],lazy[i*2+1]+=lazy[i];
    lazy[i]=0;
}
void build(int i,int l,int r)
{
    if(l==r)
    {
        tree[i]=arr[anti[l]]; //CAREFUL
        return;
    }
    int mid=(l+r)/2;
    build(i*2,l,mid);
    build(i*2+1,mid+1,r);
    tree[i]=tree[i*2]+tree[i*2+1];
}
void update(int i,int l,int r,int l1,int r1,int val)
{
    if(lazy[i])
        propogate(i,l,r);
    if(l1>r1 || l>r1 || l1>r)
        return;
    if(l1<=l && r<=r1)
    {
        tree[i]+=(r-l+1)*val;
        if(l!=r)
            lazy[i*2]+=val,lazy[i*2+1]+=val;
        return;
    }
    int mid=(l+r)/2;
    update(i*2,l,mid,l1,r1,val);
    update(i*2+1,mid+1,r,l1,r1,val);
    tree[i]=tree[i*2]+tree[i*2+1];
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
    return query(i*2,l,mid,l1,r1)+query(i*2+1,mid+1,r,l1,r1);
}
void dfs(int i,int p,int l)
{
    vis[i]=1;
    par[i][0]=p;
    lvl[i]=l;
    tim[i][0]=++ct;
    anti[ct]=i;
    for(auto j:v[i])
        if(!vis[j])
            dfs(j,i,l+1);
    tim[i][1]=ct;
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
    if(h<0 || (h>lvl[a]-1))
        return -1;
    for(int i=21;i>=0;i--)
        if((1<<i)&h)
            a=par[a][i];
    return a;
}
int32_t main()
{
    IOS;
    cin>>n>>q;
    for(int i=1;i<=n;i++)
        cin>>arr[i];
    for(int i=0;i<n-1;i++)
    {
        int a,b;
        cin>>a>>b;
        v[a].push_back(b);
        v[b].push_back(a);
    }
    dfs(1,0,1);
    build(1,1,ct);
    for(int i=1;i<22;i++)
        for(int j=1;j<=n;j++)
            if(par[j][i-1])
                par[j][i]=par[par[j][i-1]][i-1];

    int curroot=1;
    while(q--)
    {
        int type;cin>>type;
        if(type==1)
            cin>>curroot;
        else if(type==2)
        {
            int a,b,c;
            cin>>a>>b>>c;
            int lca=LCA(a,b);
            int low=0;
            int high=lvl[curroot]-lvl[lca];
            if(low>high)
            {
                update(1,1,ct,tim[lca][0],tim[lca][1],c);
                continue;
            }
            while(low<high)
            {
                int mid=(low+high)/2;
                int reach=path(curroot,mid);
                if(!(path(a,lvl[a]-lvl[reach])==reach || path(b,lvl[b]-lvl[reach])==reach))
                    low=mid+1;
                else
                    high=mid;
            }
            int reach=path(curroot,low);
            if(reach!=-1 && (path(a,lvl[a]-lvl[reach])==reach || path(b,lvl[b]-lvl[reach])==reach))
            {
                if(reach==curroot)
                {
                    update(1,1,ct,tim[1][0],tim[1][1],c);
                }
                else
                {
                    update(1,1,ct,tim[1][0],tim[1][1],c);
                    int nn=path(curroot,low-1);
                    update(1,1,ct,tim[nn][0],tim[nn][1],-c);
                }
            }
            else 
            {
                update(1,1,ct,tim[lca][0],tim[lca][1],c);
            }
        }
        else
        {
            int a;
            cin>>a;
            if(a==curroot)
            {
                cout<<query(1,1,ct,tim[1][0],tim[1][1])<<endl;
                continue;
            }
            int lca=LCA(a,curroot);
            if(a==lca && path(curroot,lvl[curroot]-lvl[lca])==a)
            {
                int nn=path(curroot,lvl[curroot]-lvl[lca]-1);
                cout<<query(1,1,ct,tim[1][0],tim[1][1])-query(1,1,ct,tim[nn][0],tim[nn][1])<<endl;
            }
            else
            {
                cout<<query(1,1,ct,tim[a][0],tim[a][1])<<endl;
            }
        } 
    }
}