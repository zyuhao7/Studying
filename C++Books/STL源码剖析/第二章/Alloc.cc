#include"Alloc.h"
#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<algorithm>
#include<cstring>
#include<vector>
#include<map>
#include<set>
#include<unordered_map>
#include<unordered_set>
#include<queue>
using namespace std;

// 2024-7-10

// 设计一个简单的空间配置器. 

// 空间的配置与释放的设计哲学:
// 1. 向 system heap 申请空间.
// 2. 考虑多线程状态.
// 3. 考虑内存不足的应对措施, 考虑 "小型区块" 可能造成的内存碎片.

int main()
{
    vector<int> v;
	v.push_back(1);
	v.push_back(1);
	v.push_back(1);
	v.push_back(1);
	for (auto e : v) cout << e << " ";
	cout << endl;
	cout << typeid(vector<int>()).name() << endl;


    return 0;
}