/**
 *    created: 05-11-2026 15:59:47
**/

#include <bits/stdc++.h>
using namespace std;
#if !defined(ONLINE_JUDGE)
#include "debug.h"
#else
#define debug(...) do {} while(0)
#endif

#define int long long

vector<vector<int>> a(17);

vector<bool> prime;
void SieveOfEratosthenes(long long n) {
    prime = vector<bool>(n + 1, true);
    prime[0] = prime[1] = false;
    for (long long p = 2; p * p <= n; ++p) {
        if (prime[p]) {
            for (long long i = p * p; i <= n; i += p)
                prime[i] = false;
        }
    }
}

void precompute() {
    for (int i = 1; i <= 16; i++) {
        for (int j = i + 1; j <= 16; j++) {
            if (prime[i + j]) {
                a[i].push_back(j);
                a[j].push_back(i);
            }
        }
    }
}

void solve() {

    int n;
    cin >> n;
    vector<int> f = {1};
    vector<int> vis(n + 1);
    vis[1] = true;

    auto dfs = [&](auto& dfs, int curr, int count) -> void {
        if (count == n) {
            if (prime[curr + 1]) {
                for (int i = 0; i < f.size(); i++) {
                    cout << f[i] << " \n"[i == n - 1];
                }
                return;
            }
        }

        for (int x : a[curr]) {
            if (x <= n and !vis[x]) {
                vis[x] = true;
                f.push_back(x);
                dfs(dfs, x, count + 1);
                vis[x] = false;
                f.pop_back();
            }
        }
    };

    dfs(dfs, 1, 1);
}

int32_t main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    SieveOfEratosthenes(1e2);
    precompute();

    int t;
    cin >> t;
    for (int i = 1; i <= t; i++) {
        cout << i << '\n';
        solve();
    }
    return 0;
}
