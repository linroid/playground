/**
Last login: Sun Oct  9 22:28:54 on console
➜  ~ cd Projects/playground/
➜  playground git:(2023.free) ✗ ls
Algorithmic Toolbox Arduino             Java                README.md           cpp                 iOS                 nand2tetris
Android             Graphics            LICENSE             cmake               csapp               leetcode
➜  playground git:(2023.free) ✗ cd leetcode
➜  leetcode git:(2023.free) ✗ ls
binary_tree string
➜  leetcode git:(2023.free) ✗ cd binary_tree
➜  binary_tree git:(2023.free) ✗ ls
101.symmetric-tree.cpp                     2415.reverse-odd-levers-of-binary-tree.cpp 897.increasing-order-search-tree.cpp
199.binary-tree-right-side-view.cpp        266.invert-binary-tree.cpp
➜  binary_tree git:(2023.free) ✗ vim 94.binary-tree-inorder-traversal.cpp
➜  binary_tree git:(2023.free) ✗ g add 94.binary-tree-inorder-traversal.cpp
➜  binary_tree git:(2023.free) ✗ g commit -m "[LeetCode]94. Binary Tree Inorder Traversal"
[2023.free dcfb2b7] [LeetCode]94. Binary Tree Inorder Traversal
 1 file changed, 28 insertions(+)
 create mode 100644 leetcode/binary_tree/94.binary-tree-inorder-traversal.cpp
➜  binary_tree git:(2023.free) ✗ g push
Enumerating objects: 8, done.
Counting objects: 100% (8/8), done.
Delta compression using up to 32 threads
Compressing objects: 100% (5/5), done.
Writing objects: 100% (5/5), 1.38 KiB | 1.38 MiB/s, done.
Total 5 (delta 2), reused 0 (delta 0), pack-reused 0
remote: Resolving deltas: 100% (2/2), completed with 2 local objects.
*
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
    vector<int> inorderTraversal(TreeNode* root) {
        vector<int> result;
        inorder(root, result);
        return result;
    }

    void inorder(TreeNode* node, vector<int> &result) {
        if (node == nullptr) {
            return;
        }
        inorder(node->left, result);
        result.push_back(node->val);
        inorder(node->right, result);
    }
};
~
~
~
~
~
~
~
~
~
~
~
"94.binary-tree-inorder-traversal.cpp" 28L, 764B
