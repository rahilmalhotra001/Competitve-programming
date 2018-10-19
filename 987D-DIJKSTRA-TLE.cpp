#include <bits/stdc++.h>
using namespace std;
 
#define IOS ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
#define endl "\n"

class pqsort
{
    public: bool operator() (pair<int,int> &a,pair<int,int> &b)
    {
        if(a.second<b.second)
            return 0;
        return 1;
    }
};

int main()
{
    IOS;
    int n,m,kk,s;
    cin>>n>>m>>kk>>s;
    vector<int> adj[n+1];
    int arr[n+1];
    for(int i=1;i<=n;i++)cin>>arr[i];
    for(int i=0;i<m;i++)
    {
        int a,b;
        cin>>a>>b;
        adj[a].emplace_back(b);
        adj[b].emplace_back(a);
    }
    int min[n+1][kk+1];
    for(int i=0;i<=n;i++)for(int j=0;j<=kk;j++)min[i][j]=1000000000;
    priority_queue<pair<int,int>,vector<pair<int,int>>,pqsort>  pq;
    for(int k=1;k<=kk;k++)
    {
        for(int i=1;i<=n;i++)
            if(arr[i]==k)
            {
                pq.push(make_pair(i,0));
                min[i][k]=0;
            }
        while(pq.size())
        {
            pair<int,int> p=pq.top();
            pq.pop();
            for(int i:adj[p.first])
            {
                if(min[i][k]>p.second+1)
                {
                    min[i][k]=p.second+1;
                    pq.push(make_pair(i,p.second+1));
                }
            }
        }
    }
    for(int i=1;i<=n;i++)
    sort(min[i],min[i]+kk+1);
    for(int i=1;i<=n;i++)
    {
        long ans=0;
        for(int j=0;j<s;j++)
        ans+=(long)min[i][j];
        cout<<ans<<" ";
    }
}