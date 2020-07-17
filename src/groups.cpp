#include "tc/groups.hpp"

#include <sstream>

namespace tc {
    Group schlafli(const std::vector<size_t> &mults, const std::string &name) {
        size_t ngens = (size_t) mults.size() + 1;

        Group g(ngens, {}, name);

        for (size_t i = 0; i < (size_t) mults.size(); i++) {
            g.set(Rel(i, i + 1, mults[i]));
        }

        return g;
    }

    Group schlafli(const std::vector<size_t> &mults) {
        std::stringstream ss;
        ss << "[";
        if (!mults.empty()) {
            for (size_t i = 0; i < mults.size() - 1; ++i) {
                ss << mults[i] << ",";
            }
            ss << mults.back();
        }
        ss << "]";

        return schlafli(mults, ss.str());
    }

    namespace group {
        Group A(const size_t dim) {
            std::stringstream ss;
            ss << "A(" << dim << ")";

            if (dim == 0)
                return Group(0, {}, ss.str());

            const std::vector<size_t> &mults = std::vector<size_t>(dim - 1, 3);

            return schlafli(mults, ss.str());
        }

        Group B(const size_t dim) {
            std::stringstream ss;
            ss << "B(" << dim << ")";

            std::vector<size_t> mults(dim - 1, 3);
            mults[0] = 4;

            return schlafli(mults, ss.str());
        }

        Group D(const size_t dim) {
            std::stringstream ss;
            ss << "D(" << dim << ")";

            std::vector<size_t> mults(dim - 1, 3);
            mults[dim - 2] = 2;

            Group g = schlafli(mults, ss.str());
            g.set(Rel(1, dim - 1, 3));

            return g;
        }

        Group E(const size_t dim) {
            std::stringstream ss;
            ss << "E(" << dim << ")";

            std::vector<size_t> mults(dim - 1, 3);
            mults[dim - 2] = 2;

            Group g = schlafli(mults, ss.str());
            g.set(Rel(2, dim - 1, 3));

            return g;
        }

        Group F4() {
            return schlafli({3, 4, 3}, "F4");
        }

        Group G2() {
            return schlafli({6}, "G2");
        }

        Group H(const size_t dim) {
            std::stringstream ss;
            ss << "H(" << dim << ")";

            std::vector<size_t> mults(dim - 1, 3);
            mults[0] = 5;

            return schlafli(mults, ss.str());
        }

        Group I2(const size_t n) {
            std::stringstream ss;
            ss << "I2(" << n << ")";

            return schlafli({n}, ss.str());
        }

        Group T(const size_t n, const size_t m) {
            std::stringstream ss;
            ss << "T(" << n << "," << m << ")";

            return schlafli({n, 2, m}, ss.str());
        }

        Group T(const size_t n) {
            std::stringstream ss;
            ss << "T(" << n << ")";

            return schlafli({n, 2, n}, ss.str());
        }
    }
}
