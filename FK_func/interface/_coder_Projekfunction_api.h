//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
//
// _coder_Projekfunction_api.h
//
// Code generation for function 'Projekfunction'
//

#ifndef _CODER_PROJEKFUNCTION_API_H
#define _CODER_PROJEKFUNCTION_API_H

// Include files
#include "emlrt.h"
#include "tmwtypes.h"
#include <algorithm>
#include <cstring>

// Variable Declarations
extern emlrtCTX emlrtRootTLSGlobal;
extern emlrtContext emlrtContextGlobal;

// Function Declarations
void Projekfunction(real_T P[3], real_T Gorg[3], real_T theta,
                    real_T outputArg1[3], real_T outputArg2[3]);

void Projekfunction_api(const mxArray *const prhs[3], int32_T nlhs,
                        const mxArray *plhs[2]);

void Projekfunction_atexit();

void Projekfunction_initialize();

void Projekfunction_terminate();

void Projekfunction_xil_shutdown();

void Projekfunction_xil_terminate();

#endif
// End of code generation (_coder_Projekfunction_api.h)
