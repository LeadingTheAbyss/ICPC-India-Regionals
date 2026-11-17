#include <bits/stdc++.h>
using namespace std;

#define int long long

// Editorial :
/*
    
*/

void solve() {
    
    int n;
    cin >> n;
    vector<int> a(n + 1);
    vector<vector<array<int, 2>>> pf(n + 1);
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }

    for (int i = 1; i <= n; i++) {
        int x = a[i];
        vector<array<int, 2>> curr;
        for (int j = 2; j * j <= x; j++) {
            if (x % j != 0) {
                continue;
            }
            int p = 0;
            while (x % j == 0) {
                x /= j;
                ++p;
            }
            curr.push_back({j, p});
        }
        if (x > 1) {
            curr.push_back({x, 1});
        }
        pf[i] = curr;
    } 
    
    vector<vector<int>> adj(n + 1);
    vector<int> deg(n + 1);
    for (int i = 0; i < n - 1; i++) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
        deg[u]++;
        deg[v]++;
    }

    queue<int> q;
    for (int i = 1; i <= n; i++) {
        if (deg[i] == 1) {
            q.push(i);
        }
    }

    int ans = 0;
    // for (int i = 1; i <= n; i++) {
    //     auto v = pf[i];
    //     if (!v.size()) continue;
    //     for (int j = 0; j < v.size(); j++) {
    //         cout << v[j][0] << " " << v[j][1] << '\n';
    //     }
    //     cout << '\n';
    // }

    while (!q.empty()) {

        auto u = q.front();
        q.pop();

        int x = -1;
        for (int v : adj[u]) {
            if (deg[v] > 0) {
                x = v;
                break;
            }
        }

        if (x == -1) {
            continue;
        }

        auto &v1 = pf[x];
        auto &v2 = pf[u];

        for (int i = 0; i < v1.size(); i++) {
            for (int j = 0; j < v2.size(); j++) {
                if (v1[i][0] == v2[j][0]) {
                    int take = min(v1[i][1], v2[j][1]);
                    ans += take;
                    v1[i][1] -= take;
                    v2[i][1] -= take;
                }
            }
        }

        deg[u] = 0;
        --deg[x];

        if (deg[x] == 1) {
            q.push(x);
        }
    }

    cout << ans << '\n';

}

int32_t main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int t = 1;
    cin >> t;
    while (t--)
    solve();

    return 0;
}
