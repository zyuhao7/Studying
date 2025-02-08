#include <iostream>

using namespace std;

// day-2025-2-8
// 226 翻转二叉树
// class Solution
// {
// public:
//     TreeNode *invertTree(TreeNode *root)
//     {
//         if (root == nullptr)
//             return nullptr;
//         TreeNode *rnode = invertTree(root->right);
//         TreeNode *lnode = invertTree(root->left);
//         root->left = rnode;
//         root->right = lnode;
//         return root;
//     }
// };

// 112 路径总和
// class Solution {
//     public:
//         bool hasPathSum(TreeNode* root, int targetSum) {
//             if(root == nullptr) return false;
//             if(root->val == targetSum && !root->left && !root->right) return true;
//             return hasPathSum(root->left, targetSum - root->val) || hasPathSum(root->right, targetSum - root->val);
//         }
//     };

// 113 路径总和 II
// class Solution
// {
// public:
//     vector<vector<int>> pathSum(TreeNode *root, int targetSum)
//     {
//         dfs(root, targetSum);
//         return res;
//     }
//     vector<vector<int>> res;
//     vector<int> path;
//     void dfs(TreeNode *root, int targetSum)
//     {
//         if (!root)
//             return;
//         targetSum -= root->val;
//         path.push_back(root->val);

//         if (targetSum == 0 && !root->left && !root->right)
//             res.push_back(path);

//         dfs(root->left, targetSum);
//         dfs(root->right, targetSum);
//         path.pop_back();
//     }
// };


int main()
{
    return 0;
}