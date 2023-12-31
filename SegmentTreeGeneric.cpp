#include<iostream>
#include<algorithm>
#include<math.h>
#include<vector>
#include<cassert>
using namespace std;

#define ll int // long long
#define sz(a) a.size()

template<class T, class U>
// T -> node, U->update.
struct Lsegtree{
    vector<T>st;
    vector<U>lazy;
    ll n;
    T identity_element;
    U identity_update;

    Lsegtree(ll n, T identity_element, U identity_update) {
        this->n = n;
        this->identity_element = identity_element;
        this->identity_update = identity_update;
        st.assign(pow(2, 1+ceil(log2(n))), identity_element);
        lazy.assign(pow(2, 1+ceil(log2(n))), identity_update);
    }

    // change the following 3 functions as required
    T combine(T l, T r) {
        T ans = (l + r);
        return ans;
    }

    T apply(T curr, U upd, ll low, ll high) {
        T ans = curr + (high - low + 1) * upd;
        return ans;
    }

    U combineUpdate(U old_upd, U new_upd, ll low, ll high) {
        U ans = old_upd;
        ans += new_upd;
        return ans;
    }  

    void buildUtil(ll v, ll low, ll high, vector<T>&a) {
        if(low == high) {
            st[v] = a[low];
            return;
        }
        ll mid = low + ((high-low)>>1);
        ll lc = v << 1, rc = lc | 1;
        buildUtil(lc, low, mid, a);
        buildUtil(rc, mid+1, high, a);
        st[v] = combine(st[lc], st[rc]);
    }

    void propagate(ll v, ll low, ll high) {
        if(lazy[v] == identity_update) return;
        st[v] = apply(st[v], lazy[v], low, high);
        if(low != high) {
            ll mid = low + ((high-low)>>1);
            ll lc = v << 1, rc = lc | 1;
            lazy[lc] = combineUpdate(lazy[lc], lazy[v], low, mid);
            lazy[rc] = combineUpdate(lazy[rc], lazy[v], mid+1, high);            
        }
        lazy[v] = identity_update;
    }

    T queryUtil(ll v, ll low, ll high, ll l, ll r) {
        // update the previous remaining updates and propagates downwards
        propagate(v, low, high);
        // No overlap ([l r low high], [low high l r], [low r l high])
        if(low > r || high < l || l > r) return identity_element;
        // Complete overlap ([l low high r])
        if(low >= l && high <= r) return st[v];
        //Partial overlap
        ll mid = low + ((high-low)>>1);
        ll lc = v << 1, rc = lc | 1;
        return combine(queryUtil(lc, low, mid, l, r), queryUtil(rc, mid+1, high, l, r));
    }
 
    void updateUtil(ll v, ll low, ll high, ll l, ll r, U upd) {
        // update the previous remaining updates and propagates downwards
        propagate(v, low, high); 
        // No overlap ([l r low high], [low high l r]
        if(low > r || high < l) return;
        // Complete overlap ([l low high r])
        if(low >=l && high <=r) {
            lazy[v] = combineUpdate(lazy[v], upd, low, high);
            propagate(v, low, high);
        } 
        else { // Partial overlap
            ll mid = low + ((high-low)>>1);
            ll lc = v << 1, rc = lc | 1;
            updateUtil(lc, low, mid, l, r, upd);
            updateUtil(rc, mid+1, high, l, r, upd);
            st[v] = combine(st[lc], st[rc]);
        }
    }

    void build(vector<T>a) {
        assert(sz(a) == n);
        buildUtil(1, 0, n-1, a);
    }

    T query(ll l, ll r) {
        return queryUtil(1, 0, n-1, l, r);
    }

    void update(ll l,ll r, U upd) {
        updateUtil(1, 0, n-1, l, r, upd);
    }
};

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    vector<int> arr = {1, 0, 2, 1, 1, 3, 0, 4, 2, 5, 2, 2, 3};
    int n = arr.size();
    Lsegtree<int, int> st(n, 0, 0);
    st.build(arr);
    // cout<<st.query(0, n-1);
    for (auto &x: st.st) 
        cout<<x<<" ";
    cout<<endl;
    cout<<st.query(7, 10)<<endl;
    st.update(0, n-1, 5);
    for (auto &x: st.st) 
        cout<<x<<" ";
    cout<<endl;
    cout<<st.query(7, 10)<<endl;
    return 0;
}