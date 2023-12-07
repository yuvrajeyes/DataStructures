#include<bits/stdc++.h>
using namespace std;
template <typename T>


class SegmentTree {
private:
    vector<T> seg, lazy;
public:
    SegmentTree(int n) {
        seg.resize(4*n+1);
        lazy.resize(4*n+1);
    }

    SegmentTree(vector<int>const &arr) : SegmentTree(arr.size()) {
        build(1, 0, arr.size()-1, arr);
    }

    T f(T a, T b) {
        return a+b;
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

    void update(int ind, int low, int high, int l, int r, int val) {
        // update the previous remaining updates and propagates downwards
        if (lazy[ind] != 0) {
            seg[ind] += ((high-low+1)*lazy[ind]);
            // propagte the lazy updates downwards for the remaining nodes to get updated
            if (low!=high) {
                lazy[2*ind+1] += lazy[ind];
                lazy[2*ind+2] += lazy[ind];
            }
            lazy[ind] = 0;
        }

        // No overlap ([l r low high], [low high l r], [low r l high])
        if (low>r || high<l || l>r) return; // change it based on question
        // Complete overlap ([l low high r])
        if (low>=l && high<=r) {
            seg[ind] += ((high-low+1)*val);
            if (low!=high) {
                lazy[2*ind+1] += val;
                lazy[2*ind+2] += val;
            }
            return;
        }
        // Partial overlap
        int mid = low + ((high-low)>>1);
        update(2*ind+1, low, mid, l, r, val);
        update(2*ind+2, mid+1, high, l, r, val);
        seg[ind] = f(seg[2*ind+1], seg[2*ind+2]);
    }

    T query(int ind, int low, int high, int l, int r) {
        // update the previous remaining updates and propagates downwards
        if (lazy[ind] != 0) {
            seg[ind] += ((high-low+1)*lazy[ind]);
            // propagte the lazy updates downwards for the remaining nodes to get updated
            if (low!=high) {
                lazy[2*ind+1] += lazy[ind];
                lazy[2*ind+2] += lazy[ind];
            }
            lazy[ind] = 0;
        }

        // No overlap ([l r low high], [low high l r], [low r l high])
        if (low>r || high<l || l>r) return 0; // change it based on question
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
    SegmentTree<int> st(arr);
    for (auto &x: st.getSeg()) 
        cout<<x<<" ";
    cout<<endl;
    cout<<st.query(1, 0, n-1, 7, 11)<<endl;
    st.update(1, 0, n-1, 0, n-1, 5);
    for (auto &x: st.getSeg()) 
        cout<<x<<" ";
    cout<<endl;
    cout<<st.query(1, 0, n-1, 7, 11)<<endl;
    for (auto &x: st.getSeg()) 
        cout<<x<<" ";
    cout<<endl;
    return 0;
}