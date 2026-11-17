#include <bits/stdc++.h>
using namespace std;

#define int long long

void solve() {

    int n;
    cin >> n;
    vector<int> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }

    vector<vector<int>> dp(n, vector<int>(n));
    for (int i = 1; i < n; i++) {
        for (int j = 0; j + i < n; j++) {
            dp[j][j + i] = max(dp[j][j + i - 1], dp[j][j + i]) + (a[j] > a[j + i]);
            dp[j + i][j] = dp[j][j + i] + (a[j + i] > a[j]);
        }
    }

    vector<int> ans(n);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            ans[i] = max(ans[i], dp[i][j]);
        }
    }

    for (int i = 0; i < n; i++) {
        cout << ans[i] << " \n"[i == n - 1];
    }

}

int32_t main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int t = 1;
    // cin >> t;
    while (t--) {
        solve();
    }
    return 0;
}
