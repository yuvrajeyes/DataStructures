#include<bits/stdc++.h>
using namespace std;

#define all(a) a.begin(), a.end()

class MergeSortTree {
private:
    vector<vector<int>> seg;
    int N;

    int combine(int a, int b) {
        return a + b;
    }

    void build(int ind, int low, int high, vector<int> const& arr) {
        if (low == high) {
            seg[ind].push_back(arr[low]);
            return;
        }
        int mid = low + ((high - low) >> 1);
        build(2 * ind, low, mid, arr);
        build(2 * ind + 1, mid + 1, high, arr);
        merge(all(seg[2 * ind]), all(seg[2 * ind + 1]), back_inserter(seg[ind]));
    }

    int query(int ind, int low, int high, int l, int r, int key) {
        if (r < low || l > high || l > r) return 0;
        if (low >= l && high <= r) {
            auto pos = upper_bound(all(seg[ind]), key);  // use lower_bound for greater than or equal to
            if (pos != seg[ind].end()) {
                return distance(pos, seg[ind].end());  // // for the number of element greater than specified number
                return *pos;  // for smallest number greater than specified number
            }
            return 0;
        }
        int mid = low + ((high - low) >> 1);
        return query(2 * ind, low, mid, l, r, key) + query(2 * ind + 1, mid + 1, high, l, r, key);
    }

public:
    MergeSortTree(int n) {
        N = n;
        seg.resize(4 * N);
    }

    MergeSortTree(vector<int>& arr) : MergeSortTree(arr.size()) {
        build(1, 0, N - 1, arr);
    }

    int query(int l, int r, int key) {
        return query(1, 0, N - 1, l, r, key);
    }

    vector<vector<int>> getSeg() {
        return seg;
    }
};

int main() {
    vector<int> arr = {2, -7, 1, 5, 6, -1, 3, 4};
    MergeSortTree mst(arr);
    cout << mst.query(4, 7, 3) << endl;
}
