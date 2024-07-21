#include <iostream>
#include <string>
using namespace std;

// 树中常见的函数定义:
/**
 *  root = 1
 *  value(i) =  x[i]
 *  leftchild(i) = 2 * i
 *  rightchild(i) = 2 * i + 1
 *  parent(i) = i / 2
 *  null(i) = (i < 1) or (i > n)
 *
 *
 *
 *  void siftUp(n)
 *          pre n > 0 && heap(1, n - 1)
 *          post heap(1, n)
 *      i = n
 *      loop
 *      if(i == 1) break
 *      p = i / 2
 *      if(x[i] >= x[p]) break
 *      swap(p,i)
 *      i = p
 *
 * void siftDown(n)
 *          pre heap(2, n) && n > 0
 *          post heap(1, n)
 *      i = 1
 *      loop
 *          c = 2 * i
 *          if c > n break  // c is the left child of i.
 *
 *          if(c + 1 <= n)
 *              if(x[c+1] < x[c]) c++
 *          if(x[i] <= x[c]) break
 *          swap(c,i);
 *          i = c
 *
 */

// 优先级队列
/**
 *      template<class T>
 *      class PriorityQueue{
 *      private:
 *          int n, maxsize;
 *          T* x;
 *          void swap(int i, int j)
 *          {
 *              T t = x[i]; x[i] = x[j]; x[j] = t;
 *          }
 *      public:
 *          PriorityQueue(int m)
 *          {
 *              maxsize = m;
 *              x = new T[maxsize + 1]
 *              n = 0
 *          }
 *
 *          void insert(T t)
 *          {
 *              int i, p;
 *              x[++n] = t;
 *              for(int i = n; i > 1 && x[p = i / 2] > x[i]; i = p)
 *                  swap(p, i);
 *          }
 *
 *          T extractmin()
 *          {
 *              int i, c;
 *              T t = x[1];
 *              swap(1, n);
 *              --n;
 *              for(i = 1; (c = 2 * i) <= n; i = c)
 *              {
 *                  if(c + 1 <= n && x[c + 1] < x[c])
 *                      c++;
 *                  if(x[i]<= x[c]) break;
 *                  swap(c, i);
 *              }
 *              return t;
 *          }
 *      };
 *
 *      void insert(t)
 *          if n >= maxsize
 *              // report error
 *          n++
 *          x[n] = t
 *          // heap(1, n - 1)
 *          siftUp(n)
 *          // heap(1, n)
 *
 *      int extractmin()
 *          if n < 1
 *              // report error
 *          t = x[1]
 *          x[1] = x[n --]
 *          // heap(2, n)
 *          siftDown(n)
 *          // heap(1, n)
 *          return t
 */

// 堆排序
/**
 *  for i = [2, n]
 *      siftUp(i)
 *  for(i = n; i >= 2; i --)
 *      swap(1, i)
 *      siftDown(i - 1)
 */

int main()
{

    return 0;
}