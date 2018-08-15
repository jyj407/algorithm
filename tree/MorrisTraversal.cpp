// Ref: http://www.cnblogs.com/AnnieKim/archive/2013/06/15/morristraversal.html
#include <vector>
#include <iostream>
using namespace std;

struct TreeNode {
     int val;
     TreeNode *left;
     TreeNode *right;
     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

void morrisInOrder(TreeNode* root) {
    TreeNode* cur = root, *prev = nullptr;
    while (cur) {
        if (!cur->left) {
            cout << cur->val << endl;
            cur = cur->right;
        } else {
            // find predecessor
            prev = cur->left;
            // find the right most node in the left substree,
            // which is the inorder predecessor of the current node
            while (prev->right && prev->right != cur)
                    prev = prev->right; 
            if (!prev->right) {
                prev->right = cur;
                cur = cur->left;
            } else {
                prev->right = nullptr;
                cout << cur->val << endl;
                cur = cur->right;
            }
        }
    }
}

TreeNode* constructTree(vector<int>& preorder, int preStart, int preEnd,
                        vector<int>& inorder, int inStart, int inEnd) {
    if (preStart > preEnd)
        return NULL;
    
    int index = 0;
    // Note must be "<=" rather that "<", since the right subtree could be null, 
    //i.e: (root is the last element in inorder)
    for (int i = inStart; i <= inEnd; i++) {
        if (inorder[i] == preorder[preStart]) {
            index = i;
            break;
        }
    }
    
    TreeNode* root = new TreeNode(preorder[preStart]);
    root->left = constructTree(preorder, preStart + 1,preStart + 1 + (index -1 - inStart),
                               inorder, inStart, index - 1);
    root->right = constructTree(preorder,  preEnd - (inEnd - index - 1), preEnd,
                                inorder, index + 1, inEnd);
    return root;
}


TreeNode* buildTree(vector<int>& preorder, vector<int>& inorder) {
    return constructTree(preorder, 0, preorder.size() - 1, inorder, 0, inorder.size() - 1);
}

int main(void) {
    vector<int> preorder = {2,3,0,5,1};
    vector<int> inorder = {0,3,2,1,5};
    TreeNode* root = buildTree(preorder, inorder);
    morrisInOrder(root);
    return 0;
}    
