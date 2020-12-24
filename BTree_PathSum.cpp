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
    bool hasPathSum(TreeNode* root, int sum) {
        if (root==nullptr) {
            return false;
        } else if (root->left==nullptr and root->right==nullptr) {
            if (root->val==sum) return true;
            else return false;
        } else {
            bool rst = false;
            if (root->left != nullptr)
                rst = rst or hasPathSum(root->left, sum-root->val);
            if (root->right != nullptr)
                rst = rst or hasPathSum(root->right, sum-root->val);
            return rst;
        }
    }
};