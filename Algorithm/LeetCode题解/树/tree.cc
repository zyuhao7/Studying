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

// day-2025-2-11
// 654 最大二叉树
// class Solution
// {
// public:
//     TreeNode *constructMaximumBinaryTree(vector<int> &nums)
//     {
//         return builder(nums, 0, nums.size() - 1);
//     }

//     TreeNode *builder(vector<int> &nums, int l, int r)
//     {
//         if (l > r)
//             return nullptr;
//         int idx = 0, maxn = -1;
//         for (int i = l; i <= r; ++i)
//         {
//             if (nums[i] > maxn)
//             {
//                 maxn = nums[i];
//                 idx = i;
//             }
//         }
//         TreeNode *node = new TreeNode(maxn);
//         node->left = builder(nums, l, idx - 1);
//         node->right = builder(nums, idx + 1, r);
//         return node;
//     }
// };

// 105 从前序与中序遍历序列构造二叉树
// class Solution {
//     public:
//         TreeNode* buildTree(vector<int>& pre, vector<int>& in) {
//             return build(pre, 0, pre.size() - 1, in, 0, in.size() -1);
//         }
//         TreeNode* build(vector<int>& pre, int pl, int pr, vector<int>& in, int il, int ir)
//         {
//             if(pl > pr) return nullptr;
//             int rootVal = pre[pl];
//             int idx = 0;
//             for(int i = il; i <= ir; ++i)
//             {
//                 if(rootVal == in[i])
//                 {
//                     idx = i;
//                     break;
//                 }
//             }
//             TreeNode *root = new TreeNode(rootVal);
//             int leftSize = idx - il;
//             root->left = build(pre, pl + 1, pl + leftSize, in, il, idx - 1);
//             root->right = build(pre, pl + leftSize + 1, pr, in, idx + 1, ir);
//             return root;
//         }
//     };

// 106 从中序与后序遍历序列构造二叉树
// class Solution {
//     public:
//         TreeNode* buildTree(vector<int>& in, vector<int>& post) {
//             return build(in, 0, in.size() - 1, post, 0, post.size() - 1);
//         }
//         TreeNode* build(vector<int>& in, int il, int ir, vector<int>& post, int pl, int pr)
//         {
//             if(il > ir) return nullptr;
//             int rootVal = post[pr];
//             int index = 0;
//             for(int i = il; i <= ir; ++i)
//             {
//                 if(in[i] == rootVal)
//                 {
//                     index = i;
//                     break;
//                 }
//             }
//             int leftSize = index - il;
//             TreeNode* root = new TreeNode(rootVal);
//             root->left = build(in, il, index - 1, post, pl, pl + leftSize - 1);
//             root->right = build(in, index + 1, ir, post, pl + leftSize, pr - 1);
//             return root;
//         }
//     };

// day-2025-2-12

// 652 寻找重复的子树
// class Solution {
//     public:
//         vector<TreeNode*> findDuplicateSubtrees(TreeNode* root) {
//             dfs(root);
//             return res;
//         }
//         vector<TreeNode*> res;
//         unordered_map<string, int> map;
//         string dfs(TreeNode* root)
//         {
//             if(root == nullptr) return "#";
//             string s = to_string(root->val) + "," + dfs(root->left) + "," + dfs(root->right);
//             if(map[s] == 1)
//                 res.push_back(root);
//             ++map[s];
//             return s;
//         }
//     };

// 102 二叉树的层序遍历
// class Solution
// {
// public:
//     vector<vector<int>> levelOrder(TreeNode *root)
//     {
//         vector<vector<int>> res;
//         queue<TreeNode *> q;
//         if (!root)
//             return res;
//         q.push(root);
//         while (!q.empty())
//         {
//             int sz = q.size();
//             vector<int> tmp;
//             for (int i = 0; i < sz; ++i)
//             {
//                 auto t = q.front();
//                 q.pop();
//                 tmp.push_back(t->val);
//                 if (t->left != nullptr)
//                     q.push(t->left);
//                 if (t->right != nullptr)
//                     q.push(t->right);
//             }
//             res.push_back(tmp);
//         }
//         return res;
//     }
// };

// 124 二叉树中的最大路径和
// class Solution
// {
// public:
//     int ans = INT_MIN;
//     int maxPathSum(TreeNode *root)
//     {
//         dfs(root);
//         return ans;
//     }

//     int dfs(TreeNode *root)
//     {
//         if (root == nullptr)
//             return 0;
//         int left = max(0, dfs(root->left));
//         int right = max(0, dfs(root->right));

//         ans = max(ans, left + right + root->val);
//         return root->val + max(left, right);
//     }
// };

// 968 监控二叉树
// class Solution
// {
// public:
//     int res = 0;
//     int minCameraCover(TreeNode *root)
//     {
//         // 0 表示没有被监视
//         // 1 表示 有摄像头
//         // 2 表示被监控到了
//         if (dfs(root) == 0)
//             res++;
//         return res;
//     }
//     int dfs(TreeNode *root)
//     {
//         if (root == nullptr)
//             return 2;
//         // 后序遍历, 先解决子树, 在解决根
//         int left = dfs(root->left);
//         int right = dfs(root->right);

//         // 左右节点有一个没被监视到, 需要在父节点安装摄像头.
//         if (left == 0 || right == 0)
//         {
//             res++;
//             return 1;
//         }
//         // 左右子节点有一个摄像头, 父节点已经被监视到了
//         if (left == 1 || right == 1)
//         {
//             return 2;
//         }
//         // 当前节点没被监视到
//         return 0;
//     }
// };

// day-2025-2-13
// 236 二叉树的最近公共祖先
//  class Solution {
//  public:
//      TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
//          if(root == nullptr || root == p || root == q) return root;
//          TreeNode* left = lowestCommonAncestor(root->left, p, q);
//          TreeNode* right = lowestCommonAncestor(root->right, p, q);
//          if(left == nullptr) return right;
//          if(right == nullptr) return left;
//          return root;
//      }
//  };

// 222 完全二叉树的节点个数
// class Solution {
//     public:
//         int countNodes(TreeNode* root) {
//             return dfs(root);
//         }
//         int dfs(TreeNode* root)
//         {
//             if(root == nullptr) return 0;
//             int leftSum = dfs(root->left);
//             int rightSum = dfs(root->right);
//             return leftSum + rightSum + 1;
//         }
//     };

// 700 二叉搜索树中的搜索
// class Solution
// {
// public:
//     TreeNode *searchBST(TreeNode *root, int val)
//     {
//         if (root == nullptr)
//             return nullptr;
//         if (root->val == val)
//             return root;
//         if (root->val < val)
//             return searchBST(root->right, val);
//         return searchBST(root->left, val);
//     }
// };

// 230 二叉搜索树中第K小的元素
// class Solution {
//     public:
//         int res;
//         int count = 0;
//         int kthSmallest(TreeNode* root, int k) {
//             inorder(root, k);
//             return res;
//         }
//         void inorder(TreeNode* root, int k)
//         {
//             if(root == nullptr) return ;
//             inorder(root->left, k);
//             count++;
//             if(count == k)
//             {
//                 res = root->val;
//                 return ;
//             }
//             inorder(root->right, k);
//             return ;
//         }
//     };

// day-20252-17
// 538 把二叉搜索树转换为累加树
// class Solution
// {
// public:
//     int s = 0;
//     TreeNode *convertBST(TreeNode *root)
//     {
//         if (root == nullptr)
//             return nullptr;
//         convertBST(root->right);
//         s += root->val;
//         root->val = s;
//         convertBST(root->left);
//         return root;
//     }
// };

// 98 验证二叉搜索树
// class Solution
// {
// public:
//     long long pre = LLONG_MIN;
//     bool isValidBST(TreeNode *root)
//     {
//         if (root == nullptr)
//             return true;
//         if (!isValidBST(root->left) || root->val <= pre)
//             return false;
//         pre = root->val;
//         return isValidBST(root->right);
//     }
// };

// 701 二叉搜索树中的插入操作
// class Solution
// {
// public:
//     TreeNode *insertIntoBST(TreeNode *root, int val)
//     {
//         if (root == nullptr)
//             return new TreeNode(val);
//         dfs(root, val);
//         return root;
//     }
//     void dfs(TreeNode *root, int val)
//     {
//         // 先找到要插入的位置.
//         if (root->val > val)
//         {
//             if (root->left == nullptr)
//                 root->left = new TreeNode(val);
//             else
//                 dfs(root->left, val);
//         }
//         else
//         {
//             if (root->right == nullptr)
//                 root->right = new TreeNode(val);
//             else
//                 dfs(root->right, val);
//         }
//     }
// };

// 450 删除二叉搜索树中的节点

// class Solution
// {
// public:
//     TreeNode *deleteNode(TreeNode *root, int key)
//     {
//         // 1. 叶子节点
//         // 2. 只有左孩子的左节点
//         //  . 只有右孩子的右节点
//         // 3. 带有左右孩子的节点
//         // 4. 找不到要删除的节点

//         // 找不到要删除的节点
//         if (root == nullptr)
//             return nullptr;
//         // 找到要删除的节点
//         if (root->val == key)
//         {
//             // 叶子节点
//             if (root->left == nullptr && root->right == nullptr)
//                 return nullptr;
//             // 只有右孩子
//             if (!root->left)
//                 return root->right;
//             // 只有左孩子
//             if (!root->right)
//                 return root->left;
//             // 左右都有
//             TreeNode *maxNode = root->left;
//             while (maxNode->right)
//                 maxNode = maxNode->right;
//             root->val = maxNode->val;
//             root->left = deleteNode(root->left, maxNode->val);
//         }
//         else if (root->val < key)
//             root->right = deleteNode(root->right, key);
//         else
//             root->left = deleteNode(root->left, key);
//         return root;
//     }
// };

// 96 不同的二叉搜索树
// class Solution {
//     public:
//         int numTrees(int n) {
//             vector<int> dp(n + 1);
//             dp[0] = 1;
//             for(int i = 1; i<= n; ++i)
//             {
//                 for(int j = 1; j <= i; ++j)
//                 {
//                     dp[i] += dp[j - 1] * dp[i - j];
//                 }
//             }
//             // 1 2 5 14 42
//             return dp[n];
//         }
//     };

// 95 不同的二叉搜索树 II
// class Solution
// {
// public:
//     vector<TreeNode *> generateTrees(int n)
//     {
//         return generate(1, n);
//     }
//     vector<TreeNode *> generate(int st, int ed)
//     {
//         vector<TreeNode *> res;
//         if (st > ed)
//         {
//             res.push_back(nullptr);
//             return res;
//         }
//         for (int i = st; i <= ed; ++i)
//         {
//             vector<TreeNode *> left = generate(st, i - 1);  // 生成左子树
//             vector<TreeNode *> right = generate(i + 1, ed); // 生成右子树
//             for (auto l : left)
//             {
//                 for (auto r : right)
//                 {
//                     TreeNode *root = new TreeNode(i);
//                     root->left = l;
//                     root->right = r;
//                     res.push_back(root);
//                 }
//             }
//         }
//         return res;
//     }
// };
int main()
{
    return 0;
}