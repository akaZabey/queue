#include <iostream>
#include "cyclic_queue.cpp"

enum consts {
    push_pop_cnt = 6
};

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
    for (int i = 0; i < push_pop_cnt; ++i) {
        std::cout << "\t~~~~~~~~~~~~~~~~~~\n";
        ret = my_q.pop();
        std::cout << "\tpop(" << i << ") returned " << ret << '\n';
        std::cout << my_q << '\n';
    }
    std::cout << "\t~~~~~~~~~~~~~~~~~~\n";
    return 0;
}