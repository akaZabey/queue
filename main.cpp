#include <iostream>
#include "cyclic_queue.cpp"

constexpr int push_pop_cnt = 6;

int main(int argc, char const *argv[]) {
    my_struct::queue<int> my_q;
    bool ret = false;
    std::cout << "\t~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
    std::cout << "\tdump right after construct\n" << my_q << '\n';
    for (int i = 0; i < push_pop_cnt; ++i) {
        std::cout << "\t~~~~~~~~~~~~~~~~~~\n";
        ret = my_q.push(i + 1);
        std::cout << "\tpush(" << i + 1 << ") returned " << ret << '\n';
        std::cout << my_q << '\n';
    }
    my_struct::queue<int> my_q_cpy(my_q);
    std::cout << "\t~~~~~~~~~~~~~~~~~~~~~\n";
    std::cout << "\tdump of copy of queue\n" << my_q_cpy << '\n';
    for (int i = 0; i < push_pop_cnt; ++i) {
        std::cout << "\t~~~~~~~~~~~~~~~~~~\n";
        ret = my_q_cpy.pop();
        std::cout << "\tpop(" << i << ") returned " << ret << '\n';
        std::cout << my_q_cpy << '\n';
    }
    std::cout << "\t~~~~~~~~~~~~~~~~~~\n";
    my_struct::queue<int> my_q_eq = my_q;
    std::cout << "\t~~~~~~~~~~~~~~~~~~~~~~\n";
    std::cout << "\tqueue init with = dump\n" << my_q_eq << '\n';
    for (int i = 0; i < push_pop_cnt; ++i) {
        std::cout << "\t~~~~~~~~~~~~~~~~~~\n";
        ret = my_q_eq.pop();
        std::cout << "\tpop(" << i << ") returned " << ret << '\n';
        std::cout << my_q_eq << '\n';
    }
    std::cout << "\t~~~~~~~~~~~~~~~~~~\n";
    std::cout << "\t~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
    std::cout << "\toriginal queue after cpy and =\n" << my_q << '\n';
    std::cout << "\t~~~~~~~~~~~~~~~~~~\n";
    my_struct::queue<int> my_q_from_tmp = std::move(my_q);
    std::cout << "\t~~~~~~~~~~~~~~~~~~~~~~~\n";
    std::cout << "\tqueue init from tmp obj\n" << my_q_from_tmp << '\n';
    for (int i = 0; i < push_pop_cnt; ++i) {
        std::cout << "\t~~~~~~~~~~~~~~~~~~\n";
        ret = my_q_from_tmp.pop();
        std::cout << "\tpop(" << i << ") returned " << ret << '\n';
        std::cout << my_q_from_tmp << '\n';
    }
    std::cout << "\t~~~~~~~~~~~~~~~~~~\n";
    std::cout << "\t~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
    std::cout << "\toriginal queue after using as tmp obj\n" << my_q << '\n';
    std::cout << "\t~~~~~~~~~~~~~~~~~~\n";
    return 0;
}