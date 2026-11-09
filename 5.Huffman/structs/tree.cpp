#include "tree.h"

TreeNode::TreeNode(char s, int w) : symbol(s), weight(w), left(nullptr), right(nullptr) {}

TreeNode::TreeNode(int w, TreeNode* l, TreeNode* r) : symbol('\0'), weight(w), left(l), right(r) {}

void deleteTree(TreeNode* root) {
    if (!root) return;
    deleteTree(root->left);
    deleteTree(root->right);
    delete root;
}
