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
    vector<int> rightSideView(TreeNode* root) {
        if (root == nullptr) return {};
        queue<TreeNode *> queue;
        queue.push(root);
        
        vector<int> result;
        while(!queue.empty()) {
            result.push_back(queue.back()->val);
            int count = queue.size();
            for (int i = 0; i < count; ++i) {
                auto front = queue.front();
                if (front->left != nullptr) {
                    queue.push(front->left);
                }
                if (front->right != nullptr) {
                    queue.push(front->right);
                }
                queue.pop();
            }
        }
        return result;
    }
};
