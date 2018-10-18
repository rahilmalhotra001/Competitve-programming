#include <bits/stdc++.h>
using namespace std;
 
#define IOS ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
#define endl "\n"

static int n;
static int arr[300][300],cache[601][300][300];
int dp(int d,int x1,int x2)
{
    if(d-x1==n-1&&d-x2==n-1&&x1==n-1&&x2==n-1)
    return arr[n-1][n-1];
    int y1=d-x1;int y2=d-x2;
    if(x1>=n||x2>=n||y1>=n||y2>=n)
    return -1000000000;
    if(cache[d][x1][x2]!=-1)
    return cache[d][x1][x2];
    int dir1[]={0,0,1,1};
    int dir2[]={1,0,1,0};
    int ans=-1000000000;
    int curr=arr[x1][y1]+arr[x2][y2];
    if(x1==x2&&y1==y2)
    curr-=arr[x1][y1];
    for(int i=0;i<4;i++)ans=max(ans,curr+dp(d+1,x1+dir1[i],x2+dir2[i]));
    return cache[d][x1][x2]=ans;
}
int main()
{
    //Learnt something new from the tutorial, i guess.
    //Expressing coordinates as the diagonal
	IOS;
    cin>>n;
    if(n==1)
    {
        int a;
        cin>>a;
        cout<<a;
        return 0;
    }
    for(int i=0;i<n;i++)for(int j=0;j<n;j++)cin>>arr[i][j];
    memset(cache,-1,sizeof(cache));
    cout<<dp(0,0,0);
}