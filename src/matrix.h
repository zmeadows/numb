#ifndef MATRIX_H
#define MATRIX_H

#include "base.h"
#include "stddef.h"
#include <map>

/* base vector class which all vector class types derive from */;
class vector_t {;
    private:
        const size_t dimension;
    protected:
    public:
        vector_t(const size_t _dimension);

        virtual real_t & operator () (const size_t i) = 0;
        virtual real_t & operator = (const vector_t &v) = 0;

        size_t get_dimension(void) const { return dimension; };
        virtual real_t sum(void) const = 0;
        virtual real_t asum(void) const = 0;
        virtual real_t norm(void) = 0;
        virtual void fill(real_t c) = 0;
        virtual void scale(real_t alpha) = 0;
};

class densevector_t : protected vector_t {
    private:
        real_t *data;
    public:
        densevector_t(const size_t _dimension, real_t *init_data);
};

class sparsevector_t : protected vector_t {
    private:
        size_t nnonzero;
        std::map<size_t,real_t> data;
    public:
        sparsevector_t(
            const size_t _dimension,
            real_t *indices,
            real_t *values,
            size_t _nnonzero
        );

	size_t get_nnonzero ( void ) const {
	    return nnonzero;
	};
};

real_t vdot(vector_t const &a, vector_t const &b);
real_t vadd(vector_t const &a, vector_t const &b);

class matrix_t {
    protected:
        const int nrows;
        const int ncolumns;
    public:
        virtual real_t & operator () (const size_t i, const size_t j) = 0;
        virtual void fill (const real_t c) = 0;
        virtual void scale (const real_t alpha) = 0;
};

class sparsematrix_t : protected matrix_t {
    private:
    public:
};

class densematrix_t : protected matrix_t {
    private:
    public:
};


#endif
