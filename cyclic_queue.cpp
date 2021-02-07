#ifndef CYCLIC_QUEUE_CPP
#define CYCLIC_QUEUE_CPP

#include <iostream>
#include "my_struct.hpp"

namespace my_struct {
    enum consts {
        OPERATION_DONE = 0,
        OPERATION_UNDONE = 1
    };

    template <typename T>
    T &queue<T>::front() const {
        return buffer[front_i];
    }

    template <typename T>
    T &queue<T>::back() const {
        return buffer[rear_i];
    }

    template <typename T>
    bool queue<T>::empty() const {
        return front_i == -1;
    }

    template <typename T>
    size_t queue<T>::size() const {
        if (rear_i == -1 && front_i == -1)
            return 0;
        else if (rear_i >= front_i)
            return rear_i - front_i + 1;
        return QBUF_SIZE - front_i + rear_i;
    }

    template <typename T>
    bool queue<T>::push(const T &to_push) {
        if ((front_i == 0 && rear_i == QBUF_SIZE - 1) || front_i - 1 == rear_i)
            return OPERATION_UNDONE;
        if (rear_i == QBUF_SIZE - 1) 
            rear_i = 0;
        else 
            ++rear_i;
        buffer[rear_i] = to_push;
        if (front_i == -1) ++front_i;
        return OPERATION_DONE;
    }

    template <typename T>
    bool queue<T>::pop() {
        if (empty()) 
            return OPERATION_UNDONE;
        if (front_i == rear_i) {
            front_i = -1;
            rear_i = -1;
        } else if (front_i == QBUF_SIZE - 1) 
            front_i = 0;
        else ++front_i;
        return OPERATION_DONE;
    }

    template<typename T>
    size_t queue<T>::get_front_i() const {
        return front_i;
    }

    template<typename T>
    size_t queue<T>::get_rear_i() const {
        return rear_i;
    }

    template<typename T>
    T *queue<T>::get_buffer() const {
        return buffer;
    }

    template <typename T>
    queue<T>::~queue() {
        delete [] buffer;
    }

    template<typename T>
    std::ostream& operator<<(std::ostream &out, const queue<T> &this_queue) {
        out << "----------------\nThis is queue dump.\nQueue buffer: ";
        T *buffer = this_queue.get_buffer();
        for (size_t i = 0; i < QBUF_SIZE; ++i) {
            out << buffer[i] << ", ";
        }
        out << "\b\b.\nQueue front_i = " << this_queue.get_front_i();
        out << "\nQueue rear_i = " << this_queue.get_rear_i();
        out << "\nQueue front = " << this_queue.front();
        out << "\nQueue back = " << this_queue.back();
        out << "\nIs queue empty = " << this_queue.empty();
        out << "\nQueue size = " << this_queue.size();
        out << "\n----------------";
        return out;
    }
}

#endif