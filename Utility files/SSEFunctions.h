//
//  SSEFunctions.h
//  SSEInterpTest
//
//  Created by Danny van Swieten on 26-08-14.
//  Copyright (c) 2014 Danny van Swieten. All rights reserved.
//

#ifndef SSE_FUNCTIONS_H
#define SSE_FUNCTIONS_H

#include <pmmintrin.h>  // Define entities up to and including SSE3.
#include <cmath>

#define _USE_MATH_DEFINES
typedef __m128 vFloat;

/*  Intel headers are available in steps including:
 mmintrin.h:  MMX.
 xmmintrin.h:  SSE.
 emmintrin.h:  SSE2.
 pmmintrin.h:  SSE3.
 tmmintrin.h:  SSSE3.
 smmintrin.h:  SSSE4 vector operations.
 nmmintrin.h:  SSSE4 string operations.
 
 Intel vector types include:
 __mm128:  four floats.
 __m128d:  2 doubles.
 __m128i:  16 8-bit, 8 16-bit, 4 32-bit, or 2 64-bit integers.
 */

static inline void vec2polSSE(const float* re, const float* im, float* a, float* ph, size_t len, const bool scaleOutput)
{
    vFloat* RE = (vFloat*)re;
    vFloat* IM = (vFloat*)im;
    vFloat scale = _mm_set_ps1((float)len);
    vFloat ResultRe;
    vFloat ResultIm;
    vFloat ResultAdd;
    vFloat A;
    vFloat Output;
    
    for (int i = 0; i < len; i+=4)
    {
        ResultRe = _mm_mul_ps(*RE, *RE);
        ResultIm = _mm_mul_ps(*IM, *IM);
        ResultAdd = _mm_add_ps(ResultRe, ResultIm);
        A = _mm_sqrt_ps(ResultAdd);
        if(scaleOutput)
        {
            Output = _mm_div_ps(A, scale);
            _mm_store_ps(&a[i], Output);
        }
        else
        {
            _mm_store_ps(&a[i], A);
        }
        RE++;
        IM++;
        
        *ph++ = atan2(*im++, *re++);
        *ph++ = atan2(*im++, *re++);
        *ph++ = atan2(*im++, *re++);
        *ph++ = atan2(*im++, *re++);
    }
}

static inline void complexMultiplyAccumulateSSE(float* re,
                                                float* im,
                                                const float* reA,
                                                const float* imA,
                                                const float* reB,
                                                const float* imB,
                                                const size_t len)
{
    const size_t end4 = 4 * (len / 4);
    for (size_t i=0; i<end4; i+=4)
    {
        const __m128 ra = _mm_load_ps(&reA[i]);
        const __m128 rb = _mm_load_ps(&reB[i]);
        const __m128 ia = _mm_load_ps(&imA[i]);
        const __m128 ib = _mm_load_ps(&imB[i]);
        __m128 real = _mm_load_ps(&re[i]);
        __m128 imag = _mm_load_ps(&im[i]);
        real = _mm_add_ps(real, _mm_mul_ps(ra, rb));
        real = _mm_sub_ps(real, _mm_mul_ps(ia, ib));
        _mm_store_ps(&re[i], real);
        imag = _mm_add_ps(imag, _mm_mul_ps(ra, ib));
        imag = _mm_add_ps(imag, _mm_mul_ps(ia, rb));
        _mm_store_ps(&im[i], imag);
    }
    for (size_t i=end4; i<len; ++i)
    {
        re[i] += reA[i] * reB[i] - imA[i] * imB[i];
        im[i] += reA[i] * imB[i] + imA[i] * reB[i];
    }
}

static inline void complexMultSSE(float* re,
                                  float* im,
                                  const float* reA,
                                  const float* imA,
                                  const float* reB,
                                  const float* imB,
                                  const size_t len)
{
    const size_t end4 = 4 * (len / 4);
    for (size_t i=0; i<end4; i+=4)
    {
        const __m128 ra = _mm_load_ps(&reA[i]);
        const __m128 rb = _mm_load_ps(&reB[i]);
        const __m128 ia = _mm_load_ps(&imA[i]);
        const __m128 ib = _mm_load_ps(&imB[i]);
        __m128 real = _mm_load_ps(&re[i]);
        __m128 imag = _mm_load_ps(&im[i]);
        real = _mm_add_ps(real, _mm_mul_ps(ra, rb));
        real = _mm_sub_ps(real, _mm_mul_ps(ia, ib));
        _mm_store_ps(&re[i], real);
        imag = _mm_add_ps(imag, _mm_mul_ps(ra, ib));
        imag = _mm_add_ps(imag, _mm_mul_ps(ia, rb));
        _mm_store_ps(&im[i], imag);
    }
    for (size_t i=end4; i<len; ++i)
    {
        re[i] = reA[i] * reB[i] - imA[i] * imB[i];
        im[i] = reA[i] * imB[i] + imA[i] * reB[i];
    }
}

static inline void vecMultSSEIP(float* one, const float* two, const int size)
{
    vFloat* vOne  = (vFloat*)one;
    vFloat* vTwo  = (vFloat*)two;
    
    for (auto i = 0; i < size; i+=4)
    {
        vOne[i] = _mm_mul_ps(vOne[i], vTwo[i]);
    }
}

static inline void vecMultSSE(const float* one, const float* two, float* result, const int size)
{
    vFloat* vOne  = (vFloat*)one;
    vFloat* vTwo  = (vFloat*)two;
    vFloat* vResult = (vFloat*)result;
    
    for (auto i = 0; i < size; i+=4)
    {
        vResult[i] = _mm_mul_ps(vOne[i], vTwo[i]);
    }
}

static inline void vecScalarMultSSE(float* X, float* result ,float scalar, int size)
{
    vFloat* vResult = (vFloat*)result;
    vFloat* vX = (vFloat*)X;
    vFloat vScalar = _mm_set1_ps(scalar);
    
    for (auto i = 0; i < size; i+=4)
    {
        *vResult++ = _mm_mul_ps(*vX++, vScalar);
    }
}

static inline void vecAddSSE(float* one, float* two, const long size)
{
    vFloat* vOne  = (vFloat*)one;
    vFloat* vTwo  = (vFloat*)two;
    
    for (auto i = 0; i < size; i+=4)
    {
        vOne[i] = _mm_add_ps(vOne[i], vTwo[i]);
    }
}

static inline void vecAddSSE(const float* result, const float* one, float* two, int size)
{
    const vFloat* vOne  = (const vFloat*)one;
    const vFloat* vTwo  = (const vFloat*)two;
    vFloat* vResult     =    (vFloat*)result;
    
    int vSize = size / 4;
    for (auto i = 0; i < vSize; i++)
    {
        vResult[i] = _mm_add_ps(vOne[i], vTwo[i]);
    }
}

static inline void vecSubSSE(const float* one, const float* two, float* result, int size)
{
    const vFloat* vOne  = (const vFloat*)one;
    const vFloat* vTwo  = (const vFloat*)two;
    vFloat* vResult     =    (vFloat*)result;
    
    int vSize = size / 4;
    for (auto i = 0; i < vSize; i++)
    {
        vResult[i] = _mm_sub_ps(vOne[i], vTwo[i]);
    }
}

#endif
