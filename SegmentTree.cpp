#include<bits/stdc++.h>
using namespace std;

struct info {
    int sum, pref, suff, ans;
};

template <typename T>


class SegmentTree {
private:
    vector<T> seg;
    int N;

    info make_info(int val) {
        info res;
        res.sum = res.pref = res.suff = res.ans = val;
        return res;
    }

    info combine(info l, info r) {
        info res;
        res.sum = l.sum + r.sum;
        res.pref = max(l.pref, l.sum + r.pref);
        res.suff = max(r.suff, r.sum + l.suff);
        res.ans = max(std::max(l.ans, r.ans), l.suff + r.pref);
        return res;
    }

    void build(int ind, int low, int high, vector<int>const &arr) {
        if (low==high) {
            seg[ind] =  make_info(arr[low]); // arr[low];
            return;
        }
        int mid = low + ((high-low)>>1);
        build(2*ind, low, mid, arr);
        build(2*ind+1, mid+1, high, arr);
        seg[ind] = combine(seg[2*ind], seg[2*ind+1]);
    }

    void update(int ind, int low, int high, int pos, int val) {
        if (low==high) {
            seg[ind] = make_info(val); // val;
            return;
        }
        int mid = low + ((high-low)>>1);
        if (pos<=mid) update(2*ind, low, mid, pos, val);
        else update(2*ind+1, mid+1, high, pos, val);
        seg[ind] = combine(seg[2*ind], seg[2*ind+1]);
    }

    T query(int ind, int low, int high, int l, int r) {
        cout<<seg[ind].ans<<endl;
        // No overlap ([l r low high], [low high l r], [low r l high])
        if (low>r or high<l or l>r) return make_info(-1e9); // change it based on question
        // Complete overlap ([l low high r])
        if (low>=l and high<=r) return seg[ind];
        //Partial overlap
        int mid = low + ((high-low)>>1);
        T left = query(2*ind, low, mid, l, r);
        T right = query(2*ind+1, mid+1, high, l, r);
        return combine(left, right);
    }

public:
    SegmentTree(int n) {
        N = n;
        seg.resize(pow(2, ceil(log2(N))+1));
    }

    SegmentTree(vector<int>const &arr) : SegmentTree(arr.size()) {
        build(1, 0, arr.size()-1, arr);
    }

    T query(int l, int r) {
        return query(1, 0, N-1, l, r);
    }

    vector<T> getSeg() {
        return seg;
    }
};

int main() {
    vector<int> arr = {-3, 100, -400, 60, 60, -400, 100, -3}; // {1, 0, 2, 1, 1, 3, 0, 4, 2, 5, 2};
    int n = arr.size();
    SegmentTree<info> st(arr);
    for (auto &x: st.getSeg()) 
        cout<<x.sum<<" ";
    cout<<endl;
    cout<<st.query(0,0).ans<<endl;
    return 0;
}