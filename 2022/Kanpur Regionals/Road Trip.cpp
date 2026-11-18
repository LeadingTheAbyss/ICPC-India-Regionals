#include <bits/stdc++.h>
using namespace std;

#define int long long

void solve() {

    int n, m, k;
    cin >> n >> m >> k;

    vector<vector<array<int, 3>>> adj(n + 1);
    for (int i = 0; i < m; i++) {
        int u, v, w, h;
        cin >> u >> v >> w >> h;
        --h;
        adj[u].push_back({v, w, h});
        adj[v].push_back({u, w, h});
    }

    auto dijkstra = [&](int s, int d) -> int {

        priority_queue<array<int, 2>, vector<array<int, 2>>, greater<array<int, 2>>> q;
        q.push({0, s});
        int inf = LLONG_MAX;
        vector<vector<vector<int>>> dist(n + 1, vector<vector<int>>(2, vector<int>(k, inf)));
        dist[s][0][0] = 0;
        dist[s][1][0] = 0;

        while (!q.empty()) {
            auto [dd, u] = q.top();
            q.pop();

            if (u == d) {
                int pick = min(dist[d][1][0], dist[d][0][0]);
                if (pick != inf) {
                    return pick;
                }
            }

            for (auto [x, w, side] : adj[u]) {
                auto upd = [&](int ch) -> void {
                    if (dist[u][side ^ 1][ch] == inf) {
                        return;
                    }
                    int rem = (dist[u][side ^ 1][ch] + w) % k;
                    if (dist[x][side][rem] > dist[u][side ^ 1][ch] + w) {
                        dist[x][side][rem] = dist[u][side ^ 1][ch] + w;
                        q.push({dist[x][side][rem], x});
                    }
                };
                for (int p = 0; p < k; p++) {
                    upd(p);
                }
            }
        }

        return -1;
    };

    int q;
    cin >> q;
    for (int i = 1; i <= q; i++) {
        cout << i << " ";
        int s, d;
        cin >> s >> d;
        int ans = dijkstra(s, d);
        if (ans == -1) {
            cout << "no such route\n";
        }
        else {
            cout << ans << '\n';
        }
    }

}

int32_t main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int t = 1;
    while (t--)
    solve();

    return 0;
}
