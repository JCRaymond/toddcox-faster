#include "tc/groups.hpp"

#include <ctime>
#include <iostream>

int main() {
    auto cube = tc::group::B(3);
    auto vars = cube.solve();

    for (size_t target = 1; target < vars.size(); target++) {
        auto &action = vars.path[target];
        std::cout << action.coset << " * " << action.gen << " = " << target << std::endl;
    }

    return 0;
}
