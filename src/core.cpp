#include "tc/core.hpp"

#include <utility>
#include <sstream>
#include <algorithm>

namespace tc {
    Action::Action(Gen from_idx, Gen gen)
        : from_idx(from_idx), gen(gen) {
    }

    void Path::add_row() {
        path.resize(path.size() + 1);
    }

    Action Path::get(Gen to_idx) const {
        return path[to_idx];
    }

    void Path::put(Gen from_idx, Gen gen, Gen to_idx) {
        path[to_idx] = Action(from_idx, gen);
    }

    size_t Path::size() const {
        return path.size();
    }

    Cosets::Cosets(Gen ngens)
        : ngens(ngens) {
    }

    void Cosets::add_row() {
        data.resize(data.size() + ngens, -1);
        path.add_row();
    }

    void Cosets::put(Gen coset, Gen gen, Gen target) {
        data[coset * ngens + gen] = target;
        data[target * ngens + gen] = coset;

        if (path.get(target).from_idx == -1) {
            path.put(coset, gen, target);
        }
    }

    void Cosets::put(Gen idx, Gen target) {
        Gen coset = idx / ngens;
        Gen gen = idx % ngens;
        data[idx] = target;
        data[target * ngens + gen] = coset;

        if (path.get(target).from_idx == -1) {
            path.put(coset, gen, target);
        }
    }

    Gen Cosets::get(Gen coset, Gen gen) const {
        return data[coset * ngens + gen];
    }

    Gen Cosets::get(Gen idx) const {
        return data[idx];
    }

    size_t Cosets::size() const {
        return path.size();
    }

    Rel::Rel(Gen a, Gen b, Gen m)
        : gens({a, b}), mult(m) {
    }

    Rel Rel::shift(Gen off) const {
        return Rel(gens[0] + off, gens[1] + off, mult);
    }

    Group::Group(Gen ngens, const std::vector<Rel> &rels, std::string name)
        : ngens(ngens), name(std::move(name)) {
        _mults.resize(ngens);

        for (auto &mult : _mults) {
            mult.resize(ngens, 2);
        }

        for (const auto &rel : rels) {
            set(rel);
        }
    }

    void Group::set(const Rel &r) {
        _mults[r.gens[0]][r.gens[1]] = r.mult;
        _mults[r.gens[1]][r.gens[0]] = r.mult;
    }

    Gen Group::get(Gen a, Gen b) const {
        return _mults[a][b];
    }

    std::vector<Rel> Group::rels() const {
        std::vector<Rel> res;
        for (Gen i = 0; i < ngens - 1; ++i) {
            for (Gen j = i + 1; j < ngens; ++j) {
                res.emplace_back(i, j, get(i, j));
            }
        }
        return res;
    }

    SubGroup Group::subgroup(const Gens &gens) const {
        return SubGroup(*this, gens);
    }

    Group Group::product(const Group &other) const {
        std::stringstream ss;
        ss << name << "*" << other.name;

        Group g(ngens + other.ngens, rels(), ss.str());

        for (const auto &rel : other.rels()) {
            g.set(rel.shift(ngens));
        }

        return g;
    }

    Group Group::power(Gen p) const {
        std::stringstream ss;
        ss << name << "^" << p;

        Group g(ngens * p, {}, ss.str());
        for (const auto &rel : rels()) {
            for (Gen off = 0; off < g.ngens; off += ngens) {
                g.set(rel.shift(off));
            }
        }

        return g;
    }

    SubGroup::SubGroup(const Group &parent, Gens gen_map)
        : Group(gen_map.size()), parent(parent) {

        std::sort(gen_map.begin(), gen_map.end());
        this->gen_map = gen_map;

        for (size_t i = 0; i < gen_map.size(); ++i) {
            for (size_t j = 0; j < gen_map.size(); ++j) {
                Gen mult = parent.get(gen_map[i], gen_map[j]);
                set(Rel(i, j, mult));
            }
        }
    }

    Group operator*(const Group &g, const Group &h) {
        return g.product(h);
    }

    Group operator^(const Group &g, Gen p) {
        return g.power(p);
    }
}
