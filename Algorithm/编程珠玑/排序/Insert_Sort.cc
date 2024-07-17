#include <iostream>
using namespace std;

// 插入排序
/**
 *  for i = [1,n]
 *     for (j = i; j > 0 && x[j - 1] > x[j];--j)
 *          swap(x[j - 1], x[j])
 *
 *   swap 函数耗费时间, 因此决定将函数展开, 并将 t 变量定义到 第一个 for, 节省空间
 *  for i = [1,n]
 *     int t = x[i];
 *     for (j = i; j > 0 && x[j - 1] > t;--j)
 *          x[j] = x[j - 1];
 *     x[j] = t;
 */

// 一种简单的快速排序
/**
 *  void qsort1(l, u)
 *      if(l >= u)
 *          return
 *      m = l
 *      for i = [l+1, u]
 *          // invariant: x[l + 1 ... m] < x[l] &&
 *                        x[m+1 ... i - 1] >= x[l]
 *           if(x[i] < x[l])
 *              swap(++m, i);
 *
 *          swap(l,m);
 *          x[l ... m - 1] < x[m] <= x[m + 1 ... u]
 *          qsort1(l, m - 1)
 *          qsort1(m + 1, u)
 */

// 更好的几种快速排序
/**
 *                  ------------------------------------------
 *                  | t |  <= t   |   ?         |   >= t     |
 *                  ------------------------------------------
 *                   ↑         ↑               ↑          ↑
 *                   l           i                j           u
 *
 *      void qsort3(l, u)
 *           if(l >= u)
 *              return
 *          t = x[l]; i = l; j = u + 1;
 *          loop
 *              do i++ while i <= u && x[i] < t
 *              do j-- while x[j] > t
 *              if i > j
 *                  break
 *              swap(i, j)
 *          swap(l, j)
 *          qsort3(l, j - 1)
 *          qsort3(j + 1, u)
 *
 *      void qsort4(l, u)
 *           if(u - 1 < cutoff)
 *              return
 *           swap(l, randint(l,u))
 *          t = x[l]; i = l; j = u + 1;
 *          loop
 *              do i++ while i <= u && x[i] < t
 *              do j-- while x[j] > t
 *              if i > j
 *                  break
 *              temp = x[i]; x[i] = x[j]; x[j] = temp;
 *          swap(l, j)
 *          qsort4(l, j - 1)
 *          qsort4(j + 1, u)

 */

int main()
{

    return 0;
}