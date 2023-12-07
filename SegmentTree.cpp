#include<bits/stdc++.h>
using namespace std;
template <typename T>


class SegmentTree {
private:
    vector<T> seg;
public:
    SegmentTree(int n) {
        seg.resize(4*n+1);
    }

    SegmentTree(vector<int>const &arr) : SegmentTree(arr.size()) {
        build(1, 0, arr.size()-1, arr);
    }

    T f(T a, T b) {
        return min(a,b);
    }

    void build(int ind, int low, int high, vector<int>const &arr) {
        if (low==high) {
            seg[ind] = arr[low];
            return;
        }
        int mid = low + ((high-low)>>1);
        build(2*ind+1, low, mid, arr);
        build(2*ind+2, mid+1, high, arr);
        seg[ind] = f(seg[2*ind+1], seg[2*ind+2]);
    }

    void update(int ind, int low, int high, int pos, int val) {
        if (low==high) {
            seg[ind] = val;
            return;
        }
        int mid = low + ((high-low)>>1);
        if (pos<=mid) update(2*ind+1, low, mid, pos, val);
        else update(2*ind+2, mid+1, high, pos, val);
        seg[ind] = f(seg[2*ind+1], seg[2*ind+2]);
    }

    T query(int ind, int low, int high, int l, int r) {
        // No overlap ([l r low high], [low high l r], [low r l high])
        if (low>r or high<l or l>r) return INT_MAX; // change it based on question
        // Complete overlap ([l low high r])
        if (low>=l and high<=r) return seg[ind];
        //Partial overlap
        int mid = low + ((high-low)>>1);
        T left = query(2*ind+1, low, mid, l, r);
        T right = query(2*ind+2, mid+1, high, l, r);
        return f(left, right);
    }

    vector<T> getSeg() {
        return seg;
    }
};

int main() {
    vector<int> arr = {1, 0, 2, 1, 1, 3, 0, 4, 2, 5, 2, 2, 3, 1, 0, 2};
    int n = arr.size();
    // SegmentTree<int> st(n);
    // st.build(1, 0, n-1, arr);
    SegmentTree<int> st(arr);
    for (auto &x: st.getSeg()) 
        cout<<x<<" ";
    cout<<endl;
    cout<<st.query(1, 0, n-1, 7, 11)<<endl;
    return 0;
}