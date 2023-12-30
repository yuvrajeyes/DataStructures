#include <bits/stdc++.h>
using namespace std;

class SegmentTree {
private:
    int N; // array size
    vector<int> seg; // Max size of seg

    int combine(int a, int b) {
        return a+b;
    }

public:
    SegmentTree(vector<int> const &arr) {
        N = arr.size();
        seg.resize(2 * N);
        build(arr);
    }

    // function to build the seg
    void build(vector<int> const &arr) {
        // insert leaf nodes in seg
        for (int i = 0; i < N; i++)
            seg[N + i] = arr[i];

        // build the seg by calculating parents
        for (int i = N - 1; i > 0; --i)
            seg[i] = combine(seg[i << 1], seg[i << 1 | 1]);
    }

    // function to update a seg node
    void update(int p, int value) {
        // set value at position p
        p = N + p;
        seg[p] = value;

        // move upward and update parents
        for (int i = p; i > 1; i >>= 1)
            seg[i >> 1] = combine(seg[i], seg[i ^ 1]);
    }

    // function to get sum on interval [l, r)
    int query(int l, int r) {
        int res = 0;

        // loop to find the sum in the range
        for (l += N, r += (N+1); l < r; l >>= 1, r >>= 1) {
            if (l & 1)
                res += seg[l++];

            if (r & 1)
                res += seg[--r];
        }

        return res;
    }
};

// driver program to test the above function
int main() {
    vector<int> a = {1, 0, 2, 1, 1, 3, 0, 4, 2, 5, 2, 2, 3};

    // create a SegmentTree object
    SegmentTree st(a);

    // print the sum in range(1,3) index-based
    cout << st.query(7, 10) << endl;


    return 0;
}
