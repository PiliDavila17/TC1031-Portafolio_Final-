#ifndef MINHEAP_H
#define MINHEAP_H

#include <vector>
#include <climits>
#include <sstream>
#include <cmath>

bool isPowerOfTwo(int n)
{
    return (std::ceil(std::log2(n)) == std::floor(std::log2(n)));
}

typedef unsigned int uint;

template <class T>
class MinHeap
{
private:
    std::vector<T> hvec;

    uint parent(uint child) const { return (child - 1) / 2; }
    uint left(uint parent) const { return (parent * 2) + 1; }
    uint right(uint parent) const { return (parent * 2) + 2; }

    void swap(uint, uint);

public:
    MinHeap() {}

    uint size() const;
    bool empty() const;

    void heapify(uint);

    T top() const;
    void push(T);
    int pop();

    std::string toString() const;

    std::string byLevel() const;
};

template <class T>
/**
 * @brief Swaps elements at i and j
 * Complexity O(1)
 * @param i
 * @param j
 */
void MinHeap<T>::swap(uint i, uint j)
{
    T temp = hvec[i];
    hvec[i] = hvec[j];
    hvec[j] = temp;
}

template <class T>
/**
 * @brief Size of the heap
 * Complexity O(1)
 * @return uint
 */
uint MinHeap<T>::size() const
{
    return hvec.size();
}

template <class T>
/**
 * @brief Returns True if the heap is empty
 * Complexity O(1)
 * @return true
 * @return false
 */
bool MinHeap<T>::empty() const
{
    return hvec.empty();
}

template <class T>
/**
 * @brief Pushes the i element down the heap into its correct place
 * Complexity O(log N)
 * @param i
 */
void MinHeap<T>::heapify(uint i)
{
    uint le = left(i);
    uint ri = right(i);
    uint min = i;

    if (le < hvec.size() && hvec[le] < hvec[min])
        min = le;

    if (ri < hvec.size() && hvec[ri] < hvec[min])
        min = ri;

    if (i != min)
    {
        swap(i, min);
        heapify(min);
    }
}

template <class T>
/**
 * @brief Returns the top element in the heap
 * Complexity O(1)
 * @return T
 */
T MinHeap<T>::top() const
{
    if (empty())
        return INT_MAX;

    else
        return hvec[0];
}

template <class T>
/**
 * @brief Inserts val into the heap
 * Complexity O(log N)
 * @param val
 */
void MinHeap<T>::push(T val)
{
    hvec.push_back(val);
    uint pos = hvec.size() - 1;
    while (pos > 0 && val < hvec[parent(pos)])
    {
        swap(pos, parent(pos));
        pos = parent(pos);
    }
}

template <class T>
/**
 * @brief Removes the top element
 * Complexity O(log N)
 */
int MinHeap<T>::pop()
{
    if (empty())
        return INT_MAX;

    int aux = hvec[0];
    hvec[0] = hvec[hvec.size() - 1];
    hvec.pop_back();
    heapify(0);
    return aux;
}

template <class T>
/**
 * @brief Transforms heap to string
 * Complexity O(N)
 * @return std::string
 */
std::string MinHeap<T>::toString() const
{
    std::stringstream aux;
    for (auto element : hvec)
    {
        aux << element << " ";
    }
    return aux.str();
}

template <class T>
std::string MinHeap<T>::byLevel() const
{
    std::stringstream aux;
    int count = 0;
    for (int i = 0; i < hvec.size(); i++)
    {
        aux << hvec[i] << " ";
        if (isPowerOfTwo(i - count) && i != 1 && i != count)
        {
            count += i;
            aux << std::endl;
        }
    }
    return aux.str();
}

#endif