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
    
    bool isSymSub(TreeNode* left, TreeNode* right) {
        if (left!=nullptr and right!=nullptr) {
            if (left->val==right->val) {
                if (isSymSub(left->left, right->right) and 
                    isSymSub(left->right, right->left)) 
                    return true;
                else return false;
            } else return false;
        } else if (left==nullptr and right==nullptr)
            return true;
        else return false;
    }
    
public:
    bool isSymmetric(TreeNode* root) {
        if (root==nullptr) return true;
        return isSymSub(root->left, root->right);
    }
};