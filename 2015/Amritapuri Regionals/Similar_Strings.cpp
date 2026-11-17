/**
 *    created: 07-11-2026 11:51:55
**/

#include <bits/stdc++.h>
using namespace std;
#if !defined(ONLINE_JUDGE)
#include "debug.h"
#else
#define debug(...) do {} while(0)
#endif

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

vector<Mint> fact, invfact;
int fact_computed = 0;

// Precomputing factorials up to n
void precompute(int n) {
    if (n <= fact_computed) return; 
    fact.assign(n + 1, Mint(0));
    invfact.assign(n + 1, Mint(0));
    
    fact[0] = Mint(1);
    for (int i = 1; i <= n; i++) {
        fact[i] = fact[i - 1] * Mint(i);
    }

    invfact[n] = inv(fact[n]);
    for (int i = n - 1; i >= 0; i--) {
        invfact[i] = invfact[i + 1] * Mint(i + 1);
    }
    fact_computed = n;
}

// nCr function 
Mint nCr(long long n, long long r) {
    if (r < 0 || r > n) return Mint(0);
    if (n > fact_computed) precompute(n);
    return fact[n] * invfact[r] * invfact[n - r];
}

// Multinomial Coefficient :
// Computes x! / (y1! * y2! * ... * ym!) % mod
Mint multi(int x, const vector<int> &y) {
    Mint res = fact[x];
    for (int p : y) {
        res = res * invfact[p];
    }
    return res;
}

void solve() {

    int n;
    cin >> n;

    Mint ans = 0;
    for (int i = 1; i <= n; i++) {
        Mint f = Mint(25);
        f = pow(f, i - 1);
        ans += (26 * f * nCr(n, i) * nCr(n, i));
    }

    cout << ans << '\n';

}

int32_t main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    precompute(5e4 + 10);

    int t = 1;
    cin >> t;
    while (t--) {
        solve();
    }
    return 0;
}
