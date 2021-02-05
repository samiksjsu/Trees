//
// Created by samik on 2/5/2021.
//

#ifndef TREE_PRACTICE_TREENODE_H
#define TREE_PRACTICE_TREENODE_H

class TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;

    explicit TreeNode(int val) : val {val}, left {nullptr}, right {nullptr} {};
};

#endif //TREE_PRACTICE_TREENODE_H
