#include <iostream>
#include <queue>
using namespace std;
// day-2024-11-7
// const int N = 100010;
// struct Node
// {
//     char val;
//     int lson;
//     int rson;
// } tree[N];

// int idx = 1;
// int newNode(char c)
// {
//     tree[idx].val = c;
//     tree[idx].lson = 0;
//     tree[idx].rson = 0;
//     return idx++;
// }

// void Insert(int &father, int child, int l_r)
// {
//     if (l_r == 0)
//         tree[father].lson = child; // 插入左孩子
//     else
//         tree[father].rson = child; // 插入右孩子
// }
// int dfn[N] = {0}; // dfn[i] 是 节点 i 的时间戳, 也就是 节点 i 是第几个进入的/
// int dfn_timer = 0;
// void dfn_order(int father) // 前序遍历
// {
//     if (father != 0)
//     {
//         dfn[father] = ++dfn_timer;
//         printf("dfn[%c] = %d; ", tree[father].val, dfn[father]);
//         dfn_order(tree[father].lson);
//         dfn_order(tree[father].rson);
//     }
// }

// int visit_timer = 0;
// void visit_order(int father)
// {
//     if (father != 0)
//     {
//         printf("visit[%c] = %d; ", tree[father].val, ++visit_timer); // 打印 DFS 序: 第一次访问节点
//         visit_order(tree[father].lson);
//         visit_order(tree[father].rson);
//         printf("visit[%c] = %d; ", tree[father].val, ++visit_timer); // 打印 DFS 序: 第二次回溯
//     }
// }

// int buildtree() // 建树
// {
//     int A = newNode('A');
//     int B = newNode('B');
//     int C = newNode('C');
//     int D = newNode('D');
//     int E = newNode('E');
//     int F = newNode('F');
//     int G = newNode('G');
//     int H = newNode('H');
//     int I = newNode('I');
//     Insert(E, B, 0);
//     Insert(E, G, 1);
//     Insert(B, A, 0);
//     Insert(B, D, 1);
//     Insert(G, F, 0);
//     Insert(G, I, 1);
//     Insert(D, C, 0);
//     Insert(I, H, 0);

//     int root = E;
//     return root;
// }
// int main()
// {
//     int root = buildtree();
//     cout << "dfn order: ";
//     dfn_order(root); // 打印时间戳.
//     cout << endl;

//     cout << "visit order: ";
//     visit_order(root); // 打印 DFS 序
//     cout << endl;

//     return 0;
// }

// 指针版 二叉树 BFS
// struct node
// {
//     char val;
//     node *l, *r;
//     node(char c = '#', node *L = nullptr, node *R = nullptr)
//         : val(c), l(L), r(R)
//     {
//     }
// };

// void remove_tree(node *root)
// {
//     if (root == nullptr)
//         return;
//     remove_tree(root->l);
//     remove_tree(root->r);
//     delete root;
// }

// int main()
// {
//     node *A, *B, *C, *D, *E, *F, *G, *H, *I;
//     A = new node('A');
//     B = new node('B');
//     C = new node('C');
//     D = new node('D');
//     E = new node('E');
//     F = new node('F');
//     G = new node('G');
//     H = new node('H');
//     I = new node('I');

//     E->l = B;
//     E->r = G;
//     B->l = A;
//     B->r = D;
//     G->l = F;
//     G->r = I;
//     D->l = C;
//     I->l = H;
//     queue<node> q;
//     q.push(*E);
//     while (!q.empty())
//     {
//         auto t = &q.front();
//         q.pop();
//         cout << t->val << " "; // E B G A D F I C H
//         if (t->l)
//             q.push(*(t->l));
//         if (t->r)
//             q.push(*(t->r));
//     }
//     remove_tree(E);
// }

// day-2024-11-4

// 静态版 二叉树 BFS
// const int N = 1e5 + 10;
// struct Node
// {
//     char val;
//     int lson, rson;
// } tree[N]; // tree[0] 不用, 表示空节点

// int index = 1;

// int newNode(char Value)
// {
//     tree[index].val = Value;
//     tree[index].lson = 0;
//     tree[index].rson = 0;
//     return index++;
// }

// void Insert(int &father, int child, int l_r)
// {
//     if (l_r == 0)
//         tree[father].lson = child;
//     else
//         tree[father].rson = child;
// }

// int buildtree()
// {
//     int A = newNode('A');
//     int B = newNode('B');
//     int C = newNode('C');
//     int D = newNode('D');
//     int E = newNode('E');
//     int F = newNode('F');
//     int G = newNode('G');
//     int H = newNode('H');
//     int I = newNode('I');
//     Insert(E, B, 0);
//     Insert(E, G, 1);
//     Insert(B, A, 0);
//     Insert(B, D, 1);
//     Insert(G, F, 0);
//     Insert(G, I, 1);
//     Insert(D, C, 0);
//     Insert(I, H, 0);

//     int root = E;
//     return root;
// }

// int main()
// {
//     int root = buildtree();
//     queue<int> q;
//     q.push(root);
//     while (!q.empty())
//     {
//         int t = q.front();
//         q.pop();
//         cout << tree[t].val << " "; // E B G A D F I C H
//         if (tree[t].lson != 0)
//             q.push(tree[t].lson);
//         if (tree[t].rson != 0)
//             q.push(tree[t].rson);
//     }

//     return 0;
// }