							Struct in c++ -

struct B 
{
	int x,y;
	B() {}
	B (int x, int y) : x(x), y(y){}

	bool operator<(const B &num) const
	{
		if(x==num.x)
			return y<num.y;
		return x<num.x;
	}
};


							 set- (distinct elements, sorted)
set <int> s;
s.insert(k);
s.erase(k);
auto it=s.lower_bound(k); (lowerbound :>=k ; upperbound: >k)
if(it!=s.end())
cout<<*it (is the value)

for(auto &it:s);

auto it=s.find(k); (if found then it contains k, else it reaches s.end())


							 multiset -(multiple elements, sorted)

multiset <int> s;
s.insert(k);

if(s.find(k)!=s.end())
s.erase(k);//erases all k values

if(s.find(k)!=s.end())
s.erase(s.find(k)); //removes one occurence of k

auto it=s.lower_bound(k); (lowerbound :>=k ; upperbound: >k)
if(it!=s.end())
cout<<*it (is the value)

for(auto &it:s);
cout<<it;


auto it=s.find(k); (if found then it contains k, else it reaches s.end())


							  map -(<key,value>, sorted by key)


map <int,int> hm;

hm[key]=val;

if(hm.find(key)!=hm.end())
cout<<hm[key];

//DONT USE
if(!hm[key]) // this will insert a key key with default value(here 0)

auto it=hm.lower_bound(key);
cout<<it->first // will give key
cout<<it->second //will give value
	

for(auto &it:hm);
 it.first, it.second;

if(hm.find(key)!=hm.end())
hm.erase(key);


							  priority_queue(sorted by comparator , log n insertions/deletions ; cant find)


priority_queue<type,vector<type>,pqsort>  pq;//default is decreasing order    


priority_queue<type,vector<type>,greater<type>> pq;//inc sorted

pq.push(type);

element = pq.top();
pq.pop();




							unordered_set ; unordered_map;




								 vector(dynamic array)

vector<int> v;
v.push_back(value);
v.back(); or v[v.size()-1];//for lastelement
sort(v.begin(),v.end(),comparator);
sort(v.begin()+l,v.begin()+r,comparator); //l to r-1

auto it=lower_bound(v.begin(),v.end(),value);
int index=it-v.begin();

vector<int> g[1000];
g[a].push_back(b);

for(auto &it:g[pos])
	dfs(it);


											stack -


stack<int> st;
st.push(a);
st.pop();  //does not return anything
st.top();

											 -


queue<int> q;
q.push(a);
q.pop();  //does not return anything
q.front();								    	



											deque -



deque<int> q;
q.push_front(a);
q.push_back(a);
q.pop_front();
q.pop_back();
q.front();
q.back();


											
//return only 0 or 1
bool comparator(int &num1,int &num2)
{
	// ascending order
	if(num1<num2)
		return 1;
	return 0;

}


											pair-




pair<int ,int> p;
p.first=a;
p.second=b;
 or 
p={a,b};

class pqsort
{
	public: bool operator() (pair<int,int> &a,pair<int,int> &b)
	{
		if(a.second-a.first<b.second-b.first)
			return 0;
		return 1;
	}
};




----------------------------------------------

sort(arr,arr+arr.size(),comparator);

bool comparator(int &num1,int &num2)
{
	// descending order
	if(num1>num2)
		return 1;
	return 0;

}

reverse(arr,arr+size());

random_shuffle(arr,arr+size());



do
{

}
while(next_permutation(arr,arr+size()));


string s;
sort(s.begin(),s.end());
reverse(s.begin(),s.end());


//s = hello
string temp=s.substr(2,2); //ll


//for files
freopen("input file name","r",stdin);
freopen("out file name","w",stdout);


------
ios::sync_with_stdio(0);
cin.tie(0);
cout.tie(0);


#define endl '\n'

---------
isalpha(ch); //if ch is alphabet 
isdigit(ch);
isalnum(ch);
http://www.cplusplus.com/reference/cctype/isdigit/


getline(cin,str); //line input
getline(ss, num, ',');// delimiter ,
stringstream ss(str); //string tokenizer
string word;
while(ss>>word)
	cout<<word;

stoi(a);//String to int
stoll(b);//String to long long
string a=to_string(num)//num to string

__builtin_popcount(a);



__gcd(a,b);

lcm(a,b);

-----------------------------------------TRIES----------------------------------------------

typedef struct data
{
	data* bit[2];
	int cnt=0;
}trie;

trie* head;

void insert(int x)
{
	trie* node = head;
	for(int i=30;i>=0;i--)
	{
		int curbit=(x>>i)&1;
		if(node->bit[curbit]==NULL)
		{
			node->bit[curbit]=new trie();
		}  
		node=node->bit[curbit];
		node->cnt++;
	}
}

void remove(int x)
{
	trie* node = head;
	for(int i=30;i>=0;i--)
	{
		int curbit=(x>>i)&1;
		node=node->bit[curbit];
		node->cnt--;
	}
}

int maxxor(int x)
{
	trie* node = head;
	int ans=0;
	for(int i=30;i>=0;i--)
	{
		int curbit=(x>>i)&1;
		if(node->bit[curbit^1]!=NULL && node->bit[curbit^1]->cnt>0)
		{
			ans+=(1LL<<i);
			node=node->bit[curbit^1];
		}
		else
			node=node->bit[curbit];
	}
	return ans;
}

int main()
{
	head=new trie();
	insert(0);
}

-----------------------------------------------------------------------------------------------------------------



for map optimizations-
m.reserve(2^15)
m.max_load_factor(0.25)

...............................................................
Never use __builtin_popcount

Always use __builtin_popcountll

...............................................................
BIT----
int tree[300005];
int sum(int i)
{
	int sum = 0; 
	while(i>0)
	{
		sum+=tree[i];
		i-=i&(-i);
	}
	return sum;
}

void update(int i, int val)
{
	while(i<300005)
	{
	   tree[i]+=val;
	   i+=i&(-i);
	}
}
................................................................
int mod=1000000007;
int inv(int x)
{
	int r,y;
	for(r=1,y=mod-2;y>0;x=(x*x)%mod,y/=2)
		if(y%2==1)
			r=r*x%mod;
	return r;
}
int nCr(int n, int m)
{
	return fact[n] *inv(fact[m])%mod *inv(fact[n-m])%mod ;
}
................................................................
int power(int x,int y,int p)
{ 
	int res = 1;      
	x = x % p;  
	while (y > 0) 
	{ 
		if((y & 1)==1) 
			res = (res * x) % p; 
		y = y >> 1;  
		x = (x * x) % p;  
	} 
	return res; 
} 

................................................................
							 DSU

int n;
int rt[200005],sizee[200005];
void initialize()
{
	for(int i=0;i<n;i++)
	{
		rt[i]=i;
		sizee[i]=1;
	}
}
int root(int i)
{
	while(rt[i]!= i)
	{
		rt[i]=rt[rt[i]]; 
		i=rt[i];
	}
	return i;
}
void merge(int A,int B)
{
	int root_A = root(A);
	int root_B = root(B);
	if(rt[root_A]==rt[root_B])
		return;
	if(sizee[root_A] < sizee[root_B])
	{
		rt[root_A] = rt[root_B];
		sizee[root_B] += sizee[root_A];
	}
	else
	{
		rt[root_B] = rt[root_A];
		sizee[root_A] += sizee[root_B];
	}
}

...............................................
				Sparse Table

int tablemin[(int)log2(150005)+2][150005];
int floorlog[150005];
int maxi(int start,int end)
{
    int p=floorlog[end-start+1];
    return max(tablemin[p][start],tablemin[p][end-(1<<p)+1]);
}
for(int i=0;(1<<i)<150005;i++)
{
    for(int j=(1<<i);j<150005 && j<(1<<(i+1)); j++)
        floorlog[j]=i;
}
for(int i=1;i<=n;i++)
    tablemin[0][i]=arr[i];

for (int j=1;(1<<j)<=n;j++) 
    for (int i=1;(i+(1<<j)-1)<=n;i++)
        tablemin[j][i]=max(tablemin[j-1][i],tablemin[j-1][i+(1<<(j - 1))]);
...............................................
				Segment tree


int tree[1000005];
int lazy[1000005];
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
		tree[i]=arr[l];
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
......................................................................

bool isVowel(char ch)
{
    if(ch == 'a' || ch == 'e' || ch == 'i' || ch == 'o' || ch == 'u' ||ch=='y'|| ch=='A'|| ch=='E'|| ch=='I'|| ch=='O'|| ch=='U'||ch=='Y')
    return true;
    else
    return false;
}
.......................................................................
                                rand
                                
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

int rand(int l, int r)
{
    uniform_int_distribution<int> uid(l, r);
    return uid(rng);
}

.......................................................................
								LCA
int lvl[1000005],par[22][1000005];
bool vis[1000005];
int tim[2][1000005];
int ct=0;
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
..........................................................................

FFT template - https://www.codechef.com/viewsolution/19136345

..........................................................................

Centroid Decomposition - 

set<int>v[1000005];
int subtree[1000005],partree[1000005];

int dfsSubtree(int i,int p)
{
    int sum=0;
    for(auto j:v[i])
        if(j!=p)
            sum+=dfsSubtree(j,i);
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
    dfsSubtree(i,p);
    int cent = centroid(i,p,subtree[i]);
    partree[cent]=p;
    for(auto j:v[cent])
    {
        v[j].erase(cent);
        decompose(j,cent);
    }
}
.......................................................................
