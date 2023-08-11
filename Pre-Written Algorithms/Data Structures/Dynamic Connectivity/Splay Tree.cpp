#include <bits/stdc++.h>
using namespace std;

struct SplayNode {
    array<SplayNode*, 2> child{};
    SplayNode* parent = nullptr;
    int  value, subtreeSize;

    SplayNode(int  value) : value(value), subtreeSize(1) {}

    SplayNode*& next(SplayNode* other) {
        return child[value < other->value];
    }

    bool equals(SplayNode* other) {
        return other ? other->value == value : false;
    }

    // true if the current node is a right child, false otherwise
    bool getSide() {
        return parent ? parent->child[1] == this : false;
    }

    // Makes the current node the root of the tree
    SplayNode* splay() {
        while (parent) {
            if (parent->parent) {
                (getSide() == parent->getSide() ? parent : this)->rotate();
            }
            rotate();
        }
        return this;
    }

    // Rotates the nodes in O(1) to reduce the current node's depth
    SplayNode* rotate() {
        bool side = getSide(), parentSide = parent->getSide();
        auto ancestor = parent->parent;
        parent->attach(child[!side], side);
        attach(parent, !side);
        if (ancestor) ancestor->attach(this, parentSide);
        else parent = nullptr;
        return this;
    }

    SplayNode* attach(SplayNode* node, int side) {
        if (node) node->parent = this;
        child[side] = node;
        update();
        return this;
    }

    // Updates subtree values
    void update() {
        subtreeSize = 1 + (child[0] ? child[0]->subtreeSize : 0) + (child[1] ? child[1]->subtreeSize : 0);
    }
};
struct SplayTree {
    SplayNode* root = nullptr;
    SplayTree() {}

    // Creates a new node with value x and inserts it in the BST
    // Amortized O(log n)
    SplayNode* insert(int x) {
        SplayNode* node = new SplayNode(x);
        if (!root) return root = node;
        SplayNode* cur = root;
        while (true) {
            // if no repetition allowed
            /*if (cur->equals(node)) {
                return splay(cur);
            }*/
            auto &child = cur->next(node);
            if (!child) {
                child = node;
                node->parent = cur;
                return splay(node);
            }
            cur = child;
        }
    }

    SplayNode* find(int x) {
        SplayNode* node = new SplayNode(x), * cur = root;
        while (cur) {
            if (cur->equals(node)) {
                break;
            }
            else if (!cur->next(node)) {
                splay(cur);
            }
            cur = cur->next(node);
        }
        delete node;
        return splay(cur);
    }

    // Makes node the root of the splay tree
    SplayNode* splay(SplayNode* node) {
        return node ? root = node->splay() : nullptr;
    }

    //Erase x from the splay tree in amortized O(logn) time
    void erase(SplayNode* x) {
        if (!x) { return; }
        splay(x);
        SplayNode* lChild = x->child[0], * rChild = x->child[1];
        if (lChild) lChild->parent = nullptr;
        if (rChild) rChild->parent = nullptr;
        root = join(lChild, rChild);
        delete x;
    }

    // Find the kth node in the tree in amortized O(logn)
    SplayNode* kth(int k) {
        SplayNode* cur = root, * ans = nullptr;
        while (cur) {
            int leftSize = (cur->child[0] ? cur->child[0]->subtreeSize : 0);
            if (leftSize == k - 1) {
                ans = cur;
                return splay(ans);
            }
            else if (leftSize >= k) cur = cur->child[0];
            else {
                k -= (leftSize + 1);
                if (!cur->child[1]) {
                    splay(cur);
                    return ans;
                }
                cur = cur->child[1];
            }
        }
    }

    vector<int> inorder() {
        vector<int> ans;
        stack<SplayNode*> st;
        SplayNode* cur = root;
        while (cur) st.push(cur), cur = cur->child[0];
        while (st.size()) {
            cur = st.top(); st.pop();
            ans.push_back(cur->value);
            cur = cur->child[1];
            while (cur) st.push(cur), cur = cur->child[0];
        }
        return ans;
    }

private:
    //Finds the node with max value in the subtree of x
    SplayNode* findMax(SplayNode* x) {
        if (!x) { return nullptr; }
        while (x->child[1]) { x = x->child[1]; }
        return x->splay();
    }

    //Finds the node with min value in the subtree of x
    SplayNode* findMin(SplayNode* x) {
        if (!x) { return nullptr; }
        while (x->child[0]) { x = x->child[0]; }
        return x->splay();
    }

    //Joins 2 splay trees rooted at a and b, assumes that all values in a are smaller than all values in b
    SplayNode* join(SplayNode* a, SplayNode* b) {
        if (!a && !b) { return nullptr; }
        if (!a) { b->parent = nullptr; return b; }
        if (!b) { a->parent = nullptr; return a; }
        SplayNode* newRoot = findMax(a);
        newRoot->attach(b, 1);
        return newRoot;
    }
};