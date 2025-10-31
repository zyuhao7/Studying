#include <iostream>
#include <string>
#include <set>
#include <vector>
using namespace std;

// day-2025-10-31
// 3407. 子字符串匹配模式 easy
//  https://leetcode.cn/problems/substring-matching-pattern/description/
/*
    查找模式串p中'*'的位置star, 然后在字符串s中查找p中'*'前缀的位置i
    如果找到了, 则继续在s中从i + star位置开始查找p中'*'后缀的位置
    如果都找到了则返回true, 否则返回false
*/

class Solution
{
public:
    bool hasMatch(string s, string p)
    {
        int star = p.find('*');
        int i = s.find(p.substr(0, star));
        return i != string::npos && s.substr(i + star).find(p.substr(star + 1)) != string::npos;
    }
};
#include <unordered_map>

// 3408. 设计任务管理器 middle
// https://leetcode.cn/problems/design-task-manager/description/
/*
    用一个哈希表和一个有序集合来维护任务信息
    哈希表 map 存储任务id到<用户id, 优先级>的映射
    有序集合 st 存储任务的优先级和任务id的对, 按照优先级从大到小排序, 优先级相同则按照任务id从大到小排序
*/

class TaskManager
{
public:
    unordered_map<int, pair<int, int>> map; // taskid, <useid, Priority>
    set<pair<int, int>> st;

public:
    TaskManager(vector<vector<int>> &tasks)
    {
        for (const auto &task : tasks)
        {
            add(task[0], task[1], task[2]);
        }
    }

    void add(int userId, int taskId, int priority)
    {
        map[taskId] = {userId, priority};
        st.insert({-priority, -taskId});
    }

    void edit(int taskId, int newPriority)
    {
        auto [useId, priority] = map[taskId];
        st.erase({-priority, -taskId});
        st.insert({-newPriority, -taskId});
        map[taskId] = {useId, newPriority};
    }

    void rmv(int taskId)
    {
        auto [useId, priority] = map[taskId];
        st.erase({-priority, -taskId});
        map.erase(taskId);
    }

    int execTop()
    {
        if (st.empty())
            return -1;
        auto e = *st.begin();
        st.erase(st.begin());
        int taskId = -e.second;
        int useId = map[taskId].first;
        map.erase(taskId);
        return useId;
    }
};