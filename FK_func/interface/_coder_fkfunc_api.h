//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
//
// _coder_fkfunc_api.h
//
// Code generation for function 'fkfunc'
//

#ifndef _CODER_FKFUNC_API_H
#define _CODER_FKFUNC_API_H

// Include files
#include "emlrt.h"
#include "tmwtypes.h"
#include <algorithm>
#include <cstring>

// Variable Declarations
extern emlrtCTX emlrtRootTLSGlobal;
extern emlrtContext emlrtContextGlobal;

// Function Declarations
void fkfunc(real_T P[3], real_T Gorg[3], real_T theta, real_T outputArg1[3],
            real_T outputArg2[3]);

void fkfunc_api(const mxArray *const prhs[3], int32_T nlhs,
                const mxArray *plhs[2]);

void fkfunc_atexit();

void fkfunc_initialize();

void fkfunc_terminate();

void fkfunc_xil_shutdown();

void fkfunc_xil_terminate();

#endif
// End of code generation (_coder_fkfunc_api.h)
