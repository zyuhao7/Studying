#include <bits/stdc++.h>
using namespace std;

// day-2026-01-08

// 3270. 求出数字答案 easy
// https://leetcode.cn/problems/find-the-key-of-the-numbers/description/
/*
    将 num1, num2, num3 转换为四位字符串, 不足四位前面补零
    对应位置取三者中的最小值, 拼接成新的字符串
    将拼接后的字符串转换为整数并返回
*/
class Solution
{
public:
    int generateKey(int num1, int num2, int num3)
    {
        string str1 = to_string(num1);
        string str2 = to_string(num2);
        string str3 = to_string(num3);

        while (str1.size() < 4)
            str1.insert(0, 1, '0');
        while (str2.size() < 4)
            str2.insert(0, 1, '0');
        while (str3.size() < 4)
            str3.insert(0, 1, '0');
        string key;
        for (int i = 0; i < 4; ++i)
        {
            int minNum = str1[i] - '0';
            if (str2[i] - '0' < minNum)
                minNum = str2[i] - '0';
            if (str3[i] - '0' < minNum)
                minNum = str3[i] - '0';
            key.push_back(minNum + '0');
        }
        return stoi(key);
    }
};

// 3271. 哈希分割字符串 mid
// https://leetcode.cn/problems/hash-divided-string/description/
/*
    按照 k 个字符一组进行分割
    计算每组字符的哈希值, 哈希值为每个字符对应的字母序号之和对 26 取模
    将哈希值转换为对应的字符, 拼接成结果字符串
*/
class Solution
{
public:
    string stringHash(string s, int k)
    {
        int n = s.size();
        string result;
        int i = 0;
        while (i <= n - k)
        {
            int j = i;
            int sum = 0;
            while (j < i + k)
            {
                sum += s[j] - 'a';
                j++;
            }
            sum %= 26;
            result.push_back(sum + 'a');
            i = j;
        }
        return result;
    }
};

// 3273. 对 Bob 造成的最少伤害 hard
// https://leetcode.cn/problems/minimum-amount-of-damage-dealt-to-bob/description/
/*
    定义一个节点类, 包含敌人的伤害值和击败敌人所需的时间
    重载小于运算符, 使得节点可以按照 "伤害值/时间" 的比值进行排序
    将所有敌人节点存入数组并排序
    按照排序后的顺序依次击败敌人, 计算总伤害值
*/
class Solution
{
public:
    class Node
    {
    public:
        int demage;
        int time;
        Node() : demage(0), time(0) {}
        Node(int d, int t) : demage(d), time(t) {}
        bool operator<(const Node &other) const
        {
            return other.demage * time < demage * other.time;
        }
    };
    long long minDamage(int power, vector<int> &demage, vector<int> &health)
    {
        int size = demage.size();
        // 两个伤害d1 d2 持续时间 t1 t2
        // 如果先消灭1, 总伤害是 d1 * t1 + d2(t1 + t2)
        // 如果先消灭2, 总伤害是 d2 * t2 + d1(t1 + t2)
        // 比较这两种情况, 要使伤害尽可能小, 则需要 d1 * t1 + d2(t1 + t2) < d2 * t2 + d1( + t2)
        // 化简得到:   d2 * t1 <   d1 * t2
        long long totalDemage = 0, time = 0;
        vector<Node> nodes(size);
        for (int i = 0; i < size; ++i)
            nodes[i] = Node(demage[i], (health[i] - 1) / power + 1);
        sort(nodes.begin(), nodes.end());

        for (Node &node : nodes)
        {
            time += node.time;
            totalDemage += node.demage * time;
        }
        return totalDemage;
    }
};