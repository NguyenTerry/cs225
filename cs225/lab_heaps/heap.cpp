#include <cmath>
#include <math.h>
/**
 * @file heap.cpp
 * Implementation of a heap class.
 */

template <class T, class Compare>
size_t heap<T, Compare>::root() const
{
    // @TODO Update to return the index you are choosing to be your root.
    return 1;
}

template <class T, class Compare>
size_t heap<T, Compare>::leftChild(size_t currentIdx) const
{
    // @TODO Update to return the index of the left child.
    int height = ceil( std::log2(currentIdx+1)-1 );
    int j = pow(2,height) - (pow(2,height+1)-1 - currentIdx);
    return (size_t)((pow(2,height+1)-1 + 2*j - 1));
}

template <class T, class Compare>
size_t heap<T, Compare>::rightChild(size_t currentIdx) const
{
    // @TODO Update to return the index of the right child.
    return (size_t)leftChild(currentIdx)+1;
}

template <class T, class Compare>
size_t heap<T, Compare>::parent(size_t currentIdx) const
{
    // @TODO Update to return the index of the parent.
    if (currentIdx == 1) {
        return 0;
    }
    int height = ceil( std::log2(currentIdx+1)-1 );
    int k = pow(2,height+1)-1 - currentIdx;
    return (size_t)(pow(2,height)-1 - floor(k/2.0));
}

template <class T, class Compare>
bool heap<T, Compare>::hasAChild(size_t currentIdx) const
{
    // @TODO Update to return whether the given node has a child
    if ( rightChild(currentIdx) > _elems.size() ) {
        if ( leftChild(currentIdx) > _elems.size() ) {
            return false;
        }
    } 
    return true;
}

template <class T, class Compare>
size_t heap<T, Compare>::maxPriorityChild(size_t currentIdx) const
{
    // @TODO Update to return the index of the child with highest priority
    ///   as defined by higherPriority()
    size_t left = leftChild(currentIdx);
    size_t right = rightChild(currentIdx);
    if (higherPriority( _elems[left], _elems[right] )) {
        return left;
    } else {
        return right;
    }
}

template <class T, class Compare>
void heap<T, Compare>::heapifyDown(size_t currentIdx)
{
    // @TODO Implement the heapifyDown algorithm.
    if (hasAChild(currentIdx)) {
        size_t right = rightChild(currentIdx);
        size_t left = leftChild(currentIdx);

        if (right <= _elems.size()) {
            if (right == maxPriorityChild(currentIdx)) {
                if (higherPriority( _elems[right], _elems[currentIdx] )) {
                    T temp = _elems[currentIdx];
                    _elems[currentIdx] = _elems[right];
                    _elems[right] = temp;
                    heapifyDown(right);
                }
            } else {
                if (higherPriority( _elems[left], _elems[currentIdx] )) {
                    T temp = _elems[currentIdx];
                    _elems[currentIdx] = _elems[left];
                    _elems[left] = temp;
                    heapifyDown(left);
                }
            }
        } else {
            if (higherPriority( _elems[left], _elems[currentIdx] )) {
                T temp = _elems[currentIdx];
                _elems[currentIdx] = _elems[left];
                _elems[left] = temp;
                heapifyDown(left);
            }
        }
    }
}

template <class T, class Compare>
void heap<T, Compare>::heapifyUp(size_t currentIdx)
{
    if (currentIdx == root())
        return;
    size_t parentIdx = parent(currentIdx);
    if (higherPriority(_elems[currentIdx], _elems[parentIdx])) {
        std::swap(_elems[currentIdx], _elems[parentIdx]);
        heapifyUp(parentIdx);
    }
}

template <class T, class Compare>
heap<T, Compare>::heap()
{
    // @TODO Depending on your implementation, this function may or may
    ///   not need modifying
    _elems.push_back(T());
}

template <class T, class Compare>
heap<T, Compare>::heap(const std::vector<T>& elems) 
{
    // @TODO Construct a heap using the buildHeap algorithm
    _elems.push_back(T());
    for(unsigned i = 0; i < elems.size(); i++) {
        push(elems[i]);
    }
}

template <class T, class Compare>
T heap<T, Compare>::pop()
{
    // @TODO Remove, and return, the element with highest priority
    T top = _elems[1];
    size_t bottom = _elems.size()-1;
    _elems[1] = _elems[bottom];
    _elems.pop_back();
    heapifyDown(1);
    return top;
}

template <class T, class Compare>
T heap<T, Compare>::peek() const
{
    // @TODO Return, but do not remove, the element with highest priority
    return _elems[1];
}

template <class T, class Compare>
void heap<T, Compare>::push(const T& elem)
{
    // @TODO Add elem to the heap
    _elems.push_back(elem);
    heapifyUp(_elems.size()-1);
}

template <class T, class Compare>
void heap<T, Compare>::updateElem(const size_t & idx, const T& elem)
{
    // @TODO In-place updates the value stored in the heap array at idx
    // Corrects the heap to remain as a valid heap even after update
    _elems[idx] = elem;
    if (idx == 1) {
        heapifyDown(1);
    } else {
        size_t parentIdx = parent(idx);
        if (higherPriority(_elems[idx], _elems[parentIdx])) {
            heapifyUp(idx);
        } else {
            heapifyDown(idx);
        }
    }
}

template <class T, class Compare>
bool heap<T, Compare>::empty() const
{
    // @TODO Determine if the heap is empty
    return (_elems.size()==1);
}

template <class T, class Compare>
void heap<T, Compare>::getElems(std::vector<T> & heaped) const
{
    for (size_t i = root(); i < _elems.size(); i++) {
        heaped.push_back(_elems[i]);
    }
}
