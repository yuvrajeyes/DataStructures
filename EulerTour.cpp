#include<iostream>
#include<algorithm>
#include<math.h>
#include<vector>
#include<cassert>
using namespace std;

#define ll int // long long
#define sz(a) a.size()

template<class T, class U, class A>
// T -> node, U->update, A->input Array.
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
        st.assign(4*this->n, identity_element);
        lazy.assign(4*this->n, identity_update);
    }

    // change the following 4 functions as required
    T combine(T l, T r) {
        return (l | r);
    }

    T make_data(T val) {
        return 1ll << val;
    }

    T apply(T curr, U upd, ll low, ll high) {
        return 1ll << upd;
    }

    U combineUpdate(U old_upd, U new_upd, ll low, ll high) {
        return new_upd;
    }  

    void buildUtil(ll v, ll low, ll high, vector<A>&a) {
        if(low == high) {
            st[v] = make_data(a[low]);
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

    void build(vector<A>a) {
        // assert(sz(a) == n);
        buildUtil(1, 1, n, a);
    }

    T query(ll l, ll r) {
        return queryUtil(1, 1, n, l, r);
    }

    void update(ll l,ll r, U upd) {
        updateUtil(1, 1, n, l, r, upd);
    }
};

class EulerTour {
public:
    vector<int> color, ltree, start, end;
    vector<vector<int>> adj;
    int time;

    EulerTour(int n) {
        color.assign(n + 1, 0);
        start.assign(n + 1, 0);
        end.assign(n + 1, 0);
        ltree.assign(n + 1, 0);
        adj.assign(n + 1, vector<int>());
        time = 0;
    }

    void dfs(int node, int p) {
        start[node] = ++time;
        ltree[time] = color[node];
        for (int v: adj[node]) {
            if (v != p) {
                dfs(v, node);
            }
        }
        end[node] = time;
    }
};


int main() { // CODEFORCES: NEW YEAR TREE
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int n, m;
    cin >> n >> m;

    EulerTour et(n);
    Lsegtree<long long, int, int> st(n, 0, 0);
    
    for (int i=1; i<n+1; i++) cin >> et.color[i];

    for (int i=1; i<n; i++) {
        int u, v;
        cin >> u >> v;
        et.adj[u].push_back(v);
        et.adj[v].push_back(u);
    }

    et.dfs(1, 0);
    st.build(et.ltree);

    while (m--) {
        int t, v;
        cin >> t >> v;
        if (t == 1) {
            int c;
            cin >> c;
            st.update(et.start[v], et.end[v], c);
        }
        else {
            long long ans = st.query(et.start[v], et.end[v]);
            int cnt = 0;
            while (ans > 0) {
                cnt++;
                ans = ans&(ans-1);
            }
            cout << cnt <<" ";
        }
    }
	
    return 0;
}

// #include<iostream>
// #include<algorithm>
// #include<math.h>
// #include<vector>
// #include<cassert>
// using namespace std;

// #define ll int // long long
// #define sz(a) a.size()

// class EulerTour {
// public:
//     vector<int> color, ltree, start, end, lazy;
//     vector<long long> st;
//     vector<vector<int>> adj;
//     int time;

//     EulerTour(int n) {
//         color.assign(n + 1, 0);
//         start.assign(n + 1, 0);
//         end.assign(n + 1, 0);
//         ltree.assign(n + 1, 0);
//         st.assign(4 * n, 0);
//         lazy.assign(4 * n, 0);
//         adj.assign(n + 1, vector<int>());
//         time = 0;
//     }

//     void dfs(int node, int p) {
//         start[node] = ++time;
//         ltree[time] = color[node];
//         for (int v: adj[node]) {
//             if (v != p) {
//                 dfs(v, node);
//             }
//         }
//         end[node] = time;
//     }

//     void build(ll v, ll low, ll high) {
//         if(low == high) {
//             st[v] = 1ll << ltree[low];
//             return;
//         }
//         ll mid = low + ((high-low)>>1);
//         ll lc = v << 1, rc = lc | 1;
//         build(lc, low, mid);
//         build(rc, mid+1, high);
//         st[v] = st[lc] | st[rc];
//     }

//     void update(ll v, ll low, ll high, ll l, ll r, int upd) {
//         // update the previous remaining updates and propagates downwards
//         propagate(v, low, high); 
//         // No overlap ([l r low high], [low high l r]
//         if(low > r || high < l) return;
//         // Complete overlap ([l low high r])
//         if(low >=l && high <=r) {
//             lazy[v] = upd;
//             propagate(v, low, high);
//         } 
//         else { // Partial overlap
//             ll mid = low + ((high-low)>>1);
//             ll lc = v << 1, rc = lc | 1;
//             update(lc, low, mid, l, r, upd);
//             update(rc, mid+1, high, l, r, upd);
//             st[v] = st[lc] | st[rc];
//         }
//     }

//     void propagate(ll v, ll low, ll high) {
//         if(lazy[v] == 0) return;
//         st[v] = 1ll << lazy[v];
//         if(low != high) {
//             ll mid = low + ((high-low)>>1);
//             ll lc = v << 1, rc = lc | 1;
//             lazy[lc] = lazy[v];
//             lazy[rc] = lazy[v];
//         }
//         lazy[v] = 0;
//     }

//     long long query(ll v, ll low, ll high, ll l, ll r) {
//         // update the previous remaining updates and propagates downwards
//         propagate(v, low, high);
//         // No overlap ([l r low high], [low high l r], [low r l high])
//         if(low > r || high < l || l > r) return 0;
//         // Complete overlap ([l low high r])
//         if(low >= l && high <= r) return st[v];
//         //Partial overlap
//         ll mid = low + ((high-low)>>1);
//         ll lc = v << 1, rc = lc | 1;
//         return query(lc, low, mid, l, r) | query(rc, mid+1, high, l, r);
//     }
// };


// int main() { // CODEFORCES: NEW YEAR TREE
//     ios_base::sync_with_stdio(0);
//     cin.tie(0);
//     int n, m;
//     cin >> n >> m;

//     EulerTour et(n);
    
//     for (int i=1; i<n+1; i++) cin >> et.color[i];

//     for (int i=1; i<n; i++) {
//         int u, v;
//         cin >> u >> v;
//         et.adj[u].push_back(v);
//         et.adj[v].push_back(u);
//     }

//     et.dfs(1, 0);
//     et.build(1, 1, n);

//     while (m--) {
//         int t, v;
//         cin >> t >> v;
//         if (t == 1) {
//             int c;
//             cin >> c;
//             et.update(1, 1, n, et.start[v], et.end[v], c);
//         }
//         else {
//             long long ans = et.query(1, 1, n, et.start[v], et.end[v]);
//             int cnt = 0;
//             while (ans > 0) {
//                 cnt++;
//                 ans -= ans&(-ans);
//             }
//             cout << cnt <<" ";
//         }
//     }
	
//     return 0;
// }