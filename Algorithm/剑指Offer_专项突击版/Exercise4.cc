#include <iostream>
#include <string>
#include <vector>
using namespace std;
// day-2024-10-13
// 剑指 Offer II 043. 往完全二叉树添加节点

// class CBTInserter
// {
// public:
//     CBTInserter(TreeNode *root)
//     {
//         this->root = root;
//         queue<TreeNode *> q;
//         q.push(root);
//         while (!q.empty())
//         {
//             TreeNode *node = q.front();
//             q.pop();
//             if (node->left)
//                 q.push(node->left);
//             if (node->right)
//                 q.push(node->right);

//             if (!node->left || !node->right)
//                 candidate.push(node);
//         }
//     }

//     int insert(int val)
//     {
//         TreeNode *node = new TreeNode(val);
//         TreeNode *t = candidate.front();
//         int ret = t->val;
//         if (!t->left)
//             t->left = node;
//         else
//         {
//             t->right = node;
//             candidate.pop();
//         }
//         candidate.push(node);
//         return ret;
//     }

//     TreeNode *get_root()
//     {
//         return root;
//     }

// private:
//     TreeNode *root;
//     queue<TreeNode *> candidate;
// };

// 剑指 Offer II 044. 二叉树每层的最大值
// class Solution
// {
// public:
//     vector<int> largestValues(TreeNode *root)
//     {
//         vector<int> res;
//         queue<TreeNode *> q;
//         if (!root)
//             return res;
//         q.push(root);
//         while (!q.empty())
//         {
//             int Maxn = INT_MIN;
//             int n = q.size();
//             for (int i = 0; i < n; ++i)
//             {
//                 TreeNode *t = q.front();
//                 q.pop();
//                 if (t->val > Maxn)
//                     Maxn = t->val;
//                 if (t->left)
//                     q.push(t->left);
//                 if (t->right)
//                     q.push(t->right);
//             }
//             res.push_back(Maxn);
//         }
//         return res;
//     }
// };

// 剑指 Offer II 045. 二叉树最底层最左边的值
// 深度搜索

// 广度搜索
// class Solution
// {
// public:
//     int findBottomLeftValue(TreeNode *root)
//     {
//         queue<TreeNode *> q;
//         q.push(root);
//         TreeNode *node;
//         while (!q.empty())
//         {
//             node = q.front();
//             q.pop();
//             if (node->right)
//                 q.push(node->right);
//             if (node->left)
//                 q.push(node->left);
//         }
//         return node->val;
//     }
// };
int main()
{

    return 0;
}