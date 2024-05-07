//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
//
// fkfunc.cpp
//
// Code generation for function 'fkfunc'
//

// Include files
#include "fkfunc.h"
#include "rt_nonfinite.h"
#include "sqrt.h"
#include "svd.h"
#include "rt_defines.h"
#include <algorithm>
#include <cmath>
#include <cstring>

// Function Declarations
static double rt_atan2d_snf(double u0, double u1);

// Function Definitions
static double rt_atan2d_snf(double u0, double u1)
{
  double y;
  if (std::isnan(u0) || std::isnan(u1)) {
    y = rtNaN;
  } else if (std::isinf(u0) && std::isinf(u1)) {
    int i;
    int i1;
    if (u0 > 0.0) {
      i = 1;
    } else {
      i = -1;
    }
    if (u1 > 0.0) {
      i1 = 1;
    } else {
      i1 = -1;
    }
    y = std::atan2(static_cast<double>(i), static_cast<double>(i1));
  } else if (u1 == 0.0) {
    if (u0 > 0.0) {
      y = RT_PI / 2.0;
    } else if (u0 < 0.0) {
      y = -(RT_PI / 2.0);
    } else {
      y = 0.0;
    }
  } else {
    y = std::atan2(u0, u1);
  }
  return y;
}

void fkfunc(const double P[3], const double Gorg[3], double theta,
            double outputArg1[3], double outputArg2[3])
{
  static const double b_a[16]{0.38479919804402751,
                              -0.922998751186842,
                              0.0016977903884631373,
                              0.0,
                              0.92300029812684414,
                              0.38479886750604908,
                              -0.00053030540146320568,
                              0.0,
                              -0.00016383659544509454,
                              0.001771122127909824,
                              0.99999841814073787,
                              0.0,
                              -0.25178,
                              -0.2401,
                              -0.03488,
                              1.0};
  static const double b_b[16]{-1.0, 0.0,  -1.2246467991473532E-16,
                              0.0,  0.0,  1.0,
                              0.0,  0.0,  1.2246467991473532E-16,
                              0.0,  -1.0, 0.0,
                              0.0,  0.0,  0.0,
                              1.0};
  static const double c_b[16]{1.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0,    0.0,
                              0.0, 0.0, 1.0, 0.0, 0.0, 0.0, -0.137, 1.0};
  creal_T b_v;
  creal_T u;
  double B_T_EE[16];
  double a[16];
  double b[16];
  double T_R_G[9];
  double tempR[9];
  double v[3];
  double b_tempR_tmp;
  double c_tempR_tmp;
  double cth;
  double sth;
  double tempR_tmp;
  int i;
  int iacol_tmp;
  boolean_T exitg1;
  boolean_T rEQ0;
  //  inputs for calibration, should be measured with UR5:
  // nulpunkt for taskframe
  // forskydning i x-retnig fra Torg
  // forskydning i ca. yretning fra Torg (bruges kun til beregning af Z-akse)
  // Place cups using this frame
  // and in a line rotated theta radians from x-axis of task space
  //  skal køres på hvert output fra Grys funktion.
  //  3-point calibration
  //  x-axis of Taskframe seen from Base
  //  Z-axis
  //  Y-axis
  // should be normal already
  //  Trasformation from Task to Goal frame.
  //  T_Gorg and theta defined in as input
  // axis of rotation is Z-axis of T (seen from T)
  cth = std::cos(theta);
  sth = std::sin(theta);
  tempR_tmp = 0.0 * (1.0 - cth);
  b_tempR_tmp = tempR_tmp + cth;
  tempR[0] = b_tempR_tmp;
  tempR[1] = tempR_tmp - sth;
  c_tempR_tmp = tempR_tmp + 0.0 * sth;
  tempR[2] = c_tempR_tmp;
  tempR[3] = tempR_tmp + sth;
  tempR[4] = b_tempR_tmp;
  tempR_tmp -= 0.0 * sth;
  tempR[5] = tempR_tmp;
  tempR[6] = tempR_tmp;
  tempR[7] = c_tempR_tmp;
  tempR[8] = (1.0 - cth) + cth;
  std::copy(&tempR[0], &tempR[9], &T_R_G[0]);
  for (i = 0; i < 3; i++) {
    T_R_G[i] = tempR[3 * i];
    T_R_G[i + 3] = tempR[3 * i + 1];
    T_R_G[i + 6] = tempR[3 * i + 2];
  }
  //  The fist cup will be placed on origin in goal space (using T_Gorg and
  //  rVec)
  std::memset(&B_T_EE[0], 0, 16U * sizeof(double));
  B_T_EE[0] = 1.0;
  B_T_EE[5] = 1.0;
  B_T_EE[10] = 1.0;
  B_T_EE[15] = 1.0;
  for (i = 0; i < 4; i++) {
    iacol_tmp = i << 2;
    b[iacol_tmp] = B_T_EE[iacol_tmp];
    b[iacol_tmp + 1] = B_T_EE[iacol_tmp + 1];
    b[iacol_tmp + 2] = B_T_EE[iacol_tmp + 2];
    b[iacol_tmp + 3] = B_T_EE[iacol_tmp + 3];
  }
  b[12] = P[0];
  b[13] = P[1];
  b[14] = P[2];
  //  rVec er ens for alle kopper
  //  B_Pcup skal regnes for hver kop
  //  TCP skal være modsat flipped zakse, og samme y-aksen derfor drejses pi rad
  //  den yaksen. TCP er 137,1 mm over TF
  for (int b_i{0}; b_i < 3; b_i++) {
    i = b_i << 2;
    B_T_EE[i] = T_R_G[3 * b_i];
    B_T_EE[i + 1] = T_R_G[3 * b_i + 1];
    B_T_EE[i + 2] = T_R_G[3 * b_i + 2];
  }
  B_T_EE[12] = Gorg[0];
  B_T_EE[13] = Gorg[1];
  B_T_EE[14] = Gorg[2];
  B_T_EE[3] = 0.0;
  B_T_EE[7] = 0.0;
  B_T_EE[11] = 0.0;
  B_T_EE[15] = 1.0;
  for (int b_i{0}; b_i < 4; b_i++) {
    cth = b_a[b_i];
    sth = b_a[b_i + 4];
    tempR_tmp = b_a[b_i + 8];
    b_tempR_tmp = b_a[b_i + 12];
    for (iacol_tmp = 0; iacol_tmp < 4; iacol_tmp++) {
      i = iacol_tmp << 2;
      a[b_i + i] = ((cth * B_T_EE[i] + sth * B_T_EE[i + 1]) +
                    tempR_tmp * B_T_EE[i + 2]) +
                   b_tempR_tmp * B_T_EE[i + 3];
    }
  }
  for (int b_i{0}; b_i < 4; b_i++) {
    cth = a[b_i];
    sth = a[b_i + 4];
    tempR_tmp = a[b_i + 8];
    b_tempR_tmp = a[b_i + 12];
    for (iacol_tmp = 0; iacol_tmp < 4; iacol_tmp++) {
      i = iacol_tmp << 2;
      B_T_EE[b_i + i] = ((cth * b[i] + sth * b[i + 1]) + tempR_tmp * b[i + 2]) +
                        b_tempR_tmp * b[i + 3];
    }
    cth = B_T_EE[b_i];
    sth = B_T_EE[b_i + 4];
    tempR_tmp = B_T_EE[b_i + 8];
    b_tempR_tmp = B_T_EE[b_i + 12];
    for (iacol_tmp = 0; iacol_tmp < 4; iacol_tmp++) {
      i = iacol_tmp << 2;
      a[b_i + i] =
          ((cth * b_b[i] + sth * b_b[i + 1]) + tempR_tmp * b_b[i + 2]) +
          b_tempR_tmp * b_b[i + 3];
    }
    cth = a[b_i];
    sth = a[b_i + 4];
    tempR_tmp = a[b_i + 8];
    b_tempR_tmp = a[b_i + 12];
    for (iacol_tmp = 0; iacol_tmp < 4; iacol_tmp++) {
      i = iacol_tmp << 2;
      B_T_EE[b_i + i] =
          ((cth * c_b[i] + sth * c_b[i + 1]) + tempR_tmp * c_b[i + 2]) +
          b_tempR_tmp * c_b[i + 3];
    }
  }
  outputArg1[0] = B_T_EE[12] / B_T_EE[15];
  outputArg1[1] = B_T_EE[13] / B_T_EE[15];
  outputArg1[2] = B_T_EE[14] / B_T_EE[15];
  cth = 0.5 * (((B_T_EE[0] + B_T_EE[5]) + B_T_EE[10]) - 1.0);
  if (!(std::abs(cth) > 1.0)) {
    u.re = std::acos(cth);
  } else {
    b_v.re = cth + 1.0;
    b_v.im = 0.0;
    coder::internal::scalar::b_sqrt(b_v);
    u.re = 1.0 - cth;
    u.im = 0.0;
    coder::internal::scalar::b_sqrt(u);
    cth = u.re;
    u.re = 2.0 * rt_atan2d_snf(cth, b_v.re);
  }
  cth = 2.0 * std::sin(u.re);
  v[0] = (B_T_EE[6] - B_T_EE[9]) / cth;
  v[1] = (B_T_EE[8] - B_T_EE[2]) / cth;
  v[2] = (B_T_EE[1] - B_T_EE[4]) / cth;
  if (std::isnan(u.re) || std::isinf(u.re)) {
    cth = rtNaN;
  } else if (u.re == 0.0) {
    cth = 0.0;
  } else {
    cth = std::fmod(u.re, 3.1415926535897931);
    rEQ0 = (cth == 0.0);
    if (!rEQ0) {
      sth = std::abs(u.re / 3.1415926535897931);
      rEQ0 = !(std::abs(sth - std::floor(sth + 0.5)) >
               2.2204460492503131E-16 * sth);
    }
    if (rEQ0) {
      cth = 0.0;
    } else if (u.re < 0.0) {
      cth += 3.1415926535897931;
    }
  }
  rEQ0 = true;
  i = 0;
  exitg1 = false;
  while ((!exitg1) && (i < 3)) {
    if (!(v[i] == 0.0)) {
      rEQ0 = false;
      exitg1 = true;
    } else {
      i++;
    }
  }
  if ((cth == 0.0) || rEQ0) {
    double vspecial_data[3];
    for (int b_i{0}; b_i < 3; b_i++) {
      vspecial_data[b_i] = 0.0;
    }
    for (int c_i{0}; c_i < 1; c_i++) {
      std::memset(&T_R_G[0], 0, 9U * sizeof(double));
      T_R_G[0] = 1.0;
      T_R_G[4] = 1.0;
      T_R_G[8] = 1.0;
      for (int b_i{0}; b_i < 3; b_i++) {
        iacol_tmp = b_i << 2;
        T_R_G[3 * b_i] -= B_T_EE[iacol_tmp];
        i = 3 * b_i + 1;
        T_R_G[i] -= B_T_EE[iacol_tmp + 1];
        i = 3 * b_i + 2;
        T_R_G[i] -= B_T_EE[iacol_tmp + 2];
      }
      rEQ0 = true;
      for (i = 0; i < 9; i++) {
        if (rEQ0) {
          cth = T_R_G[i];
          if (std::isinf(cth) || std::isnan(cth)) {
            rEQ0 = false;
          }
        } else {
          rEQ0 = false;
        }
      }
      if (rEQ0) {
        double U[9];
        coder::internal::svd(T_R_G, U, vspecial_data, tempR);
      } else {
        for (i = 0; i < 9; i++) {
          tempR[i] = rtNaN;
        }
      }
      vspecial_data[0] = tempR[6];
      vspecial_data[1] = tempR[7];
      vspecial_data[2] = tempR[8];
    }
    v[0] = vspecial_data[0];
    v[1] = vspecial_data[1];
    v[2] = vspecial_data[2];
  }
  cth = v[0];
  sth = v[1];
  tempR_tmp = v[2];
  b_tempR_tmp = 1.0 / std::sqrt((v[0] * v[0] + v[1] * v[1]) + v[2] * v[2]);
  outputArg2[0] = cth * b_tempR_tmp * u.re;
  outputArg2[1] = sth * b_tempR_tmp * u.re;
  outputArg2[2] = tempR_tmp * b_tempR_tmp * u.re;
}

// End of code generation (fkfunc.cpp)
