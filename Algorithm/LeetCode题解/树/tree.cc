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

// day-2025-2-10
//  114 二叉树展开为链表
//  class Solution
//  {
//  public:
//      void flatten(TreeNode *root)
//      {
//          if (root == nullptr)
//              return;
//          flatten(root->left);
//          flatten(root->right);
//          TreeNode *left = root->left;
//          TreeNode *right = root->right;
//          root->left = nullptr;
//          root->right = left;

//         TreeNode *p = root;
//         while (p->right != nullptr)
//         {
//             p = p->right;
//         }
//         p->right = right;
//     }
// };

// class Solution {
//     public:
//         void flatten(TreeNode* root) {
//             if(root == nullptr) return;
//             stack<TreeNode*> st;
//             st.push(root);
//             TreeNode* prev = nullptr;
//             TreeNode* cur = nullptr;
//             while(!st.empty())
//             {
//                 cur = st.top(); st.pop();
//                 if(prev != nullptr)
//                 {
//                     prev->right = cur;
//                     prev->left = nullptr;
//                 }
//                 if(cur->right)
//                     st.push(cur->right);
//                 if(cur->left)
//                     st.push(cur->left);
//                 prev = cur;
//             }
//         }
//     };

// 116 填充每个节点的下一个右侧节点指针
// class Solution
// {
// public:
//     Node *connect(Node *root)
//     {
//         if (root == nullptr)
//             return nullptr;
//         connectTwoNode(root->left, root->right);
//         return root;
//     }

//     void connectTwoNode(Node *node1, Node *node2)
//     {
//         if (node1 == nullptr || node2 == nullptr)
//             return;
//         node1->next = node2;
//         connectTwoNode(node1->left, node1->right);
//         connectTwoNode(node2->left, node2->right);
//         connectTwoNode(node1->right, node2->left);
//     }
// };

// class Solution
// {
// public:
//     Node *connect(Node *root)
//     {
//         if (root == nullptr)
//             return nullptr;
//         queue<Node *> q;
//         q.push(root);
//         while (!q.empty())
//         {
//             int sz = q.size();
//             for (int i = 0; i < sz; ++i)
//             {
//                 Node *it = q.front();
//                 q.pop();
//                 if (i < sz - 1)
//                     it->next = q.front();
//                 if (it->left)
//                     q.push(it->left);
//                 if (it->right)
//                     q.push(it->right);
//             }
//         }
//         return root;
//     }
// };

// 117 填充每个节点的下一个右侧节点指针 II
// 递归
// class Solution
// {
// public:
//     Node *connect(Node *root)
//     {
//         if (root == nullptr)
//             return nullptr;
//         Node *cur = root;
//         while (cur != nullptr)
//         {
//             Node *dummy = new Node(0);
//             Node *pre = dummy;
//             Node *head = cur;
//             while (cur != nullptr)
//             {
//                 if (cur->left != nullptr)
//                 {
//                     pre->next = cur->left;
//                     pre = pre->next;
//                 }
//                 if (cur->right != nullptr)
//                 {
//                     pre->next = cur->right;
//                     pre = pre->next;
//                 }
//                 cur = cur->next;
//             }
//             cur = dummy->next;
//           }
//         return root;
//     }
// };

int main()
{
    return 0;
}