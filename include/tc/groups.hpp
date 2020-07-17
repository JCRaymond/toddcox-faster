#pragma once

#include "core.hpp"


namespace tc {
    /**
     * Construct a group from a (simplified) Schlafli Symbol of the form [a, b, ..., c]
     * @param mults: The sequence of multiplicites between adjacent generators.
     */
    Group schlafli(const std::vector<size_t> &mults, const std::string &name);

    /**
     * Construct a group from a (simplified) Schlafli Symbol of the form [a, b, ..., c]
     * @param mults: The sequence of multiplicites between adjacent generators.
     */
    Group schlafli(const std::vector<size_t> &mults);

    namespace group {
        /**
         * Simplex
         */
        Group A(size_t dim);

        /**
         * Cube, Orthoplex
         */
        Group B(size_t dim);

        /**
         * Demicube, Orthoplex
         */
        Group D(size_t dim);

        /**
         * E groups
         */
        Group E(size_t dim);

        /**
         * 24 Cell
         */
        Group F4();

        /**
         * Hexagon
         */
        Group G2();

        /**
         * Icosahedron
         */
        Group H(size_t dim);

        /**
         * Polygonal
         */
        Group I2(size_t n);

        /**
         * Toroidal. I2(n) * I2(m)
         */
        Group T(size_t n, size_t m);

        /**
         * Toroidal. T(n, n)
         */
        Group T(Gen n);
    }
}
