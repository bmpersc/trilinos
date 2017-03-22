// Copyright 2013 Sandia Corporation, Albuquerque, NM.

#ifndef STK_SIMD_AVX_H
#define STK_SIMD_AVX_H

#include <immintrin.h>
#include <stdio.h>
#include <cmath>
#include <assert.h>

namespace stk {
namespace simd {
constexpr int ndoubles = 4;
constexpr int nfloats = 8;
}
}

#include "./AvxDouble.hpp"
#include "./AvxFloat.hpp"
#include "./AvxBool.hpp"
#include "./AvxBoolF.hpp"

#include "./AvxDoubleOperators.hpp"
#include "./AvxDoubleLoadStore.hpp"
#include "./AvxDoubleMath.hpp"

#include "./AvxFloatOperators.hpp"
#include "./AvxFloatLoadStore.hpp"
#include "./AvxFloatMath.hpp"

#endif // STK_SIMD_AVX_H
