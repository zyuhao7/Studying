#include <iostream>
#include <set>
#include <algorithm>
using namespace std;

// 搜索
class IntSetSTL
{
private:
    set<int> S;

public:
    IntSetSTL(int maxelms, int maxval) {}
    int size() { return S.size(); }
    void insert(int t) { S.insert(t); }
    void report(int *v)
    {
        int j = 0;
        set<int>::iterator i;
        for (i = S.begin(); i != S.end(); ++i)
        {
            v[j++] = *i;
        }
    }
};

class IntSetArray
{
private:
    int n, *x;

public:
    IntSetArray(int maxelms, int maxval)
    {
        x = new int[1 + maxelms];
        n = 0;
        x[0] = maxval;
    }
    int size() { return n; }
    void insert(int t)
    {
        for (int i = 0; x[i] < t; ++i)
        {
            if (x[i] == t)
                return;
            for (int j = n; j >= i; j--)
            {
                x[j + 1] = x[j];
            }
            x[i] = t;
            n++;
        }
    }
    void report(int *v)
    {
        for (int i = 0; i < n; ++i)
        {
            v[i] = x[i];
        }
    }
};

class IntSetList
{
private:
    int n;
    struct node
    {
        int val;
        node *next;
        node(int v, node *p)
        {
            val = v;
            next = p;
        }
    };
    node *head, *sentinel;
    node *rinsert(node *p, int t)
    {
        if (p->val < t)
        {
            p->next = rinsert(p->next, t);
        }
        else if (p->val > t)
        {
            p = new node(t, p);
            n++;
        }
        return p;
    }

public:
    IntSetList(int maxelms, int maxval)
    {
        sentinel = head = new node(maxval, 0);
        n = 0;
    }
    int size() { return n; }
    void insert(int t) { head = rinsert(head, t); }
    void report(int *v)
    {
        int j = 0;
        for (node *p = head; p != sentinel; p = p->next)
        {
            v[j++] = p->val;
        }
    }
};

class IntSetBST
{
private:
    int n, *v, vn;
    struct node
    {
        int val;
        node *left, *right;
        node(int v)
        {
            val = v;
            left = right = 0;
        }
    };
    node *root;
    node *rinsert(node *p, int t)
    {
        if (p == 0)
        {
            p = new node(t);
            n++;
        }
        else if (t < p->val)
        {
            p->left = rinsert(p->left, t);
        }
        else if (t > p->val)
        {
            p->right = rinsert(p->right, t);
        }
        return p;
    }
    void traverse(node *p)
    {
        if (p == 0)
            return;
        traverse(p->left);
        v[vn++] = p->val;
        traverse(p->right);
    }

public:
    IntSetBST(int maxelms, int maxval)
    {
        root = 0;
        n = 0;
    }
    int size() { return n; }
    void insert(int t) { root = rinsert(root, t) };
    void report(int *x)
    {
        v = x;
        vn = 0;
        traverse(root);
    }
};


int main()
{
    return 0;
}