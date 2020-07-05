/*
 * File: _coder_m2cpp_api.h
 *
 * MATLAB Coder version            : 4.2
 * C/C++ source code generated on  : 30-May-2020 03:24:07
 */

#ifndef _CODER_M2CPP_API_H
#define _CODER_M2CPP_API_H

/* Include Files */
#include "tmwtypes.h"
#include "mex.h"
#include "emlrt.h"
#include <stddef.h>
#include <stdlib.h>
#include "_coder_m2cpp_api.h"

/* Variable Declarations */
extern emlrtCTX emlrtRootTLSGlobal;
extern emlrtContext emlrtContextGlobal;

/* Function Declarations */
extern void m2cpp(void);
extern void m2cpp_api(int32_T nlhs);
extern void m2cpp_atexit(void);
extern void m2cpp_initialize(void);
extern void m2cpp_terminate(void);
extern void m2cpp_xil_shutdown(void);
extern void m2cpp_xil_terminate(void);

#endif

/*
 * File trailer for _coder_m2cpp_api.h
 *
 * [EOF]
 */
