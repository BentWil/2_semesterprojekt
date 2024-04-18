#ifndef TRANSFORMATION_H
#define TRANSFORMATION_H

// Include files
#include "rtwtypes.h"
#include <cstddef>
#include <cstdlib>

// Type Definitions
class transformation {
public:
    transformation();
    ~transformation();
    void FK_function(const double P[3], double output_data[], int output_size[1]);
};

#endif
