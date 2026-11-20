#include <bits/stdc++.h>
using namespace std;

/*
    Modular Arithmetic Operations (ModInt)
    Source :
        - https://github.com/bqi343/cp-notebook/blob/master/Implementations/content/number-theory%20(11.1)/Modular%20Arithmetic/ModInt.h
*/

#pragma once
const int mod = 1e9 + 7; // 998244353
// primitive root for FFT (if you need it)
const int primitive_root = 5;

struct Mint {
    int x;
    explicit operator int() const { return x; }
    Mint(): x(0) {}
    Mint(long long y) {
        x = int((-mod < y && y < mod) ? y : y % mod);
        if (x < 0) x += mod;
    }
    bool operator==(const Mint& o) const { return x == o.x; }
    friend bool operator!=(const Mint& a, const Mint& b) { return !(a == b); }
    friend bool operator<(const Mint& a, const Mint& b) { return a.x < b.x; }

    // Addition assignment (modular)
    // Time Complexity: O(1)
    Mint& operator+=(const Mint& o) {
        if ((x += o.x) >= mod) x -= mod;
        return *this;
    }

    // Subtraction assignment (modular)
    // Time Complexity: O(1)
    Mint& operator-=(const Mint& o) {
        if ((x -= o.x) < 0) x += mod;
        return *this;
    }

    // Multiplication assignment (modular)
    // Time Complexity: O(1)
    Mint& operator*=(const Mint& o) {
        x = int((long long)x * o.x % mod);
        return *this;
    }

    // Division assignment (modular): multiply by inverse
    // Time Complexity: O(log mod) due to pow in inv
    Mint& operator/=(const Mint& o) { return (*this) *= inv(o); }

    // Fast exponentiation: a^p (p >= 0)
    // Time Complexity: O(log p)
    friend Mint pow(Mint a, long long p) {
        assert(p >= 0);
        Mint ans = 1;
        while (p > 0) {
            if (p & 1) {
                ans *= a;
            }
            a *= a;
            p >>= 1;
        }
        return ans;
    }

    // Multiplicative inverse using Fermat (mod must be prime)
    // Time Complexity: O(log mod)
    friend Mint inv(const Mint& a) {
        assert(a.x != 0);
        return pow(a, mod - 2);
    }
    Mint operator-() const { return Mint(-x); }
    Mint& operator++() { return *this += 1; }
    Mint& operator--() { return *this -= 1; }
    friend Mint operator+(Mint a, const Mint& b) { return a += b; }
    friend Mint operator-(Mint a, const Mint& b) { return a -= b; }
    friend Mint operator*(Mint a, const Mint& b) { return a *= b; }
    friend Mint operator/(Mint a, const Mint& b) { return a /= b; }
    friend ostream &operator<<(ostream &out, const Mint &a) {
        return out << a.x;
    }
};

// small combinations table (nCk mod mod)
// scmb[n][k] == C(n,k) as modular integers
vector<vector<Mint>> scmb; // small combinations table

// Build Pascal's triangle up to n - 1
// Time Complexity: O(n^2)
void genComb(int n) {
    scmb.assign(n, vector<Mint>(n));
    if (n <= 0) return;
    scmb[0][0] = Mint(1);
    for (int i = 1; i < n; i++) {
        for (int j = 0; j <= i; j++) {
            Mint left = scmb[i - 1][j];
            Mint right = Mint(0);
            if (j > 0) {
                right = scmb[i - 1][j - 1];
            }
            scmb[i][j] = left + right;
        }
    }
}

// Segment Tree (Range Sum)
// Used to perform Range Sum Queries, range add updates using lazy propogation.
class SegmentTree {
public:
    int n;
    vector<Mint> tree, lazy;

    SegmentTree(int n) : n(n) {
        tree.assign(4 * n, 0);
        lazy.assign(4 * n, 0);
    }

    // For building the tree from an array 
    // Time Complexity: O(n)
    void build(const vector<long long> &a, int node, int start, int end) {
        if (start == end) {
            tree[node] = a[start];
            return;
        }
        int mid = (start + end) / 2;
        build(a, node * 2, start, mid);
        build(a, node * 2 + 1, mid + 1, end);
        tree[node] = tree[node * 2] + tree[node * 2 + 1];
    }

    // Used for applying a lazy update to a node
    // Time Complexity: O(1)
    void apply(int node, int start, int end, long x, long long y) {
        int len = (end - start + 1);
        int val = x * len + (len * (len + 1) / 2) * y;
        tree[node] += 1LL * (end - start + 1) * val;
        lazy[node] += val;
    }

    // Used for pushing pending lazy updates to children
    // Time Complexity: O(1)
    void push(int node, int start, int end, int x, int y) {
        if (lazy[node] == 0) return;
        int mid = (start + end) / 2;
        apply(node * 2, start, mid, x, y);
        apply(node * 2 + 1, mid + 1, end, x, y);
        lazy[node] = 0;
    }

    // Used for updating range [l, r] by adding val
    // Time Complexity: O(log n)
    void updateRange(int node, int start, int end, int l, int r, long long x, long long y) {
        Mint val = n * x + y * ((n - 1) * (n) / 2);
        if (l > r) return;
        if (l == start && r == end) {
            apply(node, start, end, x, y);
            return;
        }
        push(node, start, end, x, y);
        int mid = (start + end) / 2;
        updateRange(node * 2, start, mid, l, min(r, mid), x, y);
        updateRange(node * 2 + 1, mid + 1, end, max(l, mid + 1), r, x, y);
        tree[node] = tree[node * 2] + tree[node * 2 + 1];
    }

    Mint query(int node, int start, int end, int l, int r) {
        if (l > r) return 0;
        if (l == start && r == end) return tree[node];
        push(node, start, end);
        int mid = (start + end) / 2;
        return max(query(node * 2, start, mid, l, min(r, mid)), query(node * 2 + 1, mid + 1, end, max(l, mid + 1), r));
    }
};


/*

    X + (i−1)·Y  for the whole range = N * X + (0y + 1y + 2y ... n - 1Y) total change
    => N * X + y(0 + 1 + 2... N - 1)
    => N * X +  y((N - 1) * (N) / 2)




*/

void solve() {

    int n, q, m;
    cin >> n >> q >> m;

    SegmentTree st(n);

    for (int i = 1; i <= q; i++) {
        int op;
        cin >> op;
        if (op == 1) {
            int x, y;
            cin >> x >> y;
            st.updateRange(1, 0, n - 1, 0, n - 1, x, y);
        }
        else {
            int l, r;
            cin >> l >> r;
            Mint ans = st.query(1, 0, n - 1, l - 1, r - 1);
            cout << (int)ans << '\n';
        }
    }

}

int32_t main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int t = 1;
    // cin >> t;
    while (t--)
    solve();

    return 0;
}
