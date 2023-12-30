#include<bits/stdc++.h>
using namespace std;

class node{
    public:
    int val, lazy;
    node *left, *right;
    node() {
        val = 0, lazy = 0;
        left = right = NULL;
    }
};

class ST{
    private:
        void propagate(int high, int low) {
            root->val = high - low + 1;
            if(low != high) {
                root->left->lazy = 1;
                root->right->lazy = 1;
            }
            root->lazy = 0;
        }

        void update(node *root, int low, int high, int l, int r) {
        // non overlap -> low high l r, l r low high
        if(high < l || r < low) return;

        if(!root->left) {
            root->left = new node();
            root->right = new node();
        }

        //update current node and propagate laziness to the child nodes
        if(root->lazy) {
            propagate(low, high);
        }

        // all ranges are covered then return 
        if(root->val == high - low + 1) return;

        // comp overlap -> l low high r
        // assign value (high-low+1) and propagate laziness to the child nodes 
        if(low >= l && high <= r) {
            propagate(low, high);
            return;
        }

        int mid = low + (high - low) / 2;
        update(root->left, low, mid, l, r);
        update(root->right, mid+1, high, l, r);
        // update node range from its child nodes' ranges
        root->val = root->left->val + root->right->val;
    }

    public:
    node *root = new node();

    node* getRoot() {
        return root;
    }

    void update(int low, int high, int l, int r) {
        update(root, low, high, l, r);
    }
};