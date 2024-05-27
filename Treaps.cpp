#include<bits/stdc++.h>
using namespace std;

#define ll int

struct Node {
    ll key, priority, size;
    Node *left, *right;
    Node(ll val) : key(val), priority(rand()), size(1), left(NULL), right(NULL){};
    Node(ll val, ll priority) : key(val), priority(priority), size(1), left(NULL), right(NULL){};
};

typedef Node* pnode;

// class Treaps {
//     private:
//         pnode root;

//         int sz(pnode t){
//             return t?t->size:0;
//         }
//         void upd_sz(pnode t){
//             if(t)t->size = sz(t->l)+1+sz(t->r);
//         }

//     public:
//         void split(pnode t, pnode &l, pnode &r, int val) {
//             if (!t) l = r = NULL;
//             else if (t->key <= val) 
//                 split(t->right, t->right, r, val), l=t;
//             else 
//                 split(t->left, l, t->left, val), r=t;
//             upd_sz(t);
//         }

//         void merge(pnode &t, pnode &l, pnode &r) {
//             if (!l || !r) t = l ? l : r;
//             else if (l->priority > r->priority)
//                 merge(l->right, l->right, r), t = l;
//             else 
//                 merge(r->left, l, r->left), t = r;
//             upd_sz(t);
//         }

//         void insert(pnode &t, pnode it) {
//             if (!t) t = it;
//             else if (it->priority > t->priority) 
//                 split(t, it->left, it->right, it->val), t = it;
//             else insert(t->val <= it->val ? t->right: t->left, it);
//             upd_sz(t);
//         }

//         void heapify(pnode t) {
//             if (!t) return;
//             pnode mx = t;
//             if (t->left && t->left->priority > mx->priority)
//                 mx = t->left;
//             if (t->right && t->right->priority > mx->priority)
//                 mx = t->right;
//             if (mx != t) 
//                 swap(t->priority, mx->priority), heapify(mx);
//         }

//         pnode build(vector<pair<int, int>> a, int low, int high) {
//             if (n==0) return NULL;
//             int mid = low + ((high - low)>>1);
//             pnode t = new Node(a[mid].first, a[mid].second);
//             t->left = build(a, low, mid);
//             t->right = build(a, mid+1, high);
//             heapify(t);
//             upd_sz(t);
//             return t;
//         }

//         // void inorderTraversal(pitem t) {
//         //     if (t) {
//         //         inorderTraversal(t->left);
//         //         cout << t->val << " ";
//         //         inorderTraversal(t->right);
//         //     }
//         // }
// }

int sz(pnode t){
    return t?t->size:0;
}
void upd_sz(pnode t){
    if(t)t->size = sz(t->left)+1+sz(t->right);
}

void split(pnode t, pnode &l, pnode &r, int val) {
    if (!t) l = r = NULL;
    else if (t->key <= val) 
        split(t->right, t->right, r, val), l=t;
    else 
        split(t->left, l, t->left, val), r=t;
    upd_sz(t);
}

void merge(pnode &t, pnode &l, pnode &r) {
    if (!l || !r) t = l ? l : r;
    else if (l->priority > r->priority)
        merge(l->right, l->right, r), t = l;
    else 
        merge(r->left, l, r->left), t = r;
    upd_sz(t);
}

void insert(pnode &t, pnode it) {
    if (!t) t = it;
    else if (it->priority > t->priority) 
        split(t, it->left, it->right, it->key), t = it;
    else insert(t->key <= it->key ? t->right: t->left, it);
    upd_sz(t);
}

void heapify(pnode t) {
    if (!t) return;
    pnode mx = t;
    if (t->left && t->left->priority > mx->priority)
        mx = t->left;
    if (t->right && t->right->priority > mx->priority)
        mx = t->right;
    if (mx != t) 
        swap(t->priority, mx->priority), heapify(mx);
}

pnode build(int a[][2], int n) {
    if (n==0) return NULL;
    int mid = n>>1;
    pnode t = new Node(a[mid][0], a[mid][1]);
    cout<<t->key<<" ";
    t->left = build(a, mid);
    t->right = build(a, n-mid-1);
    heapify(t);
    upd_sz(t);
    return t;
}

void inorderTraversal(pnode t) {
    if (t) {
        inorderTraversal(t->left);
        cout << t->key << " ";
        inorderTraversal(t->right);
    }
}

int main() {
    int n = 3;
    int la[3][2], ra[3][2];
    for (int i=0; i<3; i++) 
        cin>>la[i][0]>>la[i][1];
    
    for (int i=0; i<3; i++) 
        cin>>ra[i][0]>>ra[i][1];
    
    
    pnode left = build(la, 3);
    pnode right = build(ra, 3);
    inorderTraversal(left);
    // inorderTraversal(right);
    return 0;
}