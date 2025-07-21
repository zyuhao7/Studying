#include <iostream>
#include <memory>
typedef unsigned long PORT_ULONG;
typedef struct listNode
{
    struct listNode *prev;
    struct listNode *next;
    void *value;
} listNode;

typedef struct list
{
    listNode *head;
    listNode *tail;
    void *(*dup)(void *ptr);
    void (*free)(void *ptr);
    int (*match)(void *ptr, void *key);
    PORT_ULONG len;
} list;

list *listCreate(void)
{
    struct list *list;

    if ((list = (struct list *)malloc(sizeof(*list))) == nullptr)
        return nullptr;
    list->head = list->tail = nullptr;
    list->len = 0;
    list->dup = nullptr;
    list->free = nullptr;
    list->match = nullptr;
    return list;
}

void listRelease(list *list)
{
    PORT_ULONG len;
    listNode *current, *next;
    current = list->head;
    len = list->len;
    while (len--)
    {
        next = current->next;
        if (list->free)
            list->free(current->value);
        free(current);
        current = next;
    }
    free(list);
}

void printList(list *list)
{
    if (list == nullptr)
        return;
    listNode *node = list->head;
    while (node != nullptr)
    {
        std::cout << *(int *)node->value << " ";
        node = node->next;
    }
}

list *listAddNodeHead(list *list, void *value)
{
    if (list == nullptr)
        return nullptr;
    // 1.创建新节点
    listNode *node = (listNode *)malloc(sizeof(listNode));
    node->value = value;
    if (node == nullptr)
    {
        std::cout << "create node failed" << std::endl;
        return nullptr;
    }
    // 2.处理空链表情况
    if (list->len == 0)
    {
        list->head = node;
        list->tail = node;
        node->prev = nullptr;
        node->next = nullptr;
    }
    else
    {
        // 3.非空链表情况
        node->next = list->head;
        list->head->prev = node;
        node->prev = nullptr;
        list->head = node;
    }
    list->len++;
    return list;
}
// 尾插
list *listAddNodeTail(list *list, void *value)
{
    if (list == nullptr)
        return nullptr;
    // 1.创建新节点
    listNode *node = (listNode *)malloc(sizeof(listNode));
    node->value = value;
    if (node == nullptr)
    {
        std::cout << "create node failed" << std::endl;
        return nullptr;
    }
    // 2.处理空链表情况
    if (list->len == 0)
    {
        list->head = node;
        list->tail = node;
        node->prev = nullptr;
        node->next = nullptr;
    }
    else
    {
        // 3.非空链表情况
        list->tail->next = node;
        node->prev = list->tail;
        node->next = nullptr;
        list->tail = node;
    }
    list->len++;
    return list;
}

list *listInsertNode(list *list, listNode *old_node, void *value, int after)
{
    listNode *node = (listNode *)malloc(sizeof(listNode));
    if (node == nullptr)
        return nullptr;
    node->value = value;
    // 插入位是在 old_node的后面
    if (after)
    {
        node->next = old_node->next;
        node->prev = old_node;
        if (list->tail == old_node)
        {
            list->tail = node;
        }
    }
    else
    {
        node->next = old_node;
        node->prev = old_node->prev;
        if (list->head == old_node)
        {
            list->head = node;
        }
    }
    if (node->prev)
        node->prev->next = node;
    if (node->next)
        node->next->prev = node;
    list->len++;
    return list;
}
void listDelNode(list *list, listNode *node)
{
    if (node->prev)
        node->prev->next = node->next;
    else
        list->head = node->next;
    if (node->next)
        node->next->prev = node->prev;
    else
        list->tail = node->prev;
    if (list->free)
        list->free(node->value);
    free(node);
    list->len--;
}

int listLength(list *list)
{
    return list->len;
}

void listRotate(list *list)
{
    listNode *tail = list->tail;

    if (listLength(list) <= 1)
        return;

    /* Detach current tail */
    list->tail = tail->prev;
    list->tail->next = NULL;
    /* Move it as head */
    list->head->prev = tail;
    tail->prev = NULL;
    tail->next = list->head;
    list->head = tail;
}

// int main()
// {
//     list *list = listCreate();
//     if (list == nullptr)
//     {
//         std::cout << "list create failed" << std::endl;
//         return 1;
//     }
//     std::cout << "list create success" << std::endl;
//     list->free = [](void *ptr)
//     { delete (int *)ptr; };

//     int *val1 = new int(1);
//     int *val2 = new int(2);
//     int *val3 = new int(3);
//     int *val4 = new int(4);
//     int *val5 = new int(5);
//     int *val6 = new int(6);

//     listAddNodeHead(list, val1);
//     listAddNodeHead(list, val2);
//     listAddNodeTail(list, val3);
//     listAddNodeTail(list, val4);
//     listAddNodeTail(list, val5);
//     listInsertNode(list, list->head, val6, 1);
//     listDelNode(list, list->head);
//     listDelNode(list, list->tail);
//     listRotate(list);

//     printList(list);

//     listRelease(list);

//     return 0;
// }