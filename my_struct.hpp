#ifndef MY_STRUCT_HPP
#define MY_STRUCT_HPP

namespace my_struct {
    template <typename T>
    class queue;

    template <typename T>
    std::ostream& operator<<(std::ostream &out, const queue<T> &);

    template <typename T>
    class queue {
    public:
        queue(size_t);    // Param is max cnt of elements can be pushed
                          // with method push, force_push ignores it.
        T &front() const; // Expect undefined behavior if
                          // the requested value is undefined.
        T &back() const;  // Expect undefined behavior if
                          // the requested value is undefined.
        bool empty() const;

        size_t size() const;

        bool push(const T &);

        bool pop();

        size_t get_front_i() const;

        size_t get_rear_i() const;

        size_t get_buf_size() const;

        size_t get_min_buf_size() const;

        T *get_buffer() const;

        queue<T> &operator=(const queue &);

        queue<T> &operator=(queue &&);

        queue(const queue &);

        queue(queue &&);

        ~queue();

        friend std::ostream& operator<<<T>(std::ostream &, const queue<T> &);
    private:
        T *buffer;
        size_t front_i;
        size_t rear_i;
        size_t buf_size;
        size_t min_buf_size;

        bool buf_enlarge();

        void buf_diminish();
    };
}

#include "cyclic_queue.cpp"

#endif
