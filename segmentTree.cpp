#include <vector>
using namespace std;

class SGTree {
    vector<int> seg;
    vector<int> lazy;

    void push(int ind, int low, int high) {
        if (lazy[ind] != 0) {
            seg[ind] += (high - low + 1) * lazy[ind];
            // If not a leaf node, propagate downwards
            if (low != high) {
                lazy[2 * ind + 1] += lazy[ind];
                lazy[2 * ind + 2] += lazy[ind];
            }
            lazy[ind] = 0;
        }
    }

public:
    SGTree(int n) {
        seg.resize(4 * n + 1, 0);
        lazy.resize(4 * n + 1, 0);
    }

    void build(int ind, int low, int high, int arr[]) {
        if (low == high) {
            seg[ind] = arr[low];
            return;
        }

        int mid = (low + high) / 2;
        build(2 * ind + 1, low, mid, arr);
        build(2 * ind + 2, mid + 1, high, arr);
        seg[ind] = seg[2 * ind + 1] + seg[2 * ind + 2];
    }

    int query(int ind, int low, int high, int l, int r) {
        // 1. Resolve pending updates before making decisions
        push(ind, low, high);

        // No overlap
        if (r < low || high < l) return 0;

        // Complete overlap
        if (low >= l && high <= r) return seg[ind];

        // Partial overlap
        int mid = (low + high) >> 1;
        int left = query(2 * ind + 1, low, mid, l, r);
        int right = query(2 * ind + 2, mid + 1, high, l, r);
        return left + right;
    }

    void updateRange(int ind, int low, int high, int l, int r, int val) {
        // 1. Resolve pending updates first
        push(ind, low, high);

        // No overlap
        if (high < l || r < low) return;

        // Complete overlap
        if (low >= l && high <= r) {
            lazy[ind] += val;
            push(ind, low, high);
            return;
        }

        // Partial overlap
        int mid = (low + high) >> 1;
        updateRange(2 * ind + 1, low, mid, l, r, val);
        updateRange(2 * ind + 2, mid + 1, high, l, r, val);
        seg[ind] = seg[2 * ind + 1] + seg[2 * ind + 2];
    }

    // Point update can simply reuse updateRange for consistency
    void updatePoint(int ind, int low, int high, int i, int val) {
        updateRange(ind, low, high, i, i, val);
    }
};
