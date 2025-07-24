#include <iostream>
#include <vector>
#include <bitset>
#include <cmath>
#include <string>
#include <functional>
#include <algorithm>

// 桶数量（必须为2的幂）
constexpr int NUM_BUCKETS = 16; // 越大越精确，但内存越大
constexpr double ALPHA = 0.673; // 常数，随 NUM_BUCKETS 改变

class SimpleHyperLogLog
{
private:
    std::vector<uint8_t> registers; // 每个桶记录的最大前导零数+1

    // Hash 函数：将字符串映射为 64 位整型
    uint64_t hash(const std::string &value) const
    {
        std::hash<std::string> hasher;
        return hasher(value);
    }

    // 计算一个数的前导零数量（从第1位开始）
    int countLeadingZeros(uint64_t x, int maxBits) const
    {
        int count = 1;
        while (((x >> (maxBits - count)) & 1) == 0 && count <= maxBits)
            count++;
        return count;
    }

public:
    SimpleHyperLogLog()
        : registers(NUM_BUCKETS, 0) {}

    // 添加元素
    void add(const std::string &value)
    {
        uint64_t hashValue = hash(value);

        // 高位决定桶索引（前 log2(NUM_BUCKETS) 位）
        int bucketBits = std::log2(NUM_BUCKETS);
        int index = hashValue >> (64 - bucketBits); // 桶编号

        // 剩下的位用于统计前导零
        uint64_t remaining = hashValue << bucketBits; // 去掉高位后用于统计
        int rank = countLeadingZeros(remaining, 64 - bucketBits);

        // 更新对应桶的最大前导零数
        registers[index] = std::max(registers[index], static_cast<uint8_t>(rank));
    }

    // 估计基数（使用 HyperLogLog 原始公式）
    double estimate() const
    {
        double harmonicMean = 0.0;
        for (int i = 0; i < NUM_BUCKETS; ++i)
        {
            harmonicMean += 1.0 / (1 << registers[i]);
        }

        double rawEstimate = ALPHA * NUM_BUCKETS * NUM_BUCKETS / harmonicMean;

        // 简化版不考虑小基数偏差校正
        return rawEstimate;
    }
};

// int main()
// {
//     SimpleHyperLogLog hll;

//     // 模拟添加元素（有重复）
//     for (int i = 0; i < 1000; ++i)
//     {
//         hll.add("user_" + std::to_string(i % 300)); // 实际只有300个不同用户
//     }

//     std::cout << "估计去重后元素数: " << hll.estimate() << std::endl;

//     return 0;
// }
