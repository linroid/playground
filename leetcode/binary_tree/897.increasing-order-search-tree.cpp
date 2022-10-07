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
    TreeNode* increasingBST(TreeNode* root) {
        TreeNode *head = new TreeNode();
        inorder(root, head);
        return head->right;
    }
    
    TreeNode* inorder(TreeNode* node, TreeNode *head) {
        if (node == nullptr) {
            return head;
        }
        head = inorder(node->left, head);
        head->right = node;
        node->left = nullptr;
        return inorder(node->right, node);
    }
    
};
