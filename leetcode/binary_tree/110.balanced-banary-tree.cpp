/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 * };
 */
class Solution {
public:
    bool isBalanced(TreeNode* root) {
        int depth = 0;
        return isBalanced(root, depth);
    }

    bool isBalanced(TreeNode* node, int& depth) {
        if (node == nullptr) {
            return true;
        }
        int leftDepth = 0;
        int rightDepth = 0;
        if (!isBalanced(node->left, leftDepth) || !isBalanced(node->right, rightDepth)) {
            return false;
        }
        depth = max(leftDepth, rightDepth) + 1;
        return abs(leftDepth - rightDepth) <= 1;
    }
};

