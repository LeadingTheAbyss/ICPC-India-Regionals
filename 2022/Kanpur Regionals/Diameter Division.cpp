#include <bits/stdc++.h>
using namespace std;

#define int long long

void solve() {

    int n;
    cin >> n;
    vector<vector<int>> adj(n + 1);

    for (int i = 0; i < n - 1; i++) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    auto farthest_dist = [&](int i) -> pair<int, vector<int>> {
        queue<int> q;
        q.push(i);
        vector<int> vis(n + 1), dist(n + 1);

        while (!q.empty()) {
            auto u = q.front();
            q.pop();
            vis[u] = true;

            for (int x : adj[u]) {
                if (!vis[x]) {
                    dist[x] = dist[u] + 1;
                    q.push(x);
                }
            }
        }

        int mx = *max_element(dist.begin(), dist.end());
        for (int i = 1; i <= n; i++) {
            if (mx == dist[i]) {
                return {i, dist};
            }
        }
    };

    vector<int> d1;
    auto [first_far, dist1] = farthest_dist(1);
    auto [l1, d] = farthest_dist(first_far);

    int mx = *max_element(d.begin(), d.end());
    cout << mx << " ";

    

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
