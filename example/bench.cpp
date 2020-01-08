#include "tc/core.hpp"
#include "tc/groups.hpp"

#include <ctime>
#include <vector>
#include <iostream>

int main() {
    std::vector<tc::Group> groups = {
        tc::group::H(2),
        tc::group::H(3),
        tc::group::H(4),
        tc::group::T(100),
        tc::group::T(500),
        tc::group::T(1000),
        tc::group::E(6),
        tc::group::E(7),
        tc::group::B(6),
        tc::group::B(7),
        tc::group::B(8),
    };

    for (const auto &group : groups) {
        auto s = std::clock(); // to measure CPU time
        auto cosets = group.solve();
        auto e = std::clock();

        double diff = (double) (e - s) / CLOCKS_PER_SEC;
        int order = cosets.size();

        std::cout << group.name << "," << order << "," << diff << std::endl;
    }

    return 0;
}
