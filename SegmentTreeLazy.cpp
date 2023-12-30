#include<bits/stdc++.h>
using namespace std;


template <typename T>

class SegmentTree {
private:
    vector<T> seg, lazy;
    int N;

    T combine(T a, T b) {
        return a+b;
    }

    void build(int ind, int low, int high, vector<int>const &arr) {
        if (low==high) {
            seg[ind] = arr[low];
            return;
        }
        int mid = low + ((high-low)>>1);
        int lc = ind << 1, rc = lc | 1;
        build(lc, low, mid, arr);
        build(rc, mid+1, high, arr);
        seg[ind] = combine(seg[lc], seg[rc]);
    }

    void propagate(int ind, int low, int high) {
        if (lazy[ind] != 0) {
            seg[ind] += ((high-low+1)*lazy[ind]);
            // propagte the lazy updates downwards for the remaining nodes to get updated
            if (low!=high) {
                int lc = ind << 1, rc = lc | 1;
                lazy[lc] += lazy[ind];
                lazy[rc] += lazy[ind];
            }
            lazy[ind] = 0;
        }
    }

    void update(int ind, int low, int high, int l, int r, int val) {
        propagate(ind, low, high);
        int lc = ind << 1, rc = lc | 1;
        // No overlap ([l r low high], [low high l r], [low r l high])
        if (low>r || high<l || l>r) return; // change it based on question
        // Complete overlap ([l low high r])
        if (low>=l && high<=r) {
            lazy[ind] = val;
            propagate(ind, low, high);
            return;
        }
        // Partial overlap
        int mid = low + ((high-low)>>1);
        update(lc, low, mid, l, r, val);
        update(rc, mid+1, high, l, r, val);
        seg[ind] = combine(seg[lc], seg[rc]);
    }

    T query(int ind, int low, int high, int l, int r) {
        // update the previous remaining updates and propagates downwards
        propagate(ind, low, high);
        int lc = ind << 1, rc = lc | 1;
        // No overlap ([l r low high], [low high l r], [low r l high])
        if (low>r || high<l || l>r) return 0; // change it based on question
        // Complete overlap ([l low high r])
        if (low>=l && high<=r) return seg[ind];
        //Partial overlap
        int mid = low + ((high-low)>>1);
        return combine(query(lc, low, mid, l, r), query(rc, mid+1, high, l, r));
    }

public:
    SegmentTree(vector<int>const &arr) {
        N = arr.size();
        seg.resize(pow(2, 1+ceil(log2(arr.size()))));
        lazy.resize(pow(2, 1+ceil(log2(arr.size()))));
        build(1, 0, N-1, arr);
    }

    void update(int l, int r, int val) {
        update(1, 0, N-1, l, r, val);
    }

    T query(int l, int r) {
        return query(1, 0, N-1, l, r);
    }

    vector<T> getSeg() {
        return seg;
    }
};

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    vector<int> arr = {1, 0, 2, 1, 1, 3, 0, 4, 2, 5, 2, 2, 3};
    int n = arr.size();
    SegmentTree<int> st(arr);
    for (auto &x: st.getSeg()) 
        cout<<x<<" ";
    cout<<endl;
    cout<<st.query(7, 10)<<endl;
    st.update(0, n-1, 5);
    for (auto &x: st.getSeg()) 
        cout<<x<<" ";
    cout<<endl;
    cout<<st.query(7, 10)<<endl;

    return 0;
}