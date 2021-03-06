#include <iostream>
#include "my_struct.hpp"

namespace my_struct {
    constexpr size_t BEAUTIFUL_CONSTANT = -1;

    template <typename T>
    queue<T>::queue(size_t max_cnt): buffer(new T[max_cnt]), 
                                     front_i(BEAUTIFUL_CONSTANT), 
                                     rear_i(BEAUTIFUL_CONSTANT), 
                                     buf_size(max_cnt),
                                     min_buf_size(max_cnt) {};

    template <typename T>
    T &queue<T>::front() const {
        if (front_i == BEAUTIFUL_CONSTANT) 
            return buffer[0];
        return buffer[front_i];
    }

    template <typename T>
    T &queue<T>::back() const {
        if (rear_i == BEAUTIFUL_CONSTANT) 
            return buffer[0];
        return buffer[rear_i];
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
        return buf_size - front_i + rear_i;
    }

    template <typename T>
    bool queue<T>::push(const T &to_push) {
        if ((front_i == 0 && rear_i == buf_size - 1) || front_i - 1 == rear_i){
            if (buf_enlarge()) 
                return true;
        }
        if (rear_i == buf_size - 1) 
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
        } else if (front_i == buf_size - 1) 
            front_i = 0;
        else ++front_i;
        buf_diminish();
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
    size_t queue<T>::get_buf_size() const {
        return buf_size;
    }

    template<typename T>
    size_t queue<T>::get_min_buf_size() const {
        return min_buf_size;
    }

    template<typename T>
    T *queue<T>::get_buffer() const {
        return buffer;
    }

    template<typename T>
    queue<T> &queue<T>::operator=(const queue<T> &other) {
        front_i = other.front_i;
        rear_i = other.rear_i;
        buf_size = other.buf_size;
        min_buf_size = other.min_buf_size;
        size_t i = 0;
        size_t other_i = other.front_i;
        if (other.front_i > other.rear_i) {
            for (; other_i < other.buf_size; ++other_i, ++i)
                buffer[i] = other.buffer[other_i];
            for (other_i = 0; other_i <= other.rear_i; ++other_i, ++i)
                buffer[i] = other.buffer[other_i];
        } else {
            for (; i <= other.rear_i; ++other_i, ++i)
                buffer[i] = other.buffer[other_i];
        }
        return *this;
    }

    template<typename T>
    queue<T> &queue<T>::operator=(queue &&other) {
        front_i = other.front_i;
        rear_i = other.rear_i;
        buf_size = other.buf_size;
        min_buf_size = other.min_buf_size;
        std::swap(buffer, other.buffer);
        return *this;
    }

    template<typename T>
    queue<T>::queue(const queue<T> &other): queue(other.buf_size) {
        *this = other;
    }

    template<typename T>
    queue<T>::queue(queue &&other): queue(other.buf_size) {
        *this = std::move(other);
    }

    template <typename T>
    queue<T>::~queue() {
        delete [] buffer;
    }

    template<typename T>
    std::ostream& operator<<(std::ostream &out, const queue<T> &this_queue) {
        out << "----------------\nThis is queue dump.\nQueue buffer: ";
        T *buffer = this_queue.buffer;
        for (size_t i = 0; i < this_queue.buf_size; ++i) {
            out << buffer[i] << ", ";
        }
        out << "\b\b.\nQueue front_i = " << this_queue.front_i;
        out << "\nQueue rear_i = " << this_queue.rear_i;
        out << "\nQueue buf_size = " << this_queue.buf_size;
        out << "\nQueue min_buf_size = " << this_queue.min_buf_size;
        out << "\nQueue front = " << this_queue.front();
        out << "\nQueue back = " << this_queue.back();
        out << "\nIs queue empty = " << this_queue.empty();
        out << "\nQueue size = " << this_queue.size();
        out << "\n----------------";
        return out;
    }

    template <typename T>
    bool queue<T>::buf_enlarge() {
        size_t new_buf_size = 0;
        if (buf_size < BEAUTIFUL_CONSTANT / 2)
            new_buf_size = buf_size * 2;
        else if (buf_size < BEAUTIFUL_CONSTANT)
            new_buf_size = BEAUTIFUL_CONSTANT;
        else 
            return true;
        T *new_buffer = new T[new_buf_size];
        size_t new_i = 0;
        size_t i = front_i;
        if (front_i > rear_i) {
            for (; i < buf_size; ++i, ++new_i)
                new_buffer[new_i] = buffer[i];
            for (i = 0; i <= rear_i; ++i, ++new_i)
                new_buffer[new_i] = buffer[i];
        } else {
            for (; i <= rear_i; ++i, ++new_i)
                new_buffer[new_i] = buffer[i];
        }
        delete [] buffer;
        buffer = new_buffer;
        buf_size = new_buf_size;
        front_i = 0;
        rear_i = --new_i;
        return false;
    }

    template <typename T>
    void queue<T>::buf_diminish() {
        if (size() * 4 > buf_size || buf_size == min_buf_size) return;
        size_t new_buf_size = 0;
        if (buf_size > min_buf_size * 2)
            new_buf_size = std::max(buf_size / 2, min_buf_size); // for safety
        else 
            new_buf_size = min_buf_size;
        T *new_buffer = new T[new_buf_size];
        size_t new_i = 0;
        size_t i = front_i;
        if (front_i > rear_i) {
            for (; i < buf_size; ++i, ++new_i)
                new_buffer[new_i] = buffer[i];
            for (i = 0; i <= rear_i; ++i, ++new_i)
                new_buffer[new_i] = buffer[i];
        } else {
            for (; i <= rear_i; ++i, ++new_i)
                new_buffer[new_i] = buffer[i];
        }
        delete [] buffer;
        buffer = new_buffer;
        buf_size = new_buf_size;
        front_i = 0;
        rear_i = --new_i;
    }
}
