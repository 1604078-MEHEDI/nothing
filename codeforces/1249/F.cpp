#include <bits/stdc++.h>
using namespace std;
#define INF 1<<30
#define endl '\n'
#define maxn 100005
#define tc printf("Case %d: ", cs)
#define tcn printf("Case %d:\n", cs);
#define FASTIO ios_base::sync_with_stdio(false), cin.tie(0), cout.tie(0);
typedef long long ll;
const double PI = acos(-1.0);

#define dbg1(x) cerr << #x << " = " << x << endl;
#define dbg2(x, y) cerr << #x << " = " << x << ", " << #y << " = " << y << endl;
#define dbg3(x, y, z) cerr << #x << " = " << x << ", " << #y << " = " << y << ", " << #z << " = " << z << endl;
#define dbg4(w,x, y, z) cerr << #w << " = " << w << ", " <<#x << " = " << x << ", " << #y << " = " << y << ", " << #z << " = " << z << endl;

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

/**___________________________________________________**/

const int N = 222;
int n, k;
const int inf = 1e9;

int a[N];
vector<int> graph[N];
int dp[N][N];



void dfs(int u, int p = 0) {
    for (auto v : graph[u]) {
        if (v == p) continue;
        dfs(v, u);
    }

    for (int i = n - 1; i; i--) {
        dp[u][i] = dp[u][i + 1];
        if (2 * i > k) {
            int tot = 0;
            for (auto v : graph[u]) {
                if (v == p) continue;
                tot += dp[v][i - 1];
            }
            dp[u][i] = max(dp[u][i], tot);
        }
        else {
            int tot = 0;
            for (auto v : graph[u]) {
                if (v == p) continue;
                tot += dp[v][k - i];
            }
            for (auto v : graph[u]) {
                if (v == p) continue;
                dp[u][i] = max(dp[u][i], tot - dp[v][k - i] + dp[v][i - 1]);
            }
        }
    }

    int sm = a[u];
    for (auto v : graph[u]) {
        if (v == p) continue;
        sm += dp[v][k];
    }
    dp[u][0] = max(dp[u][1], sm);
}

int main()
{
    FASTIO
    ///*
#ifndef ONLINE_JUDGE
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
    freopen("error.txt", "w", stderr);
#endif
//*/
    cin >> n >> k;
    for (int i = 1; i <= n; i++) cin >> a[i];
    for (int i = 1; i < n; i++) {
        int u, v;
        cin >> u >> v;
        graph[u].push_back(v);
        graph[v].push_back(u);
    }
    dfs(1);
    cout << dp[1][0] << endl;
}