#include <bits/stdc++.h>
using namespace std;

#define int long long

void solve() {

    int n, m;
    cin >> n >> m;

    vector<vector<int>> a(n, vector<int>(m)), dp(n, vector<int>(m, 1)), vis(n, vector<int>(m));

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cin >> a[i][j];
        }
    }

    auto safe = [&](int i, int j, int i2, int j2) -> bool {
        if (a[i][j] > a[i2][j2] and gcd(a[i][j], a[i2][j2]) != 1) {
            return true;
        }
        return false;
    };

    auto dfs = [&](auto& dfs, int i, int j) -> int {
        vis[i][j] = true;

        if (i + 1 < n and safe(i, j, i + 1, j)) {
            if (!vis[i + 1][j]) {
                dfs(dfs, i + 1, j);
            }
            dp[i][j] = max(dp[i][j], dp[i + 1][j] + 1);
        }
        if (j + 1 < m and safe(i, j, i, j + 1)) {
            if (!vis[i][j + 1]) {
                dfs(dfs, i, j + 1);
            }
            dp[i][j] = max(dp[i][j], dp[i][j + 1] + 1);
        }
        if (j - 1 >= 0 and safe(i, j, i, j - 1)) {
            if (!vis[i][j - 1]) {
                dfs(dfs, i, j - 1);
            }
            dp[i][j] = max(dp[i][j], dp[i][j - 1] + 1);
        }
        if (i - 1 >= 0 and safe(i, j, i - 1, j)) {
            if (!vis[i - 1][j]) {
                dfs(dfs, i - 1, j);
            }
            dp[i][j] = max(dp[i][j], dp[i - 1][j] + 1);
        }

        return dp[i][j];
    };

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (!vis[i][j]) {
                dfs(dfs, i, j);
            }
        }
    }
    
    vector<int> f;
    int maxi = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            maxi = max(maxi, dp[i][j]);
        }
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (dp[i][j] == maxi) {
                int x = dp[i][j];
                int ni = i, nj = j;
                cout << dp[i][j] << '\n';
                while (x > 0) {
                    cout << a[ni][nj] << " ";
                    --x;
                    if (ni + 1 < n and dp[ni + 1][nj] == dp[ni][nj] - 1 and safe(ni, nj, ni + 1, nj)) {
                        ni++;
                    }
                    else if (nj + 1 < m and dp[ni][nj + 1] == dp[ni][nj] - 1 and safe(ni, nj, ni, nj + 1)) {
                        nj++;
                    }
                    else if (ni - 1 >= 0 and dp[ni - 1][nj] == dp[ni][nj] - 1 and safe(ni, nj, ni - 1, nj)) {
                        ni--;
                    } 
                    else if (nj - 1 >= 0 and dp[ni][nj - 1] == dp[ni][nj] - 1 and safe(ni, nj, ni, nj - 1)) {
                        nj--;
                    }
                }
                cout << '\n';
                return;
            }
        }
    }

}

int32_t main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int t = 1;
    cin >> t;
    while (t--) {
        string s;
        cin >> s;
        cout << s << ": ";
        solve();
    }
    return 0;
}
