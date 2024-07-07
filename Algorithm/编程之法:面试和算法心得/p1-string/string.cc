#include<iostream>
#include<string>
using namespace std;
/*
     本章重点介绍 6 个典型的字符串问题分别为:
     1. 字符串的旋转.
     2. 字符串的包含.
     3. 字符串的全排列.
     4. 字符串转换成整数. (atoi)
     5. 回文串判断
     6. 最长回文串
*/
#if 1
// 1.1  字符串的旋转
/*  题目描述:
 * 给定一个字符串, 要求将前面字符串的若干个字符移到字符串的尾部. 例如, 将字符串 "abcdf" 的前三个字符 'a', 'b', 'c' 移动到
 * 字符串的尾部, 那么原字符串将变成 "defabc".
*/
// 做过此类题, 根据记忆写的一个巧妙方法 .。. 不行了, 今天 2024-7-7-23:01, 休息休息,不对, 我还得去看八股，等会 沙特杯 T1 打 Tes
//决赛, 明天开班!! 加油~ 今天算是正式开始暑假逆袭计划!!! 给我冲! 加油!!!一定行!! 本书题解明天补了~

void Reverse(string& s, int begin, int end)
{
    for(int i=begin, j = end; i < j ;++i, --j)
    {
        char t = s[i];
        s[i] = s[j];
        s[j] = t;
    }
}

string f(string& s, int n)
{
    int size = s.size();
    Reverse(s, 0, size - n - 1);
    Reverse(s,n, size - 1);
    Reverse(s, 0, size - 1);

    return s;
}

int main()
{
    int n;
    string s;
    
    cin>>s>>n;

    f(s,n);

    cout<<s<<endl;
    return 0;
}

#endif