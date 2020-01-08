#include "tc/groups.hpp"

#include <ctime>
#include <iostream>

int main() {
    auto cube = tc::group::B(3);
    auto vars = cube.solve();

    auto words = vars.path.walk<std::string>(
        "",
        {"a", "b", "c"},
        [](auto a, auto b) { return a + b; }
    );

    for (const auto &word : words) {
        std::cout << word << std::endl;
    }

//    for (size_t target = 1; target < vars.size(); target++) {
//        auto &action = vars.path.get(target);
//        std::cout << action.from_idx << " * " << action.gen << " = " << target << std::endl;
//    }

    return 0;
}
