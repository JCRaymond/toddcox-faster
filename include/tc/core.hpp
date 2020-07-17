#pragma once

#include <array>
#include <numeric>
#include <functional>
#include <vector>
#include <string>

namespace tc {
    using Gen = int;
    using Gens = std::vector<Gen>;

    Gens iota(size_t size);

    struct Action {
        Gen from_idx = -1;
        Gen gen = -1;

        Action() = default;

        Action(const Action &) = default;

        Action(Gen from_idx, Gen gen);
    };

    struct Path {
        std::vector<Action> path;

        Path() = default;

        Path(const Path &) = default;

        void add_row();

        [[nodiscard]] Action get(Gen to_idx) const;

        void put(Gen from_idx, Gen gen, Gen to_idx);

        [[nodiscard]] size_t size() const;
    };

    template<class T, class F>
    std::vector<T> walk(const Path &path, T start, F op) {
        std::vector<T> res(path.size());
        res[0] = start;

        for(size_t i = 1; i < res.size(); ++i) {
            auto &action = path.path[i];
            auto &from = res[action.from_idx];
            auto &val = action.gen;
            res[i] = op(from, val);
        }

        return res;
    }

    template<class T, class E, class F>
    std::vector<T> walk(const Path &path, T start, E gens, F op) {
        return tc::walk(path, start, [&](T from, Gen gen){
            return op(from, gens[gen]);
        });
    }

    struct Cosets {
        Gen ngens;
        Gens data;
        Path path;

        Cosets(const Cosets &) = default;

        explicit Cosets(Gen ngens);

        void add_row();

        void put(Gen coset, Gen gen, Gen target);

        void put(Gen idx, Gen target);

        [[nodiscard]] Gen get(Gen coset, Gen gen) const;

        [[nodiscard]] Gen get(Gen idx) const;

        [[nodiscard]] size_t size() const;
    };

    struct Rel {
        std::array<Gen, 2> gens;
        Gen mult;

        Rel() = default;

        Rel(const Rel &) = default;

        Rel(Gen a, Gen b, Gen m);

        [[nodiscard]] Rel shift(Gen off) const;
    };

    struct SubGroup;

    struct Group {
        const Gen ngens;
        std::vector<Gens> _mults;
        std::string name;

        Group(const Group &) = default;

        explicit Group(Gen ngens, const std::vector<Rel> &rels = {}, std::string name = "G");

        void set(const Rel &r);

        [[nodiscard]] Gen get(Gen a, Gen b) const;

        [[nodiscard]] std::vector<Rel> rels() const;

        [[nodiscard]] SubGroup subgroup(const Gens &gens) const;

        [[nodiscard]] Group product(const Group &other) const;

        [[nodiscard]] Group power(Gen p) const;

        [[nodiscard]] Cosets solve(const Gens &sub_gens = {}) const;
    };

    struct SubGroup : public Group {
        Gens gen_map;
        const Group &parent;

        SubGroup(const Group &parent, Gens gen_map);
    };

    Group operator*(const Group &g, const Group &h);

    Group operator^(const Group &g, Gen p);
}
