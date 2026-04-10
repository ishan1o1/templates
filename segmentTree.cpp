class SGTree {
    vector<int> seg, lazy;

public:
    SGTree(int n) {
        seg.resize(4 * n + 1, 0);
        lazy.resize(4 * n + 1, 0);
    }

    void build(int ind, int low, int high, vector<int>& arr) {
        if (low == high) {
            seg[ind] = arr[low];
            return;
        }
        int mid = (low + high) >> 1;
        build(2 * ind + 1, low, mid, arr);
        build(2 * ind + 2, mid + 1, high, arr);
        seg[ind] = seg[2 * ind + 1] + seg[2 * ind + 2];
    }
    void push(int ind, int low, int high) {
        if (lazy[ind] != 0) {
            seg[ind] += (high - low + 1) * lazy[ind];

            if (low != high) {
                lazy[2 * ind + 1] += lazy[ind];
                lazy[2 * ind + 2] += lazy[ind];
            }

            lazy[ind] = 0;
        }
    }

    int query(int ind, int low, int high, int l, int r) {
        push(ind, low, high);

        if (r < low || l > high) return 0;

        if (l <= low && high <= r) return seg[ind];

        int mid = (low + high) >> 1;
        return query(2 * ind + 1, low, mid, l, r) +
               query(2 * ind + 2, mid + 1, high, l, r);
    }

    void rupdate(int ind, int low, int high, int l, int r, int val) {
        push(ind, low, high);

        if (r < low || l > high) return;

        if (l <= low && high <= r) {
            lazy[ind] += val;
            push(ind, low, high);
            return;
        }

        int mid = (low + high) >> 1;
        rupdate(2 * ind + 1, low, mid, l, r, val);
        rupdate(2 * ind + 2, mid + 1, high, l, r, val);

        seg[ind] = seg[2 * ind + 1] + seg[2 * ind + 2];
    }
};
