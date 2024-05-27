#include<bits/stdc++.h>
using namespace std;

class FenwickTree {
private: 
    vector<int> bit;
    int N;
public:
    FenwickTree(int n) {
        this->N = n+1;
        this->bit.assign(N, 0);
    }

    FenwickTree(vector<int>const &arr) : FenwickTree(arr.size()){
        for (int i = 1; i < N; i++) {
            bit[i] += arr[i-1];
            int r = i + (i & -i);
            if (r < N) bit[r] += bit[i];
        }
    }
 
    vector<int> getBitArray() {
        return bit;
    }

    void update(int i, int val) {
        for (; i < N; i += (i & -i)) {
            bit[i] += val;
        }
    }

    int sum(int r) {
        int ans = 0;
        for (; r > 0; r -= (r & -r)) {
            ans += bit[r];
        }
        return ans;
    }

    int sum(int l, int r) {
        return sum(r) - sum(l-1);
    }
};

class FenwickTree2D {
private: 
    vector<vector<int>> bit;
    int N1, N2;
public:
    FenwickTree2D(int n1, int n2) {
        this->N1 = n1;
        this->N2 = n2;
        this->bit.assign(N1, vector<int>(N2, 0));
    }

    FenwickTree2D(vector<vector<int>>const &arr) : FenwickTree2D(arr.size(), arr[0].size()){
        for (int i = 0; i < N1; i++)
            for (int j = 0; j < N2; j++)
                update(i, j, arr[i][j]);
    }
 
    vector<vector<int>> getBitArray() {
        return bit;
    }

    int sum(int x, int y) {
        int ret = 0;
        for (int i = x; i >= 0; i = (i & (i + 1)) - 1)
            for (int j = y; j >= 0; j = (j & (j + 1)) - 1)
                ret += bit[i][j];
        return ret;
    }

    void update(int x, int y, int delta) {
        for (int i = x; i < N1; i = i | (i + 1))
            for (int j = y; j < N2; j = j | (j + 1))
                bit[i][j] += delta;
    }
};

int main() {
    // vector<int> arr1 = {1, 0, 2, 1, 1, 3, 0, 4, 2, 5, 2, 2, 3, 1, 0, 2};
    // FenwickTree ft1(arr1);
    // // for (int i=0; i<arr.size(); i++) ft.update(i+1, arr[i]);
    // vector<int> bit1 = ft1.getBitArray();
    // for (auto &x: bit1) cout<<x<<" ";
    // cout<<endl;
    // cout<<ft1.sum(2, 14)<<endl;

    // vector<vector<int>> arr = {{1, 0, 2, 1}, {1, 3, 0, 4}, {2, 5, 2, 2}, {3, 1, 0, 2}};
    // FenwickTree2D ft(arr);
    // // for (int i=0; i<arr.size(); i++) ft.update(i+1, arr[i]);
    // vector<vector<int>> bit = ft.getBitArray();
    // for (auto &b: bit) {
    //     for (auto &x: b) {
    //         cout<<x<<" ";
    //     }
    //     cout<<endl;
    // }
    // cout<<endl;
    // cout<<ft.sum(1, 3)<<endl;
    return 0;
}