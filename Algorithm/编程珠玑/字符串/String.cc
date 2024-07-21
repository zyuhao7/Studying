#include <iostream>
#include <string>
#include <map>
#include <set>
using namespace std;
#define NHASH 29989 // 最接近 29131 的质数. 《圣经》中有 29131 个不同的单词.
#define MULT 31
nodeptr bin[NHASH];
// 字符串.
// 散列表 :
typedef struct node *nodeptr;
typedef struct node
{
    char *word;
    int count;
    nodeptr next;
} node;

unsigned int hash(char *p)
{
    unsigned int h = 0;
    for (; *p; p++)
    {
        h = MULT * h + *p;
    }
    return h % NHASH;
}

// 增加与输入单词相关联的计数器的值.
void incword(char *s)
{
    unsigned int h = hash(s);
    for (nodeptr p = bin[h]; p != NULL; p = p->next)
    {
        if (strcmp(s, p->word) == 0)
        {
            p->count++;
            return;
        }
    }
    p = malloc(sizeof(struct node));
    p->count = 1;
    p->word = malloc(strlen(s) + 1);
    strcpy(p->word, s);
    p->next = bin[h];
    bin[h] = p;
}

int main()
{
    for (int i = 0; i < NHASH;; i++)
    {
        bin[i] = NULL;
    }
    char *buf;
    while (scanf("%s", buf) != EOF)
        incword(buf);

    for (int i = 0; i < NHASH;; i++)
    {
        for (nodeptr p = bin[i]; p != NULL; p = p->next)
        {
            cout << p->word << " " << p->count << endl;
        }
    }

    // map<string, int> M;
    // map<string, int>::iterator j;
    // string t;

    // while (cin >> t)
    // {
    //     M[t]++;
    //     for (j = M.begin(); j != M.end(); ++j)
    //         cout << j->first << " " << j->second << endl;
    // }
    return 0;
}
