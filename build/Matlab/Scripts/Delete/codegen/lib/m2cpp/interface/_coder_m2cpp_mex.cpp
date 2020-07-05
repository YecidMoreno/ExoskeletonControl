/*
 * File: _coder_m2cpp_mex.cpp
 *
 * MATLAB Coder version            : 4.2
 * C/C++ source code generated on  : 30-May-2020 03:24:07
 */

/* Include Files */
#include "_coder_m2cpp_api.h"
#include "_coder_m2cpp_mex.h"

/* Function Declarations */
static void m2cpp_mexFunction(int32_T nlhs, int32_T nrhs);

/* Function Definitions */

/*
 * Arguments    : int32_T nlhs
 *                int32_T nrhs
 * Return Type  : void
 */
static void m2cpp_mexFunction(int32_T nlhs, int32_T nrhs)
{
  emlrtStack st = { NULL,              /* site */
    NULL,                              /* tls */
    NULL                               /* prev */
  };

  st.tls = emlrtRootTLSGlobal;

  /* Check for proper number of arguments. */
  if (nrhs != 0) {
    emlrtErrMsgIdAndTxt(&st, "EMLRT:runTime:WrongNumberOfInputs", 5, 12, 0, 4, 5,
                        "m2cpp");
  }

  if (nlhs > 0) {
    emlrtErrMsgIdAndTxt(&st, "EMLRT:runTime:TooManyOutputArguments", 3, 4, 5,
                        "m2cpp");
  }

  /* Call the function. */
  m2cpp_api(nlhs);
}

/*
 * Arguments    : int32_T nlhs
 *                mxArray * const plhs[]
 *                int32_T nrhs
 *                const mxArray * const prhs[]
 * Return Type  : void
 */
void mexFunction(int32_T nlhs, mxArray *plhs[], int32_T nrhs, const mxArray
                 *prhs[])
{
  (void)plhs;
  (void)prhs;
  mexAtExit(m2cpp_atexit);

  /* Module initialization. */
  m2cpp_initialize();

  /* Dispatch the entry-point. */
  m2cpp_mexFunction(nlhs, nrhs);

  /* Module termination. */
  m2cpp_terminate();
}

/*
 * Arguments    : void
 * Return Type  : emlrtCTX
 */
emlrtCTX mexFunctionCreateRootTLS(void)
{
  emlrtCreateRootTLS(&emlrtRootTLSGlobal, &emlrtContextGlobal, NULL, 1);
  return emlrtRootTLSGlobal;
}

/*
 * File trailer for _coder_m2cpp_mex.cpp
 *
 * [EOF]
 */
