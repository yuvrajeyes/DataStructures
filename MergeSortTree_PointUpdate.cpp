#include<bits/stdc++.h>
using namespace std;

#define all(a) a.begin(), a.end()

class MergeSortTree {
private:
    vector<multiset<int>> seg;
    vector<int> array;
    int N;

    int combine(int a, int b) {
        return a + b;
    }

    void build(int ind, int low, int high) {
        if (low == high) {
            seg[ind].insert(array[low]);
            return;
        }
        int mid = low + ((high - low) >> 1);
        build(2 * ind, low, mid);
        build(2 * ind + 1, mid + 1, high);
        seg[ind].insert(seg[2 * ind].begin(), seg[2 * ind].end());
        seg[ind].insert(seg[2 * ind + 1].begin(), seg[2 * ind + 1].end());
    }

    int query(int ind, int low, int high, int l, int r, int key) {
        if (r < low || l > high || l > r) return 0;
        if (low >= l && high <= r) {
            auto pos = seg[ind].upper_bound(key);  // use lower_bound for greater than or equal to
            if (pos != seg[ind].end()) {
                return distance(pos, seg[ind].end());  // // for the number of element greater than specified number
                return *pos;  // for smallest number greater than specified number
            }
            return 0;
        }
        int mid = low + ((high - low) >> 1);
        return query(2 * ind, low, mid, l, r, key) + query(2 * ind + 1, mid + 1, high, l, r, key);
    }

    void update(int ind, int low, int high, int pos, int val) {
        seg[ind].erase(seg[ind].find(array[pos]));
        seg[ind].insert(val);
        if (low != high) {
            int mid = low + ((high-low)>>1);
            if (pos <= mid) update(2*ind, low, mid, pos, val);
            else update(2*ind+1, mid+1, high, pos, val);
        }
        else array[pos] = val;
    }

public:
    MergeSortTree(int n) {
        N = n;
        array.resize(N);
        seg.resize(4 * N);
    }

    MergeSortTree(vector<int>& arr) : MergeSortTree(arr.size()) {
        array = arr;
        build(1, 0, N - 1);
    }

    int query(int l, int r, int key) {
        return query(1, 0, N - 1, l, r, key);
    }

    void update(int pos, int val) {
        return update(1, 0, N-1, pos, val);
    }

    vector<multiset<int>> getSeg() {
        return seg;
    }
};

int main() {
    vector<int> arr = {2, -7, 1, 5, 6, -1, 3, 4};
    MergeSortTree mst(arr);
    cout << mst.query(4, 7, 3) << endl;
    mst.update(7, 3);
    cout << mst.query(4, 7, 3) << endl;
}
