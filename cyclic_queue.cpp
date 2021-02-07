#include <iostream>
#include "my_struct.hpp"

namespace my_struct {
    constexpr size_t BEAUTIFUL_CONSTANT = -1;
    constexpr size_t QBUF_SIZE = 5;

    template <typename T>
    queue<T>::queue(): buffer(new T[QBUF_SIZE]), 
                       front_i(BEAUTIFUL_CONSTANT), 
                       rear_i(BEAUTIFUL_CONSTANT) {};

    template <typename T>
    T &queue<T>::front() const {
        if (front_i == BEAUTIFUL_CONSTANT) 
            return buffer[0];               // expect undefined behavior if
        return buffer[front_i];             // the requested value is undefined
    }

    template <typename T>
    T &queue<T>::back() const {
        if (rear_i == BEAUTIFUL_CONSTANT) 
            return buffer[0];               // expect undefined behavior if
        return buffer[rear_i];              // the requested value is undefined
    }

    template <typename T>
    bool queue<T>::empty() const {
        return front_i == BEAUTIFUL_CONSTANT;
    }

    template <typename T>
    size_t queue<T>::size() const {
        if (rear_i == BEAUTIFUL_CONSTANT && front_i == BEAUTIFUL_CONSTANT)
            return 0;
        else if (rear_i >= front_i)
            return rear_i - front_i + 1;
        return QBUF_SIZE - front_i + rear_i;
    }

    template <typename T>
    bool queue<T>::push(const T &to_push) {
        if ((front_i == 0 && rear_i == QBUF_SIZE - 1) || front_i - 1 == rear_i)
            return true;
        if (rear_i == QBUF_SIZE - 1) 
            rear_i = 0;
        else 
            ++rear_i;
        buffer[rear_i] = to_push;
        if (front_i == BEAUTIFUL_CONSTANT) ++front_i;
        return false;
    }

    template <typename T>
    bool queue<T>::pop() {
        if (empty()) 
            return true;
        if (front_i == rear_i) {
            front_i = BEAUTIFUL_CONSTANT;
            rear_i = BEAUTIFUL_CONSTANT;
        } else if (front_i == QBUF_SIZE - 1) 
            front_i = 0;
        else ++front_i;
        return false;
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

    template<typename T>
    queue<T> &queue<T>::operator=(const queue<T> &other) {
        front_i = other.front_i;
        rear_i = other.rear_i;
        for (size_t i = front_i; i <= rear_i; ++i)
            buffer[i] = other.buffer[i];
        return *this;
    }

    template<typename T>
    queue<T> &queue<T>::operator=(queue &&other) {
        front_i = other.front_i;
        rear_i = other.rear_i;
        std::swap(buffer, other.buffer);
        return *this;
    }

    template<typename T>
    queue<T>::queue(const queue<T> &other): queue() {
        *this = other;
    }

    template<typename T>
    queue<T>::queue(queue &&other): queue() {
        *this = std::move(other);
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
