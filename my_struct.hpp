#ifndef MY_STRUCT_HPP
#define MY_STRUCT_HPP

namespace my_struct {
    const size_t QBUF_SIZE = 5;

    template <typename T>
    class queue;

    template <typename T>
    std::ostream& operator<<(std::ostream &out, const queue<T> &);

    template <typename T>
    class queue {
    public:
        queue(): buffer(new T[QBUF_SIZE]), front_i(-1), rear_i(-1) {};

        T &front() const;

        T &back() const;

        bool empty() const;

        size_t size() const;

        bool push(const T &);

        bool pop();

        size_t get_front_i() const;

        size_t get_rear_i() const;

        T *get_buffer() const;

        ~queue();

        friend std::ostream& operator<<<T>(std::ostream &, const queue<T> &);
    private:
        T *buffer;
        size_t front_i;
        size_t rear_i;
    };
}

#endif