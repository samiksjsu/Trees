//
// Created by samik on 2/5/2021.
//

#ifndef TREE_PRACTICE_TREE_H
#define TREE_PRACTICE_TREE_H

#include <iostream>
#include <queue>
#include <stack>
#include "TreeNode.h"

using namespace std;

class Tree {
    TreeNode *root;

    Tree(TreeNode *root) : root{root} {};

public:
    void createTree() {
        int tempVal = 0;
        cout << "Enter the value of root" << endl;
        cin >> tempVal;

        if (tempVal != -1) {
            root = new TreeNode(tempVal);
        }

        queue<TreeNode *> q;
        q.push(root);

        while (!q.empty()) {
            TreeNode *curr = q.front();
            q.pop();

            cout << "Enter the left child of " << curr->val << endl;
            cin >> tempVal;
            if (tempVal != -1) {
                curr->left = new TreeNode(tempVal);
            }

            cout << "Enter the right child of " << curr->val << endl;
            cin >> tempVal;
            if (tempVal != -1) {
                curr->right = new TreeNode(tempVal);
            }
        }
    }

    void createTreeFromArray(vector<int> &arr) {

        int idx = 0;
        int tempVal = arr[idx];
        idx++;
        root = new TreeNode(tempVal);

        queue<TreeNode *> q;
        q.push(root);

        while (!q.empty()) {
            TreeNode *curr = q.front();
            q.pop();

            if (idx < arr.size()) {
                if (arr[idx] != -1) {
                    curr->left = new TreeNode(arr[idx]);
                }
                idx++;
            }

            if (idx < arr.size()) {
                if (arr[idx] != -1) {
                    curr->right = new TreeNode(arr[idx]);
                }
                idx++;
            }
        }

    }

    int height(TreeNode *root) {
        if (root) {
            int left = height(root->left);
            int right = height(root->right);

            return left > right ? left + 1 : right + 1;
        }

        return 0;
    }

    void preOrderRecursive(TreeNode *root) {
        if (root) {
            cout << root->val << " ";
            preOrderRecursive(root->left);
            preOrderRecursive(root->right);
        }
    }

    void inOrderRecursive(TreeNode *root) {
        if (root) {
            inOrderRecursive(root->left);
            cout << root->val << " ";
            inOrderRecursive(root->right);
        }
    }

    void postOrderRecursive(TreeNode *root) {
        if (root) {
            postOrderRecursive(root->left);
            postOrderRecursive(root->right);
            cout << root->val << " ";
        }
    }

    void levelOrderRecursive(TreeNode *root) {
        int h = height(root);

        for (int i = 1; i <= h; i++) {
            printLevelOrder(root, i);
        }
    }

    void printLevelOrder(TreeNode *root, int level) {
        if (!root) return;

        if (level == 1) {
            cout << root->val << " ";
        } else {
            printLevelOrder(root->left, level - 1);
            printLevelOrder(root->right, level - 1);
        }
    }

    void preOrderIterative(TreeNode *root) {

        stack<TreeNode *> st;

        while (!st.empty() || root) {
            if (root) {
                cout << root->Val << " ";
                st.push(root);
                root = root->left;
            } else {
                root = st.top()->right;
                st.pop();
            }
        }
    }

    void inOrderIterative(TreeNode *root) {
        stack<TreeNode *> st;

        while (!st.empty() || root) {
            if (root) {
                st.push(root);
                root = root->left;
            } else {
                root = st.top();
                st.pop();
                cout << root->val << " ";
                root = root->right;
            }
        }
    }

    void postOrderIterative(TreeNode *root) {
        stack<TreeNode *> st1;
        stack<TreeNode *> st2;

        st1.push(root);

        while (!st1.empty()) {
            TreeNode *curr = st1.top();
            st1.pop();
            st2.push(curr);

            if (curr->left) st1.push(curr->left);
            if (curr->right) st2.push(curr->right);
        }

        while (!st2.empty()) {
            TreeNode *curr = st2.top();
            st2.pop();

            cout << curr->val << " ";
        }
    }

    void levelOrderIterative(TreeNode *root) {
        queue<TreeNode *> q;

        while (!q.empty()) {
            TreeNode *curr = q.front();
            q.pop();

            cout << curr->val << " ";

            if (curr->left) q.push(curr->left);
            if (curr->right) q.push(curr->right);
        }
    }

    /** BST specific functions */
    TreeNode *createBSTFromSortedArray(vector<int> nums, int start, int end) {
        if (start <= end) {
            int mid = (start + end) / 2;

            TreeNode *curr = new TreeNode(nums[mid]);
            curr->left = createBSTFromSortedArray(nums, start, mid - 1);
            curr->right = createBSTFromSortedArray(nums, mid + 1, end);

            return curr;
        }

        return nullptr;
    }

    TreeNode *inOrderSucc(TreeNode *root) {
        while (root->left) root = root->left;

        return root;
    }

    TreeNode *inOrderPred(TreeNode *root) {
        while (root->right) root = root->right;

        return root;
    }

    TreeNode *deleteNode(TreeNode *root, int val) {
        if (root) {
            if (root->val == val && !root->left && !root->right) {
                return nullptr;
            } else if (root->val == valarray) {
                if (height(root->left) >= height(root->right)) {
                    TreeNode *pred = inOrderPred(root->left);
                    root->val = pred->val;
                    deleteNode(root->left, pred->val)
                } else {
                    TreeNode *succ = inOrderSucc((root->right));
                    root->val = succ->val;
                    deleteNode(root->right, succ->val);
                }
            } else {
                if (val > root->val) deleteNode(root->right, val);
                deleteNode(root->left, val);
            }

            if (balanceFactor(root) == 2 && (balanceFactor(root->left) == 1 || balanceFactor(root->left) == 0)) {
                root = llRotation(root);
            } else if (balanceFactor(root) == 2 && balanceFactor(root->left) == -1) {
                root = lrRotation(root);
            } else if (balanceFactor(root) == -2 && (balanceFactor(root->right) == -1 || balanceFactor(root->right) == 0)) {
                root = rrRotation(root);
            } else if(balanceFactor(root) == -2 && balanceFactor(root->right) == 1) {
                root = rlRotation(root);
            }

            return root;
        }

        return nullptr;
    }

    TreeNode *insertNode(TreeNode *root, int val) {
        if (!root) {
            TreeNode *temp = new TreeNode(val);
            return temp;
        }

        if (val > root->val) root->right = insertNode(root->right, val);
        else root->left = insertNode(root->left, val);

        if (balanceFactor(root) == 2 && balanceFactor(root->left) = 1) {
            root = llRotation(root);
        } else if (balanceFactor(root) == 2 && balanceFactor(root->left) == -1) {
            root = lrRotation(root);
        } else if (balanceFactor(root) = -2 && balanceFactor(root->right) == -1) {
            root = rrRotation(root);
        } else if(balanceFactor(root) = -2 && balanceFactor(root->right) == 1) {
            root = rlRotation(root);
        }

        return root;
    }

    /** AVL specific functions */
    int balanceFactor(TreeNode *root) {
        if (root) {
            int hl = height(root->left);
            int hr = height(root->right);

            return hl - hr;
        }
    }

    TreeNode *llRotation(TreeNode *r) {
        TreeNode *rl = r->left;

        r->left = rl->right;
        rl->right = r;

        return rl;
    }

    TreeNode *lrRotation(TreeNode *r) {
        TreeNode *rl = r->left;
        TreeNode *rlr = rl->right;

        rl->right = rlr->left;
        r->left = rlr->right;
        rlr->left = rl;
        rlr->right = r;

        return rlr;
    }

    TreeNode *rrRotation(TreeNode *r) {
        TreeNode *rr = r->right;

        r->right = rr->left;
        rr->left = r;

        return rr;
    }

    TreeNode *rlRotation(TreeNode *r) {
        TreeNode *rr = r->right;
        TreeNode *rrl = rr->left;

        r->right = rrl->left;
        rr->left = rrl->right;
        rrl->left = r;
        rrl->right = rr;

        return rrl;
    }
};

#endif //TREE_PRACTICE_TREE_H
