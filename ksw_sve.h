/*
MIT License

Copyright (c) 2021 RIKEN R-CCS

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

#ifndef KSW_SVE_H
#define KSW_SVE_H

#include <arm_sve.h>

#ifndef BWA_SVE_VL
#define BWA_SVE_VL 16
#endif

#if BWA_SVE_VL == 16
#define __SV_VL_u8 SV_VL16
#define __SV_VL_i16 SV_VL8
#elif BWA_SVE_VL == 32
#define __SV_VL_u8 SV_VL32
#define __SV_VL_i16 SV_VL16
#elif BWA_SVE_VL == 64
#define __SV_VL_u8 SV_VL64
#define __SV_VL_i16 SV_VL32
#else
#error "BWA_SVE_VL must be 16, 32 or 64"
#endif

typedef uint64_t _vec[BWA_SVE_VL/8];

/* uint8_t */

#define sve_u8_init() \
  svbool_t __p = svptrue_pat_b8(__SV_VL_u8)

#define _SET1_u8(u)  svdup_u8_x(__p, (u))

#define _LOAD_u8(p) svld1_u8(__p, (uint8_t*)(p))

#define _STORE_u8(p, v) svst1_u8(__p, (uint8_t*)(p), (v))

#define _SHIFT_L_u8(v) svinsr_n_u8((v), 0)

#define _ADD_u8(va, vb) svqadd_u8((va), (vb))

#define _SUB_u8(va, vb) svqsub_u8((va), (vb))

#define _MAX_u8(va, vb) svmax_u8_x(__p, (va), (vb))

#define _MAXm_u8(p, va, vb) svmax_u8_m((p), (va), (vb))

//#define _CMP_LE_ALL_u8(va, vb) (svcntp_b8(__p, svcmple_u8(__p, (va), (vb))) == BWA_SVE_VL)
#define _CMP_LE_ALL_u8(va, vb) (!svptest_any(__p, svcmpgt_u8(__p, (va), (vb))))

#define _MAX_V_u8(v) svmaxv_u8(__p, (v))

/* int16_t */

#define sve_i16_init() \
  svbool_t __p = svptrue_pat_b16(__SV_VL_i16)

#define _SET1_i16(u)  svdup_s16_x(__p, (u))

#define _LOAD_i16(p) svld1_s16(__p, (int16_t*)(p))

#define _STORE_i16(p, v) svst1_s16(__p, (int16_t*)(p), (v))

#define _SHIFT_L_i16(v) svinsr_n_s16((v), 0)

#define _ADD_i16(va, vb) svadd_s16_x(__p, (va), (vb))

#define _SUB_i16(va, vb) svreinterpret_s16(svqsub_u16(svreinterpret_u16(va), svreinterpret_u16(vb)))

#define _MAX_i16(va, vb) svmax_s16_x(__p, (va), (vb))

#define _MAXm_i16(p, va, vb) svmax_s16_m((p), (va), (vb))

//#define _CMP_LE_ALL_i16(va, vb) (svcntp_b16(__p, svcmple_s16(__p, (va), (vb))) == (BWA_SVE_VL>>1))
#define _CMP_LE_ALL_i16(va, vb) (!svptest_any(__p, svcmpgt_s16(__p, (va), (vb))))

#define _MAX_V_i16(v) svmaxv_s16(__p, (v))

#endif /* KSW_SVE_H */
