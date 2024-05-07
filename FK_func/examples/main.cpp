//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
//
// main.cpp
//
// Code generation for function 'main'
//

/*************************************************************************/
/* This automatically generated example C++ main file shows how to call  */
/* entry-point functions that MATLAB Coder generated. You must customize */
/* this file for your application. Do not modify this file directly.     */
/* Instead, make a copy of this file, modify it, and integrate it into   */
/* your development environment.                                         */
/*                                                                       */
/* This file initializes entry-point function arguments to a default     */
/* size and value before calling the entry-point functions. It does      */
/* not store or use any values returned from the entry-point functions.  */
/* If necessary, it does pre-allocate memory for returned values.        */
/* You can use this file as a starting point for a main function that    */
/* you can deploy in your application.                                   */
/*                                                                       */
/* After you copy the file, and before you deploy it, you must make the  */
/* following changes:                                                    */
/* * For variable-size function arguments, change the example sizes to   */
/* the sizes that your application requires.                             */
/* * Change the example values of function arguments to the values that  */
/* your application requires.                                            */
/* * If the entry-point functions return values, store these values or   */
/* otherwise use them as required by your application.                   */
/*                                                                       */
/*************************************************************************/

// Include files
#include "main.h"
#include "fkfunc.h"
#include "fkfunc_terminate.h"
#include "rt_nonfinite.h"

// Function Declarations
static void argInit_1x3_real_T(double result[3]);

static double argInit_real_T();

// Function Definitions
static void argInit_1x3_real_T(double result[3])
{
  // Loop over the array to initialize each element.
  for (int idx1{0}; idx1 < 3; idx1++) {
    // Set the value of the array element.
    // Change this value to the value that the application requires.
    result[idx1] = argInit_real_T();
  }
}

static double argInit_real_T()
{
  return 0.0;
}

int main(int, char **)
{
  // The initialize function is being called automatically from your entry-point
  // function. So, a call to initialize is not included here. Invoke the
  // entry-point functions.
  // You can call entry-point functions multiple times.
  main_fkfunc();
  // Terminate the application.
  // You do not need to do this more than one time.
  fkfunc_terminate();
  return 0;
}

void main_fkfunc()
{
  double P_tmp[3];
  double outputArg1[3];
  double outputArg2[3];
  // Initialize function 'fkfunc' input arguments.
  // Initialize function input argument 'P'.
  argInit_1x3_real_T(P_tmp);
  // Initialize function input argument 'Gorg'.
  // Call the entry-point 'fkfunc'.
  fkfunc(P_tmp, P_tmp, argInit_real_T(), outputArg1, outputArg2);
}

// End of code generation (main.cpp)
