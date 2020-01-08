#pragma once

#include<array>
#include<vector>
#include<string>

namespace tc {
    struct Action {
        int coset = -1;
        int gen = -1;
        int target = -1;

        Action() = default;

        Action(const Action &) = default;

        Action(int coset, int gen, int target);
    };

    struct Cosets {
        int ngens;
        std::vector<int> data;
        std::vector<Action> path;

        Cosets(const Cosets &) = default;

        explicit Cosets(int ngens);

        void add_row();

        void put(int coset, int gen, int target);

        void put(int idx, int target);

        [[nodiscard]] int get(int coset, int gen) const;

        [[nodiscard]] int get(int idx) const;

        [[nodiscard]] size_t size() const;
    };

    struct Rel {
        std::array<int, 2> gens;
        int mult;

        Rel() = default;

        Rel(const Rel &) = default;

        Rel(int a, int b, int m);

        [[nodiscard]] Rel shift(int off) const;
    };

    struct Group {
        const int ngens;
        std::vector<std::vector<int>> _mults;
        std::string name;

        Group(const Group &) = default;

        explicit Group(int ngens, const std::vector<Rel> &rels = {}, std::string name = "G");

        void set(const Rel &r);

        [[nodiscard]] int get(int a, int b) const;

        [[nodiscard]] std::vector<Rel> rels() const;

        [[nodiscard]] Group product(const Group &other) const;

        [[nodiscard]] Group power(int p) const;

        [[nodiscard]] Cosets solve(const std::vector<int>& sub_gens = {}) const;
    };

    Group operator*(const Group &g, const Group &h);

    Group operator^(const Group &g, int p);
}
