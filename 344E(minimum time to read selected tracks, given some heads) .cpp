#include <bits/stdc++.h>
using namespace std;
 
#define IOS ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
#define endl "\n"
#define double long double
#define long long long 
#define int long

           //       |----|       /\      |    |   -----   |
           //       |   /       /  \     |    |     |     |
           //       |--/       /----\    |----|     |     |
           //       |   \     /      \   |    |     |     |
           //       |    \   /        \  |    |   -----   -------
int n,m;
int pos[100001];
int arr[100001];
//https://codeforces.com/contest/344/problem/E
bool check(int t)
{
	int start=0;
	for(int i=0;i<n;i++)
	{
		if(i==n-1)
		{
			if(arr[start]<=pos[i]&&arr[m-1]<=pos[i])
			{
				if(pos[i]-arr[start]<=t)
					return true;
			}
			else if(arr[start]>=pos[i]&&arr[m-1]>=pos[i])
			{
				if(arr[m-1]-pos[i]<=t)
					return true;
			}
			else
			{
				int a=(pos[i]-arr[start])*2+arr[m-1]-pos[i];
				a=min(a,(arr[m-1]-pos[i])*2+pos[i]-arr[start]);
				if(a<=t)
					return true;
			}
			break;
		}
		int time=0;
		int startpos=pos[i];
		if(arr[start]<=pos[i])
			time+=pos[i]-arr[start];
		if(time>t)
			break;
		while(start<m)
		{
			if(arr[start]>pos[i])
				break;
			start++;
		}
		if(start==m)
		{
			return true;
		}
		int max1=start;
		int max2=start;
		time*=2;
		while(max1<m)
		{
			if(arr[max1]-pos[i]<=(t-time))
				max1++;
			else
				break;
		}
		time/=2;
		while(max2<m)
		{
			if((arr[max2]-pos[i])*2<=(t-time))
				max2++;
			else
				break;
		}
		start=max(max1,max2);
		if(start==m)
			return true;
	}
	start=m-1;
	for(int i=n-1;i>=0;i--)
	{
		if(i==0)
		{
			if(arr[start]<=pos[i]&&arr[0]<=pos[i])
			{
				if(pos[i]-arr[0]<=t)
					return true;
			}
			else if(arr[start]>=pos[i]&&arr[0]>=pos[i])
			{
				if(arr[start]-pos[i]<=t)
					return true;
			}
			else
			{
				int a=(pos[i]-arr[0])*2+arr[start]-pos[i];
				a=min(a,(arr[start]-pos[i])*2+pos[i]-arr[0]);
				if(a<=t)
					return true;
			}
			break;
		}
		int time=0;
		int startpos=pos[i];
		if(arr[start]>=pos[i])
			time+=arr[start]-pos[i];
		if(time>t)
			break;
		while(start>=0)
		{
			if(arr[start]<pos[i])
				break;
			start--;
		}
		if(start==-1)
		{
			return true;
		}
		int max1=start;
		int max2=start;
		time*=2;
		while(max1>=0)
		{
			if(pos[i]-arr[max1]<=(t-time))
				max1--;
			else
				break;
		}
		time/=2;
		while(max2>=0)
		{
			if((pos[i]-arr[max2])*2<=(t-time))
				max2--;
			else
				break;
		}

		start=min(max1,max2);
		if(start==-1)
			return true;
	}
	return false;
}
int32_t main()
{
    IOS;
    cin>>n>>m;
    for(int i=0;i<n;i++)
    	cin>>pos[i];
    for(int i=0;i<m;i++)
    	cin>>arr[i];
    int low=0;
    int high=20000000001;
    while(low<high)
    {
    	int mid=(low+high)/2;
    	if(!check(mid))
    		low=mid+1;
    	else
    		high=mid;
    }
    cout<<low;
}