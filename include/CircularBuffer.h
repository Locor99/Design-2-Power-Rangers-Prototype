#ifndef CIRCULARBUFFER_H
#define CIRCULARBUFFER_H

#include <stdlib.h>
#include "CircularBuffer.h"

template<typename T, size_t maxNumberOfElements>
class CircularBuffer {
public:
    CircularBuffer()=default;

    void push(T item) {
        buffer[tail] = item;
        tail = (tail + 1) % maxNumberOfElements;
        if (isFull()) {
            head = (head + 1) % maxNumberOfElements;
        } else {
            ++count;
        }
    }

    T get(size_t index) const {
        return buffer[(head + index) % maxNumberOfElements];
    }

    size_t size() const {
        return count;
    }

    bool isFull() const {
        return count == maxNumberOfElements;
    }

    T getMinValue() const {
        T minVal = buffer[head];
        for (size_t i = 0; i < count; ++i) {
            T val = get(i);
            if (val < minVal) {
                minVal = val;
            }
        }
        return minVal;
    }

    T getMaxValue() const {
        T maxVal = buffer[head];
        for (size_t i = 0; i < count; ++i) {
            T val = get(i);
            if (val > maxVal) {
                maxVal = val;
            }
        }
        return maxVal;
    }

private:
    T buffer[maxNumberOfElements];
    size_t head=0;
    size_t tail=0;
    size_t count=0;
};

#endif // CIRCULARBUFFER_H
