#include <iostream>
#include <queue>
#include <string>
#include <map>
using namespace std;

// poj 3278 Catch that cow
const int N = 1e5 + 10;
const int INF = 1e9;
int d[N];
int n, k;

void BFS()
{
    int i, j;
    for (int i = 0; i < N; ++i)
        d[i] = INF;

    queue<int> q;
    q.push(n);
    d[n] = 0;
    if (n == k)
        return;
    while (!q.empty())
    {
        int t = q.front();
        q.pop();
        int ne[3];
        ne[0] = t + 1;
        ne[1] = t - 1;
        ne[2] = t * 2;
        for (int i = 0; i < 3; ++i)
        {
            if (ne[i] >= 0 && ne[i] <= 100000)
            {
                if (d[ne[i]] > d[t] + 1)
                {
                    d[ne[i]] = d[t] + 1;
                    q.push(ne[i]);
                    if (ne[i] == k)
                        return;
                }
            }
        }
    }
}

int main()
{
    cin >> n >> k;
    BFS();
    cout << d[k] << endl;
    return 0;
}

// day-2024-11-9

// struct node
// {
//     node() {}
//     node(string ss, int tt)
//     {
//         s = ss;
//         t = tt;
//     }
//     string s;
//     int t;
// };

// map<string, bool> mp; // 用于记录访问过的状态

// queue<node> q;
// void solve()
// {
//     while (!q.empty())
//     {
//         node now = q.front();
//         q.pop();
//         string s = now.s;
//         int step = now.t;

//         // 如果达到了目标状态，输出步数并退出
//         if (s == "087654321")
//         {
//             cout << step << endl;
//             break;
//         }

//         // 找到 '0' 的位置
//         int i;
//         for (i = 0; i < 9; ++i)
//             if (s[i] == '0')
//                 break;

//         // 对于 i 位置的 '0'，进行跳跃操作
//         for (int j = i - 2; j <= i + 2; ++j) // 4 种跳法
//         {
//             int k = (j + 9) % 9;
//             if (k == i) // 这是当前状态，不用检查
//                 continue;

//             string news = s;
//             char tmp = news[i];
//             news[i] = news[k];
//             news[k] = tmp; // 交换 '0' 和 k 位置的字符

//             // 如果这个状态没有出现过，加入队列继续搜索
//             if (!mp[news])
//             {
//                 mp[news] = true;
//                 q.push(node(news, step + 1));
//             }
//         }
//     }
// }

// int main()
// {
//     string s = "012345678"; // 初始状态
//     q.push(node(s, 0));     // 将初始状态加入队列
//     mp[s] = true;           // 标记初始状态已访问
//     solve();
//     return 0;
// }

// day - 2024 - 11 - 7、8
// 全球变暖
// 由于全球变暖导致海平面上升, 岛屿边缘一个像素的范围会被海水淹没, 如果一块陆地像素与海洋相邻,
/// 他就会被淹没, 问多少岛屿会被淹没.

// 1. BFS 求解连通性问题.
// const int N = 1010;
// char mp[N][N];
// int vis[N][N];
// int d[4][2] = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};
// int flag;
// typedef pair<int, int> pii;
// void bfs(int x, int y)
// {
//     queue<pii> q;
//     vis[x][y] = 1;
//     q.push({x, y});
//     while (!q.empty())
//     {
//         auto t = q.front();
//         q.pop();
//         int tx = t.first, ty = t.second;
//         if (mp[tx][ty + 1] == '#' &&
//             mp[tx][ty - 1] == '#' &&
//             mp[tx - 1][y] == '#' &&
//             mp[tx + 1][y] == '#')
//         {
//             flag = 1;
//         }
//         for (int i = 0; i < 4; ++i)
//         {
//             int dx = tx + d[i][0];
//             int dy = ty + d[i][1];
//             if (vis[dx][dy] == 0 && mp[dx][dy] == '#')
//             {
//                 vis[dx][dy] = 1;
//                 q.push({dx, dy});
//             }
//         }
//     }
// }

// int main()
// {
//     int n;
//     cin >> n;
//     for (int i = 0; i < n; ++i)
//         cin >> mp[i];
//     int ans = 0;
//     for (int i = 1; i <= n; ++i)
//     {
//         for (int j = 1; j <= n; ++j)
//         {
//             if (mp[i][j] == '#' && vis[i][j] == 0)
//             {
//                 flag = 0;
//                 bfs(i, j);
//                 if (flag == 0)
//                     ans++;
//             }
//         }
//     }
//     cout << ans << endl;
//     return 0;
// }

// 2. DFS 求解连通性问题.
// const int N = 1010;
// char mp[N][N];
// int vis[N][N] = {0};
// int d[4][2] = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};
// int flag; // 用于标记这个岛是否被完全淹没

// void dfs(int x, int y)
// {
//     vis[x][y] = 1;
//     if (mp[x][y + 1] == '#' &&
//         mp[x][y - 1] == '#' &&
//         mp[x + 1][y] == '#' &&
//         mp[x - 1][y] == '#')
//     {
//         flag = 1;
//     }

//     for (int i = 0; i < 4; ++i)
//     {
//         int dx = x + d[i][0];
//         int dy = y + d[i][1];
//         if (vis[dx][dy] == 0 && mp[dx][dy] == '#')
//             dfs(dx, dy);
//     }
// }

// int main()
// {
//     int n;
//     cin >> n;
//     for (int i = 0; i < n; i++)
//         cin >> mp[i];

//     int ans = 0;
//     for (int i = 1; i <= n; ++i)
//     {
//         for (int j = 1; j <= n; ++j)
//         {
//             if (mp[i][j] == '#' && vis[i][j] == 0)
//             {
//                 flag = 0;
//                 dfs(i, j);
//                 if (!flag) // 被淹没了, 统计被淹没岛的数量.
//                     ans++;
//             }
//         }
//     }
//     cout << ans << endl;
// }

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

// int deep[N]; // deep[i] 是节点 i 的深度
// int deep_timer = 0;
// void deep_node(int father)
// {
//     if (father != 0)
//     {
//         deep[father] = ++deep_timer;
//         printf("deep[%c] = %d; ", tree[father].val, deep[father]);
//         deep_node(tree[father].lson);
//         deep_node(tree[father].rson);
//         deep_timer--;
//     }
// }

// int num[N]; // num[i] 是以 i 为父亲的子树上的节点总数
// int num_node(int father)
// {
//     if (father == 0)
//         return 0;
//     else
//     {
//         num[father] = num_node(tree[father].lson) + num_node(tree[father].rson) + 1;
//         printf("num[%c] = %d; ", tree[father].val, num[father]);
//         return num[father];
//     }
// }

// void preOrder(int root)
// {
//     if (root == 0)
//         return;
//     cout << tree[root].val << " ";
//     preOrder(tree[root].lson);
//     preOrder(tree[root].rson);
// }

// void inOrder(int root)
// {
//     if (root == 0)
//         return;
//     inOrder(tree[root].lson);
//     cout << tree[root].val << " ";
//     inOrder(tree[root].rson);
// }

// void postOrder(int root)
// {
//     if (root == 0)
//         return;
//     postOrder(tree[root].lson);
//     postOrder(tree[root].rson);
//     cout << tree[root].val << " ";
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

//     cout << "deep order: ";
//     deep_node(root); // 打印节点深度
//     cout << endl;

//     cout << "num of order: ";
//     num_node(root); // 打印子树上的节点数
//     cout << endl;

//     cout << "in order: ";
//     inOrder(root);
//     cout << endl;

//     cout << "pre order: ";
//     preOrder(root);
//     cout << endl;

//     cout << "post order: ";
//     postOrder(root);
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