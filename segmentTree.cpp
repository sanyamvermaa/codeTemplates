#include <vector>

using namespace std;

class SGTree {
    vector<long long> seg;
    vector<long long> lazy;

    void push(int ind, int low, int high) {
        if (lazy[ind] != 0) {
            // Add (length of range * lazy value) to the segment sum
            seg[ind] += (high - low + 1) * lazy[ind];
            
            // Propagate lazy value downwards if not a leaf
            if (low != high) {
                lazy[2 * ind + 1] += lazy[ind];
                lazy[2 * ind + 2] += lazy[ind];
            }
            lazy[ind] = 0; // Clear lazy tag
        }
    }

public:
    SGTree(int n) {
        seg.resize(4 * n + 1, 0);
        lazy.resize(4 * n + 1, 0);
    }

    void build(int ind, int low, int high, const vector<int>& arr) {
        if (low == high) {
            seg[ind] = arr[low];
            return;
        }

        int mid = (low + high) >> 1;
        build(2 * ind + 1, low, mid, arr);
        build(2 * ind + 2, mid + 1, high, arr);
        seg[ind] = seg[2 * ind + 1] + seg[2 * ind + 2];
    }

    long long query(int ind, int low, int high, int l, int r) {
        // Resolve any pending updates before proceeding
        push(ind, low, high);

        // No overlap
        if (r < low || high < l) return 0; // Identity element for sum is 0

        // Complete overlap
        if (low >= l && high <= r) return seg[ind];

        // Partial overlap
        int mid = (low + high) >> 1;
        long long left = query(2 * ind + 1, low, mid, l, r);
        long long right = query(2 * ind + 2, mid + 1, high, l, r);
        return left + right;
    }

    // Point Update: set element at index `i` to `val`
    void updatePoint(int ind, int low, int high, int i, int val) {
        push(ind, low, high);

        if (low == high) {
            seg[ind] = val;
            return;
        }

        int mid = (low + high) >> 1;
        if (i <= mid) updatePoint(2 * ind + 1, low, mid, i, val);
        else updatePoint(2 * ind + 2, mid + 1, high, i, val);

        push(2 * ind + 1, low, mid);
        push(2 * ind + 2, mid + 1, high);
        seg[ind] = seg[2 * ind + 1] + seg[2 * ind + 2];
    }

    // Range Update: add `val` to all elements in range [l, r]
    void updateRange(int ind, int low, int high, int l, int r, int val) {
        push(ind, low, high);

        // No Overlap
        if (high < l || r < low) return;

        // Complete Overlap
        if (low >= l && high <= r) {
            lazy[ind] += val;
            push(ind, low, high);
            return;
        }

        // Partial Overlap
        int mid = (low + high) >> 1;
        updateRange(2 * ind + 1, low, mid, l, r, val);
        updateRange(2 * ind + 2, mid + 1, high, l, r, val);
        seg[ind] = seg[2 * ind + 1] + seg[2 * ind + 2];
    }
};
