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
    TreeNode* reverseOddLevels(TreeNode* root) {
        if (root == nullptr) {
            return nullptr;
        }
        
        vector<TreeNode *> even_layer;
        vector<TreeNode *> odd_layer;
        
        even_layer.push_back(root);
        
        while (true) {
            // refill odd layer
            if (even_layer[0]->left == nullptr) {
                break;
            }
            odd_layer.clear();
            for (int i = 0; i < even_layer.size(); ++i) {
                odd_layer.push_back(even_layer[i]->left);
                odd_layer.push_back(even_layer[i]->right);
            }

            // reverse the children for even layer
            int odd_end_index = odd_layer.size() - 1;
            for (int i = 0; i < even_layer.size(); ++i) {
                even_layer[i]->left = odd_layer[odd_end_index - i * 2];
                even_layer[i]->right = odd_layer[odd_end_index - i * 2 - 1];
            }

            // refill the next even layer
            if (odd_layer[0]->left == nullptr) {
                break;
            }
            even_layer.clear();
            for (int i = 0; i < odd_layer.size(); ++i) {
                even_layer.push_back(odd_layer[i]->left);
                even_layer.push_back(odd_layer[i]->right);
            }
            
            // relink children for reversed odd layer
            for (int i = 0; i < odd_layer.size(); ++i) {
                odd_layer[odd_end_index - i] -> left = even_layer[i * 2];
                odd_layer[odd_end_index - i] -> right = even_layer[i * 2 + 1];
            }
        }
        return root;
    }
};

