#include <iostream>
using namespace std;

// day-2025-3-10
// §3.1 基础
// 1441. 用栈操作构建数组
// class Solution {
//     public:
//         vector<string> buildArray(vector<int>& target, int n) {
//             stack<int> st;
//             vector<string> res;
//             st.push(target[0]);
//             int x = 1;
//             for(int i =1; i <= target.size(); ++i)
//             {
//                 while(st.top() != x)
//                 {
//                     x++;
//                     res.push_back("Push");
//                     res.push_back("Pop");
//                 }
//                 res.push_back("Push");
//                 x++;
//                 if(i < target.size())
//                   st.push(target[i]);
//             }
//             return res;
//         }
//     };

// 844. 比较含退格的字符串
// class Solution
// {
// public:
//     bool backspaceCompare(string s, string t)
//     {
//         stack<char> st1, st2;
//         for (auto c : s)
//         {
//             if (c == '#' && !st1.empty())
//             {
//                 st1.pop();
//             }
//             else if (c == '#' && st1.empty())
//                 continue;
//             else
//                 st1.push(c);
//         }
//         for (auto c : t)
//         {
//             if (c == '#' && !st2.empty())
//             {
//                 st2.pop();
//             }
//             else if (c == '#' && st2.empty())
//                 continue;
//             else
//                 st2.push(c);
//         }
//         while (!st1.empty() && !st2.empty())
//         {
//             auto t1 = st1.top(), t2 = st2.top();
//             st1.pop();
//             st2.pop();
//             if (t1 != t2)
//                 return false;
//         }
//         if (!st1.empty() || !st2.empty())
//             return false;
//         return true;
//     }
// };

// 682. 棒球比赛
// class Solution
// {
// public:
//     int calPoints(vector<string> &ops)
//     {
//         stack<string> st;
//         st.push(ops[0]);
//         int n = ops.size();
//         for (int i = 1; i < n; ++i)
//         {
//             if (ops[i] == "+")
//             {
//                 int n1 = stoi(st.top());
//                 st.pop();
//                 int n2 = stoi(st.top());
//                 st.pop();
//                 st.push(to_string(n2));
//                 st.push(to_string(n1));
//                 st.push(to_string(n1 + n2));
//             }
//             else if (ops[i] == "D")
//             {
//                 int n1 = stoi(st.top());
//                 st.push(to_string(n1 * 2));
//             }
//             else if (ops[i] == "C")
//             {
//                 st.pop();
//             }
//             else
//                 st.push(ops[i]);
//         }

//         int ans = 0;
//         while (!st.empty())
//         {
//             ans += stoi(st.top());
//             st.pop();
//         }
//         return ans;
//     }
// };

// day-2025-3-11
// 2390. 从字符串中移除星号
// class Solution
// {
// public:
//     string removeStars(string s)
//     {
//         string ans;
//         for (int i = 0; i < s.size(); ++i)
//         {
//             if (s[i] != '*')
//                 ans += s[i];
//             else
//                 ans.pop_back();
//         }
//         return ans;
//     }
// };

// 1472. 设计浏览器历史记录
class BrowserHistory
{
public:
    stack<string> b, f;
    BrowserHistory(string homepage)
    {
        b.push(homepage);
    }

    void visit(string url)
    {
        while (!f.empty())
            f.pop();
        b.push(url);
    }

    string back(int steps)
    {
        while (b.size() > 1 && steps > 0)
        {
            f.push(b.top());
            b.pop();
            steps--;
        }
        return b.top();
    }

    string forward(int steps)
    {
        while (!f.empty() && steps > 0)
        {
            b.push(f.top());
            f.pop();
            steps--;
        }
        return b.top();
    }
};

int main()
{
    return 0;
}