//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
//
// _coder_Projekfunction_api.cpp
//
// Code generation for function 'Projekfunction'
//

// Include files
#include "_coder_Projekfunction_api.h"
#include "_coder_Projekfunction_mex.h"

// Variable Definitions
emlrtCTX emlrtRootTLSGlobal{nullptr};

emlrtContext emlrtContextGlobal{
    true,                                                 // bFirstTime
    false,                                                // bInitialized
    131642U,                                              // fVersionInfo
    nullptr,                                              // fErrorFunction
    "Projekfunction",                                     // fFunctionName
    nullptr,                                              // fRTCallStack
    false,                                                // bDebugMode
    {2045744189U, 2170104910U, 2743257031U, 4284093946U}, // fSigWrd
    nullptr                                               // fSigMem
};

// Function Declarations
static real_T b_emlrt_marshallIn(const emlrtStack &sp, const mxArray *theta,
                                 const char_T *identifier);

static real_T b_emlrt_marshallIn(const emlrtStack &sp, const mxArray *u,
                                 const emlrtMsgIdentifier *parentId);

static real_T (*c_emlrt_marshallIn(const emlrtStack &sp, const mxArray *src,
                                   const emlrtMsgIdentifier *msgId))[3];

static real_T d_emlrt_marshallIn(const emlrtStack &sp, const mxArray *src,
                                 const emlrtMsgIdentifier *msgId);

static real_T (*emlrt_marshallIn(const emlrtStack &sp, const mxArray *P,
                                 const char_T *identifier))[3];

static real_T (*emlrt_marshallIn(const emlrtStack &sp, const mxArray *u,
                                 const emlrtMsgIdentifier *parentId))[3];

static const mxArray *emlrt_marshallOut(const real_T u[3]);

// Function Definitions
static real_T b_emlrt_marshallIn(const emlrtStack &sp, const mxArray *theta,
                                 const char_T *identifier)
{
  emlrtMsgIdentifier thisId;
  real_T y;
  thisId.fIdentifier = const_cast<const char_T *>(identifier);
  thisId.fParent = nullptr;
  thisId.bParentIsCell = false;
  y = b_emlrt_marshallIn(sp, emlrtAlias(theta), &thisId);
  emlrtDestroyArray(&theta);
  return y;
}

static real_T b_emlrt_marshallIn(const emlrtStack &sp, const mxArray *u,
                                 const emlrtMsgIdentifier *parentId)
{
  real_T y;
  y = d_emlrt_marshallIn(sp, emlrtAlias(u), parentId);
  emlrtDestroyArray(&u);
  return y;
}

static real_T (*c_emlrt_marshallIn(const emlrtStack &sp, const mxArray *src,
                                   const emlrtMsgIdentifier *msgId))[3]
{
  static const int32_T dims[2]{1, 3};
  real_T(*ret)[3];
  int32_T iv[2];
  boolean_T bv[2]{false, false};
  emlrtCheckVsBuiltInR2012b((emlrtConstCTX)&sp, msgId, src, "double", false, 2U,
                            (const void *)&dims[0], &bv[0], &iv[0]);
  ret = (real_T(*)[3])emlrtMxGetData(src);
  emlrtDestroyArray(&src);
  return ret;
}

static real_T d_emlrt_marshallIn(const emlrtStack &sp, const mxArray *src,
                                 const emlrtMsgIdentifier *msgId)
{
  static const int32_T dims{0};
  real_T ret;
  emlrtCheckBuiltInR2012b((emlrtConstCTX)&sp, msgId, src, "double", false, 0U,
                          (const void *)&dims);
  ret = *static_cast<real_T *>(emlrtMxGetData(src));
  emlrtDestroyArray(&src);
  return ret;
}

static real_T (*emlrt_marshallIn(const emlrtStack &sp, const mxArray *P,
                                 const char_T *identifier))[3]
{
  emlrtMsgIdentifier thisId;
  real_T(*y)[3];
  thisId.fIdentifier = const_cast<const char_T *>(identifier);
  thisId.fParent = nullptr;
  thisId.bParentIsCell = false;
  y = emlrt_marshallIn(sp, emlrtAlias(P), &thisId);
  emlrtDestroyArray(&P);
  return y;
}

static real_T (*emlrt_marshallIn(const emlrtStack &sp, const mxArray *u,
                                 const emlrtMsgIdentifier *parentId))[3]
{
  real_T(*y)[3];
  y = c_emlrt_marshallIn(sp, emlrtAlias(u), parentId);
  emlrtDestroyArray(&u);
  return y;
}

static const mxArray *emlrt_marshallOut(const real_T u[3])
{
  static const int32_T iv[2]{0, 0};
  static const int32_T iv1[2]{1, 3};
  const mxArray *m;
  const mxArray *y;
  y = nullptr;
  m = emlrtCreateNumericArray(2, (const void *)&iv[0], mxDOUBLE_CLASS, mxREAL);
  emlrtMxSetData((mxArray *)m, (void *)&u[0]);
  emlrtSetDimensions((mxArray *)m, &iv1[0], 2);
  emlrtAssign(&y, m);
  return y;
}

void Projekfunction_api(const mxArray *const prhs[3], int32_T nlhs,
                        const mxArray *plhs[2])
{
  emlrtStack st{
      nullptr, // site
      nullptr, // tls
      nullptr  // prev
  };
  real_T(*Gorg)[3];
  real_T(*P)[3];
  real_T(*outputArg1)[3];
  real_T(*outputArg2)[3];
  real_T theta;
  st.tls = emlrtRootTLSGlobal;
  outputArg1 = (real_T(*)[3])mxMalloc(sizeof(real_T[3]));
  outputArg2 = (real_T(*)[3])mxMalloc(sizeof(real_T[3]));
  // Marshall function inputs
  P = emlrt_marshallIn(st, emlrtAlias(prhs[0]), "P");
  Gorg = emlrt_marshallIn(st, emlrtAlias(prhs[1]), "Gorg");
  theta = b_emlrt_marshallIn(st, emlrtAliasP(prhs[2]), "theta");
  // Invoke the target function
  Projekfunction(*P, *Gorg, theta, *outputArg1, *outputArg2);
  // Marshall function outputs
  plhs[0] = emlrt_marshallOut(*outputArg1);
  if (nlhs > 1) {
    plhs[1] = emlrt_marshallOut(*outputArg2);
  }
}

void Projekfunction_atexit()
{
  emlrtStack st{
      nullptr, // site
      nullptr, // tls
      nullptr  // prev
  };
  mexFunctionCreateRootTLS();
  st.tls = emlrtRootTLSGlobal;
  emlrtEnterRtStackR2012b(&st);
  emlrtDestroyRootTLS(&emlrtRootTLSGlobal);
  Projekfunction_xil_terminate();
  Projekfunction_xil_shutdown();
  emlrtExitTimeCleanup(&emlrtContextGlobal);
}

void Projekfunction_initialize()
{
  emlrtStack st{
      nullptr, // site
      nullptr, // tls
      nullptr  // prev
  };
  mexFunctionCreateRootTLS();
  st.tls = emlrtRootTLSGlobal;
  emlrtClearAllocCountR2012b(&st, false, 0U, nullptr);
  emlrtEnterRtStackR2012b(&st);
  emlrtFirstTimeR2012b(emlrtRootTLSGlobal);
}

void Projekfunction_terminate()
{
  emlrtDestroyRootTLS(&emlrtRootTLSGlobal);
}

// End of code generation (_coder_Projekfunction_api.cpp)
