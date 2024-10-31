#include <iostream>
#include <algorithm> // For std::copy
#include <stdexcept> // For std::out_of_range
#include <cstddef>   // for ptrdiff_t
#include <iterator>  // for std::bidirectional_iterator_tag
#include <vector>
#include <chrono>
#include <cstdlib>
using namespace std;
using namespace chrono;
// day-2024-10-31

// linearList class as provided
template <class T>
class linearList
{
public:
    virtual ~linearList() {};
    virtual bool empty() const = 0;
    virtual int size() const = 0;
    virtual T &get(int idx) const = 0;
    virtual int indexOf(const T &theElement) const = 0;
    virtual void erase(int idx) = 0;
    virtual void insert(int idx, const T &e) = 0;
    virtual void output(ostream &os) const = 0;
};

// arrayList class
template <class T>
class arrayList : public linearList<T>
{
public:
    arrayList(int initCap = 10);
    arrayList(const arrayList<T> &);
    ~arrayList() { delete[] element; }

    // ADT functions
    bool empty() const { return listSize == 0; }
    int size() const { return listSize; }
    T &get(int idx) const;
    int indexOf(const T &e) const;
    void erase(int idx);
    void insert(int idx, const T &e);
    void output(ostream &os) const;

protected:
    void checkIndex(int idx) const;
    T *element;
    int arrayLength;
    int listSize;
};

// Constructor
template <class T>
arrayList<T>::arrayList(int initCap)
{
    if (initCap < 1)
        throw invalid_argument("Initial capacity must be > 0");
    arrayLength = initCap;
    element = new T[arrayLength];
    listSize = 0;
}

// Copy Constructor
template <class T>
arrayList<T>::arrayList(const arrayList<T> &other)
{
    arrayLength = other.arrayLength;
    listSize = other.listSize;
    element = new T[arrayLength];
    copy(other.element, other.element + listSize, element);
}

// Get element at index
template <class T>
T &arrayList<T>::get(int idx) const
{
    checkIndex(idx);
    return element[idx];
}

// Find index of element
template <class T>
int arrayList<T>::indexOf(const T &e) const
{
    for (int i = 0; i < listSize; ++i)
    {
        if (element[i] == e)
            return i;
    }
    return -1; // Not found
}

// Erase element at index
template <class T>
void arrayList<T>::erase(int idx)
{
    checkIndex(idx);
    // Shift elements to the left
    for (int i = idx; i < listSize - 1; ++i)
        element[i] = element[i + 1];
    // copy(element + idx + 1, element + listSize, element + idx);
    listSize--;
}

// Insert element at index
template <class T>
void arrayList<T>::insert(int idx, const T &e)
{
    if (idx < 0 || idx > listSize)
        throw out_of_range("Index out of range");

    // Resize if needed
    if (listSize == arrayLength)
    {
        arrayLength *= 2;
        T *newArray = new T[arrayLength];
        copy(element, element + listSize, newArray);
        delete[] element;
        element = newArray;
    }

    // Shift elements to the right
    for (int i = listSize; i > idx; --i)
        element[i] = element[i - 1];

    element[idx] = e;
    listSize++;
}

// Output elements
template <class T>
void arrayList<T>::output(ostream &os) const
{
    for (int i = 0; i < listSize; ++i)
        os << element[i] << " ";
    // copy(element, element + listSize, ostream_iterator<T>(cout, " "));
}

// Check index validity
template <class T>
void arrayList<T>::checkIndex(int idx) const
{
    if (idx < 0 || idx >= listSize)
        throw out_of_range("Index out of range");
}

// Overload << operator for outputting arrayList
template <class T>
ostream &operator<<(ostream &os, const arrayList<T> &list)
{
    list.output(os);
    return os;
}

// int main()
// {
//     // Test case 1: Creating an empty list and checking if it's empty
//     arrayList<int> list;
//     cout << "Initial list (should be empty): " << list << endl;
//     cout << "List empty? " << (list.empty() ? "Yes" : "No") << endl;

//     // Test case 2: Inserting elements
//     list.insert(0, 10); // Insert 10 at index 0
//     list.insert(1, 20); // Insert 20 at index 1
//     list.insert(2, 30); // Insert 30 at index 2
//     list.insert(1, 15); // Insert 15 at index 1 (should shift 20 and 30 to the right)
//     cout << "List after insertions (expected: 10 15 20 30): " << list << endl;

//     // Test case 3: Accessing elements
//     cout << "Element at index 0 (expected: 10): " << list.get(0) << endl;
//     cout << "Element at index 1 (expected: 15): " << list.get(1) << endl;
//     cout << "Element at index 2 (expected: 20): " << list.get(2) << endl;

//     // Test case 4: Checking the index of an element
//     cout << "Index of element 20 (expected: 2): " << list.indexOf(20) << endl;
//     cout << "Index of element 40 (expected: -1, not found): " << list.indexOf(40) << endl;

//     // Test case 5: Erasing elements
//     list.erase(1); // Erase element at index 1 (15)
//     cout << "List after erasing index 1 (expected: 10 20 30): " << list << endl;

//     // Test case 6: Checking the size of the list
//     cout << "List size (expected: 3): " << list.size() << endl;

//     // Test case 7: Testing dynamic resizing
//     for (int i = 0; i < 10; ++i)
//     {
//         list.insert(list.size(), i * 10);
//     }
//     cout << "List after inserting more elements to test resizing: " << list << endl;
//     cout << "List size (expected: 13): " << list.size() << endl;

//     // Test case 8: Copy constructor
//     arrayList<int> listCopy(list);
//     cout << "Copy of the list (should be identical to original): " << listCopy << endl;

//     // Test case 9: Assignment operator
//     arrayList<int> listAssign;
//     listAssign = list;
//     cout << "Assigned list (should be identical to original): " << listAssign << endl;

//     // Test case 10: Edge cases
//     try
//     {
//         list.get(-1); // Invalid index
//     }
//     catch (const out_of_range &e)
//     {
//         cout << "Error caught for get(-1): " << e.what() << endl;
//     }

//     try
//     {
//         list.erase(list.size()); // Out-of-bounds index for erase
//     }
//     catch (const out_of_range &e)
//     {
//         cout << "Error caught for erase(list.size()): " << e.what() << endl;
//     }

//     return 0;
// }

template <class T>
class iterator
{
public:
    typedef std::bidirectional_iterator_tag iterator_category;
    typedef T value_type;
    typedef std::ptrdiff_t difference_type;
    typedef T *pointer;
    typedef T &reference;

    // Constructor
    iterator(T *thePos = nullptr) : position(thePos) {}

    T &operator*() const { return *position; }
    T *operator->() const { return &(*position); }

    iterator &operator++() // Prefix increment
    {
        ++position;
        return *this;
    }

    iterator operator++(int) // Postfix increment
    {
        iterator old = *this;
        ++position;
        return old;
    }

    iterator &operator--() // Prefix decrement
    {
        --position;
        return *this;
    }

    iterator operator--(int) // Postfix decrement
    {
        iterator old = *this;
        --position;
        return old;
    }

    bool operator!=(const iterator &right) const
    {
        return position != right.position;
    }

    bool operator==(const iterator &right) const
    {
        return position == right.position;
    }

protected:
    T *position;
};

// 插入性能测试
template <class ListType>
void testInsertion(ListType &list, int numElements)
{
    auto start = high_resolution_clock::now();

    for (int i = 0; i < numElements; ++i)
    {
        list.insert(list.size(), i); // 在末尾插入元素
    }

    auto end = high_resolution_clock::now();
    cout << "Insertion time: " << duration_cast<milliseconds>(end - start).count() << " ms\n";
}

void testInsertion1(vector<int> &list, int numElements)
{
    auto start = high_resolution_clock::now();

    for (int i = 0; i < numElements; ++i)
    {
        list.push_back(i); // 在末尾插入元素
    }

    auto end = high_resolution_clock::now();
    cout << "Insertion time: " << duration_cast<milliseconds>(end - start).count() << " ms\n";
}

// 随机访问性能测试（通用版本）
template <class ListType>
void testRandomAccess(const ListType &list, int numAccesses)
{
    int listSize = list.size();
    auto start = high_resolution_clock::now();

    for (int i = 0; i < numAccesses; ++i)
    {
        volatile auto value = list.get(rand() % listSize); // 使用 get 访问
    }

    auto end = high_resolution_clock::now();
    cout << "Random access time: " << duration_cast<milliseconds>(end - start).count() << " ms\n";
}

// 针对 std::vector 的随机访问特化
template <class T>
void testRandomAccess(const vector<T> &list, int numAccesses)
{
    int listSize = list.size();
    auto start = high_resolution_clock::now();

    for (int i = 0; i < numAccesses; ++i)
    {
        volatile auto value = list[rand() % listSize]; // 使用 operator[] 访问
    }
    auto end = high_resolution_clock::now();
    cout << "Random access time (std::vector): " << duration_cast<milliseconds>(end - start).count() << " ms\n";
}

int main()
{
    const int numElements = 10000000; // 测试的插入元素数量
    const int numAccesses = 10000000; // 测试的随机访问次数

    // 测试 arrayList 插入性能
    arrayList<int> arrayListTest;
    cout << "Testing arrayList insertion...\n";
    testInsertion(arrayListTest, numElements);

    // 测试 std::vector 插入性能
    vector<int> vectorTest;
    cout << "\nTesting std::vector insertion...\n";
    testInsertion1(vectorTest, numElements);

    // 测试 arrayList 随机访问性能
    cout << "\nTesting arrayList random access...\n";
    testRandomAccess(arrayListTest, numAccesses);

    // 测试 std::vector 随机访问性能
    cout << "\nTesting std::vector random access...\n";
    testRandomAccess(vectorTest, numAccesses);

    return 0;
}