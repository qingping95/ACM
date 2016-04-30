struct Node {
	int l, r, Max, Min;
	bool flag;
} node[MAXN * 6];
struct Seg{
    void pushup(int x) {
        node[x].Max = max(node[lson(x)].Max, node[rson(x)].Max);
        node[x].Min = min(node[lson(x)].Min, node[rson(x)].Min);
    }
    void pushdown(int x) {
        if (node[x].flag) {
            node[lson(x)].Max = -node[lson(x)].Max;
            node[rson(x)].Max = -node[rson(x)].Max;
            node[lson(x)].Min = -node[lson(x)].Min;
            node[rson(x)].Min = -node[rson(x)].Min;
            swap(node[lson(x)].Max, node[lson(x)].Min);
            swap(node[rson(x)].Max, node[rson(x)].Min);
            node[lson(x)].flag = !node[lson(x)].flag;
            node[rson(x)].flag = !node[rson(x)].flag;
            node[x].flag = false;
        }
    }

    void build(int l, int r, int x = 1) {
        node[x].l = l; node[x].r = r; node[x].flag = false;
        if (l == r) {
            node[x].Max = node[x].Min = val[l];
            return;
        }
        int mid = (l + r) / 2;
        build(l, mid, lson(x));
        build(mid + 1, r, rson(x));
        pushup(x);
    }

    void update(int v, int val, int x = 1) {
        if (node[x].l == node[x].r) {
            node[x].Max = node[x].Min = val;
            return;
        }
        int mid = (node[x].l + node[x].r) / 2;
        pushdown(x);
        if (v <= mid) update(v, val, lson(x));
        if (v > mid) update(v, val, rson(x));
        pushup(x);
    }

    void negate(int l, int r, int x = 1) {
        if (node[x].l >= l && node[x].r <= r) {
            node[x].flag = !node[x].flag;
            node[x].Max = -node[x].Max;
            node[x].Min = -node[x].Min;
            swap(node[x].Max, node[x].Min);
            return;
        }
        int mid = (node[x].l + node[x].r) / 2;
        pushdown(x);
        if (l <= mid) negate(l, r, lson(x));
        if (r > mid) negate(l, r, rson(x));
        pushup(x);
    }

    int query(int l, int r, int x = 1) {
        if (node[x].l >= l && node[x].r <= r) {
            return node[x].Max;
        }
        int mid = (node[x].l + node[x].r) / 2;
        pushdown(x);
        int ans = -INF;
        if (l <= mid) ans = max(ans, query(l, r, lson(x)));
        if (r > mid) ans = max(ans, query(l, r, rson(x)));
        pushup(x);
        return ans;
    }
}seg;