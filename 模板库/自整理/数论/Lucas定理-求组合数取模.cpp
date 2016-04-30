//C(n,m)%p=C(n/p,m/p)C(n%p,m%p), pÎªËØÊý
ll qPow (ll a, ll k, ll p) {
    ll ans = 1;

    while (k) {
        if (k&1)
            ans = (ans * a) % p;
        a = (a * a) % p;
        k /= 2;
    }
    return ans;
}

ll C (ll a, ll b, ll p) {

    if (a < b)
        return 0;

    if (b > a - b)
        b = a - b;

    ll up = 1, down = 1;

    for (ll i = 0; i < b; i++) {
        up = up * (a-i) % p;
        down = down * (i+1) % p;
    }
    return up * qPow(down, p-2, p) % p; // ÄæÔª
}

ll lucas (ll a, ll b, ll p) {
    if (b == 0)
        return 1;
    return C(a%p, b%p, p) * lucas(a/p, b/p, p) % p;
}
/*
const int maxn = 25;
const ll mod = 1e9+7;
int n;
ll s, f[maxn];

ll solve () {
    ll ans = 0;
    for (int i = 0; i < (1<<n); i++) {
        ll sign = 1, sum = s;
        for (int j = 0; j < n; j++) {
            if (i&(1<<j)) {
                sum -= (f[j]+1);
                sign *= -1;
            }
        }

        if (sum < 0)
            continue;
        ans += sign * lucas(sum + n - 1, n - 1, mod);
        ans %= mod;
    }
    return (ans + mod) % mod;
}

int main () {
    scanf("%d%lld", &n, &s);
    for (int i = 0; i < n; i++)
        scanf("%lld", &f[i]);
    printf("%lld\n", solve());
    return 0;
}
*/