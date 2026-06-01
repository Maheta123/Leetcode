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
    int preorder=0;
    int kthSmallest(TreeNode* root, int k) {
            if(root == NULL){
                    return -1;
            }


            if(root->left){
                int le = kthSmallest(root->left,k);
                if(le != -1){
                        return le;
                }
            }

            if(preorder+1 == k){
                    return root->val;
            }
            preorder++;


            if(root->right){
                int re = kthSmallest(root->right,k);
                if(re != -1){
                        return re;
                }
            }

            return -1;
    }
};