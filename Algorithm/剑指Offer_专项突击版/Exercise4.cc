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

// day-2024-10-14
// 剑指 Offer II 046. 二叉树的右侧视图
// class Solution
// {
// public:
//     vector<int> rightSideView(TreeNode *root)
//     {
//         vector<int> res;
//         queue<TreeNode *> q;
//         if (root == nullptr)
//             return res;
//         q.push(root);
//         while (!q.empty())
//         {
//             int n = q.size();
//             int firstR = 0;
//             for (int i = 0; i < n; ++i)
//             {
//                 auto t = q.front();
//                 q.pop();
//                 if (i == 0)
//                     firstR = t->val;
//                 if (t->right)
//                     q.push(t->right);
//                 if (t->left)
//                     q.push(t->left);
//             }
//             res.push_back(firstR);
//         }
//         return res;
//     }
// };

// 剑指 Offer II 047. 二叉树剪枝
// class Solution
// {
// public:
//     TreeNode *pruneTree(TreeNode *root)
//     {
//         if (!root)
//             return nullptr;
//         root->left = pruneTree(root->left);
//         root->right = pruneTree(root->right);
//         if (!root->left && !root->right && root->val == 0)
//             return nullptr;
//         return root;
//     }
// };

// day-2024-10-15
//  剑指 Offer II 048. 序列化与反序列化二叉树

// 层序遍历冗余编码.
// class Codec
// {
// public:
//     string serialize(TreeNode *root)
//     {
//         string res;
//         if (root == nullptr)
//             return res;
//         queue<TreeNode *> q;
//         q.push(root);
//         while (!q.empty())
//         {
//             auto t = q.front();
//             q.pop();
//             if (t)
//             {
//                 q.push(t->left);
//                 q.push(t->right);
//                 res += to_string(t->val) + ",";
//             }
//             else
//             {
//                 res += "null,";
//             }
//         }
//         return res;
//     }
//     TreeNode *deserialize(string data)
//     {
//         stringstream ss(data);
//         queue<TreeNode *> q;
//         string str;
//         vector<string> s;
//         while (getline(ss, str, ','))
//             s.push_back(str);
//         if (s.size() == 0)
//             return nullptr;
//         q.push(new TreeNode(stoi(s[0])));
//         int i = 1;
//         auto root = q.front();
//         while (!q.empty())
//         {
//             auto t = q.front();
//             q.pop();
//             t->left = s[i] == "null" ? nullptr : new TreeNode(stoi(s[i]));
//             i++;
//             if (t->left)
//                 q.push(t->left);

//             t->right = s[i] == "null" ? nullptr : new TreeNode(stoi(s[i]));
//             i++;
//             if (t->right)
//                 q.push(t->right);
//         }
//         return root;
//     }
// };

// class Codec
// {
// public:
//     // Encodes a tree to a single string.
//     string serialize(TreeNode *root)
//     {
//         if (root == nullptr)
//             return "null";
//         return to_string(root->val) + ' ' + serialize(root->left) + ' ' + serialize(root->right);
//     }

//     TreeNode *mydeserialize(istringstream &ss)
//     {
//         string tmp;
//         ss >> tmp;
//         if (tmp == "null")
//             return nullptr;
//         TreeNode *node = new TreeNode(stoi(tmp));
//         node->left = mydeserialize(ss);
//         node->right = mydeserialize(ss);
//         return node;
//     }
//     // Decodes your encoded data to tree.
//     TreeNode *deserialize(string data)
//     {
//         istringstream ss(data);
//         return mydeserialize(ss);
//     }
// };

// 剑指 Offer II 049. 从根节点到叶节点的路径数字之和
// class Solution
// {
// public:
//     int sumNumbers(TreeNode *root)
//     {
//         return dfs(root, 0);
//     }
//     int dfs(TreeNode *root, int val)
//     {
//         if (root == nullptr)
//             return 0;
//         val = val * 10 + root->val;
//         if (root->left == nullptr && root->right == nullptr)
//             return val;
//         return dfs(root->left, val) + dfs(root->right, val);
//     }
// };

// day-2024-10-16
// 剑指 Offer II 050. 向下的路径节点之和  路径总和 III

// 深度优先搜索.
// class Solution
// {
// public:
//     int pathSum(TreeNode *root, int targetSum)
//     {
//         if (root == nullptr)
//             return 0;
//         return dfs(root, targetSum) + pathSum(root->left, targetSum) + pathSum(root->right, targetSum);
//     }
//     int dfs(TreeNode *root, long long targetSum)
//     {
//         if (!root)
//             return 0;
//         return (root->val == targetSum ? 1 : 0) + dfs(root->left, targetSum - root->val) + dfs(root->right, targetSum - root->val);
//     }
// };

// 前缀和 + 哈希 + 递归
// class Solution {
// public:
//     int pathSum(TreeNode* root, int targetSum) {
//         unordered_map<long, int> cnt;
//         cnt[0] = 1;
//         function<int(TreeNode*, long)> dfs = [&](TreeNode* node, long s) -> int {
//             if (!node) return 0;
//             s += node->val;
//             int ans = cnt[s - targetSum];
//             ++cnt[s];
//             ans += dfs(node->left, s) + dfs(node->right, s);
//             --cnt[s];
//             return ans;
//         };
//         return dfs(root, 0);
//     }
// };

// 剑指 Offer II 051. 节点之和最大的路径
// class Solution {
// public:
//     int maxPathSum(TreeNode* root) {
//         int maxSum = INT_MIN;

//         function<int(TreeNode*)> dfs = [&](TreeNode* root){
//             if(!root) return 0;
//             int left = max(0, dfs(root->left));
//             int right = max(0, dfs(root->right));

//            maxSum = max(maxSum, left + right + root->val);
//            return root->val + max(left, right);
//         };

//         dfs(root);
//         return maxSum;
//     }

// };

// 剑指 Offer II 052. 展平二叉搜索树
// class Solution
// {
// public:
//     TreeNode *increasingBST(TreeNode *root)
//     {
//         TreeNode *head = nullptr, *tail = nullptr;
//         stack<TreeNode *> st;
//         TreeNode *cur = root;
//         while (!st.empty() || cur != nullptr)
//         {
//             while (cur != nullptr)
//             {
//                 st.push(cur);
//                 cur = cur->left;
//             }
//             cur = st.top();
//             st.pop();
//             if (head == nullptr)
//                 head = cur;
//             else
//                 tail->right = cur;
//             tail = cur;
//             cur->left = nullptr;
//             cur = cur->right;
//         }
//         return head;
//     }
// };

// day-2024-10-17
// 剑指 Offer II 053. 二叉搜索树中的中序后继

// class Solution
// {
// public:
//     TreeNode *inorderSuccessor(TreeNode *root, TreeNode *p)
//     {
//         TreeNode *ans = nullptr;
//         while (root)
//         {
//             if (root->val > p->val)
//             {
//                 ans = root;
//                 root = root->left;
//             }
//             else
//             {
//                 root = root->right;
//             }
//         }
//         return ans;
//     }
// };

// 剑指 Offer II 054. 所有大于等于节点的值之和
// class Solution
// {
// public:
//     int sum = 0;
//     TreeNode *bstToGst(TreeNode *root)
//     {
//         if (!root)
//             return nullptr;
//         bstToGst(root->right);
//         sum += root->val;
//         root->val = sum;
//         bstToGst(root->left);
//         return root;
//     }
// };

// 剑指 Offer II 055. 二叉搜索树迭代器
// class BSTIterator
// {
// public:
//     vector<int> vec;
//     int cur;
//     BSTIterator(TreeNode *root)
//     {
//         cur = 0;
//         Inorder(root);
//     }

//     int next()
//     {
//         return vec[cur++];
//     }

//     bool hasNext()
//     {
//         return cur < vec.size();
//     }
//     void Inorder(TreeNode *root)
//     {
//         if (!root)
//             return;

//         Inorder(root->left);
//         vec.push_back(root->val);
//         Inorder(root->right);
//     }
// };

