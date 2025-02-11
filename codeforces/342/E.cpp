#include <bits/stdc++.h>
using namespace std;
#define INF 1<<30
#define endl '\n'
#define maxn 1000005
#define FASTIO ios_base::sync_with_stdio(false), cin.tie(0), cout.tie(0);
typedef long long ll;
const double PI = acos(-1.0);
const ll mod = 1e9 + 7;

inline void normal(ll &a) { a %= mod; (a < 0) && (a += mod); }
inline ll modMul(ll a, ll b) { a %= mod, b %= mod; normal(a), normal(b); return (a * b) % mod; }
inline ll modAdd(ll a, ll b) { a %= mod, b %= mod; normal(a), normal(b); return (a + b) % mod; }
inline ll modSub(ll a, ll b) { a %= mod, b %= mod; normal(a), normal(b); a -= b; normal(a); return a; }
inline ll modPow(ll b, ll p) { ll r = 1; while (p) { if (p & 1) r = modMul(r, b); b = modMul(b, b); p >>= 1; } return r; }
inline ll modInverse(ll a) { return modPow(a, mod - 2); }
inline ll modDiv(ll a, ll b) { return modMul(a, modInverse(b)); }


///**
template < typename F, typename S >
ostream& operator << ( ostream& os, const pair< F, S > & p ) {
	return os << "(" << p.first << ", " << p.second << ")";
}

template < typename T >
ostream &operator << ( ostream & os, const vector< T > &v ) {
	os << "{";
	for (auto it = v.begin(); it != v.end(); ++it) {
		if ( it != v.begin() ) os << ", ";
		os << *it;
	}
	return os << "}";
}

template < typename T >
ostream &operator << ( ostream & os, const set< T > &v ) {
	os << "[";
	for (auto it = v.begin(); it != v.end(); ++it) {
		if ( it != v.begin()) os << ", ";
		os << *it;
	}
	return os << "]";
}

template < typename F, typename S >
ostream &operator << ( ostream & os, const map< F, S > &v ) {
	os << "[";
	for (auto it = v.begin(); it != v.end(); ++it) {
		if ( it != v.begin() ) os << ", ";
		os << it -> first << " = " << it -> second ;
	}
	return os << "]";
}

#define dbg(args...) do {cerr << #args << " : "; faltu(args); } while(0)

clock_t tStart = clock();
#define timeStamp dbg("Execution Time: ", (double)(clock() - tStart)/CLOCKS_PER_SEC)

void faltu () { cerr << endl; }

template <typename T>
void faltu( T a[], int n ) {
	for (int i = 0; i < n; ++i) cerr << a[i] << ' ';
	cerr << endl;
}

template <typename T, typename ... hello>
void faltu( T arg, const hello &... rest) { cerr << arg << ' '; faltu(rest...); }
// Program showing a policy-based data structure.
#include <ext/pb_ds/assoc_container.hpp> // Common file 
#include <ext/pb_ds/tree_policy.hpp>
#include <functional> // for less 
#include <iostream>
using namespace __gnu_pbds;
using namespace std;
// GNU link : https://goo.gl/WVDL6g
typedef tree<int, null_type, less_equal<int>, rb_tree_tag,
        tree_order_statistics_node_update>
        new_data_set;

// find_by_order(k) – ফাংশনটি kth ordered element এর একটা পয়েন্টার রিটার্ন করে। অর্থাৎ তুমি চাইলেই kth ইন্ডেক্সে কি আছে, সেটা জেনে ফেলতে পারছো!
// order_of_key(x) – ফাংশনটি x এলিমেন্টটা কোন পজিশনে আছে সেটা বলে দেয়।

//*//**___________________________________________________**/

const int N = 1e5 + 10;
const int LOGN = 20;
const int inf = 1e9;
set<int> g[N];
int par[N], sub[N], level[N], ans[N];
int dp[LOGN][N];
int n, m;

/*----------- Pre-Processing ------------*/

void dfs0(int u)
{
	for (auto it = g[u].begin(); it != g[u].end(); it++) {
		if (*it != dp[0][u]) {
			dp[0][*it] = u;
			level[*it] = level[u] + 1;
			dfs0(*it);
		}
	}
}

void preprocess()
{
	level[0] = 0;
	dp[0][0] = 0;
	dfs0(0);
	for (int i = 1; i < LOGN; i++)
		for (int j = 0; j < n; j++)
			dp[i][j] = dp[i - 1][dp[i - 1][j]];
}

int lca(int a, int b)
{
	if (level[a] > level[b]) swap(a, b);
	int d = level[b] - level[a];
	for (int i = 0; i < LOGN; i++)
		if (d & (1 << i)) {
			b = dp[i][b];
		}

	if (a == b) return a;
	for (int i = LOGN - 1; i >= 0; i--)
		if (dp[i][a] != dp[i][b]) {
			a = dp[i][a];
			b = dp[i][b];
		}
	return dp[0][a];
}

int dist(int u, int v)
{
	return level[u] + level[v] - 2 * level[lca(u, v)];
}
/*-----------------Decomposition Part--------------------------*/
int cnt;
void dfs1(int u, int p)
{
	sub[u] = 1;
	cnt++;
	for (auto v = g[u].begin(); v != g[u].end(); v++) {
		if (*v != p) {
			dfs1(*v, u);
			sub[u] += sub[*v];
		}
	}
}

int dfs2(int u, int p)
{
	for (auto v = g[u].begin(); v != g[u].end(); v++) {
		if (*v != p && sub[*v] > cnt / 2)
			return dfs2(*v, u);
	}
	return u;
}

void decompose(int root, int p)
{
	cnt = 0;
	dfs1(root, root);
	int centroid = dfs2(root, root);
	if (p == -1) p = centroid;
	par[centroid] = p;
	for (auto v = g[centroid].begin(); v != g[centroid].end(); v++) {
		g[*v].erase(centroid);
		decompose(*v, centroid);
	}
	g[centroid].clear();
}

/*----------------- Handle the Queries -----------------*/

void update(int u)
{
	int x = u;
	while (1) {
		ans[x] = min(ans[x], dist(x, u));
		if (x == par[x]) break;
		x = par[x];
	}
}

int query(int u)
{
	int x = u;
	int ret = inf;
	while (1) {
		ret = min(ret, dist(u, x) + ans[x]);
		if (x == par[x]) break;
		x = par[x];
	}
	return ret;
}



int main()
{
	//FASTIO
	///*
#ifndef ONLINE_JUDGE
	freopen("in.txt", "r", stdin);
	freopen("out.txt", "w", stdout);
	freopen("error.txt", "w", stderr);
#endif
//*/
	scanf("%d %d", &n, &m);
	for (int i = 1; i < n; i++) {
		int u, v;
		scanf("%d %d", &u, &v);
		--u;
		--v;
		g[u].insert(v);
		g[v].insert(u);
	}
	preprocess();
	decompose(0, -1);
	for (int i = 0; i < n; i++) ans[i] = inf;
	update(0);// first node is initially painted red
	for (int i = 0; i < m; i++) {
		int t, v;
		scanf("%d%d", &t, &v);
		//dbg(t, v);
		--v;
		if (t == 1) update(v);
		else printf("%d\n", query(v));
	}
	return 0;
}