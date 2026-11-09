#ifndef TREE_H
#define TREE_H

struct TreeNode {
    char symbol;
    int weight;
    TreeNode* left;
    TreeNode* right;

    TreeNode(char s, int w);
    TreeNode(int w, TreeNode* l, TreeNode* r);
};

void deleteTree(TreeNode* root);

#endif